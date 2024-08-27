#include <algorithm>
#include <functional>
#include <iostream>
#include <string>
#include <vector>

template<typename Iter>
void print(Iter begin, Iter end) {
   while (begin != end) {
      std::cout << "[" << *begin << "] ";
      begin++;
   }
   std::cout << std::endl;
}
// 아래 대신 greater<T>() 사용해도 됨
struct int_compare { // 내림차순 정렬을 위한 함수 객체
   bool operator()(const int& a, const int& b) const { return a > b; }
};

// int main() {
//    std::vector<int> vec;
//    vec.push_back(5);
//    vec.push_back(3);
//    vec.push_back(1);
//    vec.push_back(6);
//    vec.push_back(4);
//    vec.push_back(7);
//    vec.push_back(2);

//    std::cout << "정렬 전 -----" << std::endl;
//    print(vec.begin(), vec.end());

//    // sort
//    // std::sort(vec.begin(), vec.end(), int_compare()); // RandomAccessIterator 타입을 만족해야함으로 list는 안됨

//    // partial_sort
//    std::partial_sort(vec.begin(), vec.begin() + 3, vec.end());

//    std::cout << "정렬 후 -----" << std::endl;
//    print(vec.begin(), vec.end());
// }


struct User {
   std::string name;
   int age;
   User(std::string name, int age) : name(name), age(age) {}

   bool operator<(const User& u) const { return age < u.age; }
};

std::ostream& operator<<(std::ostream& o, const User& u) {
   o << u.name << " , " << u.age;
   return o;
}

int main() {
   std::vector<User> vec;
   for (int i = 0; i < 100;i++) {
      std::string name = "";
      name.push_back('a' + i / 26);
      name.push_back('a' + i % 26);
      vec.push_back(User(name, static_cast<int>(rand() % 10)));
   }

   std::vector<User> vec2 = vec;
   std::cout << "정렬 전 ----" << std::endl;
   print(vec.begin(), vec.end());

   std::sort(vec.begin(), vec.end());

   std::cout << "정렬 후 ----" << std::endl;
   print(vec.begin(), vec.end());

   std::cout << "stable_sort의 경우 ---" << std::endl;
   std::stable_sort(vec2.begin(), vec2.end());
   print(vec2.begin(), vec2.end());
}