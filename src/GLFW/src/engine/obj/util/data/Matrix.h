//
// Created by vladl on 14/07/2020.
//

#ifndef ENG1_MATRIX_H
#define ENG1_MATRIX_H

#include <exception>
#include <iostream>

//namespace engine { template <class T> class Matrix { public: class Row; }; }

namespace engine {

    class MatrixRowColumnNull : public std::exception{
    public:
        [[nodiscard]] const char * what() const noexcept override {
            return "Cannot initialize a matrix with null rows/columns";
        }
    };

    class MatrixRequiredSameSize : public std::exception{
    public:
        [[nodiscard]] const char * what() const noexcept override {
            return "Addition/Subtraction requires matrixes of same row/column size";
        }
    };

    class MatrixRequiredTransposedSize : public std::exception{
    public:
        [[nodiscard]] const char * what() const noexcept override {
            return "Matrix multiplication requires inversed size operands. A(n x m) * B(m x n) !";
        }
    };

    template<class T>
    class Matrix {
    public:
        class Row {
        private:
            std::size_t _m;

            T** _row;
        public:
            Row() = delete;
            explicit Row(std::size_t) noexcept;
            explicit Row(std::size_t, T*) noexcept;
            Row(const Row&) noexcept;

            ~Row() noexcept;

            [[nodiscard]] std::size_t getLength() const noexcept {
                return this->_m;
            }

            T& operator[] (std::size_t) noexcept;

            friend std::ostream& operator << (std::ostream& f, const Row& x){
                for(std::size_t i = 0; i < x._m; i++)
                    f << (* (x._row[i])) << ' ';
                return f;
            }

            template <class U> friend Row operator+ (const Row&, const Row&) noexcept (false);
            template <class U> friend Row operator- (const Row&, const Row&) noexcept (false);
            template <class U> friend Row operator* (const Row&, U) noexcept;
            template <class U> friend Row operator* (U, const Row&) noexcept;

            Row& operator+= (const Row&) noexcept (false);
            Row& operator-= (const Row&) noexcept (false);
            Row& operator*= (T) noexcept;
        };
    private:
        std::size_t _n;

        Row** _matrix;
    public:
        Matrix() = delete;
        explicit Matrix(std::size_t, std::size_t) noexcept (false);
        explicit Matrix(std::size_t, std::size_t, T**) noexcept (false);
        Matrix(const Matrix&) noexcept (false);

        [[nodiscard]] std::size_t getN() const noexcept {
            return this->_n;
        }

        [[nodiscard]] std::size_t getM() const noexcept {
            return this->_matrix[0]->getLength();
        }

        ~Matrix() noexcept;

        Row& operator[] (std::size_t) noexcept;

        template <class U>
        friend std::ostream& operator << (std::ostream& f, const Matrix<U>& x){
            for(std::size_t i = 0; i < x._n; i++)
                f << (*( x._matrix[i] ) ) << '\n';
            return f;
        }

        template <class U> friend Matrix operator+ (const Matrix&, const Matrix&) noexcept(false);
        template <class U> friend Matrix operator- (const Matrix&, const Matrix&) noexcept(false);
        template <class U> friend Matrix operator* (const Matrix&, const Matrix&) noexcept(false);
        template <class U> friend Matrix operator* (const Matrix&, T) noexcept;
        template <class U> friend Matrix operator* (T, const Matrix&) noexcept;

        Matrix& operator += (const Matrix&) noexcept (false);
        Matrix& operator -= (const Matrix&) noexcept (false);
        Matrix& operator *= (const Matrix&) noexcept (false);
        Matrix& operator *= (T) noexcept;
    };
}

template <class T>
engine::Matrix<T>::Row::Row(std::size_t m) noexcept : _m(m) {
    this->_row = new T * [this->_m];

    for(std::size_t i = 0; i < this->_m; i++)
        this->_row[i] = new T();
}

template<class T>
engine::Matrix<T>::Row::Row(std::size_t m, T* arr) noexcept : _m(m) {
    this->_row = new T * [this->_m];

    for(std::size_t i = 0; i < this->_m; i++) {
        this->_row[i] = new T();
        * (this->_row[i]) = arr[i];
    }
}

