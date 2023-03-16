//
// Created by root on 23-3-5.
//

#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#define BUFF_SIZE 1024

void error_handing(char *message) {
  fputs(message, stderr);
  fputc('\n', stderr);
  exit(1);
}

int main(int argc, char *argv[]) {

  int serv_sock;
  char message[BUFF_SIZE];

  int str_len;
  struct sockaddr_in serv_addr, clnt_addr;

  if (argc != 2) {
    printf("%s not give <port>\n", argv[0]);
    exit(1);
  }

  //   udp
  serv_sock = socket(PF_INET, SOCK_DGRAM, 0);

  if (serv_sock == -1) {
    error_handing("socket() error\n");
  }

  //
  memset(&serv_addr, 0, sizeof(serv_addr));

  // serv_addr 地址
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
  serv_addr.sin_port = htons(atoi(argv[1]));

  // bin
  if (bind(serv_sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) == -1) {
    error_handing("bind error\n");
  }

  // 读写数据
  while (1) {

    socklen_t clnt_addr_sz = sizeof(clnt_addr);

    str_len = recvfrom(serv_sock, message, BUFF_SIZE, 0,
                       (struct sockaddr *)&clnt_addr, &clnt_addr_sz);
    if (str_len == -1) {
      error_handing("recvfrom() error");
    }

    // 设置 '\0' 字符串结束的地方 。不然可以会读到之前存在message中的过界信息
    message[str_len]=0;

    printf("message from client:%s \n",message);

    if (sendto(serv_sock, message, str_len, 0, (struct sockaddr *)&clnt_addr,
               clnt_addr_sz) == -1) {
      error_handing("sendto() error");

    }
  }

  close(serv_sock);
  return 0;
}
