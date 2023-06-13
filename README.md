# LINUX

---

## 목차

1. 개요
2. 각 코드에 대한 설명
3. 출처

---

### 1. 개요

대학 강의 시간에 시스템 프로그래밍을 배우면서 리눅스 명령어를 실제로 구현하는 프로젝트가 생겨 만들게 됨

### 2. 각 코드에 대한 설명

- cat : ./cat [파일] : 선택한 파일의 내용을 보여줌

```c
#include <stdio.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("사용법: %s <파일>\n", argv[0]);
        return 1;
    }

    FILE *file = fopen(argv[1], "r");
    if (file == NULL) {
        printf("파일을 열 수 없습니다.\n");
        return 1;
    }

    int ch;
    while ((ch = fgetc(file)) != EOF) {
        putchar(ch);
    }

    fclose(file);

    return 0;
}
```

- chmod : ./chmod [mode] [file] : 파일의 모드를 변환함
  - 각 옵션에 대한 설명
    - ./chmod -v : 실행 과정을 자세하게 보여준다.

```c
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

```

- clear : ./clear : 현재 화면을 지움

```c
#include <stdio.h>
#include <stdlib.h>

int main() {
    system("clear");
    return 0;
}
```

- cmp : ./cmp [file1] [file2] : file1과 file2를 비교하여 어떤 부분이 다른지 확인 가능

```c
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        fprintf(stderr, "사용법: %s [파일1] [파일2]\n", argv[0]);
        return 1;
    }

    FILE *fp1, *fp2;
    fp1 = fopen(argv[1], "rb");
    fp2 = fopen(argv[2], "rb");

    if (!fp1 || !fp2)
    {
        perror("fopen");
        return 1;
    }

    int byte_pos = 0;
    bool files_match = true;
    while (true)
    {
        int char1 = fgetc(fp1);
        int char2 = fgetc(fp2);

        byte_pos++;

        if (char1 == EOF && char2 == EOF)
        {
            break;
        }

        if (char1 != char2)
        {
            files_match = false;
            printf("%s %s differ: byte %d\n", argv[1], argv[2], byte_pos);
            break;
        }
    }

    fclose(fp1);
    fclose(fp2);

    if (files_match)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

```

- cp : ./cp source target: source 파일을 target파일로 복사함

```c
#include <stdio.h>

int main(int argc, char *argv[])
{
    char c;
    FILE *fp1, *fp2;
    if (argc != 3)
    {
        fprintf(stderr, "사용법: %s 파일1 파일2\n", argv[0]);
        return 1;
    }
    fp1 = fopen(argv[1], "r");
    if (fp1 == NULL)
    {
        fprintf(stderr, "파일 %s 열기 오류\n", argv[1]);
        return 2;
    }
    fp2 = fopen(argv[2], "w");
    while ((c = fgetc(fp1)) != EOF)
        fputc(c, fp2);
    fclose(fp1);
    fclose(fp2);
    return 0;
}

```

- date : ./date : 현재 날짜와 시간을 표시

```c
#include <stdio.h>
#include <time.h>

int main() {
  time_t rawtime;
  struct tm *timeinfo;

  time(&rawtime);
  timeinfo = localtime(&rawtime);

  printf("%s", asctime(timeinfo));

  return 0;
}
```

- echo : ./echo [텍스트 및 문자열] : 입력한 문자를 그대로 출력

```c
#include <stdio.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <문자열>\n", argv[0]);
        return 1;
    }

    for (int i = 1; i < argc; i++) {
        printf("%s ", argv[i]);
    }
    printf("\n");

    return 0;
}
```

- kill : ./kill : 실행중인 프로세스 id를 시그널(종료 신호)을 이용하여 종료 가능

```c
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <Signal> <PID>\n", argv[0]);
        return 1;
    }

    int signal_number = atoi(argv[1]);
    pid_t process_id = (pid_t)atoi(argv[2]);

    if (kill(process_id, signal_number) == -1) {
        perror("kill");
        return 1;
    }
    return 0;
}
```

- ls : ./ls [-l] [-a] [-h] [-R] [디렉토리]: 선택된 디렉토리의 리스트를 보여줌
  - 각 옵션에 대한 설명
    - ./ls -l : 파일들을 나열할 때 자세히 출력
    - ./ls -a : 경로안의 모든 파일들을 나열함(숨김파일 포함)
    - ./ls -h : 파일크기를 보기 편하게 출력
    - ./ls -R : 위치한 디렉토리 하위 디렉토리의 파일까지 모두 출력

