#include <string>
#include <iostream>

class MyString
{
   char *_string;
   int string_length;
   unsigned int memory_capacity;

   // mutable int a;
   // 위 변수는 const 함수 내에서도 변경 가능

public:
   MyString(char c);
   MyString(const char *string);
   MyString(const MyString &str);
   explicit MyString(int capacity); // 암시적 변환 불가
   // 암시적 변환 ex)
   // MyString s  = "abc"   =>   MyString s = MyString("abc")
   // 함수(MyString s)
   // 함수("abc")   =>   함수(MyString("abc"))

   ~MyString()
   {
      delete[] _string;
   }

   bool operator==(MyString &str);
   char &operator[](const int index);

   MyString &assign(const MyString &str);
   MyString &assign(const char *str);

   MyString &insert(int loc, const MyString &str);
   MyString &insert(int loc, const char *str);
   MyString &insert(int loc, char c);

   MyString &erase(int loc, int num);
   MyString &erase(int loc);

   int find(int find_from, MyString &str) const;
   int find(int find_from, const char *str) const;
   int find(int find_from, char c) const;
   int findKMP(int find_from, MyString &str) const;
   int findKMP(int find_from, const char *str) const;
   int findKMP(int find_from, char c) const;
   int findBM(int find_from, MyString &str) const;
   int findBM(int find_from, const char *str) const;
   int findBM(int find_from, char c) const;

   int compare(const MyString &str) const;

   void reserve(int size);

   char at(int i) const;
   int length() const;
   int capacity() const;

   void print() const;
   void println() const;
};

