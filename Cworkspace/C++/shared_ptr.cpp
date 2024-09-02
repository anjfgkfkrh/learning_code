#include <iostream>
#include <memory>
#include <vector>

class A : public std::enable_shared_from_this<A> {
   int* data;

public:
   A() {
      data = new int[100];
      std::cout << "자원을 획득함!" << std::endl;
   }

   ~A() {
      std::cout << "자원을 해제함!" << std::endl;
      delete[] data;
   }

   std::shared_ptr<A> get_shared_ptr() { return shared_from_this(); }
};

int main() {
   // std::vector<std::shared_ptr<A>> vec;

   // vec.push_back(std::shared_ptr<A>(new A()));
   // vec.push_back(std::shared_ptr<A>(vec[0]));
   // vec.push_back(std::shared_ptr<A>(vec[1]));

   // // 백터의 첫번째 원소를 소멸 시킨다.
   // std::cout << "첫 번쨰 소멸!" << std::endl;
   // vec.erase(vec.begin());

   // // 그 다음 원소를 소멸 시킨다.
   // std::cout << "다음 원소 소멸!" << std::endl;
   // vec.erase(vec.begin());

   // // 마지막 원소 소멸
   // std::cout << "마지막 원소 소멸!" << std::endl;
   // vec.erase(vec.begin());


   // std::cout << "프로그램 종료!" << std::endl;

   auto pa1 = std::make_shared<A>();
   auto pa2 = pa1->get_shared_ptr();

   std::cout << pa1.use_count() << std::endl;
   std::cout << pa2.use_count() << std::endl;
}