```c
#include <dirent.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>

void list_directory(const char *path, bool l_flag, bool a_flag, bool h_flag, bool R_flag);

void display_info(const char *path, const struct dirent *entry, bool h_flag);

int main(int argc, char *argv[])
{
    int opt;
    bool l_flag = false;
    bool a_flag = false;
    bool h_flag = false;
    bool R_flag = false;

    while ((opt = getopt(argc, argv, "lahR")) != -1)
    {
        switch (opt)
        {
        case 'l':
            l_flag = true;
            break;
        case 'a':
            a_flag = true;
            break;
        case 'h':
            h_flag = true;
            break;
        case 'R':
            R_flag = true;
            break;
        default:
            printf("Usage: %s [-l] [-a] [-h] [-R] [directory]\n", argv[0]);
            return 1;
        }
    }

    const char *path = ".";
    if (optind < argc)
    {
        path = argv[optind];
    }

    list_directory(path, l_flag, a_flag, h_flag, R_flag);
    return 0;
}

void list_directory(const char *path, bool l_flag, bool a_flag, bool h_flag, bool R_flag)
{
    DIR *dir;
    struct dirent *entry;
    struct stat file_stat;

    if ((dir = opendir(path)) == NULL)
    {
        perror("opendir");
        return;
    }

    while ((entry = readdir(dir)) != NULL)
    {
        if (entry->d_name[0] == '.' && !a_flag)
        {
            continue;
        }

        if (l_flag)
        {
            char full_path[1024];
            snprintf(full_path, sizeof(full_path), "%s/%s", path, entry->d_name);
            stat(full_path, &file_stat);
            display_info(full_path, entry, h_flag);
        }
        else
        {
            printf("%s\n", entry->d_name);
        }

        if (R_flag && entry->d_type == DT_DIR)
        {
            char new_path[1024];
            if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0)
            {
                snprintf(new_path, sizeof(new_path), "%s/%s", path, entry->d_name);
                printf("\n%s:\n", new_path);
                list_directory(new_path, l_flag, a_flag, h_flag, R_flag);
            }
        }
    }

    closedir(dir);
}

void display_info(const char *path, const struct dirent *entry, bool h_flag)
{
    struct stat file_stat;
    stat(path, &file_stat);

    printf((S_ISDIR(file_stat.st_mode)) ? "d" : "-");
    printf((file_stat.st_mode & S_IRUSR) ? "r" : "-");
    printf((file_stat.st_mode & S_IWUSR) ? "w" : "-");
    printf((file_stat.st_mode & S_IXUSR) ? "x" : "-");
    printf((file_stat.st_mode & S_IRGRP) ? "r" : "-");
    printf((file_stat.st_mode & S_IWGRP) ? "w" : "-");
    printf((file_stat.st_mode & S_IXGRP) ? "x" : "-");
    printf((file_stat.st_mode & S_IROTH) ? "r" : "-");
    printf((file_stat.st_mode & S_IWOTH) ? "w" : "-");
    printf((file_stat.st_mode & S_IXOTH) ? "x" : "-");

    printf(" %ld", file_stat.st_nlink);

    struct passwd *pw = getpwuid(file_stat.st_uid);
    struct group *gr = getgrgid(file_stat.st_gid);
    printf(" %s %s", pw->pw_name, gr->gr_name);

    if (h_flag)
    {
        float size = file_stat.st_size;
        const char *unit = "B";
        if (size > 1024)
        {
            size /= 1024;
            unit = "KB";
        }
        if (size > 1024)
        {
            size /= 1024;
            unit = "MB";
        }
        if (size > 1024)
        {
            size /= 1024;
            unit = "GB";
        }
        printf(" %6.2f %s", size, unit);
    }
    else
    {
        printf(" %6ld", file_stat.st_size);
    }

    char time_str[18];
    strftime(time_str, sizeof(time_str), "%Y-%m-%d %H:%M", localtime(&file_stat.st_mtime));
    printf(" %s", time_str);

    printf(" %s\n", entry->d_name);
}
```

- mkdir : ./mkdir [디렉토리] : 작성한 디렉토리 이름으로 디렉토리 생성
  - 각 옵션에 대한 설명
    - ./mkdir -v : 실행 과정을 자세하게 보여준다.

```c
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

```

- mv : ./mv [source] [target]: source를 target으로 이름을 변경함

```c
#include <stdio.h>

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("사용법: %s <소스> <대상>\n", argv[0]);
        return 1;
    }

    if (rename(argv[1], argv[2]) != 0) {
        printf("이름을 변경할 수 없습니다.\n");
        return 1;
    }

    printf("이름이 변경되었습니다.\n");

    return 0;
}
```

- pwd : ./pwd : 현재 작업중인 디렉토리 경로를 출력

```c
#include <stdio.h>
#include <unistd.h>

int main() {
    char cwd[1024];

    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        printf("현재 작업 중인 디렉토리: %s\n", cwd);
    } else {
        printf("디렉토리 경로를 가져올 수 없습니다.\n");
        return 1;
    }

    return 0;
}
```

- rev : ./rev [file] : 파일을 행 단위로 읽어 각 행의 문자를 역순으로 출력

