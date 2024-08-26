#include <iostream>

template <int X, int Y>
struct GCD {
   static const int value = GCD<Y, X% Y>::value;
};

template <int X>
struct GCD<X, 0> {
   static const int value = X;
};

template <int N, int D = 1>
struct Ratio {
private:
   const static int _gcd = GCD<N, D>::value;

public:
   using type = Ratio<N / _gcd, D / _gcd>;
   static const int num = N / _gcd;
   static const int den = D / _gcd;
};

// Rario add
template <class R1, class R2>
struct _Ratio_add {
   using type = Ratio<R1::num* R2::den + R2::num * R1::den, R1::den* R2::den>;
};
template <class R1, class R2>
struct Ratio_add : _Ratio_add<R1, R2>::type {};

// Ratio sub
template <class R1, class R2>
struct _Ratio_subtract {
   using type = Ratio<R1::num* R2::den - R2::num * R1::den, R1::den* R2::den>;
};
template <class R1, class R2>
struct Ratio_subtract : _Ratio_subtract<R1, R2>::type {};

// Ratio mul
template <class R1, class R2>
struct _Ratio_multiply {
   using type = Ratio<R1::num* R2::num, R1::den* R2::den>;
};
template <class R1, class R2>
struct Ratio_multiply : _Ratio_multiply<R1, R2>::type {};

// Ratio div
template <class R1, class R2>
struct _Ratio_divide {
   using type = Ratio<R1::num* R2::den, R1::den* R2::num>;
};
template <class R1, class R2>
struct Ratio_divide : _Ratio_divide<R1, R2>::type {};

// int main() {
//    using r1 = Ratio<2, 3>;
//    using r2 = Ratio<3, 2>;

//    using r3 = Ratio_add<r1, r2>;
//    std::cout << "2/3 + 3/2 = " << r3::num << " / " << r3::den << std::endl;

//    using r4 = Ratio_multiply<r1, r3>;
//    std::cout << "13 / 6 * 2 /3 = " << r4::num << " / " << r4::den << std::endl;
// }

////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
// 피보나치 수열
template <int n>
struct fib {
   static const int result = fib<n - 1>::result + fib<n - 2>::result;
};
template<>
struct fib<0> {
   static const int result = 0;
};
template<>
struct fib<1> {
   static const int result = 1;
};

// int main() {
//    std::cout << "5 번째 피보나치 수 :: " << fib<5>::result << std::endl;  // 5
// }

////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
// 소수 판별

// 템플릿 특수화시 연산자 사용 불가
// template <int N>
// struct check_div<N, N / 2> {
//   static const bool result = (N % (N / 2) == 0);
// };
// N/2 이런거 안됌

// TMP에서 사용가능한것
// 연산자

template <int N>
struct INT {
   static const int num = N;
};
// result가 값이 아닌 타입일 경우 사용시 앞에 typename을 붙여주어야함
// check_div 확인
template <typename a, typename b>
struct add {
   using result = INT<a::num + b::num>;
   // using 은 값과 타입 모두 가능해 사용시 컴파일러가 혼동하여 오류가 나올 수 있음
   // typedef INT<a::num + b::num> result;
};
// result가 값이 아닌 타입일 경우 사용시 앞에 typename을 붙여주어야함
// check_div 확인
template <typename a, typename b>
struct divide {
   using result = INT<a::num / b::num>;
   // using 은 값과 타입 모두 가능해 사용시 컴파일러가 혼동하여 오류가 나올 수 있음
   // typedef INT<a::num / b::num> result;
};

using one = INT<1>;
using two = INT<2>;
using three = INT<3>;

template <typename N, typename d>
struct check_div { // 재귀형식 반복문
   //result 중에 한 개라도 true 면 전체가 true
   static const bool result = (N::num % d::num == 0) || check_div<N, typename add<d, one>::result>::result;
};

