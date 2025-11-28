#  C To-Do List Application

A robust command-line To-Do List manager implemented in C. This project demonstrates advanced concepts such as **Dynamic Memory Allocation** and **File Persistence**, making it a highly functional and reliable application.

##  Key Features

* **Dynamic Memory Management:** Utilizes the `realloc` function to dynamically expand and shrink the task list in memory, ensuring efficient resource usage.
* **File Persistence:** Tasks are securely saved to a binary file (`todo_data.bin`) upon exit and automatically loaded upon startup, preventing data loss between sessions.
* **User-Friendly Interface:**
    * Displays task priority with **Color-Coding** (Red for High, Yellow for Medium, Green for Low) for quick visual assessment.
    * Offers essential CRUD (Create, Read, Update, Delete) functionality through a simple menu system.

##  Project Structure

The application is structured into three modular files for clean, professional code organization:

| File Name | Description |
| :--- | :--- |
| `main.c` | Contains the main program loop, the interactive menu, and handles the flow for loading and saving tasks. |
| `todo.h` | The header file that defines the primary data structure (`Task`), color constants (ANSI escape codes), and declares all function prototypes. |
| `todo_functions.c` | Contains the core logic functions: `add_task`, `display_tasks`, `delete_task`, and utility functions like `clear_input_buffer`. |

##  How to Compile and Run

1.  Clone this repository or download the source files.
2.  Compile the project using a C compiler (e.g., GCC or Code::Blocks).
3.  Run the executable file.
4.  Use the menu options: `A` (Add), `V` (View), `D` (Delete), or `S` (Save and Exit).
