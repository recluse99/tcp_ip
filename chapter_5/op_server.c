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

  int serv_sock, clnt_sock;

  struct sockaddr_in serv_addr;
  struct sockaddr_in clnt_addr;

  char message[BUF_SIZE];

  // 两个参数   函数名 和 端口号

  if (argc != 2) {
    error_handing("error input , please give <port>");
  }

  serv_sock = socket(PF_INET, SOCK_STREAM, 0);

  if (serv_sock == -1) {
    error_handing("socket() error");
  }

  // ==0
  memset(&serv_addr, 0, sizeof(serv_addr));

  serv_addr.sin_family = AF_INET;
  serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
  serv_addr.sin_port = htons(atoi(argv[1]));

  // bind

  if (bind(serv_sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) == -1) {
    error_handing("bind() error\n");
  }

  // listen

  if (listen(serv_sock, 5) == -1) {
    error_handing("listen() error\n");
  }

  int clnt_addr_size = sizeof(clnt_addr);
  // accept

  for (int i = 0; i < 5; ++i) {
    clnt_sock =
        accept(serv_sock, (struct sockaddr *)&clnt_addr, &clnt_addr_size);

    if (clnt_sock == -1) {
      error_handing("accept() error\n");
    } else {
      printf("connected client %d\n", i);
    }

    int str_len;
    int number[100] = {0};
    char operator[5];
    int index = 0, result = 0;
    // read 返回值为0 ，表示连接中断了。。。。可以连接下一个client
    while ((str_len = read(clnt_sock, message, BUF_SIZE)) != 0) {

      if (str_len == -1) {
        error_handing("read() error\n");
      }

      for (int i = 0; i < str_len; ++i) {
        if (message[i] != ' ') {
          if (message[i] != '+' && message[i] != '-' && message[i] != '\n') {
            number[index++] = message[i] - '0';
          } else if (message[i] != '\n') {
            operator[0] = message[i];
          }
        }
      }



      //
      printf("numbers....\n");
      for (int i = 0; i < 100; ++i) {
        if (number[i] != 0) {
          printf("%d ", number[i]);
        }
      }

      // 处理数据  这里还可以优化y一下， index 记录了 有多少 计算数字
      if (operator[0] == '+') {
        for (int i = 0; i < 100; ++i) {
          if (number[i] != 0) {
            result += number[i];
          } else {
            break;
          }
        }
      } else {
        for (int i = 0; i < 100; ++i) {
          if (number[i] != 0) {
            if (i == 0) {
              result = number[i];
            } else {
              result -= number[i];
            }
          } else {
            break;
          }
        }
      }
      printf("\n result is : %d\n", result);
    }
    close(clnt_sock);
  }

  close(serv_sock);

  return 0;
}