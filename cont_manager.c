#include <dirent.h>
#include <stdio.h>
#include <string.h>

struct Contact {
    char name[50];
    char phone[15];
    char email[50];
    char age[4];
};

void add_contact(struct Contact *contact);
void display_todo_list(FILE *fptr);
void open_file(FILE **fptr, char *filename);

int main() {

    char input_name[50];
    char input_phone[15];
    char input_email[50];
    char input_age[4];

    struct Contact contact1;

    // structs to read a dir
    DIR *d = opendir("./database");
    struct dirent *f;

    while (1) {
        int option;

        printf("Select an option:\n");
        printf("1. Add a contact\n");
        printf("2. Display a contact\n");
        printf("3. Edit a contact\n");
        printf("4. Delete a contact\n");
        printf("5. Exit\n");

        if (scanf("%d", &option) != 1) {
            printf("Invalid input. Please enter a number.\n");
            while (getchar() != '\n');
            continue;

        } else if (option < 1 || option > 5) {
            printf("Only choose 1, 2, 3, 4 or 5.\n");
            while (getchar() != '\n');
            continue;
            
        } else {
            while (getchar() != '\n');

            int choose_edit;
            int found = 0;
            char filepath[300];
            char temp_name[256];
            char name[50];

            
            switch (option) {

                case 1:
                add_contact(&contact1);
                break;

                case 2:
                printf("Type the name of the contact: \n");
                fgets(name, sizeof(name), stdin);
                name[strcspn(name, "\n")] = '\0';

                rewinddir(d);
                while ((f = readdir(d))) {
                    // Skip . and .. directories
                    if (strcmp(f->d_name, ".") == 0 || strcmp(f->d_name, "..") == 0) {
                        continue;
                    }

                    // buffer to not modify f->d_name
                    strcpy(temp_name, f->d_name);
                    
                    for (int i = 0; temp_name[i] != '\0'; i++) {
                        if (temp_name[i] == '_') {
                            temp_name[i] = ' ';
                        }
                    }

                    char *ext = strrchr(temp_name, '.'); // pointer to a string that starts at the "." so ext=".txt"
                    if (ext && strcmp(ext, ".txt") == 0) {
                        *ext = '\0';
                    }

                    if (strcmp(temp_name, name) == 0) {
                        printf("Contact found: %s\n", name);

                        sprintf(filepath, "database/%s", f->d_name);
                    
                        FILE *fptr = NULL;
                        open_file(&fptr, filepath);

                        // Read and display the file contents
                        display_todo_list(fptr);

                        fclose(fptr);
                        
                        found = 1;
                        break;
                    }
                }

                if (!found) {
                    printf("Contact not found: %s\n", name);
                }

                break;

                case 3:
                printf("Type the name of the contact to be edited: \n");
                fgets(name, sizeof(name), stdin);
                name[strcspn(name, "\n")] = '\0';

                rewinddir(d);
                while ((f = readdir(d))) {
                    // Skip . and .. directories
                    if (strcmp(f->d_name, ".") == 0 || strcmp(f->d_name, "..") == 0) {
                        continue;
                    }

                    // buffer to not modify f->d_name
                    strcpy(temp_name, f->d_name);
                    
                    for (int i = 0; temp_name[i] != '\0'; i++) {
                        if (temp_name[i] == '_') {
                            temp_name[i] = ' ';
                        }
                    }

                    char *ext = strrchr(temp_name, '.'); // pointer to a string that starts at the "." so ext=".txt"
                    if (ext && strcmp(ext, ".txt") == 0) {
                        *ext = '\0';
                    }

                    if (strcmp(temp_name, name) == 0) {
                        printf("Contact found: %s\n", name);
                        snprintf(filepath, sizeof(filepath), "database/%s", f->d_name);

                        printf("What do you want to edit:\n");
                        printf("1. Name\n");
                        printf("2. Phone\n");
                        printf("3. Email\n");
                        printf("4. Age\n");

                        while (1) {
                            if (scanf("%d", &choose_edit) != 1) {
                                printf("Invalid input. Please enter a number.\n");
                                while (getchar() != '\n'); // clear invalid
                                continue;
                            }
                            while (getchar() != '\n'); // consume newline

                            if (choose_edit < 1 || choose_edit > 4) {
                                printf("Only choose 1, 2, 3 or 4.\n");
                                continue;
                            }
                            break;
                        }
                    }
                }

                if (!found) {
                    printf("Contact not found: %s\n", name);
                }                
                
                break;

                case 4:

                printf("Type the name of the contact to be deleted: \n");
                fgets(name, sizeof(name), stdin);
                name[strcspn(name, "\n")] = '\0'; 
                rewinddir(d);
                while ((f = readdir(d))) {
                    // Skip . and .. directories
                    if (strcmp(f->d_name, ".") == 0 || strcmp(f->d_name, "..") == 0) {
                        continue;
                    }

                    // buffer to not modify f->d_name
                    strcpy(temp_name, f->d_name);
                    
                    for (int i = 0; temp_name[i] != '\0'; i++) {
                        if (temp_name[i] == '_') {
                            temp_name[i] = ' ';
                        }
                    }

                    char *ext = strrchr(temp_name, '.'); // pointer to a string that starts at the "." so ext=".txt"
                    if (ext && strcmp(ext, ".txt") == 0) {
                        *ext = '\0';
                    }

                    if (strcmp(temp_name, name) == 0) {
                        printf("Contact found: %s\n", name);
                        snprintf(filepath, sizeof(filepath), "database/%s", f->d_name);

                        if (remove(filepath) == 0) {
                            printf("Deleted contact file: %s\n", name);
                            found = 1;
                        } else {
                            perror("Failed to delete contact file");
                        }

                        break;
                    } 
                }

                if (!found) {
                    printf("Contact not found: %s\n", name);
                }                

                break;

                case 5:
                printf("Exiting program.\n");
                closedir(d);
                return 0;
            }
        }
    }

    return 0;
}

