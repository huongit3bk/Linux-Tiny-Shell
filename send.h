#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>
#include<unistd.h>
#include<sys/msg.h>
#define MAX_TEXT 512

void send(){
  struct my_msg_st{
    long int my_msg_type;
    char some_text[MAX_TEXT];
  };
  int running =1;
  struct my_msg_st some_data;
  int msgid;
  char buffer[BUFSIZ];
  msgid = msgget ((key_t) 1234, 0666 | IPC_CREAT);
  if (msgid == -1) {
    fprintf(stderr, "message get failed with error: %d\n", errno);
    exit(EXIT_FAILURE);
  }
  printf("Type some text. Enter \"end\" to finish\n");
  while(running){
    printf("Enter text here: ");
    fgets(buffer, BUFSIZ,stdin);
    some_data.my_msg_type =1;
    strcpy(some_data.some_text, buffer);
    if (msgsnd(msgid, (void *)&some_data, MAX_TEXT, 0) ==-1) {
      fprintf(stderr, "message send failed\n");
      exit(EXIT_FAILURE);
    }
    if (strncmp(buffer, "end", 3) ==0) running =0;
  }
}
