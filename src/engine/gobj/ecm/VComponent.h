//
// Created by loghin on 04.03.2021.
//

#ifndef ENG1_VCOMPONENT_H
#define ENG1_VCOMPONENT_H

#include <engineVulkanPreproc.h>
#include <CDS/Object>

namespace engine {
    class VEntity;
    class VComponent : public Object {
        friend class VEntity;
    private:
        //// private variables
        uint64          _ID { VComponent::nextID() };
        static uint64   _IDCounter;

        VEntity const * _pParentEntity {nullptr};

        //// private functions
        static auto nextID () noexcept -> uint64 { return VComponent::_IDCounter++; }

    protected:
        /// protected variables

        /// protected functions
        explicit VComponent ( VEntity * = nullptr ) noexcept;

    public:
        class RootComponentDeleteException : public std::exception {
        public:
            [[nodiscard]] auto what() const noexcept -> StringLiteral override {
                return "Invalid delete operation. Cannot delete Component of Entity placed at top-most level in scene";
            }
        };

        //// public variables

        //// public functions
        ~VComponent() noexcept override = default;

        [[nodiscard]] constexpr auto parent () const noexcept -> VEntity const * { return this->_pParentEntity; }

        static void * operator new(std::size_t) noexcept (false);
        static void operator delete(void *) noexcept(false);

        [[nodiscard]] auto toString() const noexcept -> String override;
        [[nodiscard]] constexpr auto hash () const noexcept -> Index override { return static_cast < Index > (this->_ID); }
        [[nodiscard]] constexpr auto ID () const noexcept -> uint64 { return this->_ID; }

        VComponent & operator = ( VComponent const & o ) noexcept { // NOLINT(bugprone-unhandled-self-assignment)
            return * this;
        }
    };
}

#endif //ENG1_VCOMPONENT_H
