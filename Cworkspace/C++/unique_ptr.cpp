#include <iostream>
#include <memory>
#include <vector>

class A {
   int* data;

public:
   A() {
      std::cout << "자원을 획득함!" << std::endl;
      data = new int[100];
   }

   void some() { std::cout << "일반 포인터와 동일하게 사용가능!" << std::endl; }

   ~A() {
      std::cout << "자원을 해재함!" << std::endl;
      delete[] data;
   }
};

void do_something() {
   std::unique_ptr<A> pa(new A());
   std::cout << "pa : ";
   pa->some();

   //pb에 소유권을 이전.
   std::unique_ptr<A> pb = std::move(pa);
   std::cout << "pb : ";
   pb->some();
}

void easy_unique_ptr() {
   auto pa = std::make_unique<A>(/* 생성자 인자 */);
   pa->some();
}

int main() {
   std::vector<std::unique_ptr<A>> vec;
   std::unique_ptr<A> pa(new A());

   // vec.push_back(pa); // 오류!
   vec.push_back(std::move(pa)); // 우측값으로 넘겨줘야 이동됨

   // vec.push_back(std::unique_ptr<A>(new A())); 와 동일
   vec.emplace_back(new A()); // 가능

   vec.back()->some();
}