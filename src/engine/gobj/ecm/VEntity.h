//
// Created by loghin on 04.03.2021.
//

#ifndef ENG1_VENTITY_H
#define ENG1_VENTITY_H

#include <engineVulkanPreproc.h>

#include <CDS/Object>
#include <CDS/Array>
#include <gobj/ecm/VComponent.h>

namespace engine {

    class VEntity : public Object {
    private:
        //// private variables
        VEntity                 const * _pParentEntity {nullptr};

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

    protected:
        explicit VEntity ( VEntity const * = nullptr ) noexcept;

    public:
        //// public variables

        //// public functions
        ~VEntity() noexcept override;

        virtual auto addComponent ( VComponent * ) noexcept -> bool;
        virtual auto addChild ( VEntity * ) const noexcept -> bool;

        virtual auto removeComponent ( VComponent * ) noexcept -> bool;
        virtual auto removeChild ( VEntity * ) const noexcept -> bool;

        constexpr auto parent() const noexcept -> VEntity const * { return this->_pParentEntity; }

        auto children () const noexcept -> Array < VEntity * > & { return this->_children; }
        auto siblings () const noexcept -> Array < VEntity * >;
        auto components () noexcept -> Array < VComponent * > & { return this->_components; }
        auto components () const noexcept -> Array < VComponent * > const & { return this->_components; }

        auto getComponentByClassName (String const &) noexcept -> VComponent *;
        auto getComponentByClassName (String const &) const noexcept -> VComponent const *;

        auto getComponentsByClassName (String const &) noexcept -> Array < VComponent * >;
        auto getComponentsByClassName (String const &) const noexcept -> Array < VComponent const * >;

        [[nodiscard]] auto toString() const noexcept -> String override;
        [[nodiscard]] constexpr auto hash () const noexcept -> Index override { return static_cast < Index > (this->_ID); }
        [[nodiscard]] constexpr auto ID () const noexcept -> uint64 { return this->_ID; }

        VEntity & operator = ( VEntity const & o ) noexcept { // NOLINT(bugprone-unhandled-self-assignment)
            return * this;
        }
    };
}

#endif //ENG1_VENTITY_H
