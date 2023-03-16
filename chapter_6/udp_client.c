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

  int sock;
  char message[BUFF_SIZE];

  struct sockaddr_in serv_addr, from_addr;
  int str_len;
  socklen_t clnt_size;

  if (argc != 3) {
    printf("%s must give <ip> <port>\n", argv[0]);
    exit(1);
  }

  // sock
  sock = socket(PF_INET, SOCK_DGRAM, 0);
  if (sock == -1) {
    error_handing("sock() error");
  }

  memset(&serv_addr, 0, sizeof(serv_addr));
  // server_addr
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
  serv_addr.sin_port = htons(atoi(argv[2]));

  while (1) {

    fputs("insert message(q to quit): ", stdout);
    fgets(message, BUFF_SIZE, stdin);

    if (!strcmp(message, "q\n") || !(strcmp(message, "Q\n"))) {
      break;
    }
    clnt_size = sizeof(from_addr);
    // 发给servre
    // sock 在第一次 sendto 绑定 地址和端口 。也可以使用 connect进行绑定
    // ，绑定后可以使用 write和 read
    if (sendto(sock, message, strlen(message), 0, (struct sockaddr *)&serv_addr,
               sizeof(serv_addr)) == -1) {
      error_handing("sendto() error");
    }

    socklen_t serv_size = sizeof(serv_addr);
    //  从server 直接使用 server_addr也可以
    str_len = recvfrom(sock, message, BUFF_SIZE, 0,
                       (struct sockaddr *)&serv_addr, &serv_size);
    message[str_len] = 0;

    printf("message from server:%s \n", message);
  }

  close(sock);

  return 0;
}