//
// Created by loghin on 04.03.2021.
//

#ifndef ENG1_VENTITY_H
#define ENG1_VENTITY_H

#include <VObject.hpp>
#include <CDS/Array>
#include <ecm/VComponent.hpp>
#include <transform/VTransform.hpp>

namespace engine {

    class VScene;
    class VEntity : public VObject {
    private:
        friend class VScene;
    private:
        //// private variables
        VEntity                 const * _pParentEntity  {nullptr};
        VScene                  const * _pScene         {nullptr};

        /**
         * Components immutable
         * Children mutable ( Entities ( GameObject is derived from Entity ) )
         *
         * Reasoning :
         *      ParentGObj1 { C1 = transform, C2 = mesh + renderer }
         *          - ChildGObj2 { C1 = transform, C2 = mesh }
         *              - ChildGObj5 { C1 = transform }
         *          - ChildGObj3
         *              - ChildGObj4 { C1 = transform }
         *
         *  Access Scenarios : ChildGObj1 can get children of parent, can remove ChildGObj2 ( sibling )
         *                     ChildGObj1 can only get immutable array of components. Cannot forcibly remove transform,
         *                     as it depends on it.
         *
         *                     By doing ChildGObj4 - parent we get const * to ChildGObj2.
         *                     By doing ChildGOjb2 const * - parent we get const * to ParentGObj1
         *                     Children ARE mutable, so we can get non const * to ChildGObj2 and remove transform
         *                     By doing so, ChildGObj5 will depend on ParentGObj1. Useful in IK / Object world stickiness
         *
         *                     Only components not entirely removable are ParentGObj1's components. By doing so we would
         *                     have UB ( Undefined Behaviour ). All Children must at least depend on the most-top-level transform
         *
         *                     Note : VComponent operator delete will do such assigns ( if ChildGObj2 :: C1 gets deleted,
         *                     links children transforms to ParentGObj1 ), also will throw ImpossibleOperation if attempt
         *                     to delete component of top-level Entity
         *
         */
        Array < VComponent * >          _components;
        Array < VEntity * >    mutable  _children;

        uint64                          _ID { VEntity::nextID() }; // NOLINT(bugprone-reserved-identifier)
        static uint64                   _IDCounter; // NOLINT(bugprone-reserved-identifier)

        //// private
        static auto nextID() noexcept -> uint64 { return VEntity::_IDCounter++; }

        VComponent::TypeFlags _ownedComponentFlags = VComponent::TypeFlag::NONE;

        friend auto reconstructCacheBranch (VEntity *) noexcept -> void;

    protected:
        explicit VEntity ( std::nullptr_t = nullptr ) noexcept : _pScene(nullptr), _pParentEntity(nullptr) {}

        explicit VEntity ( VEntity const * ) noexcept;
        explicit VEntity ( VScene * ) noexcept;

        explicit VEntity ( uint64 ) noexcept;

        VTransform      * _pTransform     {nullptr};

    public:
        using ClassName = String;

        class __CDS_MaybeUnused RootEntityDeleteException : public std::exception {
        public:
            __CDS_NoDiscard auto what() const noexcept -> StringLiteral override {
                return "Invalid delete operation. Cannot delete Entity placed at top-most level in Scene";
            }
        };

        //// public variables

        //// public functions
        ~VEntity() noexcept override;

        __CDS_NoDiscard virtual auto className () const noexcept -> ClassName = 0;

        static void * operator new(std::size_t) noexcept (false);
        static void operator delete(void *) noexcept (false);

        virtual auto add ( VComponent * ) noexcept -> bool;
        virtual auto add ( VEntity * ) const noexcept -> bool;
        virtual auto add ( std::nullptr_t ) const noexcept -> bool { return false; } // NOLINT(readability-convert-member-functions-to-static)

        virtual auto remove ( VComponent * ) noexcept -> bool;
        virtual auto remove ( VEntity * ) const noexcept -> bool;
        virtual auto remove ( std::nullptr_t ) const noexcept -> bool { return false; } // NOLINT(readability-convert-member-functions-to-static)

        constexpr auto parentPtr() const noexcept -> VEntity const * { return this->_pParentEntity; }
        __CDS_MaybeUnused constexpr auto scenePtr() const noexcept -> VScene const * { return this->_pScene; }

        auto children () const noexcept -> Array < VEntity * > & { return this->_children; }
        auto siblings () const noexcept -> Array < VEntity * >;
        auto components () noexcept -> Array < VComponent * > & { return this->_components; }
        auto components () const noexcept -> Array < VComponent * > const & { return this->_components; }

        __CDS_MaybeUnused auto getComponentByClassName (String const &) noexcept -> VComponent *;
        __CDS_MaybeUnused auto getComponentByClassName (String const &) const noexcept -> VComponent const *;

        __CDS_MaybeUnused auto getComponentsByClassName (String const &) noexcept -> Array < VComponent * >;
        __CDS_MaybeUnused auto getComponentsByClassName (String const &) const noexcept -> Array < VComponent const * >;

        __CDS_NoDiscard auto toString() const noexcept -> String override;
        __CDS_NoDiscard constexpr auto hash () const noexcept -> Index override { return static_cast < Index > (this->_ID); }
        __CDS_NoDiscard constexpr auto ID () const noexcept -> uint64 { return this->_ID; }

        __CDS_NoDiscard auto copy () const noexcept -> VEntity * override = 0;
        __CDS_NoDiscard auto equals (Object const &) const noexcept -> bool override;
        __CDS_NoDiscard auto operator == (VEntity const &) const noexcept -> bool;

        VEntity & operator = ( VEntity const & o ) noexcept { // NOLINT(bugprone-unhandled-self-assignment)
            return * this;
        }
    };
}

#endif //ENG1_VENTITY_H
