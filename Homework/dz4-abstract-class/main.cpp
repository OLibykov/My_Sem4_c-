#include "army.h"

int main(){
    Army supermen(0);
    Army batmen(1);
    Army magicians(2);
    cout << endl << "army of SUPERMEN" << endl;
    supermen.Show();
    cout << endl << "army of BATMEN" << endl;
    batmen.Show();
    cout << endl << "army of MAGICIANS" << endl;
    magicians.Show();
    return 0;
}
