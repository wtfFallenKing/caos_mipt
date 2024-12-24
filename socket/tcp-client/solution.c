#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>

void printError(const char* message, size_t message_size) {
  write(STDERR_FILENO, message, message_size);
  exit(EXIT_FAILURE);
}

#define error(m) printError(m, sizeof(m) - 1);

int main(int argc, char const* argv[]) {
  if (argc < 3) {
    error("Arguments count error");
  }
  __uint16_t port = 0;
  if (sscanf(argv[2], "%hd", &port) == EOF) {
    error("Reading port error");
  }
  struct sockaddr_in addr = {
    .sin_family = AF_INET,
    .sin_port = htons(port)
  };
  if (inet_pton(AF_INET, argv[1], &addr.sin_addr) == 0) {
    error("Parsing the address error");
  }
  int sock = socket(AF_INET, SOCK_STREAM, 0);
  if (sock == -1) {
    error("Socket connection opening error");
  }
  if (connect(sock, (struct sockaddr*)& addr, sizeof(addr)) == -1) {
    close(sock);
    error("Connection to provided peer error");
  }
  int value;
  int status = 0;
  while (scanf("%d", &value) != EOF) {
    status = send(sock, &value, sizeof(value), 0);
    if (status == -1 && errno == ECONNRESET || status == 0) {
      shutdown(sock, SHUT_RDWR);
      close(sock);
      return 0;
    } else if (status == 0) {
      shutdown(sock, SHUT_RDWR);
      close(sock);
      error("Data sending error");
    }
    status = recv(sock, &value, sizeof(value), 0);
    if (status == -1 && errno == ECONNRESET || status == 0) {
      shutdown(sock, SHUT_RDWR);
      close(sock);
      return 0;
    } else if (status == -1) {
      shutdown(sock, SHUT_RDWR);
      close(sock);
      error("Data sending error");
    }
    printf("%d ", value);
  }
  shutdown(sock, SHUT_RDWR);
  close(sock);
  return 0;
}