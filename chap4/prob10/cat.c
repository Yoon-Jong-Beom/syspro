#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

int main(int argc, char *argv[]) {
    FILE *fp;
    int c;
    int line_number = 1;
    bool print_line_numbers = false;

    // Check for the -n option
    if (argc > 1 && strcmp(argv[1], "-n") == 0) {
        print_line_numbers = true;
        argc--;
        argv++;
    }

    if (argc < 2) {
        fprintf(stderr, "Usage: %s [-n] file1 file2 file3 ...\n", argv[0]);
        return 1;
    }

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-") == 0) {
            fp = stdin;
        } else {
            fp = fopen(argv[i], "r");
            if (fp == NULL) {
                fprintf(stderr, "Error opening file %s\n", argv[i]);
                continue;
            }
        }

        c = getc(fp);
        bool new_line = true;

        while (c != EOF) {
            if (print_line_numbers && new_line) {
                printf("%6d  ", line_number);
                line_number++;
                new_line = false;
            }

            putc(c, stdout);
            if (c == '\n') {
                new_line = true;
            }

            c = getc(fp);
        }

        if (fp != stdin) {
            fclose(fp);
        }
    }

    return 0;
}

