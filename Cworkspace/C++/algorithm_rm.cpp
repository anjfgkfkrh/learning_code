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

// int main() {
//    std::vector<int> vec;
//    vec.push_back(5);
//    vec.push_back(3);
//    vec.push_back(1);
//    vec.push_back(2);
//    vec.push_back(3);
//    vec.push_back(4);

//    std::cout << "처음 vec 상태 -------" << std::endl;
//    print(vec.begin(), vec.end());

//    std::cout << "벡터에서 값이 3 인 원소 제거 ---" << std::endl;
//    // remove()는 원소를 삭제하는것이 아닌 해당 원소를 만났을때 뒤의 원소를 앞으로 시프팅 함
//    // 따라서 해당 원소의 개수만큼 멘 뒤에 빈 공간이 생김
//    // vec.end()는 맨 뒤가 아닌 시프팅 횟수만큼 앞으로 오게 됨
//    vec.erase(std::remove(vec.begin(), vec.end(), 3), vec.end());
//    print(vec.begin(), vec.end());
// }

struct is_odd {
   int* num_delete;

   is_odd(int* num_delete) : num_delete(num_delete) {}

   bool operator()(const int& i) {
      if (*num_delete >= 2)
         return false;

      if (i % 2 == 1) {
         (*num_delete)++;
         return true;
      }
      return false;
   }
};
bool odd(const int& i) { return i % 2 == 1; }
int main() {
   std::vector<int> vec;
   vec.push_back(5);
   vec.push_back(3);
   vec.push_back(1);
   vec.push_back(2);
   vec.push_back(3);
   vec.push_back(4);

   std::cout << "처음 vec 상태 ------" << std::endl;
   print(vec.begin(), vec.end());

   /* 함수 객체 사용 */

   // std::cout << "벡터에서 홀수 인 원소 제거 ---" << std::endl;
   // // vec.erase(std::remove_if(vec.begin(), vec.end(), is_odd()), vec.end()); // 함수 객체 사용
   // vec.erase(std::remove_if(vec.begin(), vec.end(), odd), vec.end()); // 일반 함수 사용
   // print(vec.begin(), vec.end());

   ////////////////////////////////////////////////////////////////////////////////////

   // 일정 개수 만큼만 제거
   // remove_if() 구조상 함수 객체 안에 변화하는 변수를 생성 시
   // 작동이 이상해질 수 있음
   // 따라서 외부에 변수를 만들고 함수 객체에 전달함

   // std::cout << "벡터에서 홀수인 원소 앞의 2개 제거 --- " << std::endl;
   // int num_delete = 0;
   // vec.erase(std::remove_if(vec.begin(), vec.end(), is_odd(&num_delete)), vec.end());
   // print(vec.begin(), vec.end());

   // but STL 사용할때 마다 외부에 클래스나 함수를 하나 씩 만들어줘야함
   // 협업시 다른 개발자가 의도를 파악하기 힘듦으로
   // STL 알고리즘을 사용할 때 그 안에 직접 써놓자
   // 람다 함수를 이용하면 됨


   ////////////////////////////////////////////////////////////////////////////////////
   ////////////////////////////////////////////////////////////////////////////////////
   ////////////////////////////////////////////////////////////////////////////////////

   /* 람다 함수 사용 */

   // 리턴 타입 생략 가능
   // 컴파일러가 return으로 추론 가능
   // [](int i){ return i % 2 == 1;}

   // 람다 함수 생성과 동시에 사용
   // [](int i){ return i % 2 == 1;}(3); // true
   // 람다 함수 저장 및 사용
   // auto func = [](int i){ return i % 2 == 1;};
   // func(4); // false;

   // std::cout << "백터에서 홀수인 원소 제거 ---" << std::endl;
   // vec.erase(std::remove_if(vec.begin(), vec.end(), [](int i)-> bool {return i % 2 == 1;}), vec.end());
   // print(vec.begin(), vec.end());

   ////////////////////////////////////////////////////////////////////////////////////


   std::cout << "벡터에서 홀수인 원소 ---" << std::endl;
   int num_erased = 0;
   vec.erase(std::remove_if(vec.begin(), vec.end(), [&num_erased](int i) {
      if (num_erased >= 2) return false;
      else if (i % 2 == 1) {
         num_erased++;
         return true;
      }
      return false;}),
      vec.end());
   print(vec.begin(), vec.end());
}