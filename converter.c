#include <stdio.h>
#include <stdlib.h>

float celsius_to_fahrenheit(float celsius);
float fahrenheit_to_celsius(float fahrenheit);

int main() {
    float temperature = 0;
    int option = 0;

    printf("Choose conversion option:\n");
    printf("1. Celsius to Fahrenheit\n");
    printf("2. Fahrenheit to Celsius\n");

    while (1) {
        printf("Enter option (1 or 2): ");
        
        if (scanf("%d", &option) != 1) {
            printf("Invalid input. Please enter a number.\n");
            while (getchar() != '\n');  // Clear input buffer
            continue;
        }

        if (option == 1 || option == 2) {
            break;
        } else {
            printf("Only choose 1 or 2.\n");
        }
    }

    while (1) {
        if (option == 1) {
            printf("Enter temperature in Celsius: ");
        } else {
            printf("Enter temperature in Fahrenheit: ");
        }

        if (scanf("%f", &temperature) != 1) {
            printf("Invalid input. Please enter a number.\n");
            while (getchar() != '\n');  // Clear input buffer
            continue; // Jump back to start of loop
        }
        
        break; 
    }

    if (option == 1) {
        float fahrenheit = celsius_to_fahrenheit(temperature);
        printf("%.2f Celsius is %.2f Fahrenheit\n", temperature, fahrenheit);
    } else {
        float celsius = fahrenheit_to_celsius(temperature);
        printf("%.2f Fahrenheit is %.2f Celsius\n", temperature, celsius);
    }

    return 0;
}

float celsius_to_fahrenheit(float celsius) {
    return (celsius * 9.0 / 5.0) + 32.0;
}

float fahrenheit_to_celsius(float fahrenheit) {
    return (fahrenheit - 32.0) * 5.0 / 9.0;
}