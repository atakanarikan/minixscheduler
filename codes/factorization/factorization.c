#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <sys/time.h>
#include <stdlib.h>
#include <signal.h>

FILE *ofp;
struct timeval start, end, tv;
static int keepRunning = 1; // decide whether to run the process or not. only the SIGINT signal can change it's value.
void intHandler(int dummy) {
	keepRunning = 0; // make the program terminate after the current iteration.
	fclose(ofp); // close the file before exiting the program.
}
int main(){
		signal(SIGINT, intHandler); // handle the kill signal SIGINT (ctrl + c)
		ofp = fopen("factorizationLog5", "w"); // open the log file.
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
		fprintf(ofp, "Starting time of the program: [%s.%03ld]\n", time_string, milliseconds);
		fprintf(ofp, "/*=================================================*/\n");
		while(keepRunning == 1){
			int i;
			srand(time(NULL));
			int r = rand() % 500000;
			r += 500000;		
			int n=349852; // very large number
			int div=2;
			while(n!=1){
				if(n % div == 0) n = n / div;
				else div += 1;
			}
			/* put the process to sleep */
			gettimeofday(&start, NULL);
			usleep(r);
			gettimeofday(&end, NULL);
			if (ofp != NULL) {
				ptm = localtime (&start.tv_sec);
				strftime (time_string, sizeof (time_string), "%Y-%m-%d %H:%M:%S", ptm);
				milliseconds = start.tv_usec / 1000;
				fprintf(ofp, "Went to sleep at: [%s.%03ld]\n", time_string, milliseconds);
				ptm = localtime (&end.tv_sec);
				strftime (time_string, sizeof (time_string), "%Y-%m-%d %H:%M:%S", ptm);
				milliseconds = end.tv_usec / 1000;
				fprintf(ofp, "Woke up at: [%s.%03ld]\n", time_string, milliseconds);
				fprintf(ofp, "/*=================================================*/\n");
			}
		}
	return 0;
}
