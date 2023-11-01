#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINES 10
#define MAX_LINE_LENGTH 100

void readTextFile(const char *filename, char text[MAX_LINES][MAX_LINE_LENGTH], int *totalLines);
void printLines(char text[MAX_LINES][MAX_LINE_LENGTH], char *option, int totalLines);

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <text file path>\n", argv[0]);
        return 1;
    }

    char savedText[MAX_LINES][MAX_LINE_LENGTH];
    int totalLines = 0;
    char *filename = argv[1];
    readTextFile(filename, savedText, &totalLines);

    printf("Total Line: %d\n", totalLines);

    printf("You can choose from 1 ~ %d Line\n", totalLines);
    printf("Please 'Enter' the line to select: ");
    
    char option[100];
    scanf("%s", option);

    printLines(savedText, option, totalLines);

    return 0;
}

// Function to read the text file
void readTextFile(const char *filename, char text[MAX_LINES][MAX_LINE_LENGTH], int *totalLines) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Failed to open the file");
        exit(1);
    }

    int line = 0;
    while (line < MAX_LINES && fgets(text[line], MAX_LINE_LENGTH, file) != NULL) {
        line++;
    }
    *totalLines = line;

    fclose(file);
}

// Function to print lines based on the option
void printLines(char text[MAX_LINES][MAX_LINE_LENGTH], char *option, int totalLines) {
    if (strcmp(option, "*") == 0) {
        for (int i = 0; i < totalLines; i++) {
            printf("%s", text[i]);
        }
    } else if (strchr(option, ',') != NULL) {
        char *token = strtok(option, ",");
        while (token != NULL) {
            int line = atoi(token);
            if (line >= 1 && line <= totalLines) {
                printf("%s", text[line - 1]);
            }
            token = strtok(NULL, ",");
        }
    } else if (strchr(option, '-') != NULL) {
        char *rangeStart = strtok(option, "-");
        char *rangeEnd = strtok(NULL, "-");
        int start = atoi(rangeStart);
        int end = atoi(rangeEnd);
        if (start >= 1 && end >= start && end <= totalLines) {
            for (int i = start; i <= end; i++) {
                printf("%s", text[i - 1]);
            }
        }
    } else {
        int line = atoi(option);
        if (line >= 1 && line <= totalLines) {
            printf("%s", text[line - 1]);
        } else {
            printf("Invalid option.\n");
        }
    }
}
