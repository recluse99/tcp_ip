#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

// 声明 error 函数
void error_handing(char* messages);

int main(int argc, char* argv[])
{

    int sock;
    struct sockaddr_in serv_addr;

    char message[30];

    int str_len=0;

    if (argc != 3) {
        printf("usage:%s <ip> <port> \n", argv[0]);
    }

    sock = socket(PF_INET, SOCK_STREAM, 0);

    if (sock == -1) {
        error_handing("socket() error");
    }

    memset(&serv_addr, 0, sizeof(serv_addr));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
    serv_addr.sin_port = htons(atoi(argv[2]));

    if (connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1) {
        error_handing("connect() error");
    }

    int read_len=0,index=0,str;

    //tcp连接 ，可以多次read 
    // read_len==0 才为false;
    while(read_len=read(sock,&message[index++],1)){
        if(read_len==-1){
            error_handing("read() error");
        }
        str_len+=read_len;
    }

    // str_len = read(sock, message, sizeof(message));

    // if (str_len == -1) {
    //     error_handing("read() error");
    // }

    printf("Message from server : %s \n", message);

    printf("read count is %d \n",str_len);

    close(sock);

    return 0;
}

void error_handing(char* messages)
{

    fputs(messages, stderr);
    fputc('\n', stderr);
    exit(1);
}