#include <stdio.h>
#include <string.h>
#include <dirent.h>

struct Contact{
    char name[50];
    char phone[15];
    char email[50];
    char age[4];
};

void add_contact(struct Contact* contact); 

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
        } 
        else if (option < 1 || option > 5) {
            printf("Only choose 1, 2, 3, 4 or 5.\n");
            continue;
        } 
        else {
            while (getchar() != '\n');
            switch (option)
            {
            case 1:
                add_contact(&contact1);
                break;
            
            case 2:
                char name[50];

                printf("Type the name of the contact: \n");
                fgets(name, sizeof(name), stdin);
                name[strcspn(name, "\n")] = '\0';

                rewinddir(d);
                while ((f = readdir(d))) {
                    for(int i = 0; f->d_name[i] != '\0'; i++) {
                        if(f->d_name[i] == '_') {
                            f->d_name[i] = ' ';
                        }
                    }
                    char *ext = strrchr(f->d_name, '.'); //pointer to a string that starts at the "." so ext=".txt"
                    if (ext && strcmp(ext, ".txt") == 0) {
                        *ext = '\0';
                    }
                    printf("Checking contact: %s\n", f->d_name);
                    if (strcmp(f->d_name, name) == 0) {
                        printf("Contact found:\n");
                    }
                }

                closedir(d);
                break;  
            
            case 3:
                printf("Type the name of the contact to be edited: \n");
                break;

            case 4:
                printf("Type the name of the contact to be deleted: \n");
                break;

            case 5:
                printf("Exiting program.\n");
                return 0;
            }
 
        }
    }

    return 0;
}

void add_contact(struct Contact* contact) {
    char filename[100];

    printf("Type the name of the contact to be added: \n");
    fgets(contact->name, sizeof(contact->name), stdin);
    contact->name[strcspn(contact->name, "\n")] = '\0';

    // Create filename based on contact name
    sprintf(filename, "database/%s.txt", contact->name);
    
    // Replace spaces with underscores
    for(int i = 0; filename[i] != '\0'; i++) {
        if(filename[i] == ' ') {
            filename[i] = '_';
        }
    }

    FILE *fptr = fopen(filename, "r+");
    if(fptr == NULL) //if file does not exist, create it
    {
        fptr = fopen(filename, "w+");
    }

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

    fclose(fptr);
}
