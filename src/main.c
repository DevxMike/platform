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

#include "main.h"

volatile uint8_t cycle = 0;
volatile uint8_t main_flags = 0;

int main(void){
    debug diode;

    init_main(&diode);
    sei();

    while(1){
        if(main_flags & CMD_READY){
            UART_puts(UART_gets());
            UART_puts("\n\r");
            main_flags &= ~CMD_READY;
            UART_flush();
        }
        
        switch(diode.state){
            case 0: if(!diode.tim) { diode.state = 1; diode.tim = 1000; PORTD &= ~(1 << DEBUG_DIODE); } break;
            case 1: if(!diode.tim) { diode.state = 0; diode.tim = 1000; PORTD |= (1 << DEBUG_DIODE); } break;
        }

        if(diode.tim) --diode.tim;

        while(!cycle){
            continue;
        }
        cycle ^= 0xFF;
    }
}

void init_main(debug* d){
    init_UART(UBRR_VALUE);
    init_cycle_timer();
    //just a debug case
    DDRD |= (1 << DEBUG_DIODE);
    PORTD |= (1 << DEBUG_DIODE);
    //just a debug case
    d->state = d->tim = 0;
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