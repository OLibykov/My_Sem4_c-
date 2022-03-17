#include <iostream>
#include <cstring>
#include <cstdlib>

using namespace std;
class Arr {
	int *arr;
	int size;
public:
	Arr(int s, int date = 0) :size(s) {
		arr = new int[s];
		for (int i = 0; i < size; arr[i++] = date);
	}
	Arr(const Arr & AR) {
		size = AR.size;
		arr = new int[size];
		for (int i = 0; i < size; i++) {
			arr[i] = AR.arr[i] ;
		}
	}
	~Arr() {
		delete[] arr;
	}
	Arr(Arr && AR) {
		this->arr = AR.arr;
		this->size = AR.size;
		AR.size = 0;
		AR.arr = nullptr;
	}
	Arr & operator = (Arr && AR)
	{
		if (&AR == this)
			return *this;

		delete [] arr;

		arr = AR.arr;
		size = AR.size;
		AR.arr = nullptr;
		AR.size = 0;

		return *this;
	}
	friend ostream & operator<<(ostream &out, const Arr &AR) {
		for (int i = 0; i < AR.size; i++)
		{
			cout << AR.arr[i] << " ";
		}
		cout << "\n";
		return out;
	}
	friend ostream & operator<<(ostream &out, Arr &AR) {
		for (int i = 0; i < AR.size; i++) {
			cout << AR.arr[i] << " ";
		}
		cout << "\n";
		return out;
	}
	Arr & operator & (int a) {
		if (a == 0) {
			return *this;
		}
		for (int i = 0; i < size; i++) {
			arr[i] += a;
		}
		return *this;
	}
	Arr & operator & (const Arr & AR) {
		for (int i = 0; i < size; i++) {
			arr[i] += AR.arr[0];
		}
		return *this;
	}
	Arr operator & (const Arr & AR) const {
		//return const *this;
		Arr a(AR.size, AR.arr[0]);
		return a;
	}
	Arr & operator = (const Arr & AR) {
		if (this == &AR) {
			return *this;
		}
		delete[] arr;
		size = AR.size;
		arr = new int[10];
		for (int i = 0; i < size; i++) {
			arr[i] = AR.arr[i];
		}
		return *this;
	}
	Arr & operator ! () {
		for (int i = 0; i < size; i++) {
			arr[i] *= -1;
		}
		return *this;
	}
	Arr & operator [] (int ind) {
		for (int i = 0; i < size; i++) {
			arr[i] += ind;
		}
		return *this;
	}
	Arr & operator = (int a) {
		for (int i = 0; i < size; i++) {
			arr[i] += a;
		}
		return *this;
	}
};
int main() {
	Arr a1(5), a2(10, 1), a3(4, 2);
	const Arr a4(5);
	cout << a1 << a2 << a3 << a4;
	a2 = a2 & 2;
	cout << a2;
	a3 = (!a2) & a3;
	cout << a3;
	a1 = a4 & a3;
	cout << a1;
	a1[1] = 100;
	cout << a1;
	cout << a1 << a2 << a3 << a4;
	Arr b(move(a1));
	cout << b;
	b = move(a4);
	cout << b;
}