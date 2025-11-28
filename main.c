#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "todo.h"

#define DATA_FILE "todo_data.bin"

int main() {
    Task* task_list = NULL;
    int task_count = 0;
    char choice;

    task_list = load_tasks(&task_count, DATA_FILE);

    do {
        show_menu();

        if (scanf(" %c", &choice) != 1) {
            choice = ' ';
        }
        clear_input_buffer();

        choice = toupper(choice);

        switch (choice) {
            case 'A':
                task_list = add_task(task_list, &task_count);
                break;
            case 'V':
                display_tasks(task_list, task_count);
                break;
            case 'D':
                task_list = delete_task(task_list, &task_count);
                break;
            case 'S':
                save_tasks(task_list, task_count, DATA_FILE);
                printf("\n%sExiting program. Goodbye!%s\n", BLUE, REST);
                break;
            default:
                printf("\n%sInvalid choice. Please enter A, V, D, or S.%s\n", RED, REST);
                break;
        }

    } while (choice != 'S');

    if (task_list != NULL) {
        free(task_list);
    }

    return 0;
}
