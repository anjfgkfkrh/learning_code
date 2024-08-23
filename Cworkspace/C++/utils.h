#ifndef UTILS_H
#define UTILS_H

#include <string>

namespace MyExcel
{
   template <typename T>
   class Vector
   {
      T* data;
      int capacity;
      int length;

   public:
      // 어떤 타입을 보관하는지
      typedef T value_type;

      // 생성자
      Vector(int n = 1);

      // 맨 뒤에 새로운 원소를 추가
      void push_back(T s);

      // 임의의 위치의 원소에 접근
      T operator[](int i);

      // x 번째 위치한 원소를 제거
      void remove(int x);

      // 현재 벡터의 크기를 구함
      int size();

      ~Vector();
   };

   template <>
   class Vector<bool> {
      unsigned int* data;
      int capacity;
      int length;

   public:
      typedef bool value_type;

      Vector(int n);

      void push_back(bool s);

      bool operator[](int i);

      void remove(int x);

      int size();
   };

   class Stack
   {
      struct Node
      {
         Node* prev;
         std::string s;

         Node(Node* prev, std::string s) : prev(prev), s(s) {};
      };

      Node* current;
      Node start;

   public:
      Stack();

      // 최상단에 새로운 원소 추가
      void push(std::string s);

      // 최상단의 원소를 제거하고 반환
      std::string pop();

      // 최상단의 원소를 반환 (제거 안함)
      std::string peek();

      // 스택이 비어있는지의 유무를 반환
      bool is_empty();

      ~Stack();
   };

   class NumStack
   {
      struct Node
      {
         Node* prev;
         double s;

         Node(Node* prev, double s) : prev(prev), s(s) {};
      };

      Node* current;
      Node start;

   public:
      NumStack();

      // 최상단에 새로운 원소 추가
      void push(double s);

      // 최상단의 원소를 제거하고 반환
      double pop();

      // 최상단의 원소를 반환 (제거 안함)
      double peek();

      // 스택이 비어있는지의 유무를 반환
      bool is_empty();

      ~NumStack();
   };
}
#endif