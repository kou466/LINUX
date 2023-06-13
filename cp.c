#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <utime.h>
#include <dirent.h>

void copy_files(const char *src, const char *dst, bool recursive, bool interactive, bool update, bool verbose);

int main(int argc, char *argv[]) {
    int opt;
    bool archive = false, interactive = false, recursive = false, update = false, verbose = false;

    while ((opt = getopt(argc, argv, "airuv")) != -1) {
        switch (opt) {
            case 'a':
                archive = true;
                break;
            case 'i':
                interactive = true;
                break;
            case 'r':
                recursive = true;
                break;
            case 'u':
                update = true;
                break;
            case 'v':
                verbose = true;
                break;
            default:
                printf("Usage: %s [-airuv] src dest\n", argv[0]);
                exit(EXIT_FAILURE);
        }
    }

    if (argc - optind != 2) {
        printf("Usage: %s [-airuv] src dest\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    char *src_path = argv[optind];
    char *dst_path = argv[optind + 1];
    copy_files(src_path, dst_path, recursive, interactive, update, verbose);

    return 0;
}

void copy_files(const char *src, const char *dst, bool recursive, bool interactive, bool update, bool verbose) {
    struct stat src_stat, dst_stat;
    int cp_flag = 0;

    if (lstat(src, &src_stat) == -1) {
        perror("lstat");
        exit(EXIT_FAILURE);
    }

    // Check if the source is a directory and if a recursive copy should be performed
    if (S_ISDIR(src_stat.st_mode)) {
        if (!recursive) {
            printf("cp: omitting directory '%s'\n", src);
            return;
        }

        // Copy the directory and its contents
        DIR *src_dir = opendir(src);
        if (src_dir == NULL) {
            perror("opendir");
            exit(EXIT_FAILURE);
        }

        if (mkdir(dst, src_stat.st_mode) == -1) {
            perror("mkdir");
            exit(EXIT_FAILURE);
        }

        struct dirent *entry;
        while ((entry = readdir(src_dir)) != NULL) {
            if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
                continue;
            }

            char src_entry_path[PATH_MAX];
            snprintf(src_entry_path, PATH_MAX, "%s/%s", src, entry->d_name);
            char dst_entry_path[PATH_MAX];
            snprintf(dst_entry_path, PATH_MAX, "%s/%s", dst, entry->d_name);

            copy_files(src_entry_path, dst_entry_path, recursive, interactive, update, verbose);
        }

        closedir(src_dir);
    } else {
        // Check if the destination exists or should be updated
        cp_flag = 1;
        if (lstat(dst, &dst_stat) != -1) {
            if (update && src_stat.st_mtime <= dst_stat.st_mtime) {
                cp_flag = 0;
            }

            if (interactive) {
                cp_flag = 0;
                printf("cp: overwrite '%s'? ", dst);
                char response[3];
                if (fgets(response, sizeof(response), stdin) != NULL) {
                    if (response[0] == 'y' || response[0] == 'Y') {
                        cp_flag = 1;
                    }
                }
            }
        }

        // Copy the file
        if (cp_flag) {
            int src_fd = open(src, O_RDONLY);
            if (src_fd == -1) {
                perror("open");
                exit(EXIT_FAILURE);
            }

            int dst_fd = open(dst, O_WRONLY | O_CREAT | O_TRUNC, src_stat.st_mode);
            if (dst_fd == -1) {
                perror("open");
                exit(EXIT_FAILURE);
            }

            char buf[BUFSIZ];
            ssize_t n;

            while ((n = read(src_fd, buf, sizeof(buf))) != 0) {
                if (n == -1) {
                    perror("read");
                    exit(EXIT_FAILURE);
                }

                if (write(dst_fd, buf, n) == -1) {
                    perror("write");
                    exit(EXIT_FAILURE);
                }
            }

            if (close(src_fd) == -1) {
                perror("close");
                exit(EXIT_FAILURE);
            }

            if (close(dst_fd) == -1) {
                perror("close");
                exit(EXIT_FAILURE);
            }

            if (verbose) {
                printf("'%s' -> '%s'\n", src, dst);
            }
        }
    }
}

