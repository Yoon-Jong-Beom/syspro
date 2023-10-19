#include <stdio.h>
#include <string.h>
#include "copy.h"


int main(){
    char lines[5][MAXLINE];
    char longest[MAXLINE];
    int len;

    for (int i = 0; i < 5; ++i) {
        if (fgets(lines[i], sizeof(lines[i]), stdin) == NULL) {
            printf("Must read 5 sentances\n");
            return 1;
        }

        len = strlen(lines[i]);

        if (lines[i][len - 1] == '\n') {
            lines[i][len - 1] = '\0';
            len--;
        }
    }

    for (int i = 0; i < 4; ++i) {
        for (int j = i + 1; j < 5; ++j) {
            if (strlen(lines[i]) < strlen(lines[j])) {
                copy(lines[i], longest);
                copy(lines[j], lines[i]);
                copy(longest, lines[j]);
            }
        }
    }

    for (int i = 0; i < 5; ++i) {
        printf("%s\n", lines[i]);
    }

    return 0;
}
