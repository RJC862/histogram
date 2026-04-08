#include "histogram.h"
#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
// These function prototypes / definitions are suggestions but not required to implement.
// hist_int_t get_max_count(void)
// void output_histogram(FILE* destination_stream)
// void usr1_handler/exit_handler/signal_handler(int signum)

// Note: It is bad practice to use STDIO in signal handlers. 
// For this assignment however, I am guaranteeing that multiple signals will **not** be sent at or near the same time, thus it is __okay__ to use STDIO in your signal handlers.
// That is to say, feel free to use printf, fprintf, etc. in your signal handlers.
// Challenge: For the astute, try to implement the histogram program where your signal handlers have only 1 line of code (setting a global variable/flag). Even better if you use sigaction instead of signal.

hist_int_t get_max_count(void){
    // finds the most occurrences of any byte

    hist_int_t max_count = 0;

    // checking every element in the histogram array
    for (int i = 0; i < sizeof(histogram); i++){
	    if (histogram[i] > max){
		    max_count = histogram[i];
	    }
    }

    return max_count;
}
void output_histogram(FILE* destination_stream){

	hist_int_t max_count = get_max_count();
    
	for (int i = 0; i < sizeof(histogram); i++) {
		if (histogram[i] == 0) {
		    fprintf(stdout, "%d %x |", histogram[i], i);
		} else {
			// create the string of #
			fprintf(stdout, "%d %x |%s|", histogram[i], i, 
		}
	}
}

void usr1_handler(int signum){
    //code
}

void interrupt_handler(int signum){
    //code
}

void exit_handler(int signum){
    //code
}

void read_file(FILE* fs){
    // reading the bytes in stdin

    ssize_t bytes_read;
    unsigned char buffer[4096]; // buffer storing a chunk of bytes

    // reading 4KB from stdin
    while((bytes_read = read(fs, buffer, sizeof(buffer))) > 0){

	    // looping through each byte in the current chunk
	    for (ssize_t i = 0; i < bytes_read; i++) {
		    
		    // updating the count for each byte's value in the histogram array
		    histogram[buffer[i]]++;

	    }

    }

    // handling EOF
    if (bytes_read == 0){
	    output_histogram(stdout);
    }

}











int main(void) {
    // TODO: implement the histogram program
    
    // initializing a sigaction struct
    struct sigaction new_act;

    // clearing necessary struct fields so that signals are not masked and have no flags
    sigemptyset(&new_act.sa_mask);
    new_act.sa_flags = 0;

    // assigning handlers to their appropriate signals

    // Interrupt signal handling
    new_act.sa_handler = interrupt_handler;
    sigaction(SIGINT, &new_act, NULL);

    // USR1 signal handling
    new_act.sa_handler = user1_handler;
    sigaction(SIGUSR1, &new_act, NULL);

    // Exit signal handling
    new_act.sa_handler = exit_handler;
    sigaction(SIGTERM, &new_act, NULL);

    // reading bytes from stdin and updating the histogram array
    read_file(stdin);
    return 0;
}
