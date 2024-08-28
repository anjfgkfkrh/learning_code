#include <cctype>
#include <iostream>
#include <string>
using namespace std::literals; // ""s 를 사용하기 위한 namespace

/* 문자열 연산 클래스 만들어보기 */

// char_traits 의 모든 함수들은 static 함수 입니다.
struct my_char_traits : public std::char_traits<char> {
   static int get_real_rank(char c) {
      // 숫자면 순위를 엄청 떨어트린다.
      if (isdigit(c))
         return c + 256;
      return c;
   }

   static bool lt(char c1, char c2) {
      return get_real_rank(c1) < get_real_rank(c2);
   }

   static int compare(const char* s1, const char* s2, size_t n) {
      while (n-- != 0) {
         if (get_real_rank(*s1) < get_real_rank(*s2))
            return -1;
         if (get_real_rank(*s1) > get_real_rank(*s2))
            return 1;
         ++s1;
         ++s2;
      }
      return 0;
   }
};

// int main() {
//    std::basic_string<char, my_char_traits> my_s1 = "1a";
//    std::basic_string<char, my_char_traits> my_s2 = "a1";

//    std::cout << "숫자의 우선순위가 더 낮은 무낮열 : " << std::boolalpha << (my_s1 < my_s2) << std::endl;

//    std::string s1 = "1a";
//    std::string s2 = "a1";

//    std::cout << "일반 문자열 : " << std::boolalpha << (s1 < s2) << std::endl;

// }

///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////

/* 짧은 문자열 최적화 */


// 이와 같이 new 를 전역 함수로 정의하면 모든 new 연산자를 오버로딩 해버린다.
// (어떤 클래스의 멤버 함수로 정의하면 해당 클래스의 new 오버로딩됨)
void* operator new(std::size_t count) {
   std::cout << count << " bytes 할당 " << std::endl;
   return malloc(count);
}

// int main() {
//    std::cout << "s1 생성 --- " << std::endl;
//    std::string s1 = "this is a pretty long sentence!!!";
//    std::cout << "s1 크기 : " << sizeof(s1) << std::endl;

//    std::cout << "s2 생성 --- " << std::endl;
//    std::string s2 = "short sentence";
//    std::cout << "s2 크기 : " << sizeof(s2) << std::endl;

//    auto str1 = "hello"; // const char* 으로 저장됨
//    auto str2 = "hello"s; // string 객체로 저장됨, 사용을 위해선 namespace 추가 필요

//    std::string str3 = R"(asdfasdf
//    이 안에는
//    어떤 것들이 와도
//    // 이런것도 되고
//    #define hasldasjdflkajsg
//    \n\n <--- Escape 안해도 됨
//    )";
//    // but )" 은 무시됨

//    std::cout << str3 << std::endl;

//    std::string str4 = R"foo(
//    )" 이제 무시 안됨
//    )foo";
//    //이처럼 "와 ( 사이에 어떤 값을 넣어주면 됨

//    std::cout << str4 << std::endl;
// }


///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////

/* 인코딩 방법 */

// int main() {
//    std::u32string u32_str = U"이건 UTF-32 문자열 입니다";
//    std::cout << u32_str.size() << std::endl;
//    // 문자열 길이가 나옴

//    std::u8string str = u8"이건 UTF-8 문자열 입니다";
//    std::cout << str.size() << std::endl;
//    // 메모리 크기가 나옴
// }

/* utf-8 */
// int main() {
//    std::string str = u8"이건 UTF-8 문자열 입니다.";
//    size_t i = 0;
//    size_t len = 0;

//    while (i < str.size()) {
//       int char_size = 0;

//       if ((str[i] & 0b111110000) == 0b11110000)
//          char_size = 4;
//       else if ((str[i] & 0b11110000) == 0b11100000)
//          char_size = 3;
//       else if ((str[i] & 0b11100000) == 0b11110000)
//          char_size = 2;
//       else if ((str[i] & 0b10000000) == 0b00000000)
//          char_size = 1;
//       else {
//          std::cout << "이상한 문자 발견!" << std::endl;
//          char_size = 1;
//       }

//       std::cout << str.substr(i, char_size) << std::endl;

//       i += char_size;
//       len++;
//    }
// }

/* UTF-16 */

// int main() {
//    std::u16string u16_str = u"안녕하세용 모두에 코드에 오신 것을 환영합니다";
//    std::string jaum[] = {
//       "ㄱ", "ㄲ", "ㄴ", "ㄷ", "ㄸ", "ㄹ", "ㅁ", "ㅂ", "ㅃ", "ㅅ", "ㅆ", "ㅇ", "ㅈ","ㅉ","ㅊ","ㅋ","ㅌ","ㅍ", "ㅎ"
//    };

//    for (char16_t c : u16_str) {
//       if (!(0xAC00 <= c && c <= 0xD7A3))
//          continue;

//       int offset = c - 0xAC00;
//       int jaum_offset = offset / 0x24C;
//       std::cout << jaum[jaum_offset];
//    }
// }


///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////

/* string view */

// 함수 인자로 string이나 char* 사용시 문자열을 인자로 받을때 string 또는 char*객체를 생성하여 메모리를 할당함
// 그에 따른 실행시간이 길어짐
bool contains_very(std::string_view str) {
   return str.find("very") != std::string_view::npos;
}

// int main() {
//    // string_view 생성 시에는 메모리 할당이 필요없다.
//    std::cout << std::boolalpha << contains_very("C++ string is very easy to use") << std::endl;

//    std::cout << contains_very("C++ string is not easy to use") << std::endl;

//    std::string str = "some long long long long long string"; // 메모리 할당 됨
//    std::cout << "--------------------" << std::endl;
//    std::cout << contains_very(str) << std::endl;
// }

int main() {
   std::cout << "string -----" << std::endl;
   std::string s = "sometimes string is very slow";
   std::cout << "--------------------" << std::endl;
   std::cout << s.substr(0, 20) << std::endl << std::endl;

   std::cout << "string_view ------" << std::endl;
   std::string_view sv = s;
   std::cout << "----------------------" << std::endl;
   std::cout << sv.substr(0, 20) << std::endl;
}