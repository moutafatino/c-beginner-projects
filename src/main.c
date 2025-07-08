#include "helpers.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

struct Todo {
  int ID;
  char *text;
};
struct Todos {
  struct Todo items[10];
  int length;
};

void show_help_menu(void) {
  printf("--- Todo List Menu ---\n");

  printf("1. Add Todo\n");
  printf("2. View Todos\n");
  printf("3. Help\n");
  printf("0. Exit\n");
}

void list_todos(struct Todos todos) {

  if (todos.length == 0) {
    printf("No available todos.\n");
    return;
  }

  for (int i = 0; i < todos.length; i++) {
    printf("%d - %s\n", todos.items[i].ID, todos.items[i].text);
  }
}

int current_last_id = 1;

int main(void) {

  struct Todos todos = {.length = 0};

  show_help_menu();

  while (true) {

    int choice = get_user_choice("Enter your choice: ");

    switch (choice) {
    case 0: {
      printf("Good bye!\n");
      return EXIT_SUCCESS;
    }
    case 1: {
      char *input = get_user_input("Enter new todo: ");
      todos.items[todos.length].text = input;
      todos.items[todos.length].ID = current_last_id++;
      // TODO: assign unique ID to todo.
      todos.length++;

      printf("Todo added successfully\n");
      break;
    }
    case 2: {
      list_todos(todos);
      break;
    }
    }
  }

  return 0;
}
