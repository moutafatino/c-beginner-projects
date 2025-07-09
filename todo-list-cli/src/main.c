#include "helpers.h"
#include "todos.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define TODOS_FILE "todos.csv"

void show_help_menu(void) {
  printf("--- Todo List Menu ---\n");
  printf("1. Add Todo\n");
  printf("2. View Todos\n");
  printf("3. Help\n");
  printf("0. Exit\n");
}

int main(void) {

  struct App *app = init_app();

  int valid_choices[] = {0, 1, 2, 3};

  if (!app) {
    perror("Error: Failed to initialize the application. Quitting...");
    return EXIT_FAILURE;
  }

  show_help_menu();

  while (true) {

    int choice =
        get_user_choice("Enter your choice: ", valid_choices,
                        sizeof(valid_choices) / sizeof(valid_choices[0]));

    switch (choice) {
    case 0: {
      printf("Good bye!\n");

      end_app(app);
      return EXIT_SUCCESS;
    }
    case 1: {

      enum create_todo_result result = create_new_todo(app);
      if (result == CREATE_TODO_FAILURE) {
        fprintf(stderr, "Error: Failed to create new todo.\n");
        continue;
      }

      printf("Todo added successfully\n");
      break;
    }
    case 2: {
      list_todos(app);
      break;
    }
    case 3: {
      show_help_menu();
      break;
    }
    }
  }
  return 0;
}
