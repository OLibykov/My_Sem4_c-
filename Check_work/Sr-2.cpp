#include <iostream>
#include <cstring>
#include <cstdlib>

const double pi = 3.14;
using namespace std;
class Circle {
	int c_x;
	int c_y;
	int r;
	static int count_circle;
public:
	Circle() {
		r = 1;
		c_x = 1;
		c_y = 1;
		count_circle++;
	}
	Circle(int R, int C_X, int C_Y)  {
		r = R;
		c_x = C_X;
		c_y = C_Y;
		count_circle++;
	}
	~Circle() {
		count_circle--;
	}
	void Out() {
		cout << r << " " << c_x << " " << c_y << endl;
	}
	int Get_cx() { return c_x; }
	int Get_cy() { return c_y; }
	int Get_r() { return r; }
	int static Get_count_circle(){ return count_circle; }
	void dec_count_cir() {
		count_circle--;
	}
	virtual int type_cl() {
		cout << "Circle\n";
		return 0;
	}
	virtual void inc_size(int s) {
		r *= s;
	}
	virtual double square() {
		return pi*(r*r);
	}
};
class Ring : public Circle {
	int r_r;
	static int count_ring;
public:
	Ring() : Circle (){
		r_r = 0;
		count_ring++;
		dec_count_cir();
	}
	Ring(int R, int C_X, int C_Y, int R_R) : Circle (R, C_X, C_Y){
		count_ring++;
		dec_count_cir();
		try {
			if (R_R > R) {
				throw 1;
			}
			else {
				r_r = R_R;
			}
		}
		catch (int a) {
			if (a == 1) {
				r_r = Circle::Get_r();
			}
		}
	}
	~Ring() {
		count_ring--;
	}
	int Get_r_r() { return r_r; }
	int static Get_count_ring() { return count_ring; }
	void Out(){
		Circle::Out();
		cout << r_r << endl;
	}
	int Ring_count() {
		return count_ring;
	}
	int type_cl() {
		cout << "Ring\n";
		return 1;
	}
	void inc_size(int s) {
		r_r *= s;
	}
	double square() {
		double hlp = Circle::square();
		return hlp - pi * (r_r * r_r);
	}
};
int Ring::count_ring = 0;
int Circle::count_circle = 0;

int ptr_to(Circle* a) {
	return a->type_cl();
}

class Size {
	int a;
public:
	Size(int b = 1) {
		a = b;
	}
	Circle & operator () (Circle &c) {
		c.inc_size(a);
		return c;
	}
};
int main (){
	Circle C1, C2(5, 5, 5);
	//C1.Out();
	C2.Out();
	Ring R1, R2(5, 5, 5, 2), R3(5, 5, 5, 6);
	R2.Out();
	R2.Out();
	R3.Out();
	cout << C1.Get_count_circle() << endl;
	cout << R1.Ring_count() << endl;
	Circle* x = &R2;
	ptr_to(x);
	ptr_to(&C1);
	Size obj(2);
	obj(R2);
	obj(C2);
	C2.Out();
	R2.Out();
	cout << C2.square() << endl;
	cout << R2.square() << endl;
	return 0;
}