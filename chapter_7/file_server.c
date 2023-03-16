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

void error_handing(char *message) {
  fputs(message, stderr);
  fputc('\n', stderr);
  exit(1);
}

int main(int argc, char *argv[]) {

  int serv_sd, clnt_sd;
  FILE *fp;

  char buf[BUF_SIZE];

  int read_len;

  struct sockaddr_in serv_addr, clnt_addr;
  socklen_t clnt_size;

  if (argc != 2) {
    printf("%s must give <port>", argv[0]);
    exit(1);
  }

  fp = fopen("../main.cpp", "rb");
  serv_sd = socket(PF_INET, SOCK_STREAM, 0);

  memset(&serv_addr, 0, sizeof(serv_addr));

  serv_addr.sin_family = AF_INET;
  serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
  serv_addr.sin_port = htons(atoi(argv[1]));

  // bind
  if (bind(serv_sd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) == -1) {
    error_handing("bind() error");
  }

  // listen
  if (listen(serv_sd, 5) == -1) {
    error_handing("listen() error");
  }

  // accept
  clnt_size = sizeof(clnt_size);

  clnt_sd = accept(serv_sd, (struct sockaddr *)&clnt_addr, &clnt_size);
  if (clnt_sd == -1) {
    error_handing("accept() error");
  } else {
    printf("connect ...%d", 1);
  }

  // 使用buf读取文件内容

  while (1) {
    read_len = fread((void *)buf, 1, BUF_SIZE, fp);
    // 读取 最后的部分
    if (read_len < BUF_SIZE) {
      write(clnt_sd, buf, read_len);
      break;
    }
    // 代表后面还有数据 接着 读取
    write(clnt_sd, buf, BUF_SIZE);
  }

  // 半关闭 output stream
  shutdown(clnt_sd, SHUT_WR);

  read_len = read(clnt_sd, buf, BUF_SIZE);

  // 在最后置零 '\0'
  buf[read_len] = 0;

  printf("last message from  client: %s ", buf);

  fclose(fp);
  close(clnt_sd);
  close(serv_sd);

  return 0;
}
