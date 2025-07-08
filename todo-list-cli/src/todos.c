#include "todos.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Todos *init_todos(void) {
  FILE *todos_file = fopen(TODOS_FILE, "r");
  if (!todos_file) {
    perror("Error reading todos file");
    return NULL;
  }
  size_t todos_capacity = 4;
  struct Todo *items = malloc(sizeof(struct Todo) * todos_capacity);
  if (!items) {
    perror("Error allocating space for todos");
    fclose(todos_file);
    return NULL;
  }

  int buffer_size = 1024;

  char buffer[buffer_size];
  size_t i = 0;
  while (fgets(buffer, buffer_size, todos_file) != NULL) {
    if (buffer[0] == '\n' || buffer[0] == '\0') {
      continue;
    }

    char *token = strtok(buffer, ":");
    if (!token) {
      perror("Error: invalid lien format, skipping");
      continue;
    }
    int id = atoi(token); // TODO: move to strtol

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
        perror("Error faield to reallocate space for todos");
        free_partial_todos(items, i);
        fclose(todos_file);
        return NULL;
      }

      items = temp;
    }

    char *text = strdup(token);

    if (!text) {
      perror("Error allocating text for todo");
      free_partial_todos(items, i);
      fclose(todos_file);
      return NULL;
    }

    items[i] = (struct Todo){.ID = id, .text = text};
    i++;
  }

  fclose(todos_file);

  struct Todos *todos = malloc(sizeof(struct Todos));
  if (!todos) {
    perror("Error allocating todos structure");
    free_partial_todos(items, i);
    return NULL;
  }

  todos->capacity = i;
  todos->length = i;
  struct Todo *shrinked_items = realloc(items, sizeof(struct Todo) * i);
  if (!shrinked_items) {
    perror("Error: failed to shrink the items capacity returning the original "
           "items.");
    todos->capacity = todos_capacity;
    todos->items = items;
    return todos;
  }
  todos->items = shrinked_items;

  return todos;
}

void free_partial_todos(struct Todo *items, size_t size) {
  for (size_t i = 0; i < size; i++) {
    free(items[i].text);
  }

  free(items);
}

void end_app(struct Todos *app) {
  free_partial_todos(app->items, app->length);

  free(app);
}
