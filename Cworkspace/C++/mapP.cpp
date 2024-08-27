#include <iostream>
#include <map>
#include <string>

template <typename K, typename V>
void print_map(std::map<K, V>& m) {
   //맵의 모든 원소들을 출력하기
   for (auto itr = m.begin(); itr != m.end(); ++itr)
      std::cout << itr->first << " " << itr->second << std::endl;

   // for (const auto& kv : m)
   //    std::cout << kv->first << " " << kv->second << std::endl;
}

template <typename K, typename V>
void print_map(std::multimap<K, V>& m) {
   for (const auto& kv : m)
      std::cout << kv.first << " " << kv.second << std::endl;
}

template <typename K, typename V>
void search_and_print(std::map<K, V>& m, K key) {
   auto itr = m.find(key);
   if (itr != m.end())
      std::cout << key << "--> " << itr->second << std::endl;
   else
      std::cout << key << "은(는) 목록에 없습니다" << std::endl;
}

// map
// int main() {
//    std::map<std::string, double> pitcher_list;

//    // 참고로 2017년 7월 4일 투수 방어률 순위

//    // 맵의 insert함수는 pair 객체를 인자로 받음
//    pitcher_list.insert(std::pair<std::string, double>("박세옹", 2.23));
//    pitcher_list.insert(std::pair<std::string, double>("해커", 2.83));
//    pitcher_list.insert(std::pair<std::string, double>("피어밴드", 2.95));

//    // 타입을 지정하지 않아도 간단히 std::make_pair 함수로
//    // std::pair 객체를 만들 수 도 있다.
//    pitcher_list.insert(std::make_pair("자우찬", 3.04));
//    pitcher_list.insert(std::make_pair("장원준", 3.05));
//    pitcher_list.insert(std::make_pair("헥터", 3.09));

//    // 혹은 insert를 안쓰더라도 []로 바로
//    // 원소를 추가할 수 있다.
//    pitcher_list["니퍼트"] = 3.56;
//    pitcher_list["박종훈"] = 3.76;
//    pitcher_list["켈리"] = 3.90;

//    print_map(pitcher_list);
//    std::cout << "-------------------------" << std::endl;

//    search_and_print(pitcher_list, std::string("박종훈"));
//    search_and_print(pitcher_list, std::string("류현진"));
// }


// multimap
// 하나의 키의 여러개의 값을 저장하기 때문에 
// [] 연산자 사용 불가
int main() {
   std::multimap<int, std::string> m;
   m.insert(std::make_pair(1, "hello"));
   m.insert(std::make_pair(1, "hi"));
   m.insert(std::make_pair(1, "ahihi"));
   m.insert(std::make_pair(2, "bye"));
   m.insert(std::make_pair(2, "baba"));

   print_map(m);

   // 아무거나 나옴
   std::cout << "---------------------------" << std::endl;
   std::cout << m.find(1)->second << std::endl;

   // 1을 키로 가지는 반복자들의 시작과 끝을
   // std::pair로 만들어서 리턴한다
   // range->first는 시작 itr, range->second는 끝 itr
   auto range = m.equal_range(1);
   for (auto itr = range.first; itr != range.second; ++itr)
      std::cout << itr->first << " : " << itr->second << " " << std::endl;
}