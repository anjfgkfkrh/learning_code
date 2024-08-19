#include <stdio.h>
#include <unistd.h>

int main()
{
  printf("I am child process\n");
  printf("child: parent ppid = %d\n", getppid());
  return 100;
}