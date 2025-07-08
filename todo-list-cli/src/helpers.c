#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void clear_input_buffer(void) {
  int c;
  while ((c = getchar()) != '\n' && c != EOF)
    ;
}

int get_user_choice(char *prompt, int valid_range[], size_t size) {
  char buffer[64];
  char *endptr;
  long number = -1;

  char *newline_found;
  while (true) {
    printf("%s", prompt);
    if (fgets(buffer, sizeof(buffer), stdin)) {
      newline_found = strchr(buffer, '\n');

      if (newline_found) {
        buffer[strcspn(buffer, "\n")] = 0;
      } else {
        clear_input_buffer();
      }
      number = strtol(buffer, &endptr, 10);

      if (endptr == buffer || (*endptr && *endptr != '\n')) {
        fprintf(stderr, "Invalid input: Please enter a valid number.\n");
        continue;
      }
      // TODO: Validate the range of the number to be a valide choice.
      bool is_valid = false;
      for (size_t i = 0; i < size; i++) {
        if (number == valid_range[i]) {
          is_valid = true;
        }
      }

      if (!is_valid) {
        fprintf(stderr,
                "Invalid choice: Please enter a number in the valid range.\n");
        continue;
      }

      break;
    }
  }

  return (int)number;
}
char *get_user_input(char *prompt) {
  size_t buffer_size = 128;
  char *buffer = malloc(sizeof(char) * buffer_size);
  if (!buffer) {
    perror("Failed to allocate initial buffer!");
    return NULL;
  }

  printf("%s", prompt);

  if (!fgets(buffer, (int)buffer_size, stdin)) {
    perror("Failed to read input!");
    free(buffer);
    return NULL;
  }

  size_t len = strlen(buffer);

  while (len > 0 && buffer[len - 1] != '\n') {

    buffer_size *= 2;
    char *temp = realloc(buffer, buffer_size);
    if (!temp) {
      perror("Failed to reallocate buffer!");
      free(buffer);
      return NULL;
    }

    buffer = temp;

    if (!fgets(buffer + len, (int)(buffer_size - len), stdin)) {
      perror("Failed to read more input!");
      free(buffer);
      return NULL;
    }

    len = strlen(buffer);
  }

  buffer[strcspn(buffer, "\n")] = '\0';

  char *final_buffer = realloc(buffer, strlen(buffer) + 1);
  if (!final_buffer) {
    perror("Failed to shrink buffer, returning original sized buffer!");
    return buffer;
  }

  return final_buffer;
}
