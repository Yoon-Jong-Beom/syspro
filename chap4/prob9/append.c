#include <stdio.h>

int main(int argc, char *argv[]) {
    char c;
    FILE *fp1, *fp2;

    if (argc != 3) {
        fprintf(stderr, "How to use: %s File1 File2\n", argv[0]);
        return 1;
    }

    fp1 = fopen(argv[1], "r");
    if (fp1 == NULL) {
        fprintf(stderr, "File %s Open Error\n", argv[1]);
        return 2;
    }

    fp2 = fopen(argv[2], "at");
    if (fp2 == NULL) {
        fprintf(stderr, "File %s Open Error\n", argv[2]);
        fclose(fp1);
        return 3;
    }

    while ((c = fgetc(fp1)) != EOF) {
        if (fputc(c, fp2) == EOF) {
            fprintf(stderr, "Error writing to %s\n", argv[2]);
            break;
        }
    }
	fclose(fp2);
    fclose(fp1);
    if (fclose(fp2) != 0) {
        fprintf(stderr, "Error closing %s\n", argv[2]);
        return 4;
    }
    return 0;
}
