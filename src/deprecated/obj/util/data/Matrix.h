//
// Created by vladl on 14/07/2020.
//

#ifndef ENG1_MATRIX_H
#define ENG1_MATRIX_H

#include <exception>
#include <iostream>
#include <type_traits>

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

            T** _row {nullptr};
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
            const T& operator[] (std::size_t) const noexcept;

            friend std::ostream& operator << (std::ostream& f, const Row& x) noexcept {
                for(std::size_t i = 0; i < x._m; i++)
                    f << (* (x._row[i])) << ' ';
                return f;
            }

            friend Row operator+ (const Row& a, const Row& b) noexcept (false){
                if(a._m != b._m)
                    throw engine::MatrixRequiredSameSize();

                typename engine::Matrix<T>::Row r(a);

                for(std::size_t i = 0, length = a._m; i < length; i++)
                    * ( r._row[i] ) += * ( b._row[i] );
                return r;
            };

            friend Row operator- (const Row& a, const Row& b) noexcept (false){
                if(a._m != b._m)
                    throw engine::MatrixRequiredSameSize();

                typename engine::Matrix<T>::Row r(a);

                for(std::size_t i = 0, length = a._m; i < length; i++)
                    * ( r._row[i] ) -= * ( b._row[i] );
                return r;
            }

            friend Row operator* (const Row& a, T b) noexcept {
                typename engine::Matrix<T>::Row r(a);

                for(std::size_t i = 0, length = a._m; i < length; i++)
                    (* (a._row[i]) ) *= b;
                return r;
            }

            friend Row operator* (T a, const Row& b) noexcept {
                typename engine::Matrix<T>::Row r(b);

                for(std::size_t i = 0, length = b._m; i < length; i++)
                    (* (b._row[i]) ) *= a;
                return r;
            }

            Row& operator=  (const Row&) noexcept;
            Row& operator+= (const Row&) noexcept (false);
            Row& operator-= (const Row&) noexcept (false);
            Row& operator*= (T) noexcept;
        };
    private:
        std::size_t _n;

        Row** _matrix {nullptr};
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
        const Row& operator[] (std::size_t) const noexcept;

        friend std::ostream& operator << (std::ostream& f, const Matrix<T>& x){
            for(std::size_t i = 0; i < x._n; i++)
                f << (*( x._matrix[i] ) ) << '\n';
            return f;
        }

        friend Matrix<T> operator+ (const Matrix<T>& a, const Matrix<T>& b) noexcept(false){
            if( a._n != b._n )
                throw engine::MatrixRequiredSameSize();

            engine::Matrix<T> r(a);

            for(std::size_t i = 0, length = r._n; i < length; i++)
                (* (r._matrix[i]) ) += (* (b._matrix[i]) );
            return r;
        }

        friend Matrix<T> operator- (const Matrix<T>& a, const Matrix<T>& b) noexcept(false) {
            if( a._n != b._n )
                throw engine::MatrixRequiredSameSize();

            engine::Matrix<T> r(a);

            for(std::size_t i = 0, length = r._n; i < length; i++)
                (* (r._matrix[i]) ) -= (* (b._matrix[i]) );
            return r;
        }

        friend Matrix<T> operator* (const Matrix<T>& a, const Matrix<T>& b) noexcept(false) {
            if( a.getM() != b._n )
                throw engine::MatrixRequiredTransposedSize();

            engine::Matrix<T> r(b._n, b.getM());

            for(std::size_t i = 0, height = r._n; i < height; i++)
                for(std::size_t j = 0, width = r.getM(); j < width; j++) {
                    r[i][j] = T();
                    for (std::size_t k = 0; k < height; k++) {
                        r[i][j] += a[i][k] * b[k][j];
                    }
                }

            return r;
        }

        friend Matrix<T> operator* (const Matrix<T>& a, T b) noexcept {
            engine::Matrix<T> r(a);

            for(std::size_t i = 0, length = r._n; i < length; i++)
                (* (r._matrix[i]) ) *= b;
            return r;
        }

        friend Matrix operator* (T a, const Matrix<T>& b) noexcept {
            engine::Matrix<T> r(b);

            for(std::size_t i = 0, length = r._n; i < length; i++)
                (* (r._matrix[i]) ) *= a;
            return r;
        }

        enum IdentityType {
            SINT8,
            SINT16,
            SINT32,
            SINT64,
            UINT8,
            UINT16,
            UINT32,
            UINT64,
            FLOAT32,
            FLOAT64,

            CHAR = SINT8,

            BYTE = UINT8,
            BOOL = UINT8,

            SHORT = SINT16,
            SHORT_INT = SINT16,

            UNSIGNED_SHORT = UINT16,
            UNSIGNED_SHORT_INT = UINT16,

            INT = SINT32,

            UNSIGNED = UINT32,
            UNSIGNED_INT = UINT32,

            LONG = SINT64,
            LONG_LONG = SINT64,
            LONG_LONG_INT = SINT64,

            UNSIGNED_LONG = UINT64,
            UNSIGNED_LONG_LONG = UINT64,
            UNSIGNED_LONG_LONG_INT = UINT64,

            FLOAT = FLOAT32,
            DOUBLE = FLOAT64
        };

        [[nodiscard]] static Matrix<T> identity(std::size_t) noexcept;

