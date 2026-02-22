# include <stdio.h>
# include <string.h>
# include <ctype.h>
# include <stdbool.h>

void input_validation(int *escolha);
void word_val(unsigned char *word, size_t size);
void space_val(unsigned char *word, char *key, char *key_, int key_len, int word_len);
void to_upper(unsigned char *word);

int main() {
    int option;

    printf("Which cypher would you like to use?\n");
    printf("Digite 1 para Caesar cypher\n");
    printf("Digite 2 para XOR\n");
    printf("Digite 3 Vinegere\n");

    while (1) {
        if (scanf("%d", &option) != 1) {
            printf("Please type in a number\n");
            while (getchar() != '\n');
            continue;
        }

        if (option > 3 || option < 1) {
            printf("Only 1, 2 or 3 are valid inputs\n");
            while (getchar() != '\n');
            continue;
        }
        break;
    }

    switch (option) {
        case 1: {
            char word[256];
            char buffer[256];
            int escolha;
            int i;

            printf("1 - Encode\n");
            printf("2 - Decode\n");

            input_validation(&escolha);

            if (escolha == 1) {
                while (getchar() != '\n'); // Clear the newline left by scanf
                printf("Type in the word you want to encode\n");
                fgets(word, sizeof(word), stdin);
                word[strcspn(word, "\n")] = '\0';

                for (i = 0; word[i] != '\0'; i++){
                    if ((word[i] >= 'A' && word[i] <= 'Z') || (word[i] >= 'a' && word[i] <= 'z')){
                        buffer[i] = word[i] + 3;
                    } else {
                        buffer[i] = word[i];
                    }
                }
                buffer[i] = '\0'; 

            } else {
                while (getchar() != '\n');
                printf("Type in the word you want to decode\n");
                fgets(word, sizeof(word), stdin);
                word[strcspn(word, "\n")] = '\0';

                for (i = 0; word[i] != '\0'; i++){
                    if ((word[i] >= 'A' && word[i] <= 'Z') || (word[i] >= 'a' && word[i] <= 'z')){
                        buffer[i] = word[i] - 3;
                    } else {
                        buffer[i] = word[i];
                    }
                }
                buffer[i] = '\0';
            }

            printf("%s\n", buffer);
            break;
        }

        case 2: {
            printf("XOR com chave repetida, to be implemented\n");

            unsigned char word[256];
            unsigned char buffer[256];
            unsigned char _buffer[256];
            char hex[256];
            int key = 111;
            int escolha;
            int i;
            int j;
            int num;

            printf("1 - Encode\n");
            printf("2 - Decode\n");

            input_validation(&escolha);

            if (escolha == 1) {
                while (getchar() != '\n'); // Clear the newline left by scanf
                printf("Type in the word you want to encode\n");
                fgets(word, sizeof(word), stdin);
                word[strcspn(word, "\n")] = '\0';

                for (i = 0; word[i]; i++) {
                    if ((word[i] >= 'A' && word[i] <= 'Z') || (word[i] >= 'a' && word[i] <= 'z')){
                        buffer[i] = word[i] ^ key;
                    } else {
                        buffer[i] = word[i];
                    }
                }
                
                buffer[i] = '\0';

                printf("Buffer:\n");
                for (int i = 0; buffer[i]; i++) {
                    printf("%02x ", buffer[i]);
                }
                printf("\n");

            } else {

                while (getchar() != '\n');
                printf("Use groups of 2, for example:\n1a2b\n");
                printf("If you do like:\n1a5\n");
                printf("IT IS NOT GOING TO WORK\n");
                printf("Type in the word you want to decode.\n");

                while (1) {
                    fgets(word, sizeof(word), stdin);
                    word[strcspn(word, "\n")] = '\0';

                    if (strlen(word)%2 != 0) {
                        printf("The codified word is invalid. Try again\n");
                        continue;
                    } else {
                        break;
                    }
                }
                
                j = 0;
                for (i=0; word[i] && word[i+1]; i+=2) {
                    hex[0] = word[i];
                    hex[1] = word[i+1];
                    hex[2] = '\0';
                    sscanf(hex, "%x", &num);

                    buffer[j++] = num ^ key;
                }
                buffer[j] = '\0';

                printf("%s\n", buffer);
            }

            break;
        }

        case 3: {
            unsigned char word[256];
            unsigned char cyphered_word[256];
            char key[] = "VINEGERE";
            char key_[256];
            char buffer[256];
            int has_accent = 0;
            int escolha;
            int word_pos;
            int key_pos;
            int cypher_pos;
            int i;

            
            printf("1 - Encode\n");
            printf("2 - Decode\n");

            input_validation(&escolha);

            if (escolha == 1) {
                while (getchar() != '\n');
                printf("Type in the text you want to encode: \n");

                word_val(word, sizeof(word));

                to_upper(word);

                int key_len  = strlen(key);
                int word_len = strlen(word);

                space_val(word, key, key_, key_len, word_len);

                key_[word_len] = '\0';

                for (i=0; word[i]; i++) {                  
                    if (word[i] == ' ') {
                        cyphered_word[i] = ' ';
                    } else {
                        word_pos   = word[i] - 'A';
                        key_pos    = key_[i] - 'A';
                        cypher_pos = (word_pos + key_pos) % 26;
                    
                        cyphered_word[i] = cypher_pos + 'A';
                    }
                }
                cyphered_word[i] = '\0';

                printf("%s\n", cyphered_word);
            } else {
                while (getchar() != '\n');
                printf("Type in the text you want to decode: \n");

                word_val(word, sizeof(word));

                to_upper(word);

                int key_len  = strlen(key);
                int word_len = strlen(word);

                space_val(word, key, key_, key_len, word_len);

                key_[word_len] = '\0';

                for (i=0; word[i]; i++) {                  
                    if (word[i] == ' ') {
                        cyphered_word[i] = ' ';
                    } else {
                        word_pos   = word[i] - 'A';
                        key_pos    = key_[i] - 'A';
                        cypher_pos = (word_pos - key_pos + 26) % 26;
                    
                        cyphered_word[i] = cypher_pos + 'A';
                    }
                }
                cyphered_word[i] = '\0';

                printf("%s\n", cyphered_word);
            }

        }
    } 
}

void input_validation(int *escolha) {
    while (1) {
        if (scanf("%d", escolha) != 1) {
            printf("Only numbers, please\n");
            while (getchar() != '\n');
            continue;
        }

        if (*escolha < 1 || *escolha > 2) {
            printf("Only choose 1 or 2");
            while(getchar() != '\n');
            continue;
        }
        break;
    }
}

void word_val(unsigned char *word, size_t size) {
    int has_accent;
    int i;

    while (1) {
        fgets(word, size, stdin);
        word[strcspn(word, "\n")] = '\0';
        
        has_accent = 0;
        for (i = 0; word[i]; i++){
            if (word[i] > 127) {
                printf("Please do not use accents. Type in again:\n");
                has_accent = 1;
                break;
            }
        }
        if (has_accent) {
            continue;
        }
        break;
    }
}

void space_val(unsigned char *word, char *key, char *key_, int key_len, int word_len) {
    int i;
    int j = 0;
    
    for (i=0; i < (word_len); i++) {
        if (word[i] == ' ') {
            key_[i] = ' ';
        } else {
            key_[i] = key[j % key_len];
            j++;
        }
    }
}

void to_upper(unsigned char *word) {
    int i; 
    
    for (i=0; word[i]; i++) {
        word[i] = toupper(word[i]);
    }
}

