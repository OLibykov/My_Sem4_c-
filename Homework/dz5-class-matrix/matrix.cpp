#include "matrix.h"

ostream& operator<<(ostream& out, const matrix& m)
{
    for (size_t i = 0; i < m.size().first; i++) {
        for (size_t j = 0; j < m.size().second; j++){
            out << m._data[i][j] << " ";
        }
        out << endl;
    }
    return out;
}

double* matrix::operator[]( const int i)
{
    return _data[i];
}

const double* matrix::operator[]( const int i) const
{
    return _data[i];
}


matrix::matrix(matrix&& m) {
    this->_rows = m._rows;
    this->_columns = m._columns;
    this->_data = m._data;
    m._rows = 0;
    m._columns = 0;
    m._data = nullptr;
    cout << "move constructor\n";
}


istream& operator>>(istream& in, matrix& m)
{
    for (size_t row = 0; row!=m._rows; ++row) {
        for (size_t col = 0; col!=m._columns; ++col) {
            in>>m._data[row][col];
        }
    }
    return in;
}

bool operator==(matrix &m1, matrix &m2){

    if (!(m1.size().first == m2.size().first && m1.size().second == m2.size().second)){
        return false;
    }

    for (size_t i = 0; i < m1._rows; i++){
        for (size_t j = 0; j < m1._columns; j++){
            if (fabs(m1[i][j] - m2[i][j]) >= 0.000005)
                return false;
        }
    }

    return true;
}


matrix::matrix(size_t rows, size_t columns) {

    cout << "constructor with parameters\n";

    _data = (double**)malloc(rows * sizeof(double*));
    for(int i = 0; i < rows; ++i)
        _data[i] = (double*)malloc(columns * sizeof(double));
    //_data = (double *) aligned_alloc(1024, rows * columns * sizeof(double));

    /*
       for (size_t i = 0; i < rows; i++){
       _data[i] = (double *) aligned_alloc(64, columns * sizeof(double));
       }
       */


    _rows = rows;
    _columns = columns;
}


matrix::matrix(){
        cout << "default constructor\n";
        _rows = 3;
        _columns = 3;
        //_data = (double *) aligned_alloc(1024, 9 * sizeof(double));
        _data = (double**)malloc(_rows * sizeof(double*));
        for(int i = 0; i < _rows; ++i)
            _data[i] = (double*)malloc(_columns * sizeof(double));
};

matrix::~matrix() {

    cout << "destructor\n";

    if (_data != NULL){
       for (size_t i = 0; i < _rows; i++){
           free(_data[i]);
       }
       free(_data);
       _data = nullptr;
    }

}

