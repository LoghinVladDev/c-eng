//
// Created by loghin on 04.03.2021.
//

#ifndef ENG1_VCOMPONENT_H
#define ENG1_VCOMPONENT_H

#include <VObject.hpp>

namespace engine {
    class VEntity;
    class VComponent : public VObject {
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

    protected:
        enum TypeFlag : uint8 {
            NONE            = 0x00,
            V_TRANSFORM     = 0x01,
            V_MESH          = 0x02,
            V_MESH_RENDERER = 0x04
        };

        using TypeFlags = uint8;

#if __cpp_constexpr >= 201907
        __CDS_NoDiscard virtual constexpr auto typeFlag () const noexcept -> TypeFlag = 0;
#else
        __CDS_NoDiscard virtual inline auto typeFlag () const noexcept -> TypeFlag = 0;
#endif
        friend auto reconstructCacheBranch (VEntity *) noexcept -> void;

    private:
        friend class VEntity;
        friend class VScene;
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
        explicit VComponent ( Tags, uint64 ) noexcept;

    public:
        class RootComponentDeleteException : public std::exception {
        public:
            __CDS_NoDiscard auto what() const noexcept -> StringLiteral override {
                return "Invalid delete operation. Cannot delete Component of Entity placed at top-most level in scene";
            }
        };

        //// public variables

        //// public functions
        ~VComponent() noexcept override = default;

        __CDS_NoDiscard virtual auto className () const noexcept -> ClassName = 0;

        __CDS_NoDiscard constexpr auto parent () const noexcept -> VEntity const * { return this->_pParentEntity; }

        static void * operator new(std::size_t) noexcept (false);
        static void operator delete(void *) noexcept(false);

        __CDS_NoDiscard auto toString() const noexcept -> String override;
        __CDS_NoDiscard constexpr auto hash () const noexcept -> Index override { return static_cast < Index > (this->_ID); }
        __CDS_NoDiscard constexpr auto ID () const noexcept -> uint64 { return this->_ID; }
        __CDS_NoDiscard constexpr auto tags () const noexcept -> Tags { return this->_tags; }

        __CDS_NoDiscard auto copy () const noexcept -> VComponent * override = 0;
        __CDS_NoDiscard auto equals (Object const &) const noexcept -> bool override;
        __CDS_NoDiscard auto operator == (VComponent const &) const noexcept -> bool;

        __CDS_MaybeUnused constexpr auto addTag (Tag t) noexcept -> void {
            this->_tags |= t;
        }

        __CDS_MaybeUnused constexpr auto removeTag (Tag t) noexcept -> void {
            this->_tags &= ~(t & ALL_TAGS);
        }

        __CDS_NoDiscard constexpr auto hasTag (Tag t) const noexcept -> bool {
            return (this->_tags & t) == t;
        }

        VComponent & operator = ( VComponent const & o ) noexcept { // NOLINT(bugprone-unhandled-self-assignment)
            return * this;
        }
    };
}

#endif //ENG1_VCOMPONENT_H
