#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define SHELL_RL_BUFSIZE 1024
#define SHELL_TOK_BUFSIZE 64
#define SHELL_TOK_DELIM " \t\r\n\a"

char *shell_read_line(void)
{
  int bufsize = SHELL_RL_BUFSIZE;
  int position = 0;
  char *buffer = malloc(sizeof(char) * bufsize);
  int c;

  if (!buffer) {
    fprintf(stderr, "\aError: allocation error\n");
    exit(EXIT_FAILURE);
  }

  while (1) {
    // Doc ki tu
    c = getchar();

    // Neu enter thi la xong
    if (c == '\n') {
      printf("\a");
      buffer[position] = '\0';
      return buffer;
    } else {
      buffer[position] = c;
    }
    position++;

    // Neu vuot qua bo dem thi phan bo lai va bao loi
    if (position >= bufsize) {
      bufsize += SHELL_RL_BUFSIZE;
      buffer = realloc(buffer, bufsize);
      if (!buffer) {
        fprintf(stderr, "\aError: allocation error\n");
        exit(EXIT_FAILURE);
      }
    }
  }
}

char **shell_split_line(char *line)
{
  int bufsize = SHELL_TOK_BUFSIZE, position = 0;
  char **tokens = malloc(bufsize * sizeof(char*));
  char *token;

  if (!tokens) {
    fprintf(stderr, "\aError: allocation error\n");
    exit(EXIT_FAILURE);
  }

  token = strtok(line, SHELL_TOK_DELIM);
  while (token != NULL) {
    tokens[position] = token;
    position++;

    if (position >= bufsize) {
      bufsize += SHELL_TOK_BUFSIZE;
      tokens = realloc(tokens, bufsize * sizeof(char*));
      if (!tokens) {
        fprintf(stderr, "\aError: allocation error\n");
        exit(EXIT_FAILURE);
      }
    }

    token = strtok(NULL, SHELL_TOK_DELIM);
  }
  tokens[position] = NULL;
  return tokens;
}

int shell_launch(char **args){
  pid_t pid, wpid;
  int status;

  pid = fork();
  if (pid == 0) {
    // Tien trinh con
    if (execvp(args[0], args) == -1) {
      perror("\aError");
    }
    exit(EXIT_FAILURE);
  } else if (pid < 0) {
    // Khong tao duoc tien trinh con
    perror("\aError");
  } else {
    // Tien trinh cha
    do {
      wpid = waitpid(pid, &status, WUNTRACED);
    } while (!WIFEXITED(status) && !WIFSIGNALED(status));
  }

  return 1;
}



