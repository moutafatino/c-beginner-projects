#include "utils.h"
#include <errno.h>
#include <limits.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *get_formatted_prompt(const char *format, va_list args) {
  va_list args_copy_for_size;
  va_copy(args_copy_for_size, args);

  int buffer_size = vsnprintf(NULL, 0, format, args_copy_for_size);
  va_end(args_copy_for_size);

  if (buffer_size < 0) {
    fprintf(stderr, "Error: encoding the format string failed.\n");
    return NULL;
  }

  // Add 1 for null terminator
  buffer_size += 1;

  char *buffer = malloc((size_t)buffer_size);
  if (buffer == NULL) {
    fprintf(stderr, "Error: failed to allocate memory for the buffer.\n");
    return NULL;
  }

  int result = vsnprintf(buffer, (size_t)buffer_size, format, args);

  if (result < 0 || result >= buffer_size) {
    free(buffer);
    fprintf(stderr, "Error: failed to format the string.\n");
    return NULL;
  }

  return buffer;
}

int get_int_value(int min, int max, const char *format, ...) {
  char buffer[64];
  long value;
  char *endptr;

  va_list args;
  va_start(args, format);
  char *prompt = get_formatted_prompt(format, args);
  va_end(args);

  if (prompt == NULL) {
    fprintf(stderr, "Error: failed to create prompt.\n");
    exit(EXIT_FAILURE);
  }

  while (1) {
    printf("%s", prompt);

    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
      fprintf(stderr, "Error reading input.\n");
      free(prompt); // Free before exit
      exit(EXIT_FAILURE);
    }

    buffer[strcspn(buffer, "\n")] = 0;

    errno = 0;
    value = strtol(buffer, &endptr, 10);

    if (endptr == buffer) {
      printf("Invalid input: Please enter a number!\n");
      continue;
    }

    if (*endptr != '\0') {
      printf("Invalid input: Please enter a valid number without extra "
             "characters.\n");
      continue;
    }

    if (errno == ERANGE) {
      printf("Invalid input: Number is too large or too small.\n");
      continue;
    }

    if (value < min || value > max) {
      printf("Invalid input: Number is outside the valid range (%d to %d).\n",
             min, max);
      continue;
    }

    break;
  }

  free(prompt);
  return (int)value;
}
