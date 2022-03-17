#include "dlist.h"

 
List::List()
{
   Head = Tail = NULL;
   Count = 0;
}
 
List::List(const List & L)
{
   Head = Tail = NULL;
   Count = 0;
 
   Elem * temp = L.Head;
   while(temp != 0)
   {
      push_back(*temp);
      temp = temp->next;
   }
}
 
List::~List()
{
   DelAll();
}
 
void List::push_front(Elem& n)
{
   Elem * temp = new Elem;
 
   temp->prev = 0;
   strcpy(temp->name, n.name);
   temp->number = n.number;
   temp->id = n.id;
   temp->next = Head;
 
   if(Head != 0)
      Head->prev = temp;
 
   if(Count == 0)
      Head = Tail = temp;
   else
      Head = temp;
 
   Count++;
}

int List::front(){
    return Head->id;
}
int List::back(){
    return Head->id;
}
bool List::empty(){
    return Size() == 0;
}

void List::pop_front(){
    erase(1);
}

void List::pop_back(){
    erase(Size());
}
 
void List::push_back(Elem& n)
{
   Elem * temp = new Elem;
   temp->next = 0;
   strcpy(temp->name, n.name);
   temp->number = n.number;
   temp->id = n.id;
   temp->prev = Tail;
 
   if(Tail != 0)
      Tail->next = temp;
 
   if(Count == 0)
      Head = Tail = temp;
   else
   Tail = temp;
 
   Count++;
}
 
void List::Insert(int pos, Elem& d)
{
 
   if(pos < 1 || pos > Count + 1)
   {
      cout << "Incorrect position !!!\n";
      return;
   }
 
   if(pos == Count + 1)
   {
      push_back(d);
      return;
   }
   else if(pos == 1)
   {
      push_front(d);
      return;
   }
 
   int i = 1;
 
   Elem * Ins = Head;
 
   while(i < pos)
   {
      Ins = Ins->next;
      i++;
   }
 
   Elem * PrevIns = Ins->prev;
 
   Elem * temp = new Elem;
 
   strcpy(temp->name, d.name);
   temp->number = d.number;
   temp->id = d.id;
 
   if(PrevIns != 0 && Count != 1)
      PrevIns->next = temp;
 
   temp->next = Ins;
   temp->prev = PrevIns;
   Ins->prev = temp;
 
   Count++;
}
 
void List::erase(int pos)
{
   if(pos < 1 || pos > Count)
   {
      cout << "Incorrect position !!!\n";
      return;
   }
 
   int i = 1;
 
   Elem * Del = Head;
 
   while(i < pos)
   {
      Del = Del->next;
      i++;
   }
 
   Elem * PrevDel = Del->prev;
   Elem * AfterDel = Del->next;
 
   if(PrevDel != 0 && Count != 1)
      PrevDel->next = AfterDel;
    if(AfterDel != 0 && Count != 1)
      AfterDel->prev = PrevDel;
 
   if(pos == 1)
       Head = AfterDel;
   if(pos == Count)
       Tail = PrevDel;
 
   delete Del;
 
   Count--;
}
 
void List::Print(int pos)
{
   if(pos < 1 || pos > Count)
   {
      cout << "Incorrect position !!!\n";
      return;
   }
 
   Elem * temp;

   temp = Head;
   int i = 1;

   while(i < pos)
   {
      temp = temp->next;
      i++;
   }
   cout << pos << " element: ";
   cout << temp->name << " " << temp->number << " " << temp->id << endl;
}
 
void List::Print()
{
   if(Count != 0)
   {
      Elem * temp = Head;
      cout << "{ ";
      while(temp->next != 0)
      {
          cout << temp->name << " " << temp->number << " " << temp->id << ",\n";
          temp = temp->next;
      }
 
      cout << temp->name << " " << temp->number << " " << temp->id << " }\n";
   }
}
 
void List::DelAll()
{
   while(Count != 0)
      erase(1);
}
 
int List::Size()
{
    return Count;
}
 
Elem * List::GetElem(int pos)
{
   Elem *temp = Head;
 
   if(pos < 1 || pos > Count)
   {
      cout << "Incorrect position !!!\n";
      return 0;
   }
 
   int i = 1;
   while(i < pos && temp != 0)
   {
      temp = temp->next;
      i++;
   }
 
   if(temp == 0)
      return 0;
   else
      return temp;
}
 
List & List::operator = (const List & L)
{
    if(this == &L)
       return *this;
 
   this->~List(); // DelAll();
 
   Elem * temp = L.Head;
 
   while(temp != 0)
   {
      push_back(*temp);
      temp = temp->next;
   }
 
   return *this;
}
 
