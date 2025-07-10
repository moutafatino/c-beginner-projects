# Number Guessing Game in C

This is a simple command-line number guessing game I built while learning C.

The main goal was to get hands-on experience with fundamental concepts like generating random numbers, getting user input, and using loops and conditionals.

## Features

* Generates a random number between min and max.
* Asks the user to guess the number.
* Provides feedback on whether the guess is too high or too low.
* Counts the number of attempts it takes to guess the correct number.

## How to Build and Run It

If you want to compile it yourself, you'll need `gcc`, `cmake`, and `make`.

1. **Use CMake to set up the build:**

    ```sh
    mkdir build
    cd build
    cmake ..
    ```

2. **Compile the code:**

    ```sh
    make
    ```

    This will create the `number-guessing-game` executable inside the `build` directory.

3. **Run it:**

    ```sh
    ./number-guessing-game
    ```

    The game will then start and prompt you for your guess.

## Project structure

I split the code into a few parts to keep it organized:

```
.
├── include/      # Header files
│   └── utils.h   # Function prototypes for utility functions
└── src/          # Source files
    ├── main.c    # The main program loop
    └── utils.c   # Implementation of utility functions
```

## What I Learned

* **Random Numbers:** Using `arc4random_uniform` to generate pseudo-random numbers for the game.
* **User Input:** Reading integer input from the user and handling it.
* **Project Organization:** Using a header file (`.h`) to declare functions and separating the implementation into different `.c` files.
* **Build Systems:** Setting up a basic `CMakeLists.txt` to compile the project.
