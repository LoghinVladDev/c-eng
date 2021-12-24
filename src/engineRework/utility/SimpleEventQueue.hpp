//
// Created by loghin on 23.12.2021.
//

#ifndef C_ENG_SIMPLEEVENTQUEUE_HPP
#define C_ENG_SIMPLEEVENTQUEUE_HPP

#include <Preprocess.hpp>
#include <CDS/Utility>
#include <sstream>

namespace engine :: utility {

    template<typename T>
    class SimpleEventQueue {
    private:
        struct Node {
            T data; // NOLINT(clion-misra-cpp2008-11-0-1)
            Node *pNext; // NOLINT(clion-misra-cpp2008-11-0-1)
        };

        Node *pHead{nullptr};
        Node *pBack{nullptr};

    public:
        ~SimpleEventQueue() noexcept {
            while (!this->empty()) { // NOLINT(clion-misra-cpp2008-5-3-1)
                (void) this->pop();
            }
        }

        C_ENG_NO_DISCARD constexpr auto empty() const noexcept -> bool {
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

        C_ENG_NO_DISCARD auto pop() noexcept(false) -> T {
            if (this->empty()) {
                throw cds::OutOfBoundsException();
            }

            auto p = this->pHead;
            this->pHead = p->pNext;

            auto value = p->data;
            delete p;

            return value;
        }

        C_ENG_NO_DISCARD auto toString () const noexcept -> cds :: String {
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

#endif //C_ENG_SIMPLEEVENTQUEUE_HPP
