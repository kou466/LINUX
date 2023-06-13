#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <string.h>
#include <dirent.h>

#define BUF_SIZE 4096

void copy_file(const char *src, const char *dst, int flags[], mode_t mode);
void copy_directory(const char *src, const char *dst, int flags[], mode_t mode);
void copy_items(const char* src, const char* dst, int flags[]);

int main(int argc, char *argv[]) {
    int opt;
    int flags[] = {0, 0, 0, 0};  // a, i, r, u, v

    while ((opt = getopt(argc, argv, "airuv")) != -1) {
        switch (opt) {
            case 'a':
                flags[0] = 1;
                break;
            case 'i':
                flags[1] = 1;
                break;
            case 'r':
                flags[2] = 1;
                break;
            case 'u':
                flags[3] = 1;
                break;
            case 'v':
                flags[4] = 1;
                break;
            default:
                fprintf(stderr, "Usage: %s [-a] [-i] [-r] [-u] [-v] source target\n", argv[0]);
                return 1;
        }
    }

    if (optind + 2 != argc) {
        fprintf(stderr, "Missing source and/or target arguments.\n");
        return 1;
    }

    copy_items(argv[optind], argv[optind + 1], flags);

    return 0;
}

void copy_items(const char* src, const char* dst, int flags[]) {
    struct stat src_stat;

    if (stat(src, &src_stat) == -1) {
        perror("stat");
        return;
    }

    if (S_ISDIR(src_stat.st_mode) && flags[2]) {
        copy_directory(src, dst, flags, src_stat.st_mode);
    } else if (S_ISREG(src_stat.st_mode)) {
        copy_file(src, dst, flags, src_stat.st_mode);
    } else {
        fprintf(stderr, "Invalid source path or unsupported file type.\n");
    }
}

void copy_file(const char *src, const char *dst, int flags[], mode_t mode) {
    int src_fd, dst_fd;
    char buffer[BUF_SIZE];
    struct stat dst_stat;

    src_fd = open(src, O_RDONLY);
    if (src_fd < 0) {
        perror("open src");
        return;
    }

    // Check options
    if (flags[3] && access(dst, F_OK) == 0) {
        if (stat(dst, &dst_stat) == 0) {
            if (dst_stat.st_mtime >= mode) {
                return;
            }
        }
    }

    if (flags[1] && access(dst, F_OK) == 0) {
        char overwrite;
        printf("overwrite %s? (y/n) ", dst);
        scanf("%c", &overwrite);
        if (overwrite != 'y') {
            return;
        }
    }

    dst_fd = open(dst, O_WRONLY | O_CREAT | O_TRUNC, mode);
    if (dst_fd < 0) {
        perror("open dst");
        return;
    }

    ssize_t size;
    while ((size = read(src_fd, buffer, BUF_SIZE)) > 0) {
        if (write(dst_fd, buffer, size) != size) {
            fprintf(stderr, "Error writing to file %s\n", dst);
            break;
        }
    }

    if (size < 0) {
        fprintf(stderr, "Error reading from file %s\n", src);
    }

    close(src_fd);
    close(dst_fd);
}

void copy_directory(const char *src, const char *dst, int flags[], mode_t mode) {
    DIR *dir;
    dir = opendir(src);
    if (!dir) {
        perror("opendir");
        return;
    }

    if (mkdir(dst, mode) == -1 && errno != EEXIST) {
        perror("mkdir");
        return;
    }

    char src_path[PATH_MAX], dst_path[PATH_MAX];
    struct dirent *entry;
    while ((entry = readdir(dir))) {
        if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) {
            snprintf(src_path, sizeof(src_path), "%s/%s", src, entry->d_name);
            snprintf(dst_path, sizeof(dst_path), "%s/%s", dst, entry->d_name);
            copy_items(src_path, dst_path, flags);
        }
    }

    closedir(dir);
}
