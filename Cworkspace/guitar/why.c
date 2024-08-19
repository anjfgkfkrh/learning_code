#include <stdio.h>
#include <unistd.h>
#include <string.h>

void f_print(int a, char s[])
{
    /*char str[strlen(s)];
    int i = 0, j = 0;
    while (s[i] != NULL)
    {
        if (s[i] == ' ')
            i++;
        else
        {
            str[j] = s[i];
            str[j + 1] = s[i + 1];
            str[j + 2] = s[i + 2];
            i += 3;
            j += 3;
        }
    }
    a *= 3;
    printf("%c%c%c", str[a], str[a + 1], str[a + 2]);*/
    a *= 3;
    printf("%c%c%c", s[a], s[a + 1], s[a + 2]);
}

int main()
{
    char a[] = "공부좋아";
    printf("\n");
    for (int i = 0; i < strlen(a); i += 3)
    {
        printf("%c%c%c\n", a[i], a[i + 1], a[i + 2]);
        sleep(1);
    }
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < ((strlen(a) / 3) * 5) + 1; j++)
        {
            for (int x = 0; x < j; x++)
                f_print(x % (strlen(a) / 3), a);
            printf("\n");
            usleep(50000);
        }
        for (int j = ((strlen(a) / 3) * 5) - 1; j > 0; j--)
        {
            for (int x = 0; x < j; x++)
                f_print(x % (strlen(a) / 3), a);
            printf("\n");
            usleep(50000);
        }
    }
    return 0;
}
