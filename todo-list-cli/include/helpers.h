#pragma once

#include <stddef.h>

enum input_error {
  INPUT_SUCCESS = 0,
  INPUT_ERROR_MALLOC_FAILED,
  INPUT_ERROR_REALLOC_FAILED,
  INPUT_ERROR_READ_FAILED,
  INPUT_ERROR_INVALID_PARAM
};

/*
 * @brief Returns a string representation of the input_error enum.
 * @param error The input error enum value.
 * @return A string describing the error.
 * */
const char *input_error_string(enum input_error error);

/*
 * @brief Prompts the user for an integer input and returns the result and keeps
 * prompting until a valid integer is entered.
 * @param prompt The prompt to display to the user.
 * @return The integer input from the user.
 * */
int get_int_input(char *prompt);

/*
 * @brief Prompts the user for a choice from a list of valid options and keeps
 * prompting until a valid choice is made.
 * @param prompt The prompt to display to the user.
 * @param valid_choices An array of valid choices.
 * @param size The number of valid choices in the array.
 * @return The user's choice as an integer.
 * */
int get_user_choice(char *prompt, int valid_choices[], size_t size);

/*
 * @brief Prompts the user for input and returns the result.
 * @param prompt The prompt to display to the user.
 * @param result Pointer to a char pointer where the result will be stored.
 * @return An enum indicating the success or failure of the input operation.
 * */
enum input_error get_user_input(char *prompt, char **result);
