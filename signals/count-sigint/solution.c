#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

volatile sig_atomic_t counter = 0;
volatile sig_atomic_t running = 1;

void sig_handler(int signo) {
  if (signo == SIGINT) {
    ++counter;
  } else if (signo == SIGTERM) {
    running = 0;
  }
}

int main(int argc, char const* argv[]) {
  __pid_t pid = getpid();
  printf("%d\n", pid);
  fflush(NULL);
  struct sigaction sa_int = { 0 };
  sa_int.sa_flags = SA_RESTART;
  sa_int.sa_handler = sig_handler;
  if (sigaction(SIGINT, &sa_int, NULL) == -1) {
    perror("Signal handler setting error");
    exit(EXIT_FAILURE);
  }
  struct sigaction sa_term = { 0 };
  sa_term.sa_handler = sig_handler;
  if (sigaction(SIGTERM, &sa_term, NULL) == -1) {
    perror("Signal handler setting error");
    exit(EXIT_FAILURE);
  }
  while (running) {
    pause();
  }
  printf("%d\n", counter);
  return 0;
}