#include <stdio.h>

int a = 10;

void abc(int* z)
{
   z = 8;
   a = 18;
}

int main()
{

   int num,i;

   printf("사람 수 입력해");
   scanf("%d", &num);

   int a[5];

   int *p = &a[0];
   p += 4;
   a[1];
   a[2];
   a[3];
   a[4];

}

