#include <stdio.h>
#include <utime.h>
#include <time.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("사용법: %s <파일>\n", argv[0]);
        return 1;
    }

    FILE *file = fopen(argv[1], "a");
    if (file == NULL) {
        printf("파일을 생성할 수 없습니다.\n");
        return 1;
    }

    fclose(file);

    struct utimbuf ut;
    ut.actime = ut.modtime = time(NULL);

    if (utime(argv[1], &ut) == -1) {
        printf("파일의 수정 시간을 업데이트할 수 없습니다.\n");
        return 1;
    }

    printf("파일이 생성되거나 수정 시간이 업데이트 되었습니다.\n");

    return 0;
}

