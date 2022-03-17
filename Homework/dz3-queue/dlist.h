#include <iostream>
#include <cstring>
using namespace std;
 
struct Elem
{
   char name[100];
   long int number;
   int id;
   Elem * next, * prev;
};
 
class List
{
   Elem * Head, * Tail;
   int Count;
 
public:
 
   List();
   List(const List&);
   ~List();
 
   int Size();
   Elem* GetElem(int pos);
 
   void DelAll();
   void erase(int pos = 0);
   void Insert(int pos, Elem& d);
 
   void push_back(Elem& n); 
   void push_front(Elem& n);
   int front();
   int back(); 

   void pop_front();
   void pop_back();

   void Print();
   void Print(int pos);

   int get_Count(){ return Count;}

   bool empty();
   List& operator = (const List&);
 
};
