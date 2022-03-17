#include <iostream>

using namespace std;

class Hero{
private:
    int force;
    int speed;
    int magic;
public:
    ~Hero(){};
    virtual void Print() = 0;
    int getForce(){ return force; }
    int getSpeed(){ return speed; }
    int getMagic(){ return magic; }
    void setForce(int f) {force = f; }
    void setSpeed(int s) {speed = s; }
    void setMagic(int m) {magic = m; }
};


