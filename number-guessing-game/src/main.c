#include <stdio.h>
#include <stdlib.h>

#define RANDOM_NUMBER_RANGE (11)

int main(void) {

  long int random_number = arc4random_uniform(RANDOM_NUMBER_RANGE);

  printf("%ld", random_number);
  return 0;
}
