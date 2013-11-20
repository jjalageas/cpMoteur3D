#include "debug.h"

#include <cstdlib>
#include <string.h>


// http://www.gnu.org/software/libc/manual/html_node/Backtraces.html
void displayStackTrace(int sig) {
    (void) sig;
    // ugly display...

    /*int stackSize = 300;
    void *array[stackSize];
    size_t size = backtrace(array, stackSize); // get the stack

    if (sig != -1)
        std::cerr << strsignal(sig) << " :" << std::endl;
    backtrace_symbols_fd(array, size, 2); // print the stack, 2 <=> stderr
    exit(1);*/
}
