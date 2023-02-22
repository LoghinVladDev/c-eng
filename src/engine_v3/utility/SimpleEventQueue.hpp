//
// Created by loghin on 23.12.2021.
//

#ifndef __C_ENG_SIMPLE_EVENT_QUEUE_HPP__
#define __C_ENG_SIMPLE_EVENT_QUEUE_HPP__ /* NOLINT(bugprone-reserved-identifier) */

#include <Preprocess.hpp>
#include <CDS/Utility>
#include <sstream>

namespace engine :: utility {

    template < typename T >
    class SimpleEventQueue {
    private:
        struct Node {
            T       data; // NOLINT(clion-misra-cpp2008-11-0-1)
            Node  * pNext; // NOLINT(clion-misra-cpp2008-11-0-1)
        };

        Node * pHead { nullptr };
        Node * pBack { nullptr };

    public:
        SimpleEventQueue () noexcept = default;

        SimpleEventQueue ( SimpleEventQueue const & queue ) noexcept {

            auto current = queue.pHead;
            while ( current != nullptr ) {
                this->push ( current->data );
                current = current->pNext;
            }
        }

        SimpleEventQueue ( SimpleEventQueue && queue ) noexcept :
                pHead ( cds :: exchange ( queue.pHead, nullptr ) ),
                pBack ( cds :: exchange ( queue.pBack, nullptr ) ) {

        }

        inline auto operator = ( SimpleEventQueue const & queue ) noexcept -> SimpleEventQueue & {
            if ( this == & queue ) {
                return * this;
            }

            this->clear();

            auto current = queue.pHead;
            while ( current != nullptr ) {
                this->push ( current->data );
                current = current->pNext;
            }

            return * this;
        }

        inline auto operator = ( SimpleEventQueue && queue ) noexcept -> SimpleEventQueue & {
            if ( this == & queue ) {
                return * this;
            }

            this->clear();

            this->pHead = cds :: exchange ( queue.pHead, nullptr );
            this->pBack = cds :: exchange ( queue.pBack, nullptr );

            return * this;
        }

        ~SimpleEventQueue() noexcept {
            this->clear();
        }

        inline auto clear () noexcept -> void {
            while ( ! this->empty() ) {
                (void) this->pop();
            }
        }

        __C_ENG_NO_DISCARD constexpr auto empty() const noexcept -> bool {
            return this->pHead == nullptr;
        }

        inline auto push(T const &value) noexcept -> void {
            if (this->empty()) {
                this->pHead = new Node{value, this->pHead};
                this->pBack = this->pHead;
            } else {
                this->pBack->pNext = new Node{value, nullptr};
                this->pBack = this->pBack->pNext;
            }
        }

        __C_ENG_NO_DISCARD auto pop() noexcept(false) -> T {
            if ( this->empty() ) {
                throw cds::OutOfBoundsException();
            }

            auto p = this->pHead;
            this->pHead = p->pNext;

            auto value = p->data;
            delete p;

            return value;
        }

        __C_ENG_NO_DISCARD auto toString () const noexcept -> cds :: String {
            std :: stringstream oss;
            auto pFront = this->pHead;

            while ( pFront != nullptr ) {
                cds :: Type < T > :: streamPrint ( oss, pFront->data );
                if ( pFront != pBack ) {
                    oss << ", ";
                }

                pFront = pFront->pNext;
            }

            return oss.str();
        }
    };

}

#endif //__C_ENG_SIMPLE_EVENT_QUEUE_HPP__
