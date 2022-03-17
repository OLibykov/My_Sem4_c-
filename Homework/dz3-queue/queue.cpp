#include "queue.h"

Queue::Queue() : List(){};
Queue::Queue(int size) : List(){
    max_size = size;
}
Queue::~Queue(){};
void Queue::back(Elem& n) {
    push_back(n);
    if (get_Count() > max_size){
        pop_back();
        cout << "\nqueue is full\n";
    }
}
int Queue::front(){
    return List::front();
}

void Queue::pop(){
    pop_front();
}

bool Queue::empty(){
    return List::empty();
}

int Queue::size(){
    return List::Size();
}

bool Queue::full(){
    return get_Count() >= max_size;
}

void Queue::Print(){
    List::Print();
}