//        [[nodiscard]] static Matrix<int> identityInt(std::size_t) noexcept;
//        [[nodiscard]] static Matrix<float> identityFloat(std::size_t) noexcept;
//        [[nodiscard]] static Matrix<double> identityDouble(std::size_t) noexcept;
//        [[nodiscard]] static Matrix<bool> identityBool(std::size_t) noexcept;
//        [[nodiscard]] static Matrix<unsigned int> identityUInt(std::size_t) noexcept;
//        [[nodiscard]] static Matrix<long long> identityLong(std::size_t) noexcept;
//        [[nodiscard]] static Matrix<unsigned long long> identityULong(std::size_t) noexcept;
//
//        template <typename U>
//        [[nodiscard]] static Matrix identity(std::size_t) noexcept;
//        template <>
//        [[nodiscard]] static Matrix identity<int>(std::size_t) noexcept;
//        [[nodiscard]] static Matrix<float> identity(std::size_t, float dummyParam = 0) noexcept;
//        [[nodiscard]] static Matrix<double> identity(std::size_t, double dummyParam = 0.0) noexcept;
//        [[nodiscard]] static Matrix<bool> identity(std::size_t, bool dummyParam = false) noexcept;
//        [[nodiscard]] static Matrix<unsigned int> identity(std::size_t, unsigned int dummyParam = 0) noexcept;
//        [[nodiscard]] static Matrix<long long> identity(std::size_t, long long dummyParam = 0) noexcept;
//        [[nodiscard]] static Matrix<unsigned long long> identity(std::size_t, unsigned long long dummyParam = 0) noexcept;



        Matrix& operator =  (const Matrix&) noexcept;
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