template <class T>
engine::Matrix<T>::Row::Row(const Row& obj) noexcept : _m(obj._m) {
    this->_row = new T * [this->_m];

    for(std::size_t i = 0; i < this->_m; i++) {
        this->_row[i] = new T();
        * (this->_row[i]) = * (obj._row[i]);
    }
}

template <class T>
engine::Matrix<T>::Row::~Row() noexcept {
    for(std::size_t i = 0; i < this->_m; i++)
        delete this->_row[i];
    delete[] this->_row;
}

template <class T>
T& engine::Matrix<T>::Row::operator[](std::size_t index) noexcept {
    return * (this->_row[index]);
}

template <class T>
engine::Matrix<T>::Matrix(std::size_t n, std::size_t m) noexcept (false) : _n(n) {
    if(n == 0 || m == 0)
        throw engine::MatrixRowColumnNull();

    this->_matrix = new Row* [this->_n];

    for(std::size_t i = 0; i < this->_n; i++)
        this->_matrix[i] = new Row(m);
}

template <class T>
engine::Matrix<T>::Matrix(std::size_t n, std::size_t m, T** matrix) noexcept (false) : _n(n) {
    if(n == 0 || m == 0)
        throw engine::MatrixRowColumnNull();

    this->_matrix = new Row* [this->_n];

    for(std::size_t i = 0; i < this->_n; i++)
        this->_matrix[i] = new Row(m, matrix[i]);
}

template <class T>
engine::Matrix<T>::Matrix(const Matrix<T> & obj) noexcept(false) : _n(obj._n) {
    this->_matrix = new Row* [obj._n];

    for(std::size_t i = 0; i < this->_n; i++)
        this->_matrix[i] = new Row( * ( obj._matrix[i] ) );
}

template <class T>
engine::Matrix<T>::~Matrix() noexcept {
    for(std::size_t i = 0; i < this->_n; i++)
        delete this->_matrix[i];
    delete[] this->_matrix;
}

template <class T>
typename engine::Matrix<T>::Row& engine::Matrix<T>::operator[](std::size_t index) noexcept {
    return * (this->_matrix[index]);
}

template <class T>
typename engine::Matrix<T>::Row operator+ (const typename engine::Matrix<T>::Row& a, const typename engine::Matrix<T>::Row& b) noexcept (false){
    if(a._m != b._m)
        throw engine::MatrixRequiredSameSize();

    typename engine::Matrix<T>::Row r(a);

    for(std::size_t i = 0, length = a._m; i < length; i++)
        * ( r._row[i] ) += * ( b._row[i] );
    return r;
}

template <class T>
typename engine::Matrix<T>::Row operator- (const typename engine::Matrix<T>::Row& a, const typename engine::Matrix<T>::Row& b) noexcept (false) {
    if(a._m != b._m)
        throw engine::MatrixRequiredSameSize();

    typename engine::Matrix<T>::Row r(a);

    for(std::size_t i = 0, length = a._m; i < length; i++)
        * ( r._row[i] ) -= * ( b._row[i] );
    return r;
}

template <class T>
typename engine::Matrix<T>::Row operator* (const typename engine::Matrix<T>::Row& a, T b) noexcept {
    typename engine::Matrix<T>::Row r(a);

    for(std::size_t i = 0, length = a._m; i < length; i++)
        (* (a._row[i]) ) *= b;
    return r;
}

template <class T>
typename engine::Matrix<T>::Row operator* (T a, const typename engine::Matrix<T>::Row& b) noexcept {
    typename engine::Matrix<T>::Row r(b);

    for(std::size_t i = 0, length = b._m; i < length; i++)
        (* (b._row[i]) ) *= a;
    return r;
}

template <class T>
typename engine::Matrix<T>::Row& engine::Matrix<T>::Row::operator += (const typename engine::Matrix<T>::Row& obj) noexcept (false) {
    if(this->_m != obj._m)
        throw engine::MatrixRequiredSameSize();

    for(std::size_t i = 0, length = this->_m; i < length; i++)
        (* (this->_row[i]) ) += (* (obj._row[i]) );
    return *this;
}

