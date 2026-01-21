#define _DEFAULT_SOURCE
#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

int main() {

    char path[256];
    int option = 0;
    int file_ope_option = 0;
    bool is_file_path = false;

    printf("Type the path to be read: \n");
  
    while (1) {
        fgets(path, sizeof(path), stdin);
        path[strcspn(path, "\n")] = '\0';

        if (path[0] != '/') {
            printf("Local paths are not allowed. Please provide a full path.\n");
            continue;
        }
        break;
    }

    char *last_slash = strrchr(path, '/'); 

    if (last_slash != NULL) {
        // Check if there's a dot after the last slash
        if (strchr(last_slash, '.') != NULL) {
            is_file_path = true;
        }
    }

    if (is_file_path) {
        printf("These are the operations you can perform for a file path:\n");
        printf("1. Read a file\n");
        printf("2. Delete a file\n");

        while (1) {
            if (scanf("%d", &file_ope_option) != 1) {
                printf("Invalid input. Please enter a number.\n");
                while (getchar() != '\n'); // clear invalid input
                continue;
            }

            if (file_ope_option < 1 || file_ope_option > 2) {
                printf("Only choose 1 or 2.\n");
                while (getchar() != '\n'); // clear invalid input
                continue;
            }
            break;
        }
        if (file_ope_option == 1) {
            char line[256];
            FILE *fptr = fopen(path, "r");

            if (fptr == NULL) {
                printf("Error opening file: %s\n", path);
                return 1;
            }
            
            while (fgets(line, sizeof(line), fptr) != NULL) {
                printf("%s", line);
            }
            fclose(fptr);
        } else if (file_ope_option == 2) {
            // Delete file
            if (remove(path) == 0) {
                printf("Deleted file: %s\n", path);
            } else {
                printf("Error deleting file: %s\n", path);
            }
        }
        return 0;
    }

    printf("These are the operations you can perform: \n");
    printf("1. List files in the directory\n");
    printf("2. Create a new txt file\n");
    printf("3. Read a file\n");
    printf("4. Delete a file\n");

    while (1) {
        if (scanf("%d", &option) != 1) {
            printf("Invalid input. Please enter a number.\n");
            while (getchar() != '\n'); // clear invalid input
            continue;
        }

        if (option < 1 || option > 4) {
            printf("Only choose 1, 2, 3 or 4.\n");
            while (getchar() != '\n'); // clear invalid input
            continue;
        }
        break;
    }
    
    while (getchar() != '\n'); // clear newline left by scanf

    switch (option) {
        case 1:
            DIR *d = opendir(path);
            struct dirent *f;
            
            if (d == NULL) {
                printf("Could not open directory: %s\n", path);
                return 1;
            }
            printf("Files in directory %s:\n", path);
            
            while ((f = readdir(d)) != NULL) {
                if (strcmp(f->d_name, ".") == 0 || strcmp(f->d_name, "..") == 0) {
                    continue;
                }
                printf("%s\n", f->d_name);
            }
            closedir(d);

            break;
        case 2:
            FILE *fptr;
            char filename[300];
            bool valid_filename;

            while (1) {
                printf("Type the name of the new txt file (without .txt): \n");
                fgets(filename, sizeof(filename), stdin);
                filename[strcspn(filename, "\n")] = '\0';
                
                valid_filename = true;
                for (int i = 0; filename[i] != '\0'; i++) {
                    if (filename[i] == '.' || filename[i] == ' ') {
                        printf("Invalid filename. Dots and spaces are not allowed.\n");
                        valid_filename = false;
                        break;
                    }
                }
                
                if (valid_filename) {
                    break;
                }
            }
            break;
        case 3:
            printf("You chose option 3\n");
            break;
        case 4:
            printf("You chose option 4\n");
            break;
        default:  
            printf("Invalid option.\n");  
            break;
    }

    return 0;
}


    
