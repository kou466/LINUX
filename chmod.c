#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("사용법: %s <파일 또는 디렉토리> <모드>\n", argv[0]);
        return 1;
    }

    const char *path = argv[1];
    int mode = strtol(argv[2], NULL, 8);

    if (chmod(path, mode) == 0) {
        printf("성공적으로 모드를 변경했습니다: %s\n", argv[1]);
    } else {
        printf("모드 변경 실패: %s\n", argv[1]);
        return 1;
    }

    return 0;
}

