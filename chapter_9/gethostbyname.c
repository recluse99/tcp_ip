//
// Created by root on 23-3-7.
//

#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define BUF_SIZE 1024

void error_handing(char* message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}

int main(int argc, char* argv[])
{

    struct hostent* host;

    if (argc != 2) {
        printf("%s not <port>", argv[0]);
        exit(1);
    }

    host = gethostbyname(argv[1]);
    if (!host) {
        error_handing("get host error....");
    }

    printf("official name is :%s \n", host->h_name);

    //  当 数组为null时，条件判定就会为 false 结束循环
    for (int i = 0; host->h_addr_list[i]; ++i) {
        // 直接以char * 形式格式化，会出现乱码。。。。需要转型
        printf("ip addr %d : %s \n", i + 1,
            inet_ntoa(*(struct in_addr*)host->h_addr_list[i]));
    }

    return 0;
}
