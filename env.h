#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

extern char **environ;

void env()
{
  int count = 0;


  printf("\n");
  while(environ[count] != NULL)
  {
    printf("[%s] :: ", environ[count]);
    count++;
  }

  char *val = getenv("USER");
  printf("\n\nCurrent value of environment variable USER is [%s]\n",val);
  if(setenv("USER","Pham Dang Hai",1)){
    printf("\n setenv() failed\n");
  }
  printf("\n Successfully Added a new value to existing environment variable USER\n");
  val = getenv("USER");
  printf("\nNew value of environment variable USER is [%s]\n",val);
}
