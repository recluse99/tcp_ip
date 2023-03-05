//
// Created by root on 23-3-2.
//

#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define BUF_SIZE 1024

// 声明 error 函数
void error_handing(char *messages);

int main(int argc, char *argv[]) {

    int sock;
    struct sockaddr_in serv_addr;

    char message[BUF_SIZE];

    int str_len, recv_cnt;

    if (argc != 3) {
        printf("usage:%s <ip> <port> \n", argv[0]);
    }

    sock = socket(PF_INET, SOCK_STREAM, 0);

    if (sock == -1) {
        error_handing("socket() error");
    }

    // 初始化为0
    memset(&serv_addr, 0, sizeof(serv_addr));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
    serv_addr.sin_port = htons(atoi(argv[2]));

    if (connect(sock, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) == -1) {
        error_handing("connect() error");
    } else {
        puts("connected ........");
    }

    // 当 server 没有写信息时，提前读会引发阻塞
    //str_len = read(sock, message, sizeof(message));

//    if (str_len == -1) {
//        error_handing("read() error");
//    }

    while (1) {
        fputs("input message (Q to quit): ", stdout);

        fgets(message, BUF_SIZE, stdin);


        if (!strcmp(message, "q\n") || !strcmp(message, "Q\n")) {
            break;
        }

        str_len = write(sock, message, strlen(message));

        //str_len = read(sock, message, BUF_SIZE - 1);


        int recv_len = 0;

        // 保证 发送出去的字符串可以 完整的 读到
        while (recv_len < str_len) {

            recv_cnt = read(sock, &message[recv_len], BUF_SIZE - 1);
            if (recv_cnt == -1) {
                error_handing("read()  error");
            }

            recv_len += recv_cnt;
        }
        // 将末尾置零
        message[recv_len] = 0;  // ==‘\0’

        printf("message from server %s", message);


    }

    // printf("Message from server : %s \n", message);

    close(sock);

    return 0;
}

void error_handing(char *messages) {

    fputs(messages, stderr);
    fputc('\n', stderr);
    exit(1);
}
