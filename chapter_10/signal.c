//
// Created by root on 23-3-19.
//

#include <signal.h>
#include <stdio.h>
#include <unistd.h>

void timeout(int sig) {
  if (sig == SIGALRM) {
    puts("time out....2s");
  }
  alarm(2);
}

void keycontrol(int sig) {

  if (sig == SIGINT) {
    puts("CTRL +C ");
  }
}

int main(int argc, char *argv[]) {

  int i;

  signal(SIGALRM, timeout);

  signal(SIGINT, keycontrol);

  alarm(2);

  for (i = 0; i < 10; ++i) {
    puts("wait ....");
    sleep(100);
  }
  return 0;
}
