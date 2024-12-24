#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <ctype.h>

#define MAX_BUFFER_SIZE 4096

int main(int argc, char *argv[]) {
  if (argc < 4) {
    perror("Too few arguments error");
    return 1;
  }
  int input_fd = open(argv[1], O_RDONLY);
  if (input_fd < 0) {
    perror("Error opening input file");
    return 1;
  }
  char digits_buffer[MAX_BUFFER_SIZE];
  char other_buffer[MAX_BUFFER_SIZE];
  size_t digits_index = 0;
  size_t other_index = 0;
  char buffer;
  size_t bytes_read;
  while ((bytes_read = read(input_fd, &buffer, 1)) > 0) {
    if (isdigit(buffer)) {
      digits_buffer[digits_index++] = buffer;
    } else {
      other_buffer[other_index++] = buffer;
    }
  }
  if (bytes_read < 0) {
    perror("Error reading input file");
    close(input_fd);
    return 3;
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
  if (write(output_fd_digits, digits_buffer, digits_index) < 0) {
    perror("Error writing to digits file");
    close(input_fd);
    close(output_fd_digits);
    close(output_fd_other);
    return 3;
  }
  if (write(output_fd_other, other_buffer, other_index) < 0) {
    perror("Error writing to other characters file");
    close(input_fd);
    close(output_fd_digits);
    close(output_fd_other);
    return 3;
  }
  close(input_fd);
  close(output_fd_digits);
  close(output_fd_other);
  return 0;
}