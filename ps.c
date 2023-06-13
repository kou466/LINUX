#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    int opt;
    char cmd[1024];

    sprintf(cmd, "ps");

    while ((opt = getopt(argc, argv, "aux")) != -1) {
        switch (opt) {
            case 'a':
                sprintf(cmd, "%s -a", cmd);
                break;
            case 'u':
                sprintf(cmd, "%s -u", cmd);
                break;
            case 'x':
                sprintf(cmd, "%s -X", cmd);
                break;
            default:
                printf("Usage: %s [-a] [-u] [-x]\n", argv[0]);
                return 1;
        }
    }

    system(cmd);

    return 0;
}
