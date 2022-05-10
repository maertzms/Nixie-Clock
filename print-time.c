#include <time.h>
#include <stdio.h>
#include <unistd.h>

int main(){
int i = 0;
	do{
		i = i;
		time_t t = time(NULL);
		struct tm time = *localtime(&t);
		sleep(1);
		printf("time-%d:%d:%d\n", time.tm_hour, time.tm_min, time.tm_sec);
	}while(i < 5);
	return 0;
}