void open_file(FILE **fptr, char *filename) {
    *fptr = fopen(filename, "r+");
    if (*fptr == NULL) {
        *fptr = fopen(filename, "w+");
    }
}

void add_contact(struct Contact *contact) {
    char filename[100];

    printf("Type the name of the contact to be added: \n");
    fgets(contact->name, sizeof(contact->name), stdin);
    contact->name[strcspn(contact->name, "\n")] = '\0';

    // Create filename based on contact name
    sprintf(filename, "database/%s.txt", contact->name);

    // Replace spaces with underscores
    for (int i = 0; filename[i] != '\0'; i++) {
        if (filename[i] == ' ') {
            filename[i] = '_';
        }
    }

    FILE *fptr;
    open_file(&fptr, filename);

    fprintf(fptr, "Name: %s\n", contact->name);

    printf("Type the phone number of the contact to be added: ");
    fgets(contact->phone, sizeof(contact->phone), stdin);
    contact->phone[strcspn(contact->phone, "\n")] = '\0';
    fprintf(fptr, "Phone: %s\n", contact->phone);

    printf("Type the email of the contact to be added: ");
    fgets(contact->email, sizeof(contact->email), stdin);
    contact->email[strcspn(contact->email, "\n")] = '\0';
    fprintf(fptr, "Email: %s\n", contact->email);

    printf("Type the age of the contact to be added: ");
    fgets(contact->age, sizeof(contact->age), stdin);
    contact->age[strcspn(contact->age, "\n")] = '\0';
    fprintf(fptr, "Age: %s\n", contact->age);

    printf("Contact added successfully!\n");

    fclose(fptr);
}

void display_todo_list(FILE *fptr) {
    char line[100];

    if (fptr == NULL) {
        printf("Error opening file.\n");
        return;
    }

    printf("\n--- Contact Details ---\n");
    while (fgets(line, sizeof(line), fptr) != NULL) {
        printf("%s", line);
    }
    printf("------------------------\n\n");
}
