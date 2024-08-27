#include <algorithm>
#include <functional>
#include <iostream>
#include <string>
#include <vector>

template <typename Iter>
void print(Iter begin, Iter end) {
   while (begin != end) {
      std::cout << "[" << *begin << "]";
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

//    // 하나만 찾음
//    // auto result = std::find(vec.begin(), vec.end(), 3);
//    // std::cout << "3 은 " << std::distance(vec.begin(), result) + 1 << " 번째 원소" << std::endl;


//    // 모두 찾음
//    auto current = vec.begin();
//    while (true) {
//       // current = std::find(current, vec.end(), 3); //  일반 find() 함수
//       current = std::find_if(current, vec.end(), [](int i) { return i % 3 == 2;}); //  find_if() 함수
//       if (current == vec.end()) break;
//       std::cout << "3 으로 나눈 나머지가 2인 원소는 :  " << std::distance(vec.begin(), current) + 1 << " 번째 원소 " << *current << " 이다." << std::endl;
//       current++;
//    }
//    // find 함수를 자체적을 지원하는 컨테이너의 경우는 사용 x
//    // 컨테이너의 내부 정보를 모르기 때문에 훨씬 느림
// }

struct User {
   std::string name;
   int level;

   User(std::string name, int level) : name(name), level(level) {}
   bool operator==(const User& user) const {
      if (name == user.name && level == user.level) return true;
      return false;
   }
};

class Party {
   std::vector<User> users;

public:
   bool add_user(std::string name, int level) {
      User new_user(name, level);
      if (std::find(users.begin(), users.end(), new_user) != users.end())
         return false;
      users.push_back(new_user);
      return true;
   }

   // all_of()
   // 파티원 모두가 15 레벨 이상이어야지 던전 입장 가능
   bool can_join_dungeon() {
      return std::all_of(users.begin(), users.end(), [](User& user) {return user.level >= 15;});
   }

   // any_of()
   // 파티원 중 한명이라도 19렙 이상이면 특별 아이템 사용 가능
   bool can_use_special_item() {
      return std::any_of(users.begin(), users.end(), [](User& user) {return user.level >= 19;});
   }
};

int main() {
   Party party;
   party.add_user("철수", 15);
   party.add_user("영희", 18);
   party.add_user("민수", 12);
   party.add_user("수빈", 19);

   std::cout << std::boolalpha;
   std::cout << "던전 입장 가능 ? " << party.can_join_dungeon() << std::endl;
   std::cout << "특별 아이템 사용 가능 ?" << party.can_use_special_item() << std::endl;
}