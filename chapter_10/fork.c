#include <stdio.h>
#include <unistd.h>

int gval = 10;

int main(int argc, char* argv[])
{

    pid_t pid;

    int lval = 20;

    ++gval;
    lval += 6;

    pid = fork();

    // child process
    if (pid == 0) {
        ++gval;
        lval++;
    } else {
        gval = 0;
        lval = 100;
    }

    if (pid == 0) {
        printf("this is child  process...   gval=%d , lval=%d\n", gval, lval);
    } else {
        printf("this is parent process  gval=%d , lval=%d\n", gval, lval);
    }

    return 0;
}