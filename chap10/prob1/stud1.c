#include <stdio.h>
#include <stdlib.h>

struct student {
    int id;
    char name[20];
};

/* Program to input the number of students, input their information,
   and then print the information in reverse order. */
int main() {
    struct student *ptr; // Pointer to dynamically allocated block
    int n, i;

    printf("How many students do you want to input? ");
    scanf("%d", &n);
    if (n <= 0) {
        fprintf(stderr, "Error: Invalid number of students entered.\n");
        fprintf(stderr, "Exiting the program.\n");
        exit(1);
    }

    ptr = (struct student *)malloc(n * sizeof(struct student));
    if (ptr == NULL) {
        perror("malloc");
        exit(2);
    }

    printf("Enter the ID and name for %d students.\n", n);
    for (i = 0; i < n; i++)
        scanf("%d %s", &ptr[i].id, ptr[i].name);

    printf("\n* Student Information (Reversed) *\n");
    for (i = n - 1; i >= 0; i--)
        printf("%d %s\n", ptr[i].id, ptr[i].name);

    printf("\n");
    free(ptr); // Free the dynamically allocated memory
    exit(0);
}

