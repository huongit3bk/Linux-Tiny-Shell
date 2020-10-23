#include<time.h>
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>

void getdate(){
  struct tm *tm_ptr;
  time_t the_time;
  char name_of_weekDay[10];
  (void) time(&the_time);
  tm_ptr = gmtime(&the_time);
  switch(tm_ptr-> tm_wday){
    case 0: {strcpy(name_of_weekDay, "Sunday"); break;}
    case 1: {strcpy(name_of_weekDay, "Monday"); break;}
    case 2: {strcpy(name_of_weekDay, "Tuesday"); break;}
    case 3: {strcpy(name_of_weekDay, "Wednesday"); break;}
    case 4: {strcpy(name_of_weekDay, "Thursday"); break;}
    case 5: {strcpy(name_of_weekDay, "Friday"); break;}
    case 6: {strcpy(name_of_weekDay, "Saturday"); break;}
  }
  printf("Date: %s %02d/%02d/%d\n", name_of_weekDay, tm_ptr->tm_mday, tm_ptr->tm_mon+1, tm_ptr -> tm_year +1900);
  printf("Time: %02d:%02d:%02d\n",tm_ptr->tm_hour, tm_ptr->tm_min, tm_ptr->tm_sec);
}