template <typename N>
struct _is_prime {
   static const bool result = !check_div<N, two>::result;
};

template <>
struct _is_prime<two> {
   static const bool result = true;
};

template <>
struct _is_prime<three> {
   static const bool result = true;
};

template <typename N>
struct check_div<N, typename divide<N, two>::result> {
   static const bool result = (N::num % (N::num / 2) == 0);
};

template <int N>
struct is_prime {
   static const bool result = _is_prime<INT<N>>::result;
};

// int main()
// {
//    std::cout << std::boolalpha;
//    std::cout << "Is prime ? :: " << is_prime<2>::result << std::endl; // true
//    std::cout << "Is prime ? :: " << is_prime<10>::result << std::endl; // false
//    std::cout << "Is prime ? :: " << is_prime<11>::result << std::endl; // true
//    std::cout << "Is prime ? :: " << is_prime<61>::result << std::endl; // true
// }

////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////

// Unit - 단위

template <typename U, typename V, typename W>
struct Dim {
   using M = U; // kg
   using L = V; // m
   using T = W; // s

   using type = Dim<M, L, T>;
};

template <typename U, typename V>
struct add_dim_ {
   typedef Dim<typename Ratio_add<typename U::M, typename V::M>::type,
      typename Ratio_add<typename U::L, typename V::L>::type,
      typename Ratio_add<typename U::T, typename V::T>::type>
      type;
};
template <typename U, typename V>
struct subtract_dim_ {
   typedef Dim<typename Ratio_subtract<typename U::M, typename V::M>::type,
      typename Ratio_subtract<typename U::L, typename V::L>::type,
      typename Ratio_subtract<typename U::T, typename V::T>::type>
      type;
};

template <typename T, typename D>
struct quantity {
   T q;
   using dim_type = D;

   quantity operator+(quantity<T, D> quant) { return quantity<T, D>(q + quant.q); }
   quantity operator-(quantity<T, D> quant) { return quantity<T, D>(q - quant.q); }

   template <typename D2>
   quantity<T, typename add_dim_<D, D2>::type> operator*(quantity<T, D2> quant) {
      return quantity<T, typename add_dim_<D, D2>::type>(q * quant.q);
   }
   template <typename D2>
   quantity<T, typename subtract_dim_<D, D2>::type> operator/(quantity<T, D2> quant) {
      return quantity<T, typename subtract_dim_<D, D2>::type>(q / quant.q);
   }

   quantity<T, D> operator*(T scalar) { return quantity<T, D>(q * scalar); }
   quantity<T, D> operator/(T scalar) { return quantity<T, D>(q / scalar); }

   quantity(T q) :q(q) {}
};

template<typename T, typename D>
std::ostream& operator<<(std::ostream& out, const quantity<T, D>& q) {
   out << q.q << "kg^" << D::M::num / D::M::den << "m^" << D::L::num / D::L::den << "s^" << D::T::num / D::T::den;

   return out;
}

// int main() {
//    using one = Ratio<1, 1>;
//    using zero = Ratio<0, 1>;

//    quantity<double, Dim<one, zero, zero>> kg(1);
//    quantity<double, Dim<zero, one, zero>> meter(1);
//    quantity<double, Dim<zero, zero, one>> second(1);

//    // Good
//    kg + kg;

//    int a = 10;
//    // Bad
//    // kg + meter;
// }
int main() {
   using one = Ratio<1, 1>;
   using zero = Ratio<0, 1>;

   quantity<double, Dim<one, zero, zero>> kg(2);
   quantity<double, Dim<zero, one, zero>> meter(3);
   quantity<double, Dim<zero, zero, one>> second(1);

   // F 의 타입은 굳이 알필요 없다! // autoP 파일을 보자
   auto F = kg * meter / (second * second);
   std::cout << "2 kg 물체를 3m/s^2 의 가속도로 밀기 위한 힘의 크기는? " << F
      << std::endl;
}