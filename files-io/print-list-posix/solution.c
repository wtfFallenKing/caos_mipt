#define _XOPEN_SOURCE 500
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdbool.h>

struct Item {
  int value;
  uint32_t next_pointer;
};

int main(int argc, char const* argv[]) {
  if (argc < 2) {
    perror("Invalid number of arguments\n");
    return 1;
  }
  int fd = open(argv[1], O_RDONLY);
  struct Item buffer;
  uint32_t offset = 0;
  while (true) {
    int read_size = pread(fd, &buffer, sizeof(struct Item), offset);
    if (read_size == -1) {
      perror("Read fail\n");
      close(fd);
      exit(1);
    } else if (read_size == 0) {
      break;
    }
    printf("%d ", buffer.value);
    if (buffer.next_pointer == 0) {
      break;
    } else {
      offset = buffer.next_pointer;
    }
  }
  close(fd);
  return 0;
}