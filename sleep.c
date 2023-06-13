#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s seconds\n", argv[0]);
        return 1;
    }

    int sec = atoi(argv[1]);

    sleep(sec);

    printf("Done.\n");

    return 0;
}
