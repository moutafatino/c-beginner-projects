#include <stdio.h>
#include <stdlib.h>

int main(void) {
  int *age = malloc(sizeof(int));
  const int AGE = 10;
  *age = AGE;
  printf("Hello, World! %d\n", *age);
  return 0;
}
