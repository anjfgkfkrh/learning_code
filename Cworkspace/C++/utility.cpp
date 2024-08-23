#include "utils.h"

namespace MyExcel
{
   // ====================
   //     Vector 시작
   // ====================

   template <typename T>
   Vector<T>::Vector(int n) : data(new T[n]), capacity(n), length(0) {}

   template <typename T>
   void Vector<T>::push_back(T s)
   {
      if (length >= capacity)
      {
         capacity *= 2;
         T* temp = new T[capacity];
         for (int i = 0; i < length; i++)
            temp[i] = data[i];
         delete[] data;
         data = temp;
      }
      data[length] = s;
      length++;
   }

   template <typename T>
   T Vector<T>::operator[](int i)
   {
      return data[i];
   }

   template <typename T>
   void Vector<T>::remove(int x)
   {
      for (int i = x; i < length - 1; i++)
         data[i] = data[i + 1];
      length--;
   }

   template <typename T>
   int Vector<T>::size()
   {
      return length;
   }

   template <typename T>
   Vector<T>::~Vector()
   {
      if (data)
         delete[] data;
   }

   // ====================
   //     Vector<T> 끝
   // ====================
   //     Vector<bool> 시작
   // ====================

   Vector<bool>::Vector(int n) : data(new unsigned int[n / 32 + 1]), capacity(n / 32 + 1), length(0) {
      for (int i = 0; i < capacity;i++)
         data[i] = 0;
   }

   void Vector<bool>::push_back(bool s) {
      if (capacity * 32 <= length) {
         unsigned int* temp = new unsigned int[capacity * 2];
         for (int i = 0; i < capacity; i++)
            temp[i] = data[i];
         for (int i = 0; i < capacity; i++)
            temp[i] = 0;

         delete[] data;
         data = temp;
         capacity *= 2;
      }

      if (s)
         data[length / 32] |= (1 << (length % 32));

      length++;
   }

   bool Vector<bool>::operator[](int i) { return (data[i / 32] & (1 << (i % 32))) != 0; }

   void Vector<bool>::remove(int x) {
      for (int i = x + 1; i < length; i++) {
         int prev = i - 1;
         int curr = i;

         // 만일 curr 위치에 있는 비트가 1 이라면
         // prev 위치에 있는 비트를 1로 만든다.
         if (data[curr / 32] & (1 << (curr % 32)))
            data[prev / 32] |= (1 << (prev % 32));
         // 아니면 prev 위치에 있는 비트를 0으로 지운다
         else {
            unsigned int all_ones_except_prev = 0xFFFFFFFF;
            all_ones_except_prev ^= (1 << (prev % 32));
            data[prev / 32] &= all_ones_except_prev;
         }
      }
      length--;
   }

   int Vector<bool>::size() { return length; }
   Vector<bool>::~Vector() {
      if (data)
         delete[] data;
   }


   // ====================
   //     Vector<bool> 끝
   // ====================
   //     Stack 시작
   // ====================

   Stack::Stack() : start(NULL, "")
   {
      current = &start;
   }

   void Stack::push(std::string s)
   {
      Node* n = new Node(current, s);
      current = n;
   }

   std::string Stack::pop()
   {
      if (current == &start)
         return "";

      std::string s = current->s;
      Node* n = current;
      current = current->prev;

      delete n;
      return s;
   }

   std::string Stack::peek()
   {
      return current->s;
   }

   bool Stack::is_empty()
   {
      return current == &start;
   }

   Stack::~Stack()
   {
      while (current != &start)
      {
         Node* n = current;
         current = current->prev;
         delete n;
      }
   }

   // ====================
   //     Stack 끝
   //     NumStack 시작
   // ====================

   NumStack::NumStack() : start(NULL, 0)
   {
      current = &start;
   }

   void NumStack::push(double s)
   {
      Node* n = new Node(current, s);
      current = n;
   }

   double NumStack::pop()
   {
      if (current == &start)
         return 0;

      double s = current->s;
      Node* n = current;
      current = current->prev;

      delete n;
      return s;
   }

   double NumStack::peek()
   {
      return current->s;
   }

   bool NumStack::is_empty()
   {
      return current == &start;
   }

   NumStack::~NumStack()
   {
      while (current != &start)
      {
         Node* n = current;
         current = current->prev;
         delete n;
      }
   }

}