template<class T>
const T &engine::Matrix<T>::Row::operator[](std::size_t index) const noexcept {
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

template<class T>
const typename engine::Matrix<T>::Row& engine::Matrix<T>::operator[](std::size_t index) const noexcept {
    return * (this->_matrix[index]);
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

template<class T>
typename engine::Matrix<T>::Row &engine::Matrix<T>::Row::operator= (const typename engine::Matrix<T>::Row & obj) noexcept {
    if( this == &obj )
        return *this;

    if( this->_row != nullptr ) {
        for(std::size_t i = 0; i < this->_m; i++)
            delete this->_row[i];
        delete[] this->_row;
    }

    this->_m = obj._m;

    this->_row = new T * [this->_m];
    for(std::size_t i = 0; i < this->_m; i++)
        this->_row[i] = new T();

    for(std::size_t i = 0, length = obj._m; i < length; i++)
        * (this->_row[i]) = * (obj._row[i]);

    return *this;
}

template<class T>
engine::Matrix<T> &engine::Matrix<T>::operator=(const engine::Matrix<T> &obj) noexcept {
    if( this == &obj )
        return *this;

    if( this->_matrix == nullptr ){
        for(std::size_t i = 0; i < this->_n; i++)
            delete this->_matrix[i];
        delete[] this->_matrix;
    }

    this->_n = obj._n;

    this->_matrix = new Row * [this->_n];
    for(std::size_t i = 0, width = obj.getM(); i < this->_n; i++)
        this->_matrix[i] = new Row(width, *(obj._matrix[i]) );
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

#define __GEN_ID_MAT__( _null_val_, _valid_val_, _type_, _size_)        \
    engine::Matrix<_type_> r(_size_, _size_);                           \
    for(std::size_t i = 0; i < _size_; i++)                             \
        for(std::size_t j = 0; j < _size_; j++)                         \
            if( i == j )                                                \
                r[i][j] = _valid_val_;                                  \
            else                                                        \
                r[i][j] = _null_val_;                                   \
    return r;


template <class T>
[[nodiscard]] engine::Matrix<T> engine::Matrix<T>::identity(std::size_t size) noexcept {
    if constexpr ( std::is_same_v<T, int> ) {
        __GEN_ID_MAT__(0, 1, int, size)
    } else if constexpr ( std::is_same_v<T, float> ) {
        __GEN_ID_MAT__(0.0f, 1.0f, float, size)
    } else if constexpr ( std::is_same_v<T, double> ) {
        __GEN_ID_MAT__(0.0, 1.0, double, size)
    } else if constexpr ( std::is_same_v<T, bool> ) {
        __GEN_ID_MAT__(false, true, bool, size)
    } else if constexpr ( std::is_same_v<T, unsigned int> ) {
        __GEN_ID_MAT__(0U, 1U, unsigned int, size)
    } else if constexpr ( std::is_same_v<T, long long int> ) {
        __GEN_ID_MAT__(0LL, 1LL, long long int, size)
    } else if constexpr ( std::is_same_v<T, unsigned long long int> ) {
        __GEN_ID_MAT__(0ULL, 1ULL, unsigned long long int, size)
    } else {
        engine::Matrix<T> r(1,1);
        return r;
    }

//    return r;
}
//template <class T>
//engine::Matrix<int> engine::Matrix<int>::identity<int>(std::size_t size) noexcept {
//    engine::Matrix<int> r(size, size);
//    for(std::size_t i = 0; i < size; i++)
//        for(std::size_t j = 0; j < size; j++)
//            if(i == j)
//                r[i][j] = 1;
//            else
//                r[i][j] = 0;
//}

//template<class T>
//template<>
//engine::Matrix<T> engine::Matrix<T>::identity<int>(std::size_t) noexcept {
//    return engine::Matrix<T>();
//}

//template<class T>
//template<typename U>
//engine::Matrix<T> engine::Matrix<T>::identity(std::size_t) noexcept {
//    return engine::Matrix<T>(2,2);
//}
//

//template <class T>
//engine::Matrix<float> engine::Matrix<T>::identity(std::size_t size, [[maybe_unused]] float dummyParam) noexcept {
//    engine::Matrix<float> r(size, size);
//    for(std::size_t i = 0; i < size; i++)
//        for(std::size_t j = 0; j < size; j++)
//            if(i == j)
//                r[i][j] = 1.0f;
//            else
//                r[i][j] = 0.0f;
//}
//
//template <class T>
//engine::Matrix<double> engine::Matrix<T>::identity(std::size_t size, [[maybe_unused]] double dummyParam) noexcept {
//    engine::Matrix<double> r(size, size);
//    for(std::size_t i = 0; i < size; i++)
//        for(std::size_t j = 0; j < size; j++)
//            if(i == j)
//                r[i][j] = 1.0;
//            else
//                r[i][j] = 0.0;
//}
//
//template <class T>
//engine::Matrix<bool> engine::Matrix<T>::identity(std::size_t size, [[maybe_unused]] bool dummyParam) noexcept {
//    engine::Matrix<bool> r(size, size);
//    for(std::size_t i = 0; i < size; i++)
//        for(std::size_t j = 0; j < size; j++)
//            r[i][j] = i == j;
//}
//
//template <class T>
//engine::Matrix<unsigned int> engine::Matrix<T>::identity(std::size_t size, [[maybe_unused]] unsigned int dummyParam) noexcept {
//    engine::Matrix<unsigned int> r(size, size);
//    for(std::size_t i = 0; i < size; i++)
//        for(std::size_t j = 0; j < size; j++)
//            if(i == j)
//                r[i][j] = 1U;
//            else
//                r[i][j] = 0U;
//}
//
//template <class T>
//engine::Matrix<long long int> engine::Matrix<T>::identity(std::size_t size, [[maybe_unused]] long long int dummyParam) noexcept {
//    engine::Matrix<long long int> r(size, size);
//    for(std::size_t i = 0; i < size; i++)
//        for(std::size_t j = 0; j < size; j++)
//            if(i == j)
//                r[i][j] = 1LL;
//            else
//                r[i][j] = 0LL;
//}
//
//template <class T>
//engine::Matrix<unsigned long long int> engine::Matrix<T>::identity(std::size_t size, [[maybe_unused]] unsigned long long int dummyParam) noexcept {
//    engine::Matrix<unsigned long long int> r(size, size);
//    for(std::size_t i = 0; i < size; i++)
//        for(std::size_t j = 0; j < size; j++)
//            if(i == j)
//                r[i][j] = 1ULL;
//            else
//                r[i][j] = 0ULL;
//}

#endif //ENG1_MATRIX_H

