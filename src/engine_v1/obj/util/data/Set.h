//
// Created by loghin on 7/22/20.
//

#ifndef ENG1_SET_H
#define ENG1_SET_H

#include <iostream>
#include "Array.h"
#include <initializer_list>
#include "Pair.h"

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

        bool _autoShrink {true};

    public:
        [[maybe_unused]] SimpleSet() noexcept;
        [[maybe_unused]] SimpleSet(const SimpleSet&) noexcept;
        [[maybe_unused]] SimpleSet(const T*, std::size_t) noexcept(false);
        [[maybe_unused]] SimpleSet(const std::initializer_list<T> &) noexcept;

        ~SimpleSet() noexcept;

        [[maybe_unused]] void setAutoShrink(bool toggle) noexcept {
            this->_autoShrink = toggle;
        }

        [[maybe_unused]] void enableAutoShrink() noexcept {
            this->_autoShrink = true;
        }

        [[maybe_unused]] void disableAutoShrink() noexcept {
            this->_autoShrink = false;
        }

        [[maybe_unused]] [[nodiscard]] std::size_t length() const noexcept;
        [[maybe_unused]] [[nodiscard]] std::size_t size() const noexcept;
        [[maybe_unused]] [[nodiscard]] bool isEmpty() const noexcept {
            return this->_len == 0;
        }

        [[maybe_unused]] void clear(std::size_t = 0) noexcept;

        [[maybe_unused]] [[nodiscard]] bool contains(const T&) const noexcept;
        [[maybe_unused]] [[nodiscard]] bool contains(const SimpleSet&) const noexcept;
        [[maybe_unused]] [[nodiscard]] bool contains(const Array<T>&) const noexcept;
        [[maybe_unused]] [[nodiscard]] bool contains(const T*, std::size_t) const noexcept;
        [[maybe_unused]] [[nodiscard]] bool contains(const std::initializer_list<T> &) const noexcept;

        [[maybe_unused]] [[nodiscard]] bool isSubsetOf(const SimpleSet& b) const noexcept {
            return b.contains(*this);
        }

        [[maybe_unused]] SimpleSet& insert(const T&) noexcept;
        [[maybe_unused]] SimpleSet& insert(const SimpleSet&) noexcept;
        [[maybe_unused]] SimpleSet& insert(const Array<T>&) noexcept;
        [[maybe_unused]] SimpleSet& insert(const T*, std::size_t) noexcept (false);
        [[maybe_unused]] SimpleSet& insert(const std::initializer_list<T>&) noexcept;

        [[maybe_unused]] SimpleSet& remove(const T&) noexcept;
        [[maybe_unused]] SimpleSet& remove(const SimpleSet&) noexcept;
        [[maybe_unused]] SimpleSet& remove(const Array<T>&) noexcept;
        [[maybe_unused]] SimpleSet& remove(const T*, std::size_t) noexcept;
        [[maybe_unused]] SimpleSet& remove(const std::initializer_list<T>&) noexcept;

        [[maybe_unused]] static SimpleSet unity(const SimpleSet&, const SimpleSet&) noexcept;
        [[maybe_unused]] static SimpleSet intersection(const SimpleSet&, const SimpleSet&) noexcept;
        [[maybe_unused]] static SimpleSet outerIntersection(const SimpleSet&, const SimpleSet&) noexcept;
        template<class U> [[maybe_unused]] static SimpleSet<Pair<T,U>> cartesian (const SimpleSet<T>&, const SimpleSet<U>&) noexcept;
        [[maybe_unused]] static SimpleSet<Pair<T,T>> cartesian (const SimpleSet<T>&, const SimpleSet<T>&) noexcept;

        [[maybe_unused]] SimpleSet& unite(const SimpleSet&) noexcept;
        [[maybe_unused]] SimpleSet& intersect(const SimpleSet&) noexcept;

        template <class U> [[maybe_unused]] SimpleSet<Pair<T, U>> cartesian (const SimpleSet<U>&) const noexcept;
        [[maybe_unused]] SimpleSet<Pair<T, T>> cartesian (const SimpleSet<T>&) const noexcept;

        friend SimpleSet<T> operator+ (const SimpleSet<T>& a, const SimpleSet<T>& b) noexcept {
            return engine::SimpleSet<T>::unity(a, b);
        }

        friend SimpleSet<T> operator+ (const SimpleSet<T>& a, const T& b) noexcept {
            engine::SimpleSet<T> res(a);
            res.insert(b);
            return res;
        }

        friend SimpleSet<T> operator+ (const T& a, const SimpleSet<T>& b) noexcept {
            return (b + a);
        }

        friend SimpleSet<T> operator+ (const T& a, const std::initializer_list<T>& b) noexcept {
            engine::SimpleSet<T> res(a);

            for( auto & element : b ){
                res.insert(element);
            }
            return res;
        }

        friend SimpleSet<T> operator- (const SimpleSet<T>& a, const SimpleSet<T>& b) noexcept {
            engine::SimpleSet<T> res(a);
            return res.remove(b);
        }

        friend SimpleSet<T> operator- (const SimpleSet<T>& a, const T& b) noexcept {
            engine::SimpleSet<T> res(a);
            return res.remove(b);
        }

        friend SimpleSet<T> operator- (const T& a, const std::initializer_list<T>& b) noexcept {
            engine::SimpleSet<T> res(a);
            return res.remove(b);
        }

        template<class U> friend SimpleSet<Pair<T, U>> operator* (const SimpleSet<T>& a, const SimpleSet<T>& b) noexcept {
            return engine::SimpleSet<T>::cartesian(a, b);
        }

        friend SimpleSet<Pair<T, T>> operator* (const SimpleSet<T>& a, const SimpleSet<T>& b) noexcept {
            return engine::SimpleSet<T>::cartesian(a, b);
        }

