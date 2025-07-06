#include <stdio.h>
#include <stdlib.h>

struct Todo {
  int ID;
  char *text;
};

void show_help_menu(void) {
  printf("--- Todo List Menu ---\n");

  printf("1. Add Todo\n");
  printf("2. View Todos\n");
  printf("3. Help\n");
  printf("0. Exit\n");
}

int main(void) {

  show_help_menu();

  return 0;
}
