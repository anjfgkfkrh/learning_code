#include <iostream>

class Int
{
   int data;

public:
   Int(int data) : data(data) {}
   Int(const Int &i) : data(i.data) {}

   Int &operator++()
   {
      data++;
      return *this;
   }
   Int operator++(int)
   {
      Int x = data++;
      return x;
   }
   Int &operator--()
   {
      data--;
      return *this;
   }
   Int operator--(int)
   {
      Int x = data--;
      return x;
   }
   operator int() { return data; }
};
int main()
{
   Int x = 3;
   std::cout << ++x << std::endl
             << x++ << x << std::endl;
}