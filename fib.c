#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>

const int MAX = 13;

static void doFib(int n, int doPrint);

/*
 * unix_error - unix-style error routine.
 */
inline static void 
unix_error(char *msg)
{
    fprintf(stdout, "%s: %s\n", msg, strerror(errno));
    exit(1);
}


int main(int argc, char **argv)
{
  int arg;

  if(argc != 2){
    fprintf(stderr, "Usage: fib <num>\n");
    exit(-1);
  }

  arg = atoi(argv[1]);
  if(arg < 0 || arg > MAX){
    fprintf(stderr, "number must be between 0 and %d\n", MAX);
    exit(-1);
  }

  doFib(arg, 1);

  return 0;
}

static int exitcode(pid_t pid)
{
    pid_t retpid;
    int status;
    retpid = waitpid(pid, &status, 0);
    if(pid != retpid)
    {
        printf("waitpid error\n");
    }

    return WEXITSTATUS(status);
}
/* 
 * Recursively compute the specified number. If print is
 * true, print it. Otherwise, provide it to my parent process.
 *
 * NOTE: The solution must be recursive and it must fork
 * a new child for each call. Each process should call
 * doFib() exactly once.
 */
/* borrow code from http://stackoverflow.com/questions/9311999/recursive-fibonacci-using-fork-in-c-pt-2 */
static void 
doFib(int n, int doPrint)
{
    int cur_pid = getpid();
    if(n < 2)
        exit(n);
    int pid1 = fork();
    if(pid1 == 0)
    {
        doFib(n-1,  0);
        exit(n-1);
    }
    else if(pid1 > 0) 
    {
        int pid2 = fork();
        if(pid2 == 0)
        {
            doFib(n-2, 0);
            exit(n-2);
        }

        int r1 = exitcode(pid1);
        int r2 = exitcode(pid2);

        if(getpid() == cur_pid)
        {
            int result = r1 + r2;
            if(doPrint)
            {
                printf("%d\n", result);
            }
            else
            {
                exit(result);
            }
        }

    }
}
