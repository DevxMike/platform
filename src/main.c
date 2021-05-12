/*MIT License

Copyright (c) 2021 Michał Bazan

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <string.h>

#include "main.h"

volatile uint8_t cycle = 0;
volatile uint8_t main_flags = 0;

int main(void){
    debug diode;
    main_vars_t vars;

    init_main(&vars, &diode);
    sei();

    while(1){
        if(main_flags & CMD_READY){
            strcpy(vars.command, UART_gets());
            switch(vars.command[0]){
                case SET_ANGLE_CMD_START: 
                
                
                break;
                
                case TRANSMIT_INFO_CMD_START: 
                switch(vars.command[1]){
                    case 'A': 
                        UART_puts("Angle set: "); UART_puts(int_to_str(vars.angle)); 
                        UART_puts(", Current angle: "); UART_puts(int_to_str(vars.current)); UART_puts("\n\r"); 
                    break; 
                    case 'E': main_flags &= ~TRANSMISSION_ENABLE; UART_puts("Transmission disabled.\n\r"); break;
                    case 'V':    
                        if(main_flags & TRANSMISSION_ENABLE){
                            UART_puts("Transmission has been enabled before.\n\r");
                        }
                        else{
                            main_flags |= TRANSMISSION_ENABLE;
                            UART_puts("Transmission enabled.\n\r");
                        }
                    break;
                }
                
                break;
                default: UART_puts("No such command as \""); UART_puts(vars.command) ; UART_puts("\", try again.\n\r"); break;
            }
            main_flags &= ~CMD_READY;
        }

        switch(vars.cmd_automata.state){
            case 0: if(!vars.cmd_automata.tim && (TRANSMISSION_ENABLE & main_flags)) vars.cmd_automata.state = 1; break;
            case 1: 
                UART_puts("Angle set: "); UART_puts(int_to_str(vars.angle)); 
                UART_puts(", Current angle: "); UART_puts(int_to_str(vars.current)); UART_puts("\n\r"); 
                vars.cmd_automata.state = 0; vars.cmd_automata.tim = 1000;
            break;
        }
        
        switch(diode.state){
            case 0: if(!diode.tim) { diode.state = 1; diode.tim = 1000; PORTD &= ~(1 << DEBUG_DIODE); } break;
            case 1: if(!diode.tim) { diode.state = 0; diode.tim = 1000; PORTD |= (1 << DEBUG_DIODE); } break;
        }

        if(diode.tim) --diode.tim;
        if(vars.cmd_automata.tim) --vars.cmd_automata.tim;
        
        while(!cycle){
            continue;
        }
        cycle ^= 0xFF;
    }
}

void init_main(main_vars_t* m, debug* d){
    init_UART(UBRR_VALUE);
    init_cycle_timer();
    //just a debug case
    DDRD |= (1 << DEBUG_DIODE);
    PORTD |= (1 << DEBUG_DIODE);
    //just a debug case
    d->state = d->tim = 0;
    memset(m->command, 0, 19);
    m->current = m->angle = 0;
    m->cmd_automata.state = 0;
    m->cmd_automata.tim = 0;
}

ISR(TIMER2_COMP_vect){
    cycle ^= 0xFF;
}
ISR(USART_RXC_vect){
    static char c;
    c = UDR;
    if(c == TERMINATING_CHAR){
        c = '\0';
        main_flags |= CMD_READY;
    }
    UART_pushc(c);
}