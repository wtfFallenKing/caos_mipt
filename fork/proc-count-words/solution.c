#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

void printError(const char* message, size_t message_size) {
  write(STDERR_FILENO, message, message_size);
  exit(EXIT_FAILURE);
}

#define error(msg) printError(msg, sizeof(msg) - 1);

int main(int argc, char const* argv[]) {
  char buffer[4096];
  int count = 0;
  int res = 0;
  while (1) {
    pid_t pid = fork();
    if (pid == -1) {
      error("Creating fork error");
    }
    if (pid == 0) {
      if (scanf("%s", buffer) == 1) {
        return 0;
      } else {
        return 1;
      }
    } else {
      wait(&res);
      if (res == 0) {
        ++count;
      } else {
        break;
      }
    }
  }
  printf("%d\n", count);
  return 0;
}