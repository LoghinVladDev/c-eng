/*
 * Created by loghin on 20/02/23.
 */

#ifndef __C_ENG_STORAGE_HPP__
#define __C_ENG_STORAGE_HPP__

#include <CDS/Union>

#include <base/core/Core.hpp>
#include <base/core/Object.hpp>

namespace engine::storage {

    class Node : public Object {
    public:
        using AnyOrNone = cds::Union <
                int,
                float,
                cds::StringView,
                std::nullptr_t
        >;

        explicit Node (Object const * pParent = nullptr) noexcept;
        ~Node () noexcept override = default;
        __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto className () const noexcept -> cds::StringView override {
            return "Node";
        }

        __CDS_NoDiscard auto getInt (cds::StringView key) const noexcept (false) -> int;
        __CDS_NoDiscard auto getFloat (cds::StringView key) const noexcept (false) -> float;
        __CDS_NoDiscard auto getString (cds::StringView key) const noexcept (false) -> cds::StringView;
        __CDS_NoDiscard auto getIntOrDefault (cds::StringView key, int defaultValue) const noexcept -> int;
        __CDS_NoDiscard auto getFloatOrDefault (cds::StringView key, float defaultValue) const noexcept -> float;
        __CDS_NoDiscard auto getStringOrDefault (cds::StringView key, cds::StringView defaultValue) const noexcept -> cds::StringView;

        __CDS_NoDiscard virtual auto get (cds::StringView key) const noexcept -> AnyOrNone = 0;
        virtual auto set (cds::StringView key, AnyOrNone data) noexcept -> void = 0;
    };

    class Storage : public Object {
    public:

        explicit Storage (Object const * pParent = nullptr) noexcept;
        ~Storage () noexcept override = default;
        __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto className () const noexcept -> cds::StringView override {
            return "Storage";
        }

        __CDS_NoDiscard virtual auto getNode (cds::StringView key) noexcept -> Node & = 0;
        __CDS_NoDiscard virtual auto getNode (cds::StringView key) const noexcept -> Node const & = 0;
        virtual auto reset () noexcept -> void = 0;
        virtual auto save () noexcept -> void = 0;
    };

}


#endif /* __C_ENG_STORAGE_HPP__ */
