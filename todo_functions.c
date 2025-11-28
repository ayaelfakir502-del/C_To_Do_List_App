#include "todo.h"
#include <string.h>

// Function to clear the input buffer after using scanf
void clear_input_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Displays the main menu options
void show_menu() {
    printf("\n\n=== To Do List Menu ===%s\n", REST);
    printf("1. Add a new Task (%sA%s)\n", GREEN, REST);
    printf("2. View all Tasks (%sV%s)\n", YELLOW, REST);
    printf("3. Delete a Task (%sD%s)\n", RED, REST);
    printf("4. Save and Exit (%sS%s)\n", BLUE, REST);
    printf("Enter your choice: ");
}

// Adds a new task to the list
Task* add_task(Task* list, int* count) {
    Task* new_list;
    int priority_input;

    //  Allocate space for the new task
    (*count)++;
    new_list = (Task*)realloc(list, (*count) * sizeof(Task));

    if (new_list == NULL) {
        printf("%sError: Memory allocation failed!%s\n", RED, REST);
        (*count)--;
        return list;
    }

    list = new_list;


    printf("Enter task priority (%s1=High%s, %s2=Medium%s, %s3=Low%s): ", RED, REST, YELLOW, REST, GREEN, REST);

    if (scanf("%d", &priority_input) != 1 || priority_input < 1 || priority_input > 3) {
        printf("%sInvalid priority entered. Setting to Low (3).%s\n", YELLOW, REST);
        priority_input = 3;
    }

    clear_input_buffer();
    list[*count - 1].priority = priority_input;


    printf("Enter task description (max %d chars): ", MAX_DESC_LENGTH - 1);
    fgets(list[*count - 1].description, MAX_DESC_LENGTH, stdin);
    list[*count - 1].description[strcspn(list[*count - 1].description, "\n")] = 0;

    printf("\n%sTask '%s' added successfully!%s\n", GREEN, list[*count - 1].description, REST);
    return list;
}

// Displays all tasks in the list
void display_tasks(const Task* list, int count) {
    if (count == 0) {
        printf("\n%sThe To Do List is currently empty. Start by adding a new task (A).%s\n", YELLOW, REST);
        return;
    }

    printf("\n\n=== Current To Do List (%d Tasks) ===\n", count);

    for (int i = 0; i < count; i++) {
        char* color_code;
        char* priority_text;

        if (list[i].priority == 1) {
            color_code = RED;
            priority_text = "High";
        } else if (list[i].priority == 2) {
            color_code = YELLOW;
            priority_text = "Medium";
        } else {
            color_code = GREEN;
            priority_text = "Low";
        }

        printf("%s%d. Priority: %s | Task: %s%s\n",
               color_code,
               i + 1,
               priority_text,
               list[i].description,
               REST);
    }
    printf("======================================%s\n", REST);
}

// Deletes a task by its index
Task* delete_task(Task* list, int* count) {
    if (*count == 0) {
        printf("\n%sList is empty, nothing to delete.%s\n", YELLOW, REST);
        return list;
    }

    int index_to_delete;
    printf("Enter the number of the task to delete (1 to %d): ", *count);

    if (scanf("%d", &index_to_delete) != 1 || index_to_delete < 1 || index_to_delete > *count) {
        printf("\n%sInvalid number entered. Deletion cancelled.%s\n", RED, REST);
        clear_input_buffer();
        return list;
    }

    int delete_index = index_to_delete - 1;

    // Shift elements left
    for (int i = delete_index; i < *count - 1; i++) {
        list[i] = list[i + 1];
    }

    // Shrink the memory block
    (*count)--;
    Task* new_list = NULL;

    if (*count > 0) {
        new_list = (Task*)realloc(list, (*count) * sizeof(Task));
        if (new_list == NULL) {
             printf("\n%sError: Memory reallocation failed after deletion! List size unchanged.%s\n", RED, REST);
             (*count)++;
             return list;
        }
        list = new_list;
    } else {
        free(list);
        list = NULL;
    }

    printf("\n%sTask number %d deleted successfully!%s\n", GREEN, index_to_delete, REST);
    return list;
}

void save_tasks(const Task* list, int count, const char* filename) {
    FILE* fp = fopen(filename, "wb");
    if (fp == NULL) {
        printf("\n%sError: Could not open file %s for saving.%s\n", RED, filename, REST);
        return;
    }

    fwrite(&count, sizeof(int), 1, fp);
    fwrite(list, sizeof(Task), count, fp);

    fclose(fp);
    printf("\n%sSuccessfully saved %d tasks to %s.%s\n", GREEN, count, filename, REST);
}

Task* load_tasks(int* count, const char* filename) {
    FILE* fp = fopen(filename, "rb");
    if (fp == NULL) {
        *count = 0;
        return NULL;
    }

    fread(count, sizeof(int), 1, fp);

    if (*count > 0) {
        Task* list = (Task*)malloc((*count) * sizeof(Task));
        if (list == NULL) {
            printf("\n%sError: Memory allocation failed during loading.%s\n", RED, REST);
            *count = 0;
            fclose(fp);
            return NULL;
        }

        fread(list, sizeof(Task), *count, fp);
        fclose(fp);
        printf("\n%sSuccessfully loaded %d tasks from %s.%s\n", GREEN, *count, filename, REST);
        return list;
    }

    fclose(fp);
    return NULL;
}
