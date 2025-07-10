#pragma once
#include <stdbool.h>
#include <stddef.h>

#define TODOS_FILE "todos.csv"

enum create_todo_result {
  CREATE_TODO_SUCCESS = 0,
  CREATE_TODO_FAILURE = -1,
};

struct Todo {
  int ID;       // Unique identifier for the todo item
  char *text;   // The text of the todo item
  bool is_done; // Status of the todo item, true if done, false if not
};

/*
 * @brief Represents the application state.
 * */
struct App {
  struct Todo *items; // Array of todo items
  size_t length;      // Size of the todo items array
  size_t capacity;    // Capacity of the allocated memory for todo items
  int next_id;        // Next ID to assign to a new todo item
};

/*
 * @brief Initializes the application and loads todo items from a file.
 * @return A pointer to the initialized App structure.
 * */
struct App *init_app(void);

/*
 * @brief Saves the todo items to a file.
 * @param app The application instance containing the todo items.
 * */
void save_todos(struct App *app);

/*
 * @brief Lists all todo items in the application.
 * @param todos The application instance containing the todo items.
 * */
void list_todos(struct App *todos);

/*
 * @brief Toggles the status of a todo item, Sets it to done if not done, and
 * vice versa.
 * @param app The application instance containing the todo items.
 * @id The ID of the todo item to toggle.
 * @return A message indicating the new status of the todo item or NULL if the
 * ID is invalid.
 * */
const char *toggle_todo_status(struct App *app, int id);

/*
 * @brief Creates a new todo item.
 * @param app The application instance to add the todo item to.
 * @return The result of the creation operation.
 * */
enum create_todo_result create_new_todo(struct App *app);

/*
 * @brief Deletes a todo item by its ID.
 * @param app The application instance containing the todo items.
 * @param id The ID of the todo item to delete.
 * @return True if the todo item was successfully deleted, false otherwise.
 * */
bool delete_todo(struct App *app, int id);

/*
 * @brief Cleans up the todo items.
 * @param items The array of todo items to free.
 * @param size The number of items in the array.
 * */
void free_todos(struct Todo *items, size_t size);

/*
 * @brief Cleans up the application resources.
 * @param app The application instance to clean up.
 * */
void end_app(struct App *app);
