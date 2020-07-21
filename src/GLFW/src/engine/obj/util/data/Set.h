//
// Created by loghin on 7/22/20.
//

#ifndef ENG1_SET_H
#define ENG1_SET_H

#include <iostream>
#include "Array.h"

//namespace engine { template<class T>class SimpleSet; }
// TODO : implement inline
//template<class T> engine::SimpleSet<T> operator+ (const engine::SimpleSet<T>&, const engine::SimpleSet<T>&) noexcept;
//template<class T> engine::SimpleSet<T> operator+ (const engine::SimpleSet<T>&, const T&) noexcept;
//template<class T> engine::SimpleSet<T> operator+ (const T&, const engine::SimpleSet<T>&) noexcept;
//
//template<class T> engine::SimpleSet<T> operator- (const engine::SimpleSet<T>&, const engine::SimpleSet<T>&) noexcept;
//template<class T> engine::SimpleSet<T> operator- (const engine::SimpleSet<T>&, const T&) noexcept;
//template<class T> engine::SimpleSet<T> operator- (const T&, const engine::SimpleSet<T>&) noexcept;
//
//template<class T> engine::SimpleSet<T> operator* (const engine::SimpleSet<T>&, const engine::SimpleSet<T>&) noexcept;
//
//template<class T> bool operator== (const engine::SimpleSet<T>&, const engine::SimpleSet<T>&) noexcept;
//template<class T> bool operator!= (const engine::SimpleSet<T>&, const engine::SimpleSet<T>&) noexcept;
//
//template<class T> std::ostream& operator << (std::ostream&, const engine::SimpleSet<T>&) noexcept;

namespace engine {

    class EngineSetOutOfBounds : public std::exception{
    public:
        [[nodiscard]] const char * what() const noexcept override{
            return "Tried accessing memory outside of memory bounds";
        }
    };

    template<class T>
    class SimpleSet {
    private:
        T** _arr        {nullptr};
        std::size_t _len {0};
        std::size_t _cap {0};

        constexpr static const std::size_t MAX_ARR_SIZE = UINT32_MAX;

        void _alloc(std::size_t) noexcept;
        void _relocateMemory(std::size_t) noexcept;
        void _shrink() noexcept;

    public:
        [[maybe_unused]] SimpleSet() noexcept;
        [[maybe_unused]] SimpleSet(const SimpleSet&) noexcept;
        [[maybe_unused]] SimpleSet(const T*, std::size_t) noexcept(false);

        ~SimpleSet() noexcept;

        [[maybe_unused]] [[nodiscard]] std::size_t length() const noexcept;
        [[maybe_unused]] [[nodiscard]] std::size_t size() const noexcept;

        [[maybe_unused]] [[nodiscard]] bool contains(const T&) const noexcept;
        [[maybe_unused]] void insert(const T&) noexcept;
        [[maybe_unused]] void insert(const SimpleSet&) noexcept;
        [[maybe_unused]] void insert(const Array<T>&) noexcept;
        [[maybe_unused]] void insert(const T*, std::size_t) noexcept (false);

        [[maybe_unused]] void remove(const T&) noexcept;
        [[maybe_unused]] void remove(const SimpleSet&) noexcept;
        [[maybe_unused]] void remove(const Array<T>&) noexcept;
        [[maybe_unused]] void remove(const T*, std::size_t) noexcept;

        [[maybe_unused]] static SimpleSet unity(const SimpleSet&, const SimpleSet&) noexcept;
        [[maybe_unused]] static SimpleSet intersection(const SimpleSet&, const SimpleSet&) noexcept;
        template<class U> [[maybe_unused]] static SimpleSet<std::pair<T,U>> cartesian (const SimpleSet<T>&, const SimpleSet<U>&) noexcept;

        SimpleSet& unite(const SimpleSet&) noexcept;
        SimpleSet& intersect(const SimpleSet&) noexcept;

        template <class U> SimpleSet<std::pair<T, U>> cartesian (const SimpleSet<U>&) noexcept;

        friend SimpleSet<T> operator+ (const SimpleSet<T>&, const SimpleSet<T>&) noexcept {
            return engine::SimpleSet<T>();
        }

        friend SimpleSet<T> operator+ (const SimpleSet<T>&, const T&) noexcept {
            return engine::SimpleSet<T>();
        }

        friend SimpleSet<T> operator+ (const T&, const SimpleSet<T>&) noexcept {
            return engine::SimpleSet<T>();
        }

        friend SimpleSet<T> operator- (const SimpleSet<T>&, const SimpleSet<T>&) noexcept {
            return engine::SimpleSet<T>();
        }

        friend SimpleSet<T> operator- (const SimpleSet<T>&, const T&) noexcept {
            return engine::SimpleSet<T>();
        }

        friend SimpleSet<T> operator- (const T&, const SimpleSet<T>&) noexcept {
            return engine::SimpleSet<T>();
        }

        friend SimpleSet<T> operator* (const SimpleSet<T>&, const SimpleSet<T>&) noexcept {
            return engine::SimpleSet<T>();
        }

        friend bool operator== (const SimpleSet&, const SimpleSet&) noexcept  {
            return false;
        }

