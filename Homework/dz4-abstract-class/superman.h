#include "abst.h"


class Superman : public Hero
{
public:
    Superman(){
        setForce(10);
        setSpeed(100);
        setMagic(0);
    }
    Superman(int f, int s){
        setForce(f);
        setSpeed(s);
        setMagic(0);
    }
    ~Superman(){};
    void boost(){
        setSpeed(getSpeed() * 2);
    }
    void Print(){
        cout << getForce() << " " << getSpeed() << endl;
    }
};


class Batman : public Hero
{
public:
    Batman(){
        setForce(10);
        setSpeed(100);
        setMagic(2);
    }
    Batman(int f, int s){
        setForce(f);
        setSpeed(s);
    }
    ~Batman(){};
    void boom(){
        setForce(getForce() + 10);
    }
    void Print(){
        cout << getForce() << " " << getSpeed() << endl;
    }
};



class Magician : public Hero
{
public:
    Magician(){
        setForce(3);
        setSpeed(15);
        setMagic(10);
    }
    Magician(int f, int s, int m){
        setForce(f);
        setSpeed(s);
        setMagic(m);
    }
    ~Magician(){};
    void vengardium_leviosa(){
        cout << "OOOO";
    }
    void Print(){
        cout << getForce() << " " << getSpeed() << " " << getMagic() << endl;
    }
};

