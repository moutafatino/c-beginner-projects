# C Beginner Projects

This repository contains a collection of simple C projects that I created while learning the language.

Each project is self-contained in its own directory and includes its own build files and source code.

## Projects

Here are the projects currently in this collection:

### 1. Number Guessing Game

A simple command-line game where the player has to guess a randomly generated number.

* **Focus:** `arc4random_uniform`, getting user input, and basic loops/conditionals.
* **Location:** `number-guessing-game/`

### 2. CLI Todo List

A command-line application for managing a todo list.

* **Focus:** `malloc`/`realloc`/`free`, file I/O, custom data structures, and splitting a project into multiple files.
* **Location:** `todo-list-cli/`

## How to Build and Run

Each project uses **CMake** and can be built using the standard process. To build and run a specific project, navigate to its directory and follow the instructions in its respective `README.md` file.

Generally, the steps are:

1. **Navigate to the project directory:**

    ```sh
    cd name-of-project/
    ```

2. **Create a build directory:**

    ```sh
    mkdir build && cd build
    ```

3. **Run CMake and Make:**

    ```sh
    cmake ..
    make
    ```

4. **Run the executable:**

    ```sh
    ./<executable_name>
    ```

