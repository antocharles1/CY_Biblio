

#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#include <time.h>
 
void return_time(int *heure,int *minute,int *sec){
    time_t crt = time(NULL);
    char buf[20];
    strftime(buf, sizeof(buf), "%H\n", localtime(&crt));
    *heure = atoi(buf);
    strftime(buf, sizeof(buf), "%M \n", localtime(&crt));
    *minute = atoi(buf);
     strftime(buf, sizeof(buf), "%S \n", localtime(&crt));
    *sec = atoi(buf);
  

    
}

void gap_time(int* h,int* min,int* sec,int h2,int min2,int sec2){  // procedure that gives the exact time when the book is borrowed
	int a,b,c;
	a=*h;
	b=*min;
	c=*sec;
	*sec=*sec+(a*3600)+(b*60);                                // when transform the times into seconds and then compare them
	sec2=sec2+(h2*3600)+(min2*60);
	*sec=*sec-sec2; 
}





