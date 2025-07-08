#pragma once
#include <stddef.h>

#define TODOS_FILE "todos.csv"

struct Todo {
  int ID;
  char *text;
};
struct Todos {
  struct Todo *items;
  size_t length;
  size_t capacity;
};

struct Todos *init_todos(void);

void save_todos(struct Todos *app);

void free_partial_todos(struct Todo *items, size_t size);
void end_app(struct Todos *app);
