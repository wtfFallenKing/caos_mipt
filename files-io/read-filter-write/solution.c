#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <ctype.h>
#include <errno.h>

#define MAX_BUFFER_SIZE 4096

int main(int argc, char *argv[]) {
  if (argc != 4) {
    perror("Arguments count error");
    return 1;
  }
  int input_fd = open(argv[1], O_RDONLY);
  if (input_fd < 0) {
    perror("Error opening input file");
    return 1;
  }
  int output_fd_digits = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0644);
  if (output_fd_digits < 0) {
    perror("Error opening output file for digits");
    close(input_fd);
    return 2;
  }
  int output_fd_other = open(argv[3], O_WRONLY | O_CREAT | O_TRUNC, 0644);
  if (output_fd_other < 0) {
    perror("Error opening output file for other characters");
    close(input_fd);
    close(output_fd_digits);
    return 2;
  }
  char buffer[MAX_BUFFER_SIZE];
  ssize_t bytes_read;
  while ((bytes_read = read(input_fd, buffer, MAX_BUFFER_SIZE)) > 0) {
    char digits_buffer[MAX_BUFFER_SIZE];
    char other_buffer[MAX_BUFFER_SIZE];
    ssize_t digits_index = 0;
    ssize_t other_index = 0;
    for (ssize_t i = 0; i < bytes_read; i++) {
      if (isdigit(buffer[i])) {
        digits_buffer[digits_index++] = buffer[i];
      } else {
        other_buffer[other_index++] = buffer[i];
      }
    }
    if (write(output_fd_digits, digits_buffer, digits_index) < 0) {
      perror("Error writing to digits file");
      return 3;
    }
    if (write(output_fd_other, other_buffer, other_index) < 0) {
      perror("Error writing to other characters file");
      return 3;
      }
  }
  if (bytes_read < 0) {
    perror("Error reading input file");
    return 3;
  }
  close(input_fd);
  close(output_fd_digits);
  close(output_fd_other);
  return 0;
}