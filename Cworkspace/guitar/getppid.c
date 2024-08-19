#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <string.h>
#include <stdlib.h>

int main()
{
  pid_t new;
  int status = 0;
  int d = 0;
  new = fork();

  switch (new)
  {
  case 0:
    sleep(1);
    printf("parent pid : %d\n", getppid());
    break;

  default:
    for (int i = 0; i < 20; i++)
    {
      d++;
    }
    wait(NULL);
    break;
  }

  return 0;
}