#include <fcntl.h>
#include <getopt.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

void print_usage(const char *program_name) {
  fprintf(stderr, "Usage: %s [OPTIONS] file\n", program_name);
  fprintf(stderr, "Options:\n");
  fprintf(stderr, "  %-20s Append to the given file. Do not overwrite\n",
          "-a, --append");
  fprintf(stderr, "  %-20s Display this help message\n", "-h, --help");
}

int main(int argc, char **argv) {

  bool mode_append = false;

  static struct option long_options[] = {
      {"append", no_argument, 0, 'a'},
      {"help", no_argument, 0, 'h'},
  };

  int opt;
  while ((opt = getopt_long(argc, argv, "ah", long_options, NULL)) != -1) {
    switch (opt) {
    case 'a': {
      mode_append = true;
      break;
    }
    case 'h':
    case '?': {
      print_usage(argv[0]);
      return EXIT_FAILURE;
      break;
    }
    }
  }

  const int REQUIRED_ARGS = 1;
  if ((argc - optind) < REQUIRED_ARGS) {
    print_usage(argv[0]);
    return EXIT_FAILURE;
  }

  int open_flags = O_CREAT | O_WRONLY;

  if (mode_append) {
    open_flags |= O_APPEND;
  } else {
    open_flags |= O_TRUNC;
  }

  int output_fd =
      open(argv[optind], open_flags,
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
