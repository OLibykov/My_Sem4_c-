
#include <utility>
#include <vector>
#include <iostream>
#include <cmath>

using namespace std;


class matrix{
public:
	friend ostream& operator<<(ostream& out, const matrix& m);
	double * operator[](const int i);
	const double * operator[](const int i) const;
	friend matrix operator*(matrix &m1, matrix &m2);
	friend istream& operator>>(istream& in, matrix& m);
	friend bool operator==(matrix &m1, matrix &m2);
	matrix & operator=(const matrix & m1);
	matrix(matrix && m);



	matrix();

	matrix(const matrix & m) = delete;

	matrix(size_t rows, size_t columns);
	~matrix();
	pair <size_t, size_t> size() const{
		return pair<size_t, size_t>(_rows, _columns);
	};

	size_t _rows{};
	size_t _columns{};
	double ** _data = nullptr;
};


