#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int input_val();
void add_task(FILE *fptr);
void display_todo_list(FILE *fptr);
void delete_task();

int main() {

    int option = 0;

    FILE *fptr = fopen("list.txt", "rb+");
    if(fptr == NULL) //if file does not exist, create it
    {
        fptr = fopen("list.txt", "wb");
    }

    printf("What do you want to do?\n");
    printf("1. Add a to-do task\n");
    printf("2. Read the to-do list \n");
    printf("3. Remove a task \n");
    printf("4. Exit\n");

    option = input_val();

    switch (option) {
    case 1:
        add_task(fptr);
        break;

    case 2:
        printf("Displaying the to-do list \n");
        display_todo_list(fptr);
        break;
    case 3:
        delete_task();
        break;  
    case 4:
        printf("Exiting program.\n");
        break;
    }

    return 0;
}

int input_val() {
    int option;

    while (1) {
        if (scanf("%d", &option) != 1) {
            printf("Invalid input. Please enter a number.\n");
            while (getchar() != '\n');
            continue;
        } 
        else if (option != 1 && option != 2 && option != 3 && option != 4) {
            printf("Only choose 1, 2, 3 or 4.\n");
            continue;
        } 
        else {
            while (getchar() != '\n');
            return option;
        }
    }
}

void add_task(FILE *fptr) {

    char task[100];
    char *end;

    while (1) {
        printf("Enter your to-do task: ");
        fgets(task, sizeof(task), stdin);
        task[strcspn(task, "\n")] = '\0'; // Remove trailing newline

        if (strlen(task) == 0) {
            printf("Task cannot be empty.\n");
            continue;
        }

        strtol(task, &end, 10);

        if (*end == '\0') {
            printf("Numbers are not allowed. Please enter text.\n");
            continue;
        }

        break;
    }

    fseek(fptr, 0, SEEK_END);
    fprintf(fptr, "%s\n", task);
    printf("Task added!\n");
}

void display_todo_list(FILE *fptr) {
    
    int c;

    if (fptr == NULL) {
        printf("Error opening file.\n");
    } else {
        while ((c = getc(fptr)) != EOF)
            putchar(c);
    }
}

void delete_task() {
    
    char task_to_delete[100];
    char line[100];
    int found = 0;

    printf("Enter the task to delete: ");
    fgets(task_to_delete, sizeof(task_to_delete), stdin);
    task_to_delete[strcspn(task_to_delete, "\n")] = '\0'; // Remove trailing newline

    FILE *fptr = fopen("list.txt", "r");
    FILE *temp = fopen("temp.txt", "w");

    if (fptr == NULL || temp == NULL) {
        printf("Error opening file.\n");
        return;
    }

    while (fgets(line, sizeof(line), fptr) != NULL) {
        line[strcspn(line, "\n")] = '\0';  // Remove newline for comparison
        if (strcmp(line, task_to_delete) != 0) {
            fprintf(temp, "%s\n", line);
        } else {
            found = 1;
        }
    }

    fclose(fptr);
    fclose(temp);

    remove("list.txt");
    rename("temp.txt", "list.txt");

    if (found) {
        printf("Task deleted!\n");
    } else {
        printf("Task not found.\n");
    }
}