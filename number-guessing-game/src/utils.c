#include "utils.h"
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int get_int_value(const char *format, ...) {
  char buffer[64];
  long value;
  char *endptr;
  char prompt[256];

  va_list args;
  va_start(args, format);

  vsnprintf(prompt, sizeof(prompt), format, args);
  va_end(args);

  while (1) {
    printf("%s", prompt);

    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
      fprintf(stderr, "Error reading input.\n");
      exit(EXIT_FAILURE);
    }

    buffer[strcspn(buffer, "\n")] = 0;

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

    return (int)value;
  }
}
