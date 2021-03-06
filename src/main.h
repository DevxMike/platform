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

#ifndef main_h_
#define main_h_

#include "time/timers.h"
#include "communication/uart.h"
#include "../config/macros.h"

typedef struct{
    uint16_t tim;
    uint8_t state;
}cmd;

typedef struct{
    char command[20];
    int16_t angle, current;
    cmd cmd_automata;
}main_vars_t;

typedef struct{
    uint16_t tim;
    uint8_t state;
}debug;

void init_main(main_vars_t* m, debug* d);

#endif