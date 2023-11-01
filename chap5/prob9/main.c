#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINES 100
#define MAX_LINE_LENGTH 100

int main(int argc, char *argv[]) {
    if (argc != 2) {
        return 1;
    }

    char lines[MAX_LINES][MAX_LINE_LENGTH];
    char *filename = argv[1];
    
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Failed to open the file");
        return 1;
    }

    int totalLines = 0;
    while (fgets(lines[totalLines], MAX_LINE_LENGTH, file) != NULL) {
        totalLines++;
    }

    fclose(file);

    for (int i = totalLines - 1; i >= 0; i--) {
        printf("%s", lines[i]);
    }

    return 0;
}
