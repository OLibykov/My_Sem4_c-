#include "dlist.h"

class Queue : private List {
    int max_size = 10;
public:
    Queue();
    Queue(int size);
    ~Queue();
    void back(Elem& n);
    int front();
    void pop();
    bool empty();
    int size();
    bool full();
    void Print();
};
