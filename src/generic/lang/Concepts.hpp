//
// Created by loghin on 11/9/24.
//

#pragma once

#include <cds/meta/ObjectTraits>

namespace c_eng::generic::concepts::detail {
using cds::meta::IsDerivedFrom;
using cds::meta::IsBaseOf;

template <typename T, typename B> concept DerivedFrom = IsDerivedFrom<T, B>::value;
template <typename B, typename T> concept BaseOf = IsBaseOf<B, T>::value;

template <typename F, typename T> concept ConvertibleTo = cds::meta::IsConvertible<F, T>::value;

template <typename T, typename E> concept IterableOf = requires(T const& obj) {
  obj.begin();
  obj.end();
  { *obj.begin() } -> ConvertibleTo<E>;
};

template <typename T> concept Integer = cds::meta::Or<cds::meta::IsSigned<T>, cds::meta::IsUnsigned<T>>::value;
} // namespace c_eng::generic::detail

namespace c_eng::generic::concepts {
using detail::DerivedFrom;
using detail::BaseOf;
using detail::IterableOf;
using detail::Integer;
} // namespace c_eng::generic
