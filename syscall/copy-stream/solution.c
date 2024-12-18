#define STDIN  0
#define STDOUT 1
#define EXIT_OK 0
#define EXIT_FAIL 1
#define SYS_READ 0
#define SYS_WRITE 1
#define SYS_EXIT 60


long syscall(long number, ...);

long read(int fd, char* buffer, unsigned int buffer_size) {
  return syscall(SYS_READ, fd, buffer, buffer_size);
}

long write(int fd, char* buffer, unsigned int buffer_size) {
  return syscall(SYS_WRITE, fd, buffer, buffer_size);
}

void _exit(int status) {
  syscall(SYS_EXIT, status);
}

void _start() {
  int read_amount_bytes = 0;
  const unsigned int buffer_size = 4096;
  char buffer[buffer_size];
  
  while ((read_amount_bytes = read(STDIN, buffer, buffer_size)) > 0) {
    if (write(STDOUT, buffer, read_amount_bytes) < 0) {
      _exit(EXIT_FAIL);
    }
  }

  if (read_amount_bytes == -1) {
    _exit(EXIT_FAIL);
  }

  _exit(EXIT_OK);
}
