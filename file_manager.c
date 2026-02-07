#define _DEFAULT_SOURCE
#include <dirent.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

bool filename_check(char *filename);
void validfilename(char *filename, size_t size, bool is_delete_prompt);
void openfile(FILE **fptr, char *filename);
bool findfile(DIR *d, char *filename, bool file_found, char *path, struct dirent *f);

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
            FILE *fptr = NULL;

            openfile(&fptr, path);

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
            while (getchar() != '\n');
            continue;
        }

        if (option < 1 || option > 4) {
            printf("Only choose 1, 2, 3 or 4.\n");
            while (getchar() != '\n');
            continue;
        }
        break;
    }
    
    while (getchar() != '\n');

    switch (option) {
        case 1: {
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
        };
        case 2: {
            FILE *fptr = NULL;
            char filename[300];
            char txt_to_add[500];
            char full_path[560];
            bool valid_filename;

            while (1) {
                printf("Type the name of the new txt file (without .txt): \n");
                fgets(filename, sizeof(filename), stdin);
                filename[strcspn(filename, "\n")] = '\0';
                
                valid_filename = filename_check(filename);
                
                if (valid_filename) {
                    break;
                }
            }
            
            snprintf(full_path, sizeof(full_path), "%s/%s.txt", path, filename);

            printf("Type in the content of the file: \n");
            printf("and use # in order to add a new line. \n");
            fgets(txt_to_add, sizeof(txt_to_add), stdin);
            txt_to_add[strcspn(txt_to_add, "\n")] = '\0';

            for (int i = 0; txt_to_add[i] != '\0'; i++) {
                if (txt_to_add[i] == '#') {
                    txt_to_add[i] = '\n';
                }
            }

            openfile(&fptr, full_path);
            fprintf(fptr, "%s", txt_to_add);
            printf("Text file created successfully\n");
            fclose(fptr);

            break;
        };
        case 3: {
            DIR *d = opendir(path);
            FILE *fptr = NULL;
            struct dirent *f;
            char filename[300];
            char full_path[560];
            char line[100];
            bool valid_filename;
            bool file_found = false;
            bool is_delete_prompt = false;

            validfilename(filename, sizeof(filename), is_delete_prompt);
            
            file_found = findfile(d, filename, file_found, path, f);

            if (file_found){
                char *ext = strrchr(filename, '.');

                if (ext != NULL && (strcmp(ext, ".png") == 0 || strcmp(ext, ".jpg") == 0)) {
                    printf("This is an image, implement later (maybe)");
                } else if (ext != NULL && strcmp(ext, ".txt") == 0) {
                    snprintf(full_path, sizeof(full_path), "%s/%s", path, filename);

                    fptr = fopen(full_path, "r+");

                    if (fptr == NULL) {
                        printf("Error opening the file: %s\n", full_path);
                    } else {
                        printf("These are the contents of the file: \n\n");
                        while (fgets(line, sizeof(line), fptr) != NULL) {
                            printf("%s", line);
                        }
                        fclose(fptr);
                    }
                }
            } else {
                printf("File not found. Did you add an extension?\n");
            }

            closedir(d);

            break;
        };
        case 4: {
            DIR *d = opendir(path);
            struct dirent *f;
            char filename[300];
            char full_path[560];
            bool valid_filename;
            bool file_found = false;
            bool is_delete_prompt = true;

            validfilename(filename, sizeof(filename), is_delete_prompt);

            file_found = findfile(d, filename, file_found, path, f);
    

            if (file_found) {
                snprintf(full_path, sizeof(full_path), "%s/%s", path, filename);
                
                if (remove(full_path) == 0) {
                    printf("Deleted file: %s\n", filename);
                } else {
                    perror("Failed to delete file");
                }
            } else {
                printf("File not found. Did you add an extension?\n");
            }

            closedir(d);

            break;
        }
        default:  
            printf("Invalid option.\n");  
            break;
    }

    return 0;
}

bool filename_check(char *filename) {
    for (int i = 0; filename[i] != '\0'; i++) {
        if (filename[i] == '.' || filename[i] == ' ') {
            printf("Invalid filename. Dots and/or spaces are not allowed.\n");
            return false;
        }
    }

    return true;
}

void validfilename(char *filename, size_t size, bool is_delete_prompt) {
    if (is_delete_prompt) {
        printf("Which file do you want to delete? Please add the extension: \n");
    } else {
        printf("Which file do you want to read? Please add the extension: \n");
    }
    while (1) {
        fgets(filename, size, stdin);
        filename[strcspn(filename, "\n")] = '\0';

        if (filename[0] == '/') {
            printf("Fullpaths are not allowed, please try again\n");
            continue;
        }

        if (strlen(filename) == 0) {
            printf("Filenames cannot be empty. Try again \n");
            continue;
        }

        break;
    }
}

void openfile(FILE **fptr, char *filename) {
    *fptr = fopen(filename, "r+");

    if (*fptr == NULL) {
        *fptr = fopen(filename, "w+");
    }
}

bool findfile(DIR *d, char *filename, bool file_found, char *path, struct dirent *f) {
    if (d == NULL) {
            printf("Could not open directory: %s\n", path);
            return false;
    }

    while ((f = readdir(d)) != NULL) {
        if (strcmp(f->d_name, ".") == 0 || strcmp(f->d_name, "..") == 0) {
            continue;
        }

        if (strcmp(f->d_name, filename) == 0) {
            return true;
        }
    };
    return false;
}
