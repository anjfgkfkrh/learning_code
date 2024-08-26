#include <iostream>

// 템플릿 메타 프로그래밍
// TMP - Template Meta Programming

// 템플릿 사용시 만들어지는 구조체, 클래스들은 인스턴트화 되기 때문에 모두 독립적임
// 쉽게 말해 같은 클래스, 구조체 같아도 서로 다른 거임
// 따라서 서로 공유해야 하는 static 변수들도 공유하지 못함

/* 컴파일 타임 팩토리얼 계산 */
template <int N>
struct Factorial {
   static const int result = N * Factorial<N - 1>::result; // 재귀 형식
};

template<>
struct Factorial<1> {
   static const int result = 1;
};

// int main() {
//    std::cout << "6! = 1*2*3*4*5*6 = " << Factorial<6>::result << std::endl;
// }

int gcd(int a, int b) {
   if (b == 0)
      return a;
   return gcd(b, a % b);
}

// 위 재귀 함수를 TMP로 바꿈

template <int X, int Y>
struct GCD {
   static const int value = GCD<Y, X% Y>::value;
};

template <int X>
struct GCD<X, 0> {
   static const int value = X;
};

// int main() {
//    std::cout << "gcd (36, 24) :: " << GCD<36, 24>::value << std::endl;
// }

// 분수 구조체
template <int N, int D = 1>
struct Ratio {
   typedef Ratio<N, D> type;
   static const int num = N; // 분자
   static const int den = D; // 분모
};

// 분수 덧셈
template <class R1, class R2>
struct _Ratio_add {
   typedef Ratio<R1::num* R2::den + R2::num * R1::den, R1::den* R2::den> type;
};

template <class R1, class R2>
struct Ratio_add : _Ratio_add<R1, R2>::type {};


// using = typedef
int main() {
   // typedef Ratio<2, 3> rat;
   using rat = Ratio<2, 3>; // 위와 같음
   typedef Ratio<3, 2> rat2;
   // using rat2 Ratio<3, 2>; // 위와 같음
   typedef Ratio_add<rat, rat2> rat3;
   // using rat3 = Ratio_add<rat, rat2>; // 위와 같음

   std::cout << rat3::num << " / " << rat3::den << std::endl;

   return 0;
}