#include <functional>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

int some_func1(const std::string& a) {
   std::cout << "Func1 호출1 " << a << std::endl;
   return 0;
}

struct S {
   void operator()(char c) { std::cout << "Func2 호출! " << c << std::endl; }
};

// int main() {
//    std::function<int(const std::string&)> f1 = some_func1;
//    std::function<void(char)> f2 = S();
//    std::function<void()> f3 = []() {std::cout << "Func3 호출!" << std::endl;};

//    f1("hello");
//    f2('c');
//    f3();
// }

// int main() {
//    std::vector<int> a(1);
//    std::vector<int> b(2);
//    std::vector<int> c(3);
//    std::vector<int> d(4);

//    std::vector<std::vector<int>> container;
//    container.push_back(b);
//    container.push_back(d);
//    container.push_back(a);
//    container.push_back(c);

//    std::function<size_t(const std::vector<int>&)> sz_func = &std::vector<int>::size;

//    std::vector<int> size_vec(4);
//    // std::transform(container.begin(), container.end(), size_vec.begin(), sz_func);
//    // std::transform(container.begin(), container.end(), size_vec.begin(), std::mem_fn(&std::vector<int>::size));
//    std::transform(container.begin(), container.end(), size_vec.begin(), [](const auto& v) { return v.size(); });
//    for (auto itr = size_vec.begin(); itr != size_vec.end(); ++itr) {
//       std::cout << "백터 크기 :: " << *itr << std::endl;
//    }
// }

///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////

// std::bind
// 함수 객체의 인자 지정
void add(int x, int y) {
   std::cout << x << " + " << y << " = " << x + y << std::endl;
}

void subtract(int x, int y) {
   std::cout << x << " - " << y << " = " << x - y << std::endl;
}
// int main() {
//    auto add_with_2 = std::bind(add, 2, std::placeholders::_1);
//    add_with_2(3);

//    // 두 번째 인자는 무시된다.
//    add_with_2(3, 4);

//    auto subtract_from_2 = std::bind(subtract, std::placeholders::_1, 2);
//    // 인자 순서 바꿈
//    // subtract(_1,_2) 순으로 호출됨
//       auto negate = std::bind(subtract, std::placeholders::_2, std::placeholders::_1);

//    subtract_from_2(3);
//    negate(4, 2);
// }

struct V {
   int data;
   V(int data) : data(data) { std::cout << "일반 생성자 호출!" << std::endl; }
   V(const V& v) {
      std::cout << "복사 생성자 호출!" << std::endl;
      data = v.data;
   }

   V(V&& v) {
      std::cout << "이동 생성자 호출!" << std::endl;
      data = v.data;
   }
};

void do_something(V& v1, const V& v2) { v1.data = v2.data + 3; }
int main() {
   V v1(1), v2(2);

   std::cout << "Before : " << v1.data << std::endl;

   // v1이 그대로 전달된 것이 아니라 v1의 복사본이 전달됨!
   // auto do_something_with_v1 = std::bind(do_something, v1, std::placeholders::_1);
   // v1을 레퍼런스로 전달
   auto do_something_with_v1 = std::bind(do_something, std::ref(v1), std::placeholders::_1);
   do_something_with_v1(v2);

   std::cout << "After :: " << v1.data << std::endl;
}