        friend bool operator!= (const SimpleSet&, const SimpleSet&) noexcept {
            return false;
        }

        friend std::ostream& operator<< (std::ostream& f, const SimpleSet& set) noexcept {
            f << "Set [ ";

            for(std::size_t i = 0; i < set._len - 1; i++)
                f << (*set._arr[i]) << ", ";

            if(set._len > 0)
                f << (*set._arr[set._len - 1]);

            return (f << " ] ");
        }

        SimpleSet& operator=  (const SimpleSet&) noexcept;
        SimpleSet& operator+= (const SimpleSet&) noexcept;
        SimpleSet& operator+= (const T&) noexcept;
        SimpleSet& operator-= (const SimpleSet&) noexcept;
        SimpleSet& operator-= (const T&) noexcept;

        [[maybe_unused]] explicit operator std::string() const;

        [[maybe_unused]] void shrink() noexcept;
    };

}

template<class T>
void engine::SimpleSet<T>::_alloc(std::size_t reqSize) noexcept {
    if(reqSize + this->_len <= this->_cap)
        return;

    std::size_t newSize = (this->_len + reqSize > 2 * this->_cap) ? (this->_len + reqSize) : (2 * this->_cap);

    if( newSize > MAX_ARR_SIZE )
        newSize = MAX_ARR_SIZE;

    this->_relocateMemory(newSize);
}

template<class T>
void engine::SimpleSet<T>::_relocateMemory(std::size_t blockSize) noexcept {
    T** newMemLoc = new T* [blockSize];

    for(std::size_t i = 0; i < blockSize; i++) {
        if( i < this->_len )
            newMemLoc[i] = this->_arr[i];
        else
            newMemLoc[i] = new T;
    }

    for( std::size_t i = this->_len; i < this->_cap; i++ )
        delete this->_arr[i];
    delete[] this->_arr;

    this->_arr = newMemLoc;
    this->_cap = blockSize;
}

template <class T>
void engine::SimpleSet<T>::_shrink() noexcept {
    this->_relocateMemory(this->_len);
}

template <class T>
inline engine::SimpleSet<T>::SimpleSet() noexcept = default;

template <class T>
engine::SimpleSet<T>::SimpleSet(const SimpleSet<T> & obj) noexcept {
    this->_alloc(obj._cap);

    for( ; this->_len < obj._len; this->_len++ )
        * ( this->_arr[this->_len] ) = * ( obj._arr[this->_len] );
}

template <class T>
engine::SimpleSet<T>::SimpleSet(const T* array, std::size_t len) noexcept(false) {
    if( len >= MAX_ARR_SIZE )
        throw engine::EngineSetOutOfBounds();

    this->_alloc(len);

    for( ; this->_len < len; this->_len++ )
        * ( this->_arr[this->_len] ) = array[this->_len];
}

template <class T>
engine::SimpleSet<T>::~SimpleSet() noexcept {
    for( std::size_t i = 0; i < this->_cap; i++ )
        delete this->_arr[i];

    delete[] this->_arr;
}

template <class T>
[[maybe_unused]] [[nodiscard]] inline std::size_t engine::SimpleSet<T>::length() const noexcept {
    return this->_len;
}

template <class T>
[[maybe_unused]] [[nodiscard]] inline std::size_t engine::SimpleSet<T>::size() const noexcept {
    return this->_cap;
}

template <class T>
[[maybe_unused]] [[nodiscard]] bool engine::SimpleSet<T>::contains(const T & obj) const noexcept {
    for(std::size_t i = 0; i < this->_len; i++)
        if( * (this->_arr[i]) == obj )
            return true;
    return false;
}

template <class T>
[[maybe_unused]] void engine::SimpleSet<T>::insert(const T & obj) noexcept {
    if(this->contains(obj))
        return;

    this->_alloc(1);
     * (this->_arr[this->_len++]) = obj;
}

template <class T>
[[maybe_unused]] void engine::SimpleSet<T>::insert(const Array<T> & collection) noexcept {
    this->_alloc(collection.getLength());

    for( std::size_t i = 0; i < collection.getLength(); i++ ) {
        if(this->contains(collection[i]))
            continue;
        *(this->_arr[this->_len++]) = collection[i];
    }

    this->_shrink();
}

template <class T>
[[maybe_unused]] void engine::SimpleSet<T>::insert(const engine::SimpleSet<T>& set) noexcept {
    this->_alloc(set._len);

    for( std::size_t i = 0; i < set._len; i++ ) {
        if(this->contains(*(set._arr[i])))
            continue;
        *(this->_arr[this->_len++]) = (*(set._arr[i]));
    }

    this->_shrink();
}

template <class T>
[[maybe_unused]] void engine::SimpleSet<T>::insert(const T* arr, std::size_t len) noexcept (false) {
    if( len >= MAX_ARR_SIZE )
        throw engine::EngineSetOutOfBounds();

    this->_alloc(len);

    for( std::size_t i = 0; i < len; i++ ) {
        if(this->contains(arr[i]))
            continue;
        *(this->_arr[this->_len++]) = arr[i];
    }

    this->_shrink();
}

namespace engine {

    template <class T>
    using Set = SimpleSet<T>;
}

#endif //ENG1_SET_H
