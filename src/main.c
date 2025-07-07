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
      // TODO: Validate the range of the number to be a valide choice.

      break;
    }
  }

  return (int)number;
}

void list_todos(struct Todo todos[], int size) {

  for (int i = 0; i < size; i++) {
    printf("%d - %s\n", todos[i].ID, todos[i].text);
  }
}

int main(void) {

  struct Todo todos[10] = {{.ID = 1, .text = "First Todo"}};

  show_help_menu();

  int choice = get_user_choice("Enter your choice: ");

  switch (choice) {
  case 2: {
    list_todos(todos, 1);
    break;
  }
  }

  return 0;
}
