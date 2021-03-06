//
// Created by loghin on 04.03.2021.
//

#ifndef ENG1_VCOMPONENT_H
#define ENG1_VCOMPONENT_H

#include <CDS/Object>

namespace engine {
    class VEntity;
    class VComponent : public Object {
        friend class VEntity;
    private:
        //// private variables
        VEntity const * _pParentEntity {nullptr};

        //// private functions

    public:
        class RootComponentDeleteException : public std::exception {
        public:
            [[nodiscard]] auto what() const noexcept -> StringLiteral override {
                return "Invalid delete operation. Cannot delete Component of Entity placed at top-most level in scene";
            }
        };

        //// public variables

        //// public functions
        explicit VComponent ( VEntity * = nullptr ) noexcept;
        ~VComponent() noexcept override = default;

        [[nodiscard]] constexpr auto parent () const noexcept -> VEntity const * { return this->_pParentEntity; }

        static void * operator new(std::size_t) noexcept (false);
        static void operator delete(void *) noexcept(false);

        [[nodiscard]] auto toString() const noexcept -> String override;
    };
}

#endif //ENG1_VCOMPONENT_H
