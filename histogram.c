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

volatile sig_atomic_t signal_status = 0;

hist_int_t get_max_count(void){
    // finds the most occurrences of any byte

    hist_int_t max_count = 0;

    // checking every element in the histogram array
    for (int i = 0; i < (sizeof(histogram) / sizeof(histogram[0])); i++){
	    if (histogram[i] > max_count){
		    max_count = histogram[i];
	    }
    }

    return max_count;
}
void output_histogram(FILE* destination_stream){

	//getting the most occurrences of any byte in the histogram
	hist_int_t max_count = get_max_count();
    
	// writing a histogram of every byte value and their frequencies
	for (int i = 0; i < (sizeof(histogram) / sizeof(histogram[0])); i++) {
		
		// printing the information for the current byte, formatting: as specified

		fprintf(destination_stream, "%*d 0x%02x |", sizeof(long long int), histogram[i], i);


		// bar length, proportional to max count and max bar length
		int bar_length;
		if (max_count == 0) {
			bar_length = 0;
		} else {
			bar_length = (MAX_BAR_WIDTH * histogram[i]) / max_count;
		}
		
		if (bar_length > 0){ 
			for (int k = 0; k < bar_length; k++){
				fprintf(destination_stream,"#");
			}
			fprintf(destination_stream,"|");
		}

		fprintf(destination_stream, "\n");
		
	}
}

void usr1_handler(int signum){
    signal_status = 1;
}

void interrupt_handler(int signum){
    signal_status = 2;
}

void exit_handler(int signum){
    signal_status = 3;
}

int read_file(int fd){
    // reading the bytes in stdin

    ssize_t bytes_read;
    unsigned char buffer[256]; // buffer storing a chunk of bytes

    // reading 4KB from stdin
    while((bytes_read = read(fd, buffer, sizeof(buffer))) > 0){

	    // looping through each byte in the current chunk
	    for (ssize_t i = 0; i < bytes_read; i++) {
		    
		    // updating the count for each byte's value in the histogram array
		    histogram[buffer[i]]++;

	    }

    }

    // handling EOF
    if (bytes_read == 0){
	    output_histogram(stdout);
	    return 0;
    }

    return 0;

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
    new_act.sa_handler = usr1_handler;
    sigaction(SIGUSR1, &new_act, NULL);

    // Exit signal handling
    new_act.sa_handler = exit_handler;
    sigaction(SIGTERM, &new_act, NULL);

    // reading bytes from stdin and updating the histogram array
    read_file(STDIN_FILENO);
    
    FILE *output_file = fopen("histo.out", "w");

    if (output_file == NULL){
	    return -1;
    }

    // outputting the histogram to histo.out
    output_histogram(output_file);
    return 0;
}
