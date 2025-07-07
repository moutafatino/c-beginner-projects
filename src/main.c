#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

void list_todos(struct Todos todos) {

  for (int i = 0; i < todos.length; i++) {
    printf("%d - %s\n", todos.items[i].ID, todos.items[i].text);
  }
}

char *get_user_input(char *prompt) {
  size_t buffer_size = 128;
  char *buffer = malloc(sizeof(char) * buffer_size);
  if (!buffer) {
    perror("Failed to allocate initial buffer!");
    return NULL;
  }

  printf("%s", prompt);

  if (!fgets(buffer, (int)buffer_size, stdin)) {
    perror("Failed to read input!");
    free(buffer);
    return NULL;
  }

  size_t len = strlen(buffer);

  while (len > 0 && buffer[len - 1] != '\n') {

    buffer_size *= 2;
    char *temp = realloc(buffer, buffer_size);
    if (!temp) {
      perror("Failed to reallocate buffer!");
      free(buffer);
      return NULL;
    }

    buffer = temp;

    if (!fgets(buffer + len, (int)(buffer_size - len), stdin)) {
      perror("Failed to read more input!");
      free(buffer);
      return NULL;
    }

    len = strlen(buffer);
  }

  buffer[strcspn(buffer, "\n")] = '\0';

  char *final_buffer = realloc(buffer, strlen(buffer) + 1);
  if (!final_buffer) {
    perror("Failed to shrink buffer, returning original sized buffer!");
    return buffer;
  }

  return final_buffer;
}

int main(void) {

  struct Todos todos;
  todos.items[0] = (struct Todo){.ID = 1, .text = "First Todo"};
  todos.length = 1;

  show_help_menu();

  while (true) {

    int choice = get_user_choice("Enter your choice: ");

    switch (choice) {
    case 0: {
      return EXIT_SUCCESS;
    }
    case 1: {
      char *input = get_user_input("Enter new todo: ");
      todos.items[todos.length].text = input;
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