template <class T>
typename engine::Matrix<T>::Row& engine::Matrix<T>::Row::operator -= (const typename engine::Matrix<T>::Row& obj) noexcept (false) {
    if(this->_m != obj._m)
        throw engine::MatrixRequiredSameSize();

    for(std::size_t i = 0, length = this->_m; i < length; i++)
        (* (this->_row[i]) ) -= (* (obj._row[i]) );
    return *this;
}

template <class T>
typename engine::Matrix<T>::Row& engine::Matrix<T>::Row::operator*= (T b) noexcept {
    for(std::size_t i = 0, length = this->_m; i < length; i++)
        (* (this->_row[i]) ) *= b;
    return *this;
}

template <class T>
engine::Matrix<T> operator+ (const engine::Matrix<T>& a, const engine::Matrix<T>& b) noexcept (false) {
    if( a._n != b._n )
        throw engine::MatrixRequiredSameSize();

    engine::Matrix<T> r(a);

    for(std::size_t i = 0, length = r._n; i < length; i++)
        (* (r._matrix[i]) ) += (* (b._matrix[i]) );
    return r;
}

template <class T>
engine::Matrix<T> operator- (const engine::Matrix<T>& a, const engine::Matrix<T>& b) noexcept (false) {
    if( a._n != b._n )
        throw engine::MatrixRequiredSameSize();

    engine::Matrix<T> r(a);

    for(std::size_t i = 0, length = r._n; i < length; i++)
        (* (r._matrix[i]) ) -= (* (b._matrix[i]) );
    return r;
}

template <class T>
engine::Matrix<T> operator* (const engine::Matrix<T>& a, T b) noexcept{
    engine::Matrix<T> r(a);

    for(std::size_t i = 0, length = r._n; i < length; i++)
        (* (r._matrix[i]) ) *= b;
    return r;
}

template <class T>
engine::Matrix<T> operator* (T a, const engine::Matrix<T>& b) noexcept{
    engine::Matrix<T> r(b);

    for(std::size_t i = 0, length = r._n; i < length; i++)
        (* (r._matrix[i]) ) *= a;
    return r;
}

template <class T>
engine::Matrix<T>& engine::Matrix<T>::operator += (const engine::Matrix<T>& obj) noexcept (false) {
    if(this->_n != obj._n)
        throw engine::MatrixRequiredSameSize();

    for(std::size_t i = 0, length = this->_n; i < length; i++)
        (* (this->_matrix[i]) ) += (* (obj._matrix[i]) );
    return *this;
}

template <class T>
engine::Matrix<T>& engine::Matrix<T>::operator -= (const engine::Matrix<T>& obj) noexcept (false) {
    if(this->_n != obj._n)
        throw engine::MatrixRequiredSameSize();

    for(std::size_t i = 0, length = this->_n; i < length; i++)
        (* (this->_matrix[i]) ) -= (* (obj._matrix[i]) );
    return *this;
}

template <class T>
engine::Matrix<T>& engine::Matrix<T>::operator *= (T obj) noexcept{
    for(std::size_t i = 0, length = this->_n; i < length; i++)
        (* (this->_matrix[i]) ) *= obj;
    return *this;
}

template <class T>
engine::Matrix<T> operator* (const engine::Matrix<T>& a, const engine::Matrix<T>& b) noexcept (false) {
    if( a.getM() != b._n )
        throw engine::MatrixRequiredTransposedSize();

    engine::Matrix<T> r(b._n, b.getM());

    for(std::size_t i = 0, height = r._n; i < height; i++)
        for(std::size_t j = 0, width = r.getM(); j < width; j++) {
            r._matrix[i][j] = T();
            for (std::size_t k = 0; k < height; k++) {
                r._matrix[i][j] += a._matrix[i][k] * b._matrix[k][j];
            }
        }

    return r;
}

#endif //ENG1_MATRIX_H
