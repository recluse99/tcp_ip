//
// Created by root on 23-3-7.
//

#include <arpa/inet.h>
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

    int sock;
    FILE* fp;
    int read_len;
    char buf[BUF_SIZE];
    struct sockaddr_in serv_addr;

    if (argc != 3) {
        printf("%s must give <ip> <port>", argv[0]);
        exit(1);
    }
    //
    fp = fopen("../new.cpp", "wb");
    sock = socket(PF_INET, SOCK_STREAM, 0);

    memset(&serv_addr, 0, sizeof(serv_addr));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
    serv_addr.sin_port = htons(atoi(argv[2]));

    // conenct

    if (connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1) {
        error_handing("connect error()");
    }

    // 当 server 端半关闭 ，就会read 到EOF
    while ((read_len = read(sock, buf, BUF_SIZE)) != 0) {
        fwrite((void*)buf, 1, read_len, fp);
    }

    // server out stream close

    write(sock, "thanks\n", 10);

    

    fclose(fp);
    close(sock);

    return 0;
}
