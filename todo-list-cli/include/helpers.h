#pragma once

#include <stddef.h>

enum input_error {
  INPUT_SUCCESS = 0,
  INPUT_ERROR_MALLOC_FAILED,
  INPUT_ERROR_REALLOC_FAILED,
  INPUT_ERROR_READ_FAILED,
  INPUT_ERROR_INVALID_PARAM
};

const char *input_error_string(enum input_error error);

int get_int_input(char *prompt);
int get_user_choice(char *prompt, int valid_choices[], size_t size);

enum input_error get_user_input(char *prompt, char **result);
