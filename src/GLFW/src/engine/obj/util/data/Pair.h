//
// Created by loghin on 7/22/20.
//

#ifndef ENG1_PAIR_H
#define ENG1_PAIR_H

#include <iostream>

namespace engine {

    template <class T, class U>
    class NonConstexprPair {
    private:
        T* _first   {new T()};
        U* _second  {new U()};

    public:
        constexpr NonConstexprPair() noexcept {
            this->_first = new T();
            this->_second = new U();
        };

        [[maybe_unused]] explicit NonConstexprPair(const T& first, const U& second) noexcept {
            this->_first = new T(first);
            this->_second = new T(second);
        }

        ~NonConstexprPair() noexcept {
            delete this->_first;
            delete this->_second;
        }

        [[maybe_unused]] T getFirst() const noexcept {
            return * (this->_first);
        }

        [[maybe_unused]] T getSecond() const noexcept {
            return * (this->_second);
        }

        [[maybe_unused]] void setFirst(const T& x) noexcept {
            * (this->_first) = x;
        }

        [[maybe_unused]] void setSecond(const U& x) noexcept {
            * (this->_second) = x;
        }

        friend bool operator == (const engine::NonConstexprPair<T, U>& x, const engine::NonConstexprPair<T, U>& y) noexcept {
            if(&x == &y)
                return true;

            return *(x._first) == *(y._first) && *(x._second) == *(y._second);
        }

        friend bool operator != (const engine::NonConstexprPair<T, U>& x, const engine::NonConstexprPair<T, U>& y) noexcept {
            return ! (x == y);
        }

        NonConstexprPair& operator= (const NonConstexprPair<T, U>& obj) noexcept {
            if(this == &obj)
                return *this;

            *this->_first = *obj._first;
            *this->_second = *obj._second;
            return *this;
        }

        friend std::ostream& operator << (std::ostream& f, const engine::NonConstexprPair<T, U>& obj ) noexcept {
            return (f << "{" << (*obj._first) << ", " << (*obj._second) << "}");
        }

    };

}


namespace engine {
    template <class T, class U>
    using Pair = NonConstexprPair<T, U>;
}

#endif //ENG1_PAIR_H
