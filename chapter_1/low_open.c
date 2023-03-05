#include <arpa/inet.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

void error_handing(char* messages)
{

    fputs(messages, stderr);
    fputc('\n', stderr);
    exit(1);
}

int main()
{

    char buf[] = "hello,xuqiang";

    int fd = open("data.txt", O_CREAT | O_WRONLY | O_TRUNC);

    if (fd == -1) {
        error_handing("open() error");
    }

    printf("file open descriptor , %d \n", fd);

    // 指针的sizeof与操作系统有关  32位的是4字节  64位的是8字节  。 在此系统是8字节
    // sizeof(char) 是1字节 
    if (write(fd, buf, sizeof(buf)) == -1) {
        error_handing("write() error");
    }
    // 关闭
    close(fd);


    char* message="xuqing";
    // 根据char* 得到字符串的长度 。不包括的 \0
    int len=strlen(message);

    printf("%d \n",len);


    return 0;
}