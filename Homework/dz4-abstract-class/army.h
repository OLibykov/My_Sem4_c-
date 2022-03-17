
#include "superman.h"
class Army{
public:
    Hero* cohort;
    Army(int type){
        if (type == 0){
            cohort = new Superman[5];
            Superman s1(1, 2);
            cohort[0] = s1;
            cohort[1] = s1;
            cohort[2] = s1;
            cohort[3] = s1;
            cohort[4] = s1;
        }
        else if (type == 1){
            cohort = new Batman[5];
            Batman s1(15, 20);
            cohort[0] = s1;
            cohort[1] = s1;
            cohort[2] = s1;
            cohort[3] = s1;
            cohort[4] = s1;
        }
        else if (type == 2){
            cohort = new Magician[5];
            Magician s1(13, 24, 332);
            cohort[0] = s1;
            cohort[1] = s1;
            cohort[2] = s1;
            cohort[3] = s1;
            cohort[4] = s1;
        }
    }
    void Show(){
        for (int i = 0; i < 5; i++){
            cohort[i].Print();
        }
    }
};


