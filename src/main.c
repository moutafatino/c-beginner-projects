#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Todo {
  int ID;
  char *text;
};

void show_help_menu(void) {
  printf("--- Todo List Menu ---\n");

  printf("1. Add Todo\n");
  printf("2. View Todos\n");
  printf("3. Help\n");
  printf("0. Exit\n");
}

int get_user_choice(char *prompt) {
  char buffer[8];
  char *endptr;
  long number = -1;

  while (true) {
    printf("%s", prompt);
    if (fgets(buffer, 8, stdin)) {
      buffer[strcspn(buffer, "\n")] = 0;

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

int main(void) {

  show_help_menu();

  int choice = get_user_choice("Enter your choice: ");

  printf("User choice: %d", choice);

  return 0;
}
