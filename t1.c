#include <stdio.h>
#include <stdlib.h>

int get_valid_int(const char *prompt) {
    int value;
    char term;

    while (1) {
        printf("%s", prompt);

        // Try to read an integer followed by a character
        if (scanf("%d%c", &value, &term) == 2 && term == '\n') {
            return value;  // Valid integer input
        } else {
            printf("Error: Please enter a valid integer.\n");

            // Clear invalid input from buffer
            while (getchar() != '\n');
        }
    }
}

int main() {
    int v1 = get_valid_int("Enter v1: ");
    int v2 = get_valid_int("Enter v2: ");
    int v3 = get_valid_int("Enter v3: ");

    printf("You entered: v1 = %d, v2 = %d, v3 = %d\n", v1, v2, v3);

    // Save to binary file
    FILE *fp = fopen("data.bin", "wb");
    if (fp == NULL) {
        perror("Failed to open file");
        return 1;
    }

    fwrite(&v1, sizeof(int), 1, fp);
    fwrite(&v2, sizeof(int), 1, fp);
    fwrite(&v3, sizeof(int), 1, fp);
    fclose(fp);

    printf("Values saved to binary file.\n");

    return 0;
}