//        friend SimpleSet<T> operator* (const SimpleSet<T>&a, const SimpleSet<T>& b) noexcept {
//            return engine::SimpleSet<T>::cartesian(a, b);
//        }

        friend bool operator== (const SimpleSet& a, const SimpleSet& b) noexcept  {
            return (a-b).isEmpty();
        }

        friend bool operator!= (const SimpleSet& a, const SimpleSet& b) noexcept {
            return ! ( a == b );
        }

        friend std::ostream& operator<< (std::ostream& f, const SimpleSet& set) noexcept {
            f << "Set [ ";

            if(set._len > 0) {
                for (std::size_t i = 0; i < set._len - 1; i++)
                    f << (*set._arr[i]) << ", ";


                f << (*set._arr[set._len - 1]);
            }

            return (f << " ] ");
        }

        SimpleSet& operator=  (const std::initializer_list<T>&) noexcept;
        SimpleSet& operator=  (const SimpleSet&) noexcept;
        SimpleSet& operator=  (const Array<T>&) noexcept;

        SimpleSet& operator+= (const SimpleSet& obj) noexcept {
            return this->insert(obj);
        }

        SimpleSet& operator+= (const Array<T>& obj) noexcept{
            return this->insert(obj);
        }

        SimpleSet& operator+= (const T& obj) noexcept{
            return this->insert(obj);
        }

        SimpleSet& operator+= (const std::initializer_list<T>& obj) noexcept{
            return this->insert(obj);
        }

        SimpleSet& operator-= (const SimpleSet& obj) noexcept {
            return this->remove(obj);
        }

        SimpleSet& operator-= (const Array<T>& obj) noexcept {
            return this->remove(obj);
        }

        SimpleSet& operator-= (const T& obj) noexcept {
            return this->remove(obj);
        }

        SimpleSet& operator-= (const std::initializer_list<T>& obj) noexcept {
            return this->remove(obj);
        }

        [[maybe_unused]] explicit operator std::string() const;

        [[maybe_unused]] void shrink() noexcept {
            this->_shrink();
        }

        [[maybe_unused]] void debugPrintInfo () noexcept {
            std::cout << "\nSet : { _arr : [ ";
            if(this->_len > 0) {
                for (std::size_t i = 0; i < this->_len - 1; i++)
                    std::cout << (*this->_arr[i]) << ", ";
                std::cout << (*this->_arr[this->_len - 1]);
            }
            std::cout << "], _fullArr : [ ";
            if(this->_cap > 0) {
                for (std::size_t i = 0; i < this->_cap - 1; i++)
                    std::cout << (*this->_arr[i]) << ", ";
                std::cout << (*this->_arr[this->_cap - 1]);
            }
            std::cout << " ], _len : " << this->_len << ", _cap = " << this->_cap << " } " << '\n';
        }
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

//    this->debugPrintInfo();

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

