#include <fcntl.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char **argv) {

  if (argc < 2 || strcmp(argv[1], "--help") == 0) {
    fprintf(stderr, "usage: %s file [-a]\n", argv[1]);
    return EXIT_FAILURE;
  }

  int open_flags = O_WRONLY | O_CREAT;

  int opt;

  while ((opt = getopt(argc, argv, "a")) != -1) {
    switch (opt) {
    case 'a':
      open_flags |= O_APPEND;
      printf("SHOULD APPEND\n");
      break;
    case '?':
      fprintf(stderr, "usage: %s file [-a]\n", argv[1]);
      return EXIT_FAILURE;
      break;
    }
  }

  int output_fd =
      open(argv[optind], open_flags,
           S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);

  size_t buff_size = 128;

  char *buff = malloc(buff_size);
  if (buff == NULL) {
    perror("malloc");
    return EXIT_FAILURE;
  }

  size_t len = 0;

  ssize_t num_read;
  while (true) {
    num_read = read(STDIN_FILENO, buff + len, buff_size - len - 1);
    if (num_read == -1) {
      free(buff);
      return EXIT_FAILURE;
    }

    if (num_read == 0)
      break;

    len += (size_t)num_read;
    buff[len] = '\n';

    char *newline_pos = strchr(buff, '\n');
    if (newline_pos) {
      *newline_pos = '\0';
      printf("%s\n", buff);

      if (write(output_fd, buff, buff_size) == -1) {
        perror("write");
        return EXIT_FAILURE;
      }

      memset(buff, 0, buff_size);
      len = 0;
    } else {
      if (len >= buff_size - 1) {
        buff_size *= 2;
        char *temp_buff = realloc(buff, buff_size);
        if (!temp_buff) {
          free(buff);
          return EXIT_FAILURE;
        }
        buff = temp_buff;
      }
    }
  }

  free(buff);

  return 0;
}
