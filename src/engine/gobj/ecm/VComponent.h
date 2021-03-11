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
    public:
        enum Tag: uint8 {
            DISTINCT        = 0x01,
            HAS_DEPENDENCY  = 0x02
        };

        using Tags = uint8;

        constexpr static Tags NO_TAGS = 0u;
        constexpr static Tags ALL_TAGS =
                DISTINCT        |
                HAS_DEPENDENCY;

        using ClassName = String;

    private:
        friend class VEntity;
        //// private variables
        uint64          _ID             { VComponent::nextID() }; // NOLINT(bugprone-reserved-identifier)
        static uint64   _IDCounter;                               // NOLINT(bugprone-reserved-identifier)

        VEntity const * _pParentEntity  { nullptr };
        Tags            _tags           { NO_TAGS };

        //// private functions
        static auto nextID () noexcept -> uint64 { return VComponent::_IDCounter++; }

    protected:
        /// protected variables

        /// protected functions
        explicit VComponent ( Tags, VEntity * = nullptr ) noexcept;

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

        [[nodiscard]] virtual auto className () const noexcept -> ClassName = 0;

        [[nodiscard]] constexpr auto parent () const noexcept -> VEntity const * { return this->_pParentEntity; }

        static void * operator new(std::size_t) noexcept (false);
        static void operator delete(void *) noexcept(false);

        [[nodiscard]] auto toString() const noexcept -> String override;
        [[nodiscard]] constexpr auto hash () const noexcept -> Index override { return static_cast < Index > (this->_ID); }
        [[nodiscard]] constexpr auto ID () const noexcept -> uint64 { return this->_ID; }
        [[nodiscard]] constexpr auto tags () const noexcept -> Tags { return this->_tags; }

        constexpr auto addTag (Tag t) noexcept -> void {
            this->_tags |= t;
        }

        constexpr auto removeTag (Tag t) noexcept -> void {
            this->_tags &= ~(t & ALL_TAGS);
        }

        [[nodiscard]] constexpr auto hasTag (Tag t) const noexcept -> bool {
            return (this->_tags & t) == t;
        }

        VComponent & operator = ( VComponent const & o ) noexcept { // NOLINT(bugprone-unhandled-self-assignment)
            return * this;
        }
    };
}

#endif //ENG1_VCOMPONENT_H
