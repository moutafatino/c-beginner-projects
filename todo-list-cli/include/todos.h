#pragma once
#include <stdbool.h>
#include <stddef.h>

#define TODOS_FILE "todos.csv"

enum create_todo_result {
  CREATE_TODO_SUCCESS = 0,
  CREATE_TODO_FAILURE = -1,
};

struct Todo {
  int ID;
  char *text;
  bool is_done;
};
struct App {
  struct Todo *items;
  size_t length;
  size_t capacity;
  int next_id;
};

struct App *init_app(void);

void save_todos(struct App *app);

void list_todos(struct App *todos);
const char *toggle_todo_status(struct App *app, int id);

enum create_todo_result create_new_todo(struct App *app);

void free_todos(struct Todo *items, size_t size);
void end_app(struct App *app);
