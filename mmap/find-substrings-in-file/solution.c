#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <string.h>

void printError(const char* message, size_t message_size) {
  write(STDERR_FILENO, message, message_size);
  exit(EXIT_FAILURE);
}

#define error(msg) printError((msg), sizeof(msg) - 1);

int main(int argc, char const* argv[]) {
  if (argc < 3) {
    error("Too few arguments error");
  }
  int fd = open(argv[1], O_RDONLY);
  if (fd == -1) {
    error("Opening file error");
  }
  struct stat sb;
  if (fstat(fd, &sb) == -1) {
    close(fd);
    error("Stats getting error");
  }
  char* data = (char*) mmap(NULL, sb.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
  if (data == NULL) {
    close(fd);
    error("Mapping file memory error");
  }
  const char* needle = argv[2];
  size_t needle_len = strlen(needle);
  if (needle_len <= sb.st_size) {
    char* haystack = data;
    for (size_t i = 0; i <= sb.st_size - needle_len; ++i) {
      if (memcmp(haystack, needle, needle_len) == 0) {
        printf("%ld ", i);
      }
      ++haystack;
    }
  }
  if (munmap(data, sb.st_size) == -1) {
    close(fd);
    error("Failed to unmap file");
  }
  if (close(fd) == -1) {
    error("Failed to close file");
  }
  return 0;
}