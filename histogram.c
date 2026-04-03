#include "histogram.h"

// These function prototypes / definitions are suggestions but not required to implement.
// hist_int_t get_max_count(void)
// void output_histogram(FILE* destination_stream)
// void usr1_handler/exit_handler/signal_handler(int signum)

// Note: It is bad practice to use STDIO in signal handlers. 
// For this assignment however, I am guaranteeing that multiple signals will **not** be sent at or near the same time, thus it is __okay__ to use STDIO in your signal handlers.
// That is to say, feel free to use printf, fprintf, etc. in your signal handlers.
// Challenge: For the astute, try to implement the histogram program where your signal handlers have only 1 line of code (setting a global variable/flag). Even better if you use sigaction instead of signal.

int main(void) {
    // TODO: implement the histogram program
    return 0;
}
