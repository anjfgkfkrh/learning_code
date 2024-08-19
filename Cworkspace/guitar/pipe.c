#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int main()
{
  pid_t child;
  int fd[2];
  char buf[20];
  int status;

  pipe(fd);

  child = fork();

  switch (child)
  {
  case 0:
    strcpy(buf, "Hello parent!\n");
    write(fd[1], buf, strlen(buf));
    sleep(3);
    printf("child: %d parent: %d", getpid(), getppid());
    return 0;
    break;

  default:
    bzero(buf, sizeof(buf));
    read(fd[0], buf, sizeof(buf));
    printf("%s", buf);
    printf("child: %d parent: %d \n", child, getpid());
    // wait(&status);
    // printf("%d\n", WEXITSTATUS(status));
    break;
  }

  return 0;
}