#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/stat.h>

int main(int argc, char *argv[])
{
    int opt;
    mode_t mode;
    bool verbose = false;

    while ((opt = getopt(argc, argv, "v")) != -1)
    {
        switch (opt)
        {
        case 'v':
            verbose = true;
            break;
        default:
            fprintf(stderr, "사용법: %s [-v] <모드> <파일>\n", argv[0]);
            return 1;
        }
    }

    if (argc - optind < 2)
    {
        fprintf(stderr, "사용법: %s [-v] <모드> <파일>\n", argv[0]);
        return 1;
    }

    mode = strtol(argv[optind], NULL, 8);
    char *path = argv[optind + 1];

    if (chmod(path, mode) == -1)
    {
        perror("chmod");
        return 1;
    }

    if (verbose)
    {
        printf("'%s' 파일의 접근 권한이 %03o 으로 변경되었습니다.\n", path, mode);
    }

    return 0;
}