```c
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void reverse_string(char *str)
{
    size_t len = strlen(str);
    char temp;
    for (size_t i = 0; i < len / 2; i++)
    {
        temp = str[i];
        str[i] = str[len - 1 - i];
        str[len - 1 - i] = temp;
    }
}

int main(int argc, char *argv[])
{
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    FILE *file;

    if (argc == 1)
    {
        file = stdin;
    }
    else
    {
        file = fopen(argv[1], "r");
        if (!file)
        {
            perror("fopen");
            return 1;
        }
    }

    // 파일의 각 줄 뒤집기
    while ((read = getline(&line, &len, file)) != -1)
    {
        reverse_string(line);
        printf("%s", line);
    }

    fclose(file);
    free(line);
    return 0;
}
```

- rm : ./rm [File or Directory] : 파일을 삭제함

```c
#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("사용법: %s <파일> [<파일> ...]\n", argv[0]);
        return 1;
    }

    for (int i = 1; i < argc; ++i) {
        if (remove(argv[i]) == 0) {
            printf("'%s' 파일이 성공적으로 삭제되었습니다.\n", argv[i]);
        } else {
            printf("'%s' 파일을 삭제할 수 없습니다.\n", argv[i]);
        }
    }

    return 0;
}
```

- rmdir : ./rmdir [디렉토리] : 디렉토리를 삭제함
  - 각 옵션에 대한 설명
    - ./rmdir -v : 실행 과정을 자세하게 보여준다.

```c
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>

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
            fprintf(stderr, "사용법: %s [-v] <디렉토리>\n", argv[0]);
            return 1;
        }
    }

    if (argc - optind < 1)
    {
        fprintf(stderr, "사용법: %s [-v] <디렉토리>\n", argv[0]);
        return 1;
    }

    char *path = argv[optind];

    if (rmdir(path) == -1)
    {
        perror("rmdir");
        return 1;
    }

    if (verbose)
    {
        printf("'%s' 디렉토리가 삭제되었습니다.\n", path);
    }

    return 0;
}

```

- sleep : ./sleep [Seconds] : 지정한 시간만큼 프로세스를 일시 중단

```c
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
```

- touch : ./touch [파일] : 파일의 수정 시간을 현재 시간을 업데이트 하거나, 파일이 없다면 새로 만듦

```c
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

    return 0;
}
```

- uname : ./uname [-s] [-r] [-v] [-m] [-p] [-o] : 운영체제에 대한 이름, 시스템 정보, 커널 정보 등을 확인
  - 각 옵션에 대한 설명
    - ./uname -s : 커널의 이름을 출력
    - ./uname -r : 커널의 릴리즈 정보를 출력
    - ./uname -v : 커널의 버전을 출력
    - ./uname -m : 시스템의 하드웨어 타입을 출력
    - ./uname -p : 프로세서의 유형을 출력
    - ./uname -o : 운영체제를 출력

```c
#include <stdio.h>
#include <sys/utsname.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    int opt;
    int opt_s = 0, opt_r = 0, opt_v = 0, opt_m = 0, opt_p = 0, opt_o = 0;
    int no_option_passed = 1;
    struct utsname un;

    while ((opt = getopt(argc, argv, "srvmpo")) != -1) {
        no_option_passed = 0;

        switch (opt) {
            case 's':
                opt_s = 1;
                break;
            case 'r':
                opt_r = 1;
                break;
            case 'v':
                opt_v = 1;
                break;
            case 'm':
                opt_m = 1;
                break;
            case 'p':
                opt_p = 1;
                break;
            case 'o':
                opt_o = 1;
                break;
            default:
                fprintf(stderr, "Usage: %s [-s] [-r] [-v] [-m] [-p] [-o]\n", argv[0]);
                return 1;
        }
    }

    if (uname(&un) == -1) {
        perror("uname");
        return 1;
    }

    if (opt_s || no_option_passed) {
        printf("%s\n", un.sysname);
    }

    if (opt_r) {
        printf("%s\n", un.release);
    }

    if (opt_v) {
        printf("%s\n", un.version);
    }

    if (opt_m) {
        printf("%s\n", un.machine);
    }

    if (opt_p) {
        printf("%s\n", un.machine);
    }

    if (opt_o) {
        printf("GNU/Linux\n");
    }

    return 0;
}

```

- vim : ./vim : vim 편집기를 엶

```c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    pid_t pid = fork();

    if (pid == 0) {
        execvp("vim", argv);
        perror("execvp");
        exit(1);
    } else if (pid < 0) {
        perror("fork");
        exit(1);
    } else {
        waitpid(pid, NULL, 0);
    }

    return 0;
}

```

### 3. 출처

> https://rhrhth23.tistory.com/145  
> https://jhnyang.tistory.com/entry/%EB%A6%AC%EB%88%85%EC%8A%A4-%EC%9C%A0%EB%8B%89%EC%8A%A4-ps-%ED%94%84%EB%A1%9C%EC%84%B8%EC%8A%A4-%EB%AA%85%EB%A0%B9%EC%96%B4-%EC%A0%95%EB%A6%AC%ED%95%98%EA%B8%B0  
> https://coding-factory.tistory.com/748  
> https://chat.openai.com  
> https://bard.google.com  
> 강의 자료에서 일부 사용
