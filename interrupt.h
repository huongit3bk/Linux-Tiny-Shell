#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

void interrupt(){
  int sig =0;

  void sighandler(int signum)
  {
    printf("\nCatch signal %d, break!\n", signum);
    sig =1;   
  }
  signal(SIGINT, sighandler);
  while(1) {
    printf("Type \"Ctrl+C\" to end task\n");
    sleep(1); 
    if(sig==1) break;
  }
}