MyString::MyString(char c)
{
   string_length = 1;
   memory_capacity = 1;
   _string = new char[string_length];

   _string[0] = c;
}
MyString::MyString(const char *string)
{
   memory_capacity = strlen(string);
   string_length = memory_capacity;
   _string = new char[string_length];

   for (int i = 0; i < string_length; i++)
      _string[i] = string[i];
}
MyString::MyString(const MyString &str)
{
   memory_capacity = str.length();
   string_length = memory_capacity;
   _string = new char[string_length];

   for (int i = 0; i < string_length; i++)
      _string[i] = str._string[i];
}
MyString::MyString(int capacity)
{
   _string = new char[capacity];
   string_length = 0;
   memory_capacity = capacity;
   std::cout << "Capacity : " << capacity << std::endl;
}
bool MyString::operator==(MyString &str)
{
   return !compare(str);
}
char &MyString::operator[](const int index)
{
   return _string[index];
}
MyString &MyString::assign(const MyString &str)
{
   if (str.length() > memory_capacity)
   {
      delete[] _string;
      memory_capacity = str.length();
      string_length = memory_capacity;
      _string = new char[string_length];
   }

   for (int i = 0; i < string_length; i++)
      _string[i] = str._string[i];

   return *this;
}
MyString &MyString::assign(const char *str)
{
   if (strlen(str) > memory_capacity)
   {
      delete[] _string;
      memory_capacity = strlen(str);
      string_length = memory_capacity;
      _string = new char[string_length];
   }

   for (int i = 0; i < string_length; i++)
      _string[i] = str[i];

   return *this;
}
MyString &MyString::insert(int loc, const MyString &str)
{
   if (loc >= string_length || loc < 0)
      return *this;

   if (memory_capacity < string_length + str.length())
   {
      char *prev_string_content = _string;

      if (memory_capacity * 2 > string_length + str.length())
         memory_capacity *= 2;
      else
         memory_capacity = string_length + str.length();

      _string = new char[memory_capacity];

      int i;
      for (i = 0; i < loc; i++)
      {
         _string[i] = prev_string_content[i];
      }
      for (int j = 0; j < str.length(); j++)
      {
         _string[j + loc] = str.at(j);
      }
      for (; i < string_length; i++)
      {
         _string[i + str.length()] = prev_string_content[i];
      }

      delete[] prev_string_content;

      string_length += str.length();
      return *this;
   }
   else
   {
      for (int i = string_length - 1; i >= loc; i--)
         _string[i + str.length()] = _string[i];

      for (int i = 0; i < str.length(); i++)
         _string[i + loc] = str.at(i);

      string_length += str.length();
      return *this;
   }
}
MyString &MyString::insert(int loc, const char *str)
{
   MyString temp(str);
   return insert(loc, temp);
}
MyString &MyString::insert(int loc, char c)
{
   MyString temp(c);
   return insert(loc, temp);
}
MyString &MyString::erase(int loc, int num)
{
   if (loc >= string_length || loc < 0 || num < 0 || loc + num >= string_length)
      return *this;

   for (int i = loc; i < string_length - num; i++)
      _string[i] = _string[i + num];

   string_length -= num;

   return *this;
}
MyString &MyString::erase(int loc)
{
   return erase(loc, 1);
}
int MyString::find(int find_from, MyString &str) const
{
   // brute-force Algorithm
   if (find_from < 0 || find_from >= string_length || str.length() == 0)
      return -1;

   int i, j;
   for (i = find_from; i <= string_length - str.length(); i++)
   {
      if (_string[i] == str.at(0))
         for (j = 1; j < str.length(); j++)
            if (_string[i + j] != str.at(j))
               break;
      if (j == str.length())
         return i;
   }

   return -1;
}
int MyString::find(int find_from, const char *str) const
{
   MyString temp(str);
   return find(find_from, temp);
}
int MyString::find(int find_from, char c) const
{
   MyString temp(c);
   return find(find_from, temp);
}
int MyString::findKMP(int find_from, MyString &str) const
{
   // KMP Algorithm
   if (find_from < 0 || find_from >= string_length || str.length() == 0)
      return -1;

   int pi[str.length()];
   std::fill_n(pi, str.length(), 0);

   // 접두미사 패턴 추출
   // 반복문 1단계에서는 문자열의 크기를 하나 씩 증가시킴
   // 이후 패턴 추출
   // 1단계 반복문이 증가 할 수록 문자열은 하나씩 늘어남
   // 전 단계의 결과가 pi배열에 기록 됨
   // i는 문자열의 크기를 나타냄
   //

   // #1 전 pi = 0, 현 pi = 1
   // => 처음과 맨 끝이 같은 경우
   // #2 전 pi = 1, 현 pi = 2
   // => str[1]과 맨 끝이 같은 경우
   // #3 전 pi = 0, 현 pi = 2 ex)

   // %중요% pi는 순차적으로 증가한다.
   // ex) pi[1] = 0, pi[2] =2 될 수 없음
   // 접미와 접두가 같으려면 점두의 문자열을 접미에서 하나씩 쌓아서 가야하기 때문
   // 단, 감소는 상관 없음

   // str[0]의 중복 위치가 중요

   // 증가는 쉽게 판단 가능
   // 전 pi를 가지고 str[pi] == 끝 문자 비교
   // true면 증가
   // false면 0또는 특정 값
   // 지금까지 대조했던 패턴안에 또 따른 패턴이 있을 시 (pi값이 0이 아닐시 패턴이 존재) 그 패턴과 비교
   // 계속 카피하던 패턴의 pi값을 확인(패턴 안의 패턴 확인) 그 이후를 이어나길수 있는지 체크

   // ABCDABCA/qwerxcxb/ABCDABCA/B
   // 00001231/00000000/12345678/

   // 012345678910
   // ABABABABAB/AB/C
   // 0012345678/910/

   int i, j;
   j = 0;
   for (i = 1; i < str.length(); i++)
   {
      while (j > 0 && str.at(i) != str.at(j))
         j = pi[j - 1];
      if (str.at(i) == str.at(j))
         pi[i] = ++j;
   }

   /*
   j = 0; // 문자열 일치 개수 == 비교중인 문자 위치
   i = 0; // 문자열의 본문에서의 위치
   while (i <= string_length - str.length())
   {
      std::cout << i << " " << j + i << std::endl;
      if (_string[i + j] == str.at(j))
      {
         if (j == str.length() - 1)
            return i;
         else
            j++;
      }
      else
      {
         if (j > 0 && pi[j - 1] != 0)
         {
            i = i + j - pi[j - 1];
            j = pi[j - 1];
         }
         else
         {
            i++;
            j = 0;
         }
      }
   }
   return -1;*/

   // *중요* 본문의 모든 문자열을 **한번씩만** 순회하며 검사함
   // 시간 복잡도 = O(n)
   i = 0; // 본문의 비교중인 문자 위치
   j = 0; // 문자열의 비교중인 문자 위치
   for (i = 0; i < string_length; i++)
   {
      while (j > 0 && _string[i] != str.at(j))
         j = pi[j - 1];
      if (_string[i] == str.at(j))
      {
         if (j == str.length() - 1)
            return i - j;
         else
            j++;
      }
   }
   return -1; // 못 찾을시 리턴값
}
int MyString::findKMP(int find_from, const char *str) const
{
   MyString temp(str);
   return MyString::findKMP(find_from, temp);
}
int MyString::findKMP(int find_from, char c) const
{
   MyString temp(c);
   return MyString::findKMP(find_from, temp);
}
int MyString::findBM(int find_from, MyString &str) const
{
   // 나중에 구현
   // 귀찮아짐
}
int MyString::compare(const MyString &str) const
{
   if (str.length() <= 0)
      return -2;

   for (int i = 0; i < std::min(string_length, str.length()); i++)
      if (_string[i] != str.at(i))
         return _string[i] > str.at(i) ? 1 : -1;

   if (string_length == str.length())
      return 0;
   else
      return string_length > str.length() ? 1 : -1;
}
void MyString::reserve(int size)
{
   if (size <= memory_capacity)
      return;

   char *prev_string_content = _string;

   memory_capacity = size;
   _string = new char[memory_capacity];

   for (int i = 0; i < string_length; i++)
      _string[i] = prev_string_content[i];

   delete[] prev_string_content;
}
char MyString::at(int i) const
{
   if (i >= string_length || i < 0)
      return 0;
   else
      return _string[i];
}
int MyString::length() const
{
   return string_length;
}
int MyString::capacity() const
{
   return memory_capacity;
}
void MyString::print() const
{
   std::cout << _string;
}
void MyString::println() const
{
   std::cout << _string << std::endl;
}

int main()
{
   MyString str("abcdef");
   str[3] = 'c';

   str.println();
}