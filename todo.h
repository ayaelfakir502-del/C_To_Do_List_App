#ifndef TODO_H
#define TODO_H

#include <stdlib.h>
#include <stdio.h>

// ANSI Escape Codes for Terminal Colors
#define REST   "\033[0m"
#define RED    "\033[31m"
#define GREEN  "\033[32m"
#define YELLOW "\033[33m"
#define BLUE   "\033[34m"

// Max length for task description
#define MAX_DESC_LENGTH 50

// Data Structure for a Task
typedef struct {
    char description[MAX_DESC_LENGTH];
    int priority;
} Task;

// Function Prototypes (Declarations)

void clear_input_buffer();
void show_menu();

Task* add_task(Task* list, int* count);
void display_tasks(const Task* list, int count);
Task* delete_task(Task* list, int* count);
void save_tasks(const Task* list, int count, const char* filename);
Task* load_tasks(int* count, const char* filename);

#endif // TODO_H
