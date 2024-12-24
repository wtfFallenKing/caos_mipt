#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

void printError(const char* message, size_t message_size) {
  write(STDERR_FILENO, message, message_size);
  exit(EXIT_FAILURE);
}

#define error(msg) printError(msg, sizeof(msg) - 1);

void fork_print(int current, int N) {
  __pid_t pid = fork();
  if (-1 == pid) {
    error("Failed to fork process");
  }
  if (0 == pid) {
    if (current > 1) {
      fork_print(current - 1, N);
      exit(0);
    }
  } else {
    wait(NULL);
    printf("%d", current);
    if (current == N) {
      printf("\n");
    } else {
      printf(" ");
    }
  }
}

int main(int argc, char const* argv[]) {
  if (argc < 2) {
    error("Too few arguments passed");
  }
  int N;
  sscanf(argv[1], "%d", &N);
  fork_print(N, N);
  return 0;
}