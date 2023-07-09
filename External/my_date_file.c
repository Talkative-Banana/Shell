#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

int main(int argc, char* argv[]){
	time_t Time;
	if(!strcmp(argv[1],"-u")){
		printf("GMT DATE-TIME\n");
		time(&Time);
		printf("%s",ctime(&Time));
	} else if(!strcmp(argv[1],"NULL")){
		printf("PDT DATE_TIME\n");
		time(&Time);
		printf("%s",asctime(gmtime(&Time)));
	}
	return 0;
}
