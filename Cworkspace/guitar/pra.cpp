#include <iostream>
#include <unistd.h>
using namespace std;

class fuck
{
private:
    string s;
    int leng;

public:
    fuck(string a)
    {
        s = a;
        cout << s.length() << s << endl;
        s.erase(remove(s.begin(), s.end(), ' '), s.end());
        cout << s.length() << s << endl;
        leng = s.length() / 3;
    }

    void print(int a)
    {
        a *= 3;
        cout << s[a] << s[a + 1] << s[a + 2];
    }

    void start(int a, int b)
    {
        for (int i = 0; i < a; i++)
        {
            for (int j = 0; j < (leng * b + 1); j++)
            {
                for (int k = 0; k < j; k++)
                {
                    print(k % leng);
                }
                cout << "\n";
                usleep(50000);
            }
            for (int j = (leng * b - 1); j > 0; j--)
            {
                for (int k = 0; k < j; k++)
                {
                    print(k % leng);
                }
                cout << "\n";
                usleep(50000);
            }
        }
    }
};

int main()
{
    fuck s = fuck("공 부 좋 아 넘 무 좋 아 시 발 좋 아");
    s.start(3, 3);
    return 0;
}
