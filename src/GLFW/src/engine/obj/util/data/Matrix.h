//
// Created by vladl on 14/07/2020.
//

#ifndef ENG1_MATRIX_H
#define ENG1_MATRIX_H

#include <exception>

namespace engine {

    class MatrixRowColumnNull : public std::exception{
    public:
        [[nodiscard]] const char * what() const noexcept override {
            return "Cannot initialize a matrix with null rows/columns";
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
        };
    private:
        std::size_t _n;
//        int _m;

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
        this->_matrix = new Row(m);
}

template <class T>
engine::Matrix<T>::Matrix(std::size_t n, std::size_t m, T** matrix) noexcept (false) : _n(n) {
    if(n == 0 || m == 0)
        throw engine::MatrixRowColumnNull();

    this->_matrix = new Row* [this->_n];

    for(std::size_t i = 0; i < this->_n; i++)
        this->_matrix = new Row(m, matrix[i]);
}

template <class T>
engine::Matrix<T>::Matrix(const Matrix<T> & obj) noexcept(false) : _n(obj._n) {
    this->_matrix = new Row* [obj._n];

    for(std::size_t i = 0; i < this->_n; i++)
        this->_matrix = new Row( * ( obj._matrix[i] ) );
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

#endif //ENG1_MATRIX_H
