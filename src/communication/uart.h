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

#ifndef uart_h_
#define uart_h_

#include <avr/io.h>
#include "../../config/macros.h"

void init_UART(uint8_t ubrr);
void UART_putc(char c);
void UART_puts(const char* string);
void UART_pushc(char c);
const char* UART_gets(void);
void UART_flush(void);
const char* int_to_str(int16_t value);
int16_t str_to_int(const char* string);
#endif