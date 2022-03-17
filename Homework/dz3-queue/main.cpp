#include "queue.h"
 
int main()
{
   Elem e1; strcpy(e1.name,  "roga\0"); e1.number = 89109264921; e1.id = 1;
   Elem e2; strcpy(e2.name, "kopyta\0"); e2.number = 89109264922; e2.id = 2;
   Elem e3; strcpy(e3.name, "shmot\0"); e3.number = 89109264923; e3.id = 3;

   Queue Q1(3);
   Q1.back(e1);
   Q1.back(e2);
   Q1.back(e3);
   Q1.back(e1);
   Q1.back(e2);
   Q1.Print();
   cout << Q1.size() << endl;
   cout << Q1.full() << endl;
   Q1.Print();
   while (!Q1.empty()){
       cout << Q1.front() << endl;
       Q1.pop();
   }

   return 0;
}
//g++ dlist.h dlist.cpp queue.h queue.cpp main.cpp 
