#include "helpers.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void clear_input_buffer(void) {
  int c;
  while ((c = getchar()) != '\n' && c != EOF)
    ;
}

int get_int_input(char *prompt) {
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

      break;
    }
  }

  return (int)number;
}

int get_user_choice(char *prompt, int valid_choices[], size_t size) {
  while (true) {
    int number = get_int_input(prompt);
    bool is_valid = false;
    for (size_t i = 0; i < size; i++) {
      if (number == valid_choices[i]) {
        is_valid = true;
        break;
      }
    }

    if (!is_valid) {
      fprintf(stderr, "Invalid input: Please enter a valid command number.\n");
      continue;
    }

    return number;
  }
}

enum input_error get_user_input(char *prompt, char **result) {
  size_t buffer_size = 128;
  char *buffer = malloc(sizeof(char) * buffer_size);
  if (!buffer) {
    return INPUT_ERROR_MALLOC_FAILED;
  }

  printf("%s", prompt);

  if (!fgets(buffer, (int)buffer_size, stdin)) {
    free(buffer);
    return INPUT_ERROR_READ_FAILED;
  }

  size_t len = strlen(buffer);

  while (len > 0 && buffer[len - 1] != '\n') {

    buffer_size *= 2;
    char *temp = realloc(buffer, buffer_size);
    if (!temp) {
      free(buffer);
      return INPUT_ERROR_REALLOC_FAILED;
    }

    buffer = temp;

    if (!fgets(buffer + len, (int)(buffer_size - len), stdin)) {
      free(buffer);
      return INPUT_ERROR_READ_FAILED;
    }

    len = strlen(buffer);
  }

  buffer[strcspn(buffer, "\n")] = '\0';

  char *final_buffer = realloc(buffer, strlen(buffer) + 1);
  if (!final_buffer) {
    *result = buffer;
  } else {
    *result = final_buffer;
  }
  return INPUT_SUCCESS;
}

const char *input_error_string(enum input_error error) {
  switch (error) {
  case INPUT_SUCCESS:
    return "Success";
  case INPUT_ERROR_MALLOC_FAILED:
    return "Memory allocation failed";
  case INPUT_ERROR_REALLOC_FAILED:
    return "Memory reallocation failed";
  case INPUT_ERROR_READ_FAILED:
    return "Input read failed";
  case INPUT_ERROR_INVALID_PARAM:
    return "Invalid parameter";
  default:
    return "Unknown error";
  }
}
