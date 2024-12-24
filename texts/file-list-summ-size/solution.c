#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/stat.h>

int main(int argc, char const* argv[]) {
  char buffer[4096];
  size_t size = 0;
  while (scanf("%s", buffer) != EOF) {
    int fd = open(buffer, O_RDONLY);
    if (fd == -1) {
      fprintf(stderr, "Opening file %s error: %d", buffer, errno);
      continue;
    }
    struct stat sb;
    if (fstat(fd, &sb) == -1) {
      fprintf(stderr, "Getting file %s error: %d", buffer, errno);
      close(fd);
    }
    if (S_ISREG(sb.st_mode)) {
      size += sb.st_size;
    }
    if (close(fd) == -1) {
      fprintf(stderr, "Closing file %s error: %d", buffer, errno);
    }
  }
  printf("%ld\n", size);
  return 0;
}