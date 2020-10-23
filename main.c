#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <signal.h>
#include "loop.h"
#include "send.h"
#include "receive.h"
#include "list.h"
#include "getdate.h"
#include "interrupt.h"
#include"env.h"

int shell_cd(char **args);
int shell_date(char **args);
int shell_send(char **args);
int shell_receive(char **args);
int shell_interrupt(char **args);
int shell_env(char **args);
int shell_alarm(char **args);
int shell_list(char **args);
int shell_help(char **args);
int shell_exit(char **args);

char *build_str[] = {
  "cd",
  "date",
  "send",
  "receive",
  "interrupt",
  "environment",
  "list",
  "help",
  "exit"
};

int (*functions[]) (char **) = {
  &shell_cd,
  &shell_date,
  &shell_send,
  &shell_receive,
  &shell_interrupt,
  &shell_env,
  &shell_list,
  &shell_help,
  &shell_exit
};

int shell_num_builds() {
  return sizeof(build_str) / sizeof(char *);
}

int shell_cd(char **args)
{
  if (args[1] == NULL) {
    fprintf(stderr, "\aError: expected argument to \"cd\"\n");
  } else {
    if (chdir(args[1]) != 0) {
      perror("\aError");
    } 
  }
  return 1;
}

int shell_date(char **args){
  getdate();
  return 1;
}

int shell_send(char **args){
  send();
  return 1;
}

int shell_receive(char **args){
  receive();
  return 1;
}

int shell_interrupt(char **args){
  interrupt();
  return 1;
}

int shell_env(char **args){
  env();
  return 1;
}

int shell_list(char **args){
  list();
  return 1;
}

int shell_help(char **args){
  int i; 
  printf("There are all commands in my shell:\n");
  printf("cd: Change directory, you can type \"list\" to see all file\n");
  printf("date: See date and time\n");
  printf("send: Create a message queue to send message\n");
  printf("receive: Receive message from message queue, if not have any message queue then error\n");
  printf("interrupt: Simulate an interrupt signal\n");
  printf("environment: Get the environmel values and change it\n");
  printf("list: Show all files and folders in this directory\n");
  printf("help: Show all command in the shell\n");
  printf("exit: Finish shell\n");
  printf("Let's choose a command.\n");
  return 1;
}

int shell_exit(char **args)
{
  printf("Thank you for using my shell! See you later!!!\n");
  return 0;
}

int shell_execute(char **args)
{
  int i;

  if (args[0] == NULL) {
    // An empty command was entered.
    return 1;
  }

  for (i = 0; i < shell_num_builds(); i++) {
    if (strcmp(args[0], build_str[i]) == 0) {
      return (*functions[i])(args);
    }
  }

  return shell_launch(args);
}

void shell_loop(void)
{
  char *line;
  char **args;
  int status;

  do {
    printf(">");
    line = shell_read_line();
    args = shell_split_line(line);
    status = shell_execute(args);

    free(line);
    free(args);
  } while (status);
}

int main(int argc, char **argv)
{
 printf("Hello Teacher Pham Dang Hai! This is my Tiny Shell\n");
  printf("Type \"help\" and hit Enter to show all commands.\n");
  shell_loop();


  return EXIT_SUCCESS;
}
