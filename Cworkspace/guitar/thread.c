#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h>

void mainPause(pthread_t newThread)
{
  if (pthread_join(newThread, NULL)) // 새 스레드 종료까지 메인 스레드 정지
  {
    fprintf(stderr, "Error joining thread\n");
    exit(2);
  }
}

void *stopthread(void *agr) // s를 입력받으면 stop을 1로 변경하는 스레드
{
  int *stop = (int *)agr; // 인자 받아옴
  char c;
  while (1) // s 입력 받을 때 까지 반복
  {
    c = getchar();
    if (c == 's')
    {
      *stop = 1;
      break;
    }
  }

  return NULL;
}

void *funtionthread(void *arg)
{
  pthread_t stopth;
  int stop = 0; // stop == 1 이면 스레드 종료

  if (pthread_create(&stopth, NULL, stopthread, &stop))
  {
    fprintf(stderr, "Error creating thread\n");
    exit(1);
  }

  while (1)
  {

    if (stop == 1)
      break;

    time_t current_time = time(NULL);
    char *str_time = ctime(&current_time);

    // printf("\033[H\033[J"); //화면 초기화
    printf("%s", str_time);
    sleep(1);
  }
  mainPause(stopth);
  return NULL;
}

int main()
{
  pthread_t newThread;
  long n = 0;

  if (pthread_create(&newThread, NULL, funtionthread, NULL)) // 새 스레드 생성 및 실행
  {
    fprintf(stderr, "Error creating thread\n");
    return 1;
  }

  for (int i = 0; i < 2000000000; i++)
  { // n을 출력하기한 메인 스레드 지연용
    n++;
  }

  printf("hello %ld\n", n);
  mainPause(newThread);

  return 0;
}