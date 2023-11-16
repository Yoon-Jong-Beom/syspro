#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <-e[env_name] | -u | -g | -i | -p>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    char option = argv[1][1];

    switch (option) {
        case 'e': {
            if (argc < 3 || argv[2][0] == '-') {
                extern char **environ;
                for (char **env = environ; *env != NULL; env++) {
                    printf("%s\n", *env);
                }
                break;
            }

            char *env_name = argv[2];
            char *env_value = getenv(env_name);

            if (env_value == NULL) {
                fprintf(stderr, "Environment variable %s not found.\n", env_name);
            } else {
                printf("%s=%s\n", env_name, env_value);
            }

            break;
        }

        case 'u':
            printf("Real UID: %d\nEffective UID: %d\n", getuid(), geteuid());
            break;

        case 'g':
            printf("Real GID: %d\nEffective GID: %d\n", getgid(), getegid());
            break;

        case 'i':
            printf("Process ID: %d\n", getpid());
            break;

        case 'p':
            printf("Parent Process ID: %d\n", getppid());
            break;

        default:
            {
                extern char **environ;
                for (char **env = environ; *env != NULL; env++) {
                    printf("%s\n", *env);
                }
            }
    }

    return 0;
}
