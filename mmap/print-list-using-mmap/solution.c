#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/mman.h>

void printError(const char* message, size_t message_size) {
  write(STDERR_FILENO, message, message_size);
  exit(EXIT_FAILURE);
}

#define error(msg) printError((msg), sizeof(msg) - 1);

struct Item {
  int value;
  __uint32_t next_pointer;
};

int main(int argc, char const* argv[]) {
  if (argc < 2) {
    error("Too few arguments error");
  }
  int fd = open(argv[1], O_RDONLY);
  if (fd == -1) {
    error("Opening file error");
  }
  struct stat sb;
  if (fstat(fd, &sb) == -1) {
    error("Getting stats error");
  }
  if (sb.st_size == 0) {
    close(fd);
    return 0;
  }
  void* base = mmap(NULL, sb.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
  if (base == NULL) {
    close(fd);
    error("Mapping file memory error");
  }
  struct Item* item = (struct Item*) base;
  while (item != NULL) {
    printf("%d ", item->value);
    if (item->next_pointer == 0) {
      item = NULL;
    } else {
      item = (struct Item*) (base + item->next_pointer);
    }
  }
  munmap(base, sb.st_size);
  close(fd);
  return 0;
}