#include <fcntl.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

int main(int argc, char **argv) {

  if (argc < 2) {
    fprintf(stderr, "usage: %s file", argv[1]);
    return EXIT_FAILURE;
  }

  int open_flags = O_CREAT | O_WRONLY;

  int output_fd =
      open(argv[1], open_flags,
           S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);

  const size_t BUFF_SIZE = 4096;
  char buffer[BUFF_SIZE];
  ssize_t bytes_read;

  while ((bytes_read = read(STDIN_FILENO, buffer, BUFF_SIZE)) > 0) {
    if (write(STDOUT_FILENO, buffer, (size_t)bytes_read) != bytes_read) {
      perror("write stdin");
      close(output_fd);
      return EXIT_FAILURE;
    }

    if (write(output_fd, buffer, (size_t)bytes_read) != bytes_read) {
      perror("write to file");
      close(output_fd);
      return EXIT_FAILURE;
    }
  }

  if (bytes_read == -1) {
    perror("read");
    close(output_fd);
    return EXIT_FAILURE;
  }

  if (close(output_fd) == -1) {
    perror("close");
    return EXIT_FAILURE;
  }

  return 0;
}
