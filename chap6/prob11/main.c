#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <grp.h>
#include <pwd.h>
#include <dirent.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

char type(mode_t);
char *perm(mode_t);
void printStat(char*, char*, struct stat*, int, int, int);

int main(int argc, char **argv) {
    DIR *dp;
    char *dir;
    struct stat st;
    struct dirent *d;
    char path[BUFSIZ+1];
    int showInode = 0;
    int showSlash = 0;
    int showQuotes = 0;

    // Parse command-line options
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-i") == 0) {
            showInode = 1;
        } else if (strcmp(argv[i], "-p") == 0) {
            showSlash = 1;
        } else if (strcmp(argv[i], "-Q") == 0) {
            showQuotes = 1;
        } else {
            dir = argv[i];
        }
    }

    if (dir == NULL)
        dir = ".";

    if ((dp = opendir(dir)) == NULL)
        perror(dir);

    while ((d = readdir(dp)) != NULL) {
        sprintf(path, "%s/%s", dir, d->d_name);
        if (lstat(path, &st) < 0)
            perror(path);
        else
            printStat(path, d->d_name, &st, showInode, showSlash, showQuotes);
    }

    closedir(dp);
    exit(0);
}

void printStat(char *pathname, char *file, struct stat *st, int showInode, int showSlash, int showQuotes) {
    if (showInode) {
        printf("%lu ", st->st_ino);
    }

    if (showQuotes) {
        printf("\"%s\" ", file);
    } else {
        printf("%s ", file);
    }

    if (showSlash && S_ISDIR(st->st_mode)) {
        printf("/ ");
    } else {
        printf(" ");
    }

    printf("%c%s ", type(st->st_mode), perm(st->st_mode));
    printf("%3d ", st->st_nlink);
    printf("%s %s ", getpwuid(st->st_uid)->pw_name, getgrgid(st->st_gid)->gr_name);
    printf("%9ld ", st->st_size);
    printf("%.12s ", ctime(&st->st_mtime) + 4);
    printf("\n");
}

char type(mode_t mode) {
    if (S_ISREG(mode))
        return '-';
    if (S_ISDIR(mode))
        return 'd';
    if (S_ISCHR(mode))
        return 'c';
    if (S_ISBLK(mode))
        return 'b';
    if (S_ISLNK(mode))
        return 'l';
    if (S_ISFIFO(mode))
        return 'p';
    if (S_ISSOCK(mode))
        return 's';
}

char *perm(mode_t mode) {
    static char perms[10];
    strcpy(perms, "---------");

    for (int i = 0; i < 3; i++) {
        if (mode & (S_IRUSR >> i * 3))
            perms[i * 3] = 'r';
        if (mode & (S_IWUSR >> i * 3))
            perms[i * 3 + 1] = 'w';
        if (mode & (S_IXUSR >> i * 3))
            perms[i * 3 + 2] = 'x';
    }
    return (perms);
}
