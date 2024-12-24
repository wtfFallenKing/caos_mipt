#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

void printError(const char* message, size_t message_size) {
  write(STDERR_FILENO, message, message_size);
  exit(EXIT_FAILURE);
}

#define error(m) printError(m, sizeof(m) - 1);

size_t trim(char* string) {
  size_t length = strlen(string);
  char* new_string = string;
  while (isspace(new_string[length - 1])) {
    new_string[--length] = '\0';
  }
  while(*new_string != '\0' && isspace(*new_string)) {
    ++new_string;
    --length;
  }
  memmove(string, new_string, length + 1);
  return length;
}

int main(int argc, char const* argv[]) {
  char buffer[1024];
  int read_size = read(STDIN_FILENO, buffer, sizeof(buffer) / sizeof(buffer[0]));
  if (read_size == -1) {
    error("STDIN READ FAIL");
  }
  if (trim(buffer) == 0) {
    return 0;
  }
  const char* template = "gcc -o a.out -x c - <<eof\n#include <stdio.h>\nvoid main()"
                         "{ printf(\"%%d\\n\", (%s)); }\neof";
  char buffer_template[4096];
  snprintf(buffer_template, sizeof(buffer_template) / sizeof(buffer_template[0]), template, buffer);
  printf("%s\n", buffer_template);
  system(buffer_template);
  execl("./a.out", (char*) NULL);
  return 0;
}