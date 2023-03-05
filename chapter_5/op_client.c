//
// Created by root on 23-3-3.
//

#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define BUF_SIZE 1024

void error_handing(char *message) {
  fputs(message, stderr);
  fputc('\n', stderr);
  exit(1);
}

int main(int argc, char *argv[]) {

  int sock;

  struct sockaddr_in serv_addr;

  char message[BUF_SIZE];

  int str_len, clnt_len;

  if (argc != 3) {
    printf("usage :%s <ip> <port> \n", argv[0]); // argv[0]中存放的是程序名
  }

  //
  sock = socket(PF_INET, SOCK_STREAM, 0);
  if (sock == -1) {
    error_handing("socket() error\n");
  }

  // serv_addr  to 0

  memset(&serv_addr, 0, sizeof(serv_addr));

  // 地址设置和绑定
  serv_addr.sin_family = AF_INET;

  serv_addr.sin_addr.s_addr = inet_addr(argv[1]);

  serv_addr.sin_port = htons(
      atoi(argv[2])); // 将 string -> int -> 网络字节序  。。。。也就是大端序

  // 连接服务器 socket
  if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) == -1) {
    error_handing("connect() error\n");
  } else {
    puts("connected ......\n");
  }

  // 键入数字和运算符

  while (1) {

    fputs("input number and operator(Q to quit):", stdout);

    fgets(message, BUF_SIZE, stdin);

    if (!strcmp(message, "q\n") || !strcmp(message, "Q\n")) {
      break;
    }

    if(write(sock,message, strlen(message))==-1){
      printf("write .. error\n");
    }else{
      printf("send to server: %s\n",message);
    }


  }

  close(sock);


  return 0;
}
