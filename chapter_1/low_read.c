#include <arpa/inet.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#define BUF_SIZE 100

void error_handing(char* messages)
{

    fputs(messages, stderr);
    fputc('\n', stderr);
    exit(1);
}

int main()
{

    int fd;

    char buf[BUF_SIZE];

    fd = open("data.txt", O_RDONLY);

    if (fd == -1) {
        error_handing("open() error");
    }

    if (read(fd, buf, sizeof(buf)) == -1) {
        error_handing("read() error");
    }

    printf("file data is :%s \n", buf);

    close(fd);

    return 0;
}