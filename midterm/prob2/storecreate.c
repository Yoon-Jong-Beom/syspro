1 #include <stdio.h>
  2 #include "student.h"
  3
  4 int main(int argc, char* argv[])
  5 {
  6    struct student rec;
  7    FILE *fp;
  8
  9    if (argc != 2) {
 10       fprintf(stderr, "How to use: %s FileName\n",argv[0]);
 11       exit(1);
 12    }
 13
 14    fp = fopen(argv[1], "w");
 15    printf("%-13s %-11s %-9s\n %-7s\n %-5s\n", "id", "name", "category",
 16            "exired date", "stock");
 17    while (scanf("%d %s %s %d %d", &rec.id, rec.name,rec.category,
 18           &rec.expired date, &rec.stock) == 5)
 19       fwrite(&rec, sizeof(rec), 1, fp);
 20
 21    fclose(fp);
 22    exit(0);
 23 }

