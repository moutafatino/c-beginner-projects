#include <stdio.h>
#include <stdlib.h>

#define RANDOM_NUMBER_RANGE (11)
#define MAX_ATTEMPTS (10)

int main(void) {

  printf("Welcome to the Number Guessing Game!\n");
  printf("I'm thinking of a whole number between 1 and %d. You have 10 "
         "attempts to guess it.\n",
         RANDOM_NUMBER_RANGE - 1);

  long int random_number = arc4random_uniform(RANDOM_NUMBER_RANGE);

  printf("RANDOM NUMBER %ld\n", random_number);
  int current_attempt = 0;
  while (current_attempt != MAX_ATTEMPTS) {
    printf("Attempt %d/%d: Enter your guess: ", current_attempt + 1,
           MAX_ATTEMPTS);

    int attempt;
    scanf("%d", &attempt);

    if (attempt > random_number) {
      printf("Too high! Try again.\n");
    } else if (attempt < random_number) {
      printf("Too low! Try again.\n");

    } else {
      printf("Congratulations! You guessed the number %ld in %d attempts!\n",
             random_number, current_attempt + 1);
      break;
    }
    current_attempt++;
  }

  if (current_attempt == MAX_ATTEMPTS) {
    printf("Game Over! You ran out of attempts. The secret number was %ld.",
           random_number);
  }

  return 0;
}
