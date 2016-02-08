#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <sys/time.h>
#include <stdlib.h>
#include <signal.h>

FILE *ofp2;
struct timeval start, end, tv;
static int keepRunning = 1; // decide whether to run the process or not. only the SIGINT signal can change it's value.
void intHandler(int dummy) {
	fclose(ofp2); // close the file before exiting the program.
	keepRunning = 0; // make the program terminate after the current iteration.
}
int main(){
		signal(SIGINT, intHandler); // handle the kill signal SIGINT (ctrl + c)
		ofp2 = fopen("fibonacciLog", "w"); // open the log file.
		struct tm* ptm;
		char time_string[40];
		long milliseconds;
		gettimeofday (&tv, NULL);
		ptm = localtime (&tv.tv_sec);
		/* Format the date and time, down to a single second. */
		strftime (time_string, sizeof (time_string), "%Y-%m-%d %H:%M:%S", ptm);
		/* Compute milliseconds from microseconds. */
		milliseconds = tv.tv_usec / 1000;
		/* Print the formatted time, in seconds, followed by a decimal point
		and the milliseconds. */
		fprintf(ofp2, "Starting time of the program: [%s.%03ld]\n", time_string, milliseconds);
		fprintf(ofp2, "/*=================================================*/\n");
	while(keepRunning == 1){
		int n, first = 0, second = 1, next, i;
		srand(time(NULL));
		int r = rand() % 500000;
		r += 500000;		
		n=10000;
		next=0;
		for (i = 0 ; i < n ; i++ ){
			if ( i <= 1 ) next = i;
			else{
				next = first + second;
				first = second;
				second = next;
			}
		}
		FILE *ofp;
		ofp = fopen("fiboResult", "w");
		if (ofp != NULL) {
			fprintf(ofp, "%d\n", next);
		}
		fclose(ofp);
		/* put the process to sleep */
		gettimeofday(&start, NULL);
		usleep(r);
		gettimeofday(&end, NULL);
		if (ofp2 != NULL) {
			ptm = localtime (&start.tv_sec);
			strftime (time_string, sizeof (time_string), "%Y-%m-%d %H:%M:%S", ptm);
			milliseconds = start.tv_usec / 1000;
			fprintf(ofp2, "Went to sleep at: [%s.%03ld]\n", time_string, milliseconds);
			ptm = localtime (&end.tv_sec);
			strftime (time_string, sizeof (time_string), "%Y-%m-%d %H:%M:%S", ptm);
			milliseconds = end.tv_usec / 1000;
			fprintf(ofp2, "Woke up at: [%s.%03ld]\n", time_string, milliseconds);
			fprintf(ofp2, "/*=================================================*/\n");
		}
	}
	return 0;
}
