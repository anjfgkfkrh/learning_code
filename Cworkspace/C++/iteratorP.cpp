#include <iostream>
#include <vector>
#include <list>
#include <deque>

// int main() {
//    std::vector<int> vec;
//    vec.push_back(10);
//    vec.push_back(20);
//    vec.push_back(30);
//    vec.push_back(40);

//    // 전체 백터를 출력하기
//    for (std::vector<int>::iterator itr = vec.begin(); itr != vec.end(); ++itr) {
//       std::cout << *itr << std::endl;
//    }

//    std::vector<int>::iterator itr = vec.begin() + 2;
//    std::cout << "3 번째 원소 :: " << *itr << std::endl;
// }

template <typename T>
void print_vector(std::vector<T>& vec) {
   std::cout << "[";
   for (typename std::vector<T>::iterator itr = vec.begin(); itr != vec.end(); ++itr) {
      std::cout << *itr << " ";
   }
   std::cout << "]" << std::endl;
}

// vector
// int main() {
//    std::vector<int> vec;
//    vec.push_back(10);
//    vec.push_back(20);
//    vec.push_back(30);
//    vec.push_back(40);

//    std::cout << "처음 백터 상태" << std::endl;
//    print_vector(vec);
//    std::cout << "----------------------------" << std::endl;


//    // // vec[2] 앞에 15 추가
//    // vec.insert(vec.begin() + 2, 15);
//    // print_vector(vec);

//    // std::cout << "----------------------------" << std::endl;
//    // // vec[3] 제거
//    // vec.erase(vec.begin() + 3);
//    // print_vector(vec);

//    /////////////////////////////////////////////////////////////////////////////
//    /////////////////////////////////////////////////////////////////////////////

//    // std::vector<int>::iterator itr = vec.begin();

//    // for (; itr != vec.end(); ++itr) {
//    //    if (*itr == 20) {
//    //       vec.erase(itr);
//    //       itr = vec.begin();
//    //    } // 삭제, 추가시 기존 itr 사용 불가
//    // }

//    // print_vector(vec);

//    /////////////////////////////////////////////////////////////////////////////
//    /////////////////////////////////////////////////////////////////////////////

//    // std::vector<int>::iterator itr = vec.begin() + 2;

//    // *itr = 50;

//    // std::cout << "-----------------------" << std::endl;
//    // print_vector(vec);

//    // std::vector<int>::const_iterator citr = vec.cbegin() + 2;

//    // 상수 반복자가 가리키는 값은 바꿀수 없다.
//    // *citr = 30;
//    // 불가능


//    /////////////////////////////////////////////////////////////////////////////
//    /////////////////////////////////////////////////////////////////////////////

//    std::cout << "역으로 vec 출력하기!" << std::endl;
//    // itr은 vec[2]를 가리킨다.
//    auto r_iter = vec.rbegin();
//    std::cout << "역 itr 사용" << std::endl;
//    for (; r_iter != vec.rend(); r_iter++)
//       std::cout << *r_iter << std::endl;

//    /////////////////////////////////////////////////////////////////////////////
//    /////////////////////////////////////////////////////////////////////////////

//    std::cout << "범위기반 for문 사용" << std::endl;
//    // for (int elem : vec)
//    //    std::cout << elem << std::endl;

//    for (const auto& elem : vec)
//       std::cout << elem << std::endl;

// }

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

template <typename T>
void print_list(std::list<T>& lst) {
   std::cout << "[ ";
   for (const auto& elem : lst)
      std::cout << elem << " ";

   std::cout << "]" << std::endl;
}


// int main() {
//    std::list<int> lst;

//    lst.push_back(10);
//    lst.push_back(20);
//    lst.push_back(30);
//    lst.push_back(40);

//    // for (std::list<int>::iterator itr = lst.begin(); itr != lst.end(); ++itr)
//    //    std::cout << *itr << std::endl;

//    // list는 itr + 2 같은 연산 불가
//    // 오로지 ++ , -- 연산만 가능

//    std::cout << "처음 리스트의 상태 " << std::endl;
//    print_list(lst);

//    for (auto itr = lst.begin(); itr != lst.end(); itr++)
//       if (*itr == 20)
//          lst.insert(itr, 50); // 리스트는 삽입 후 이터레이터 계속 사용 가능

//    std::cout << "값이 20인 원소 앞에 50을 추가 " << std::endl;
//    print_list(lst);

//    for (auto itr = lst.begin(); itr != lst.end(); itr++)
//       if (*itr == 30) {
//          lst.erase(itr);
//          break; // 리스트는 원소 삭제 후 이터레이터 계속 사용 가능
//       }

//    std::cout << "값이 30 인 원소를 제거한다" << std::endl;
//    print_list(lst);
// }

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

template <typename T>
void print_deque(std::deque<T>& dq) {
   std::cout << "[ ";
   for (const auto& elem : dq)
      std::cout << elem << " ";
   std::cout << " ] " << std::endl;
}

int main() {
   std::deque<int> dq;
   dq.push_back(10);
   dq.push_back(20);
   dq.push_back(30);
   dq.push_back(40);

   std::cout << "초기 dq 상태" << std::endl;
   print_deque(dq);

   std::cout << "멘 앞의 원소 제거" << std::endl;
   dq.pop_front();
   print_deque(dq);
}