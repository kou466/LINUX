#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/stat.h>

int main(int argc, char *argv[])
{
    int opt;
    bool verbose = false;

    while ((opt = getopt(argc, argv, "v")) != -1)
    {
        switch (opt)
        {
        case 'v':
            verbose = true;
            break;
        default:
            fprintf(stderr, "사용법: %s [-v] <디렉토리 이름>\n", argv[0]);
            return 1;
        }
    }

    if (argc - optind < 1)
    {
        fprintf(stderr, "사용법: %s [-v] <디렉토리 이름>\n", argv[0]);
        return 1;
    }

    char *path = argv[optind];

    if (mkdir(path, 0755) == -1)
    {
        perror("mkdir");
        return 1;
    }

    if (verbose)
    {
        printf("'%s' 디렉토리가 생성되었습니다.\n", path);
    }

    return 0;
}
