#include <iostream>
#include <set>
#include <unordered_set>

// template <typename T>
// void print_set(std::set<T>& s) {
//    // 셋의 모든 원소들을 출력하기
//    std::cout << "[ ";
//    for (auto itr = s.begin(); itr != s.end(); ++itr) {
//       std::cout << *itr << " ";
//    }
//    std::cout << " ] " << std::endl;
// }

// int main() {
//    std::set<int> s;
//    s.insert(10);
//    s.insert(50);
//    s.insert(20);
//    s.insert(40);
//    s.insert(30);

//    std::cout << "순서대로 정렬되서 나온다" << std::endl;
//    print_set(s);

//    std::cout << "20 이 s 의 원소인가요? :: ";
//    auto itr = s.find(20);
//    if (itr != s.end())
//       std::cout << "Yes" << std::endl;
//    else
//       std::cout << "No" << std::endl;


//    std::cout << "25 가 s 의 원소인가요? :: ";
//    itr = s.find(25);
//    if (itr != s.end())
//       std::cout << "Yes" << std::endl;
//    else
//       std::cout << "No" << std::endl;

// }

template<typename T, typename C>
void print_set(std::set<T, C>& s) {
   for (const auto& elem : s)
      std::cout << elem << " " << std::endl;
}

class Todo {
   int priority; // 중요도. 높을 수록 급한것!
   std::string job_desc; // 할 일

public:
   Todo(int priority, std::string job_desc) : priority(priority), job_desc(job_desc) {}

   // bool operator<(const Todo& t) const {
   //    if (priority == t.priority) // 이 조건 없으면 priority가 같을 시, 두 개를 같은 것으로 인식해 하나를 삭제 함
   //       return job_desc < t.job_desc;
   //    return priority > t.priority;
   // }

   // hash 함수에서 사용 
   bool operator==(const Todo& t) const {
      if (priority == t.priority && job_desc == t.job_desc)
         return true;
      return false;
   }

   friend struct TodoCmp;
   friend struct std::hash<Todo>;
   friend std::ostream& operator<<(std::ostream& os, const Todo& t);
};
struct TodoCmp { // 만약 Todo가 기존 클래스여서 수정을 못할 경우
   bool operator()(const Todo& t1, const Todo& t2) const {
      if (t1.priority == t2.priority)
         return t1.job_desc < t2.job_desc;
      return t1.priority > t2.priority;
   }
};

std::ostream& operator<<(std::ostream& os, const Todo& t) {
   os << "[ 중요도: " << t.priority << "] " << t.job_desc;
   return os;
}


// int main() {
//    std::set<Todo, TodoCmp> todos;

//    todos.insert(Todo(1, "농구 하기"));
//    todos.insert(Todo(2, "수학 숙제 하기"));
//    todos.insert(Todo(1, "프로그래밍 프로젝트"));
//    todos.insert(Todo(3, "친구 만나기"));
//    todos.insert(Todo(2, "영화 보기"));

//    print_set(todos);

//    std::cout << "-------------" << std::endl;
//    std::cout << "숙제를 끝냈다면!" << std::endl;
//    todos.erase(todos.find(Todo(2, "수학 숙제 하기")));
//    print_set(todos);
// }


// multiset
template<typename K>
void print_set(const std::multiset<K>& s) {
   for (const auto& elem : s)
      std::cout << elem << std::endl;
}

// int main() {
//    std::multiset<std::string> s;

//    s.insert("a");
//    s.insert("b");
//    s.insert("a");
//    s.insert("c");
//    s.insert("d");
//    s.insert("c");

//    print_set(s);
// }




// unordered set
// 정렬되지 않은 셋 (해쉬 셋)x
template <typename K>
void print_unordered_set(const std::unordered_set<K>& m) {
   for (const auto& elem : m)
      std::cout << elem << std::endl;
}

template <typename K>
void is_exist(std::unordered_set<K>& s, K key) {
   auto itr = s.find(key);
   if (itr != s.end())
      std::cout << key << " 가 존재!" << std::endl;
   else
      std::cout << key << " 가 없다" << std::endl;
}

// Todo 해시 힘수를 위한 함수객체(functor)를 만들어줌
// std namespace 안에 정의
namespace std {
   template<>
   struct hash<Todo> {
      size_t operator()(const Todo& t) const {
         hash<string> hash_func;

         return t.priority ^ (hash_func(t.job_desc));
      }
   };
}

int main() {
   // std::unordered_set<std::string> s;

   // s.insert("hi");
   // s.insert("my");
   // s.insert("name");
   // s.insert("is");
   // s.insert("ljh");
   // s.insert("welcome");
   // s.insert("to");
   // s.insert("c++");

   // print_unordered_set(s);
   // std::cout << "-----------------------------"<< std::endl;
   // is_exist(s,std::string("c++"));
   // is_exist(s,std::string("c"));

   // std::cout << "-----------------------------" << std::endl;
   // std::cout <<"'hi' 를 삭제" <<std::endl;
   // s.erase(s.find("hi"));
   // is_exist(s, std::string("hi"));

   std::unordered_set<Todo> todos;

   todos.insert(Todo(1, "농구하기"));
   todos.insert(Todo(2, "수학 숙제 하기"));
   todos.insert(Todo(1, "프로그래밍 프로젝트"));
   todos.insert(Todo(3, "친구 만나기"));
   todos.insert(Todo(2, "영화보기"));
   print_unordered_set(todos);
   std::cout << "------------------------" << std::endl;
}
