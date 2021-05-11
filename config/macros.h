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

#ifndef macros_h_
#define macros_h_

/*--------------------------------timers-----------------------------------*/
#define TIMER2_COMPARE_VAL 0x7C //1kHz cycle duration
#define TCCR2_CONFIG 0x0D //CTC mode, 128 prescaler
#define TIMER2_TIMSK_CONFIG 0x80 //CTC interrupt
/*--------------------------------timers-----------------------------------*/

/*---------------------------------UART------------------------------------*/
#define UBRR_VALUE 103 //baud 9600bps
/*---------------------------------UART------------------------------------*/

#define DEBUG_DIODE 0x04

#endif