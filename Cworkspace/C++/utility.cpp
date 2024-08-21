#include "utils.h"

namespace MyExcel
{
   // ====================
   //     Vector 시작
   // ====================

   Vector::Vector(int n) : data(new std::string[n]), capacity(n), length(0) {}

   void Vector::push_back(std::string s)
   {
      if (length >= capacity)
      {
         capacity *= 2;
         std::string* temp = new std::string[capacity];
         for (int i = 0; i < length; i++)
            temp[i] = data[i];
         delete[] data;
         data = temp;
      }
      data[length] = s;
      length++;
   }

   std::string Vector::operator[](int i)
   {
      return data[i];
   }

   void Vector::remove(int x)
   {
      for (int i = x; i < length - 1; i++)
         data[i] = data[i + 1];
      length--;
   }

   int Vector::size()
   {
      return length;
   }

   Vector::~Vector()
   {
      if (data)
         delete[] data;
   }

   // ====================
   //     Vector 끝
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