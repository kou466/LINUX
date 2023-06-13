#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("사용법: %s <파일 또는 디렉토리> [<파일 또는 디렉토리> ...]\n", argv[0]);
        return 1;
    }

    for (int i = 1; i < argc; ++i) {
 if (remove(argv[i]) == 0) {
            printf("'%s' 파일 또는 디렉토리가 성공적으로 삭제되었습니다.\n", argv[i]);
        } else {
            printf("'%s' 파일 또는 디렉토리를 삭제할 수 없습니다.\n", argv[i]);
        }
    }

    return 0;
}

