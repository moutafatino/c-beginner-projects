#include "todos.h"
#include "helpers.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct App *init_app(void) {
  FILE *todos_file = fopen(TODOS_FILE, "a+");
  if (!todos_file) {
    perror("Error: Opening todos file");
    return NULL;
  }
  size_t todos_capacity = 4;
  struct Todo *items = malloc(sizeof(struct Todo) * todos_capacity);
  if (!items) {
    perror("Error: Failed to allocate memory for todos");
    fclose(todos_file);
    return NULL;
  }

  int buffer_size = 1024;

  char buffer[buffer_size];
  size_t i = 0;
  char *endptr;
  int max_id = 0; // to select the next ID
  while (fgets(buffer, buffer_size, todos_file) != NULL) {
    if (buffer[0] == '\n' || buffer[0] == '\0') {
      continue;
    }

    char *token = strtok(buffer, ":");
    if (!token) {
      perror("Error: Invalid line format, skipping");
      continue;
    }

    int id = (int)strtol(token, &endptr, 10);
    if (endptr == token || (*endptr != '\0' && *endptr != '\n')) {
      perror("Error: invalid ID format, skipping");
      continue;
    }

    if (id > max_id) {
      max_id = id; // update max_id to the highest ID found
    }

    token = strtok(NULL, ":");
    if (!token) {
      fprintf(stderr, "Error: Missing text for ID %d, skipping\n", id);
      continue;
    }

    token[strcspn(token, "\n")] = '\0';

    if (i == todos_capacity) {
      todos_capacity *= 2;
      struct Todo *temp = realloc(items, sizeof(struct Todo) * todos_capacity);
      if (!temp) {
        perror("Error: Failed to reallocate space for todos");
        free_todos(items, i);
        fclose(todos_file);
        return NULL;
      }

      items = temp;
    }

    char *text = strdup(token);

    if (!text) {
      perror("Error: Failed to allocate memory for todo text");
      free_todos(items, i);
      fclose(todos_file);
      return NULL;
    }

    items[i] = (struct Todo){.ID = id, .text = text};
    i++;
  }

  fclose(todos_file);

  struct App *todos = malloc(sizeof(struct App));
  if (!todos) {
    perror("Error: Failed to allocate memory for App object.");
    free_todos(items, i);
    return NULL;
  }

  todos->capacity = i;
  todos->length = i;
  todos->next_id = max_id + 1;
  todos->items = items;

  return todos;
}

void free_todos(struct Todo *items, size_t size) {
  for (size_t i = 0; i < size; i++) {
    free(items[i].text);
  }
  free(items);
}

void end_app(struct App *app) {
  free_todos(app->items, app->length);
  free(app);
}

void save_todos(struct App *app) {
  FILE *todos_file = fopen(TODOS_FILE, "w");
  if (!todos_file) {
    perror("Error: Failed to open todos file for writing");
    return;
  }

  for (size_t i = 0; i < app->length; i++) {
    fprintf(todos_file, "%d:%s\n", app->items[i].ID, app->items[i].text);
  }

  fclose(todos_file);
}

void list_todos(struct App *todos) {

  if (todos->length == 0) {
    printf("No available todos.\n");
    return;
  }

  for (size_t i = 0; i < todos->length; i++) {
    printf("%d - %s\n", todos->items[i].ID, todos->items[i].text);
  }
}

enum create_todo_result create_new_todo(struct App *app) {
  if (app->length >= app->capacity) {
    app->capacity += 2;
    struct Todo *items =
        realloc(app->items, sizeof(struct Todo) * app->capacity);
    if (!items) {
      fprintf(stderr, "Error: Failed to realloc memory for todos.\n");
      return CREATE_TODO_FAILURE;
    }
    app->items = items;
  }

  char *input;
  enum input_error result = get_user_input("Enter new todo: ", &input);
  if (result != INPUT_SUCCESS) {
    fprintf(stderr, "Error: %s\n", input_error_string(result));
    return CREATE_TODO_FAILURE;
  }

  app->items[app->length] = (struct Todo){.ID = app->next_id, .text = input};
  app->length++;
  app->next_id++;

  save_todos(app);

  return CREATE_TODO_SUCCESS;
}
