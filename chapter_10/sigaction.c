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


/*
 * 现在z
 *
 * */
int main(int argc, char **argv) {

  int i;

  struct sigaction act;

  act.sa_handler = timeout;
  sigemptyset(&act.sa_mask);
  act.sa_flags = 0;

  sigaction(SIGALRM, &act, 0);

  alarm(2);

  for (i = 0; i < 3; ++i) {
    puts("waiting for...");
    sleep(100);
  }

  return 0;
}