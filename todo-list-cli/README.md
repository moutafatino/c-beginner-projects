# CLI Todo List in C

This is a simple command-line todo list application I built while learning C.

The main goal was to get hands-on experience with fundamental concepts like memory management (`malloc`, `realloc`, `free`), file I/O, data structures, and splitting a project into multiple files.

## Features

* Add new todos.
* View all todos.
* Toggle the status of todos.
* Delete todos.
* Todos are saved in a csv file.

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

    This will create the `todo-list` executable inside the `build` directory.

3. **Run it:**

    ```sh
    ./todo-list
    ```

    You'll see a menu with options to manage your todos.

## Project structure

I split the code into a few parts to keep it organized:

```
.
├── include/      # Header files
│   ├── todos.h   # Defines the App and Todo structs and function prototypes for todo logic
│   └── helpers.h # Function prototypes for getting user input
└── src/          # Source files
    ├── main.c    # The main program loop and user menu
    ├── todos.c   # The core logic for adding, deleting, saving todos, etc.
    └── helpers.c # Helper functions for reading input from the command line
```

## What I Learned

* **Dynamic Memory:** A lot of `malloc` and `realloc`! Especially for handling the list of todos and reading user input of unknown length. Also, learning the hard way to always `free` what you allocate.
* **File I/O:** Reading from and writing to the `todos.csv` file. I used `strtok` to parse the lines, which was a bit tricky.
* **Project Organization:** Using header files (`.h`) to declare functions and structs, and separating the implementation into different `.c` files.
* **Build Systems:** Setting up a basic `CMakeLists.txt` to compile everything together (actually I just used the quick start template from a neovim plugin).
