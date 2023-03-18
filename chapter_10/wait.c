#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char *argv[]) {

  int status;

  pid_t pid;

  pid = fork();

  if (pid == 0) {

    sleep(15);

    return 5;
  } else {
    // 等待 子进程的返回值
    while (!waitpid(pid, &status, WNOHANG)) {
      sleep(3);
      puts("sleep 3sec");
    }
    if (WIFEXITED(status)) {
      printf("child send %d \n", WEXITSTATUS(status));
    }
  }

  return 0;
}