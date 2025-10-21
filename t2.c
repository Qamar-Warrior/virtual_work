#include <stdio.h>

int main() {
    int v1, v2, v3;

    // Open the binary file for reading
    FILE *fp = fopen("data.bin", "rb");
    if (fp == NULL) {
        perror("Error opening file");
        return 1;
    }

    // Read the three integers
    fread(&v1, sizeof(int), 1, fp);
    fread(&v2, sizeof(int), 1, fp);
    fread(&v3, sizeof(int), 1, fp);
    fclose(fp);

    // Perform calculations
    int result1 = v1 + v2 - v3;
    int result2 = v1 + v2 + v3;

    // Print results
    printf("v1 + v2 - v3 = %d\n", result1);
    printf("v1 + v2 + v3 = %d\n", result2);

    return 0;
}
