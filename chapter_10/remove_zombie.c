//
// Created by root on 23-3-19.
//
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

void read_childproc(int sig);

int main(int argc, char *argv[]) {

  pid_t pid;

  struct sigaction action;
  action.sa_handler = read_childproc;
  sigemptyset(&action.sa_mask);
  action.sa_flags = 0;
  // 子进程结束后会触发这个信号量
  sigaction(SIGCHLD, &action, NULL);

  pid = fork();

  if (pid == 0) {
    // puts 最后自带 \n
    puts("hi i am child process");
    sleep(10);
    return 13;
  } else {

    printf("child proc id :%d \n", pid);
    pid = fork();

    if (pid == 0) {
      puts("hi i am child process 2 ");
      sleep(10);
      exit(22);
    } else {
      int i;
      printf("child proc id :%d \n", pid);

      for (i = 0; i < 10; i++) {
        puts(" wait .....");
        // 发生信号时 ，父进程会被唤醒
        sleep(5);
      }
    }
  }

  return 0;
}

void read_childproc(int sig) {

  int status;
  pid_t id = waitpid(-1, &status, WNOHANG);

  if (WIFEXITED(status)) {
    printf("remove child process id : %d\n", id);
    printf("child send : %d \n", WEXITSTATUS(status));
  }
}

