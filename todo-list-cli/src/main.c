#include "helpers.h"
#include "todos.h"
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

int create_new_todo(struct Todos *app) {
  if (app->length >= app->capacity) {
    app->capacity += 2;
    struct Todo *items =
        realloc(app->items, sizeof(struct Todo) * app->capacity);
    if (!items) {
      fprintf(stderr, "Error: Failed to realloc memory for todos.\n");
      return EXIT_FAILURE;
    }

    app->items = items;
  }

  char *input = get_user_input("Enter new todo: ");

  app->items[app->length] =
      (struct Todo){.ID = (int)app->length + 1, .text = input};
  app->length++;

  save_todos(app);

  return EXIT_SUCCESS;
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

      int result = create_new_todo(app);
      if (result == EXIT_FAILURE) {
        fprintf(stderr, "Error while creating new todo");
        return result;
      }

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