#pragma clang diagnostic push
#pragma ide diagnostic ignored "bugprone-infinite-loop"
template <class T>
[[maybe_unused]] engine::SimpleSet<T>::SimpleSet(const T* array, std::size_t len) noexcept(false) {
    if( len >= MAX_ARR_SIZE )
        throw engine::EngineSetOutOfBounds();

    this->_alloc(len);

    for( ; this->_len < len; this->_len++ )
        * ( this->_arr[this->_len] ) = array[this->_len];
}
#pragma clang diagnostic pop

template <class T>
[[maybe_unused]] engine::SimpleSet<T>::SimpleSet(const std::initializer_list<T> & obj) noexcept : _len(0) {
    this->_alloc(obj.size());

    for( auto & element : obj )
         * (this->_arr[this->_len++] ) = element;
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
[[maybe_unused]] engine::SimpleSet<T>& engine::SimpleSet<T>::insert(const T & obj) noexcept {
    if(this->contains(obj))
        return *this;

    this->_alloc(1);
     * (this->_arr[this->_len++]) = obj;

    return *this;
}

template <class T>
[[maybe_unused]] engine::SimpleSet<T>& engine::SimpleSet<T>::insert(const Array<T> & collection) noexcept {
    this->_alloc(collection.getLength());

    for( std::size_t i = 0; i < collection.getLength(); i++ ) {
        if(this->contains(collection[i]))
            continue;
        *(this->_arr[this->_len++]) = collection[i];
    }

    if(this->_autoShrink)
        this->_shrink();
    return *this;
}

template <class T>
[[maybe_unused]] engine::SimpleSet<T>& engine::SimpleSet<T>::insert(const engine::SimpleSet<T>& set) noexcept {
    this->_alloc(set._len);

    for( std::size_t i = 0; i < set._len; i++ ) {
        if(this->contains(*(set._arr[i])))
            continue;
        *(this->_arr[this->_len++]) = (*(set._arr[i]));
    }

    if(this->_autoShrink)
        this->_shrink();
    return *this;
}

template <class T>
[[maybe_unused]] engine::SimpleSet<T>& engine::SimpleSet<T>::insert(const T* arr, std::size_t len) noexcept (false) {
    if( len >= MAX_ARR_SIZE )
        throw engine::EngineSetOutOfBounds();

    this->_alloc(len);

    for( std::size_t i = 0; i < len; i++ ) {
        if(this->contains(arr[i]))
            continue;
        *(this->_arr[this->_len++]) = arr[i];
    }

    if(this->_autoShrink)
        this->_shrink();
    return *this;
}

template <class T>
[[maybe_unused]] engine::SimpleSet<T>& engine::SimpleSet<T>::insert(const std::initializer_list<T> & obj) noexcept {
    this->_alloc(obj.size());

    for( auto & e : obj ) {
        if(this->contains(e))
            continue;
        * (this->_arr[this->_len++]) = e;
    }

    if(this->_autoShrink)
        this->_shrink();
    return *this;
}

template <class T>
[[maybe_unused]] engine::SimpleSet<T>& engine::SimpleSet<T>::remove(const T& obj) noexcept {
    std::size_t i = 0;
    for( ; i < this->_len; i++ )
        if( * ( this->_arr[i] ) == obj ) {
//            delete this->_arr[i];

            this->_len--;
            break;
        }

    for( ; i < this->_len - 1; i++ )
        * this->_arr[i] = * this->_arr[i+1];


    if(this->_autoShrink)
        this->_shrink();
    return *this;
}

template <class T>
[[maybe_unused]] engine::SimpleSet<T>& engine::SimpleSet<T>::remove(const engine::Array<T> & arr) noexcept {
    for(std::size_t aIt = 0, aLen = arr.getLength(); aIt < aLen; aIt++) {
        std::size_t i = 0;
        for( ; i < this->_len; i++ )
            if( * ( this->_arr[i] ) == arr[aIt] ) {
//                delete this->_arr[i];
                this->_len--;
                break;
            }

        for( ; i < this->_len - 1; i++ )
            * this->_arr[i] = * this->_arr[i+1];
    }
    if(this->_autoShrink)
        this->_shrink();
    return *this;
}

template <class T>
[[maybe_unused]] engine::SimpleSet<T>& engine::SimpleSet<T>::remove(const engine::SimpleSet<T> & set) noexcept {
    for(std::size_t aIt = 0, aLen = set._len; aIt < aLen; aIt++) {
        std::size_t i = 0;
        for( ; i < this->_len; i++ )
            if( * ( this->_arr[i] ) == * ( set._arr[aIt] ) ) {
//                delete this->_arr[i];
                this->_len--;
                break;
            }

        for( ; i < this->_len ; i++ )
            * this->_arr[i] = * this->_arr[i+1];
    }
    if(this->_autoShrink)
        this->_shrink();
    return *this;
}

template <class T>
[[maybe_unused]] engine::SimpleSet<T>& engine::SimpleSet<T>::remove(const T * arr, std::size_t len) noexcept {
    for(std::size_t aIt = 0, aLen = len; aIt < aLen; aIt++) {
        std::size_t i = 0;
        for( ; i < this->_len; i++ )
            if( * ( this->_arr[i] ) == arr[aIt] ) {
//                delete this->_arr[i];
                this->_len--;
                break;
            }

        for( ; i < this->_len; i++ )
            * this->_arr[i] = * this->_arr[i+1];
    }
    if(this->_autoShrink)
        this->_shrink();
    return *this;
}

template <class T>
[[maybe_unused]] engine::SimpleSet<T>& engine::SimpleSet<T>::remove(const std::initializer_list<T>& obj) noexcept {
    for( auto & e : obj ) {

        std::size_t i = 0;
        for(; i < this->_len; i++)
            if( * (this->_arr[i]) == e ) {
//                delete this->_arr[i];
                this->_len--;
                break;
            }

        for( ; i < this->_len - 1; i++)
            * this->_arr[i] = * this->_arr[i+1];
    }
    if(this->_autoShrink)
        this->_shrink();
    return *this;
}

template <class T>
[[maybe_unused]] engine::SimpleSet<T> engine::SimpleSet<T>::unity(const engine::SimpleSet<T>& a, const engine::SimpleSet<T>& b) noexcept {
    engine::SimpleSet<T> res(a);
    res.insert(b);

    return res;
}

template <class T>
[[maybe_unused]] [[nodiscard]] bool engine::SimpleSet<T>::contains(const SimpleSet<T> & set) const noexcept {
    for(std::size_t i = 0; i < set._len; i++)
        if( ! this->contains(*(set._arr[i])) )
            return false;
    return true;
}

template <class T>
[[maybe_unused]] [[nodiscard]] bool engine::SimpleSet<T>::contains(const Array<T> & arr) const noexcept {
    for(std::size_t i = 0, len = arr.getLength(); i < len; i++)
        if( ! this->contains(arr[i]) )
            return false;
    return true;
}

template <class T>
[[maybe_unused]] [[nodiscard]] bool engine::SimpleSet<T>::contains(const T * arr, std::size_t len) const noexcept {
    for(std::size_t i = 0; i < len; i++)
        if( ! this->contains(arr[i]) )
            return false;
    return true;
}

template <class T>
[[maybe_unused]] [[nodiscard]] bool engine::SimpleSet<T>::contains(const std::initializer_list<T> & obj) const noexcept {
    for(auto & element : obj)
        if( ! this->contains(obj) )
            return false;

    return true;
}

template <class T>
[[maybe_unused]] engine::SimpleSet<T> engine::SimpleSet<T>::intersection(const SimpleSet<T> & a, const SimpleSet<T> & b) noexcept {
    engine::SimpleSet<T> res;

    for(std::size_t i = 0; i < a._len; i++)
        if(b.contains(*(a._arr[i])))
            res.insert(*(a._arr[i]));

    return res;
}

template <class T>
[[maybe_unused]] engine::SimpleSet<T> engine::SimpleSet<T>::outerIntersection(const SimpleSet<T> & a, const SimpleSet<T> & b) noexcept {
    return engine::SimpleSet<T>::unity(a, b) - engine::SimpleSet<T>::intersection(a, b);
}

template<class T>
template<class U>
[[maybe_unused]] engine::SimpleSet<engine::Pair<T, U>> engine::SimpleSet<T>::cartesian(const engine::SimpleSet<T> & a, const engine::SimpleSet<U> & b) noexcept {
    engine::SimpleSet<engine::Pair<T,U>> res;

    for(std::size_t i = 0; i < a._len; i++)
        for(std::size_t j = i; j < b._len; j++)
            res.insert(engine::Pair<T,U>(*(a._arr[i]), *(b._arr[j])));

    return res;
}

template <class T>
[[maybe_unused]] engine::SimpleSet<engine::Pair<T, T>> engine::SimpleSet<T>::cartesian(const SimpleSet<T> & a, const SimpleSet<T> & b) noexcept {
    engine::SimpleSet<engine::Pair<T,T>> res;

    for(std::size_t i = 0; i < a._len; i++)
        for(std::size_t j = i; j < b._len; j++)
            res.insert(engine::Pair<T,T>(*(a._arr[i]), *(b._arr[j])));

    return res;
}

template<class T>
[[maybe_unused]] engine::SimpleSet<T>& engine::SimpleSet<T>::unite(const SimpleSet<T> & b) noexcept {
    for(std::size_t i = 0; i < b._len; i++)
        this->insert(*b._arr[i]);
    if(this->_autoShrink)
        this->_shrink();
    return *this;
}

template <class T>
[[maybe_unused]] engine::SimpleSet<T>& engine::SimpleSet<T>::intersect(const SimpleSet<T> & b) noexcept {
    for(std::size_t i = 0; i < this->_len; i++)
        if(! b.contains(*(this->_arr[i])) ) {
            this->remove(*(this->_arr[i--]));
        }

    if(this->_autoShrink)
        this->_shrink();
    return *this;
}

//#pragma clang diagnostic push
//#pragma ide diagnostic ignored "UnusedLocalVariable"
//template <class T, class U>
//[[maybe_unused]] engine::SimpleSet<engine::Pair<T, U>> engine::SimpleSet<T>::cartesian(const engine::SimpleSet<U>& obj) const noexcept {
//    return engine::SimpleSet<T>::intersection(*this, obj);
//}
//#pragma clang diagnostic pop

template <class T>
[[maybe_unused]] void engine::SimpleSet<T>::clear(std::size_t elementsToLeave) noexcept {
    for(std::size_t it = elementsToLeave; it < this->_cap; it++)
        delete this->_arr[it];
//    delete[] this->_arr;

    if(this->_cap < elementsToLeave)
        this->_alloc(elementsToLeave - this->_cap);

    this->_cap = this->_len = elementsToLeave;
}

#pragma clang diagnostic push
#pragma ide diagnostic ignored "bugprone-unhandled-self-assignment"
template <class T>
engine::SimpleSet<T>& engine::SimpleSet<T>::operator= (const engine::SimpleSet<T>& obj) noexcept {
    if(this == &obj)
        return *this;

    this->clear(obj._len);

    for(std::size_t i = 0; i < obj._len; i++)
        * (this->_arr[i]) = * (obj._arr[i]);

    this->_len = obj._len;

    return *this;
}
#pragma clang diagnostic pop

template <class T>
engine::SimpleSet<T>& engine::SimpleSet<T>::operator= (const Array<T>& obj) noexcept {
    this->clear(obj.getLength());

    for(std::size_t i = 0, length = obj.getLength(); i < length; i++ ){
        * (this->_arr[i] ) = obj[i];
    }

    this->_len = obj.getLength();

    return *this;
}

template <class T>
engine::SimpleSet<T>& engine::SimpleSet<T>::operator=(const std::initializer_list<T> & obj) noexcept {
    this->clear(obj.size());

    this->_len = 0;
    for(auto & e : obj)
        * (this->_arr[this->_len++]) = e;

    return *this;
}

template <class T>
engine::SimpleSet<T>::operator std::string() const {
    std::string res = "Set [ ";

    if( this->_len > 0 ) {
        for (std::size_t i = 0; i < this->_len - 1; i++)
            res.append((std::string) (*(this->_arr[i]))).append(", ");

        res.append(this->_arr[this->_len - 1]);
    }

    return res.append(" ] ");
}

template<class T>
template<class U>
[[maybe_unused]] engine::SimpleSet<engine::Pair<T, U>> engine::SimpleSet<T>::cartesian(const engine::SimpleSet<U> & obj) const noexcept {
    return engine::SimpleSet<T>::intersection(*this, obj);
}

template<class T>
[[maybe_unused]] engine::SimpleSet<engine::Pair<T, T>> engine::SimpleSet<T>::cartesian(const engine::SimpleSet<T> & obj) const noexcept {
    return engine::SimpleSet<T>::intersection(*this, obj);
}

namespace engine {

    template <class T>
    using Set = SimpleSet<T>;
}

//template <class T, class U>
//[[maybe_unused]] std::ostream& operator<< (std::ostream& f, const std::pair<T, U>& obj) noexcept {
//    return (f << "{" << obj.first << ", " << obj.second << "}");
//}

#endif //ENG1_SET_H
