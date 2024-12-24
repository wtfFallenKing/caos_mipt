#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

void printError(const char* message, size_t message_size) {
  write(STDERR_FILENO, message, message_size);
  exit(EXIT_FAILURE);
}

#define error(msg) printError(msg, sizeof(msg) - 1);

int main(int argc, char const* argv[]) {
  if (argc < 3) {
    error("Arguments amount fail");
  }
  int pipefd[2];
  if (pipe(pipefd) == -1) {
    error("Input pipe opening fail");
  }
  pid_t pid = fork();
  if (pid == -1) {
    error("Fork process erorr");
  }
  if (pid == 0) {
    close(pipefd[0]);
    dup2(pipefd[1], STDOUT_FILENO);
    close(pipefd[1]);
    execlp(argv[1], argv[1], (char*) NULL);
    error("First command execution error");
  } else {
    close(pipefd[1]);
    dup2(pipefd[0], STDIN_FILENO);
    close(pipefd[0]);
    execlp(argv[2], argv[2], (char*) NULL);
    error("Second command execution error");
  }
  return 0;
}