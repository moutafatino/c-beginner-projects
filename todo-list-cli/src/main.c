#include "helpers.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TODOS_FILE "todos.csv"





void show_help_menu(void) {
  printf("--- Todo List Menu ---\n");

  printf("1. Add Todo\n");
  printf("2. View Todos\n");
  printf("3. Help\n");
  printf("0. Exit\n");
}

void list_todos(struct Todos *todos) {

  if (todos->length == 0) {
    printf("No available todos.\n");
    return;
  }

  for (size_t i = 0; i < todos->length; i++) {
    printf("%d - %s\n", todos->items[i].ID, todos->items[i].text);
  }
}

int main(void) {

  struct Todos *app = init_todos();

  if (!app) {
    perror("Error initializing the app");
    return EXIT_FAILURE;
  }

  show_help_menu();

  while (true) {

    int choice = get_user_choice("Enter your choice: ");

    switch (choice) {
    case 0: {
      printf("Good bye!\n");

      end_app(app);
      return EXIT_SUCCESS;
    }
    case 1: {
      char *input = get_user_input("Enter new todo: ");
      app->items[app->length].text = input;
      app->items[app->length].ID = 1;
      // TODO: assign unique ID to todo.
      app->length++;

      printf("Todo added successfully\n");
      break;
    }
    case 2: {
      list_todos(app);
      break;
    }
    }
  }

  return 0;
}
