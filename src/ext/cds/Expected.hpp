//
// Created by loghin on 11/14/24.
//

#pragma once

#include <cds/Union>

#include <cds/collection/HashMap>
#include <cds/collection/Vector>

namespace cds::experimental {
namespace impl {
using meta::And;
using meta::IsTriviallyCopyConstructible;
using meta::IsTriviallyMoveConstructible;
using meta::IsTriviallyCopyAssignable;
using meta::IsTriviallyMoveAssignable;
using meta::IsTriviallyDestructible;
using meta::InvokeReturnOf;
using meta::RemoveRef;
using cds::impl::fwd;
using cds::impl::mv;

namespace fn = functional;

template <typename E> class Unexpected {
  static_assert(And<
      IsTriviallyDestructible<E>,
      IsTriviallyCopyConstructible<E>,
      IsTriviallyMoveConstructible<E>,
      IsTriviallyCopyAssignable<E>,
      IsTriviallyMoveAssignable<E>
  >::value, "Error type is not trivial");
public:
  template <typename... Args> explicit constexpr Unexpected(Args&&... args) noexcept : _error{fwd<Args>(args)...} {}
  [[nodiscard]] auto get() const noexcept -> E {
    return _error;
  }

private:
  E _error;
};

struct Unexpect {};

template <typename T, typename E> class Expected : private Union<T, E> {
public:
  explicit(false) constexpr Expected(Unexpected<E> error) noexcept : Union<T, E>{InPlaceIndex<1>{}, error.get()} {}
  constexpr Expected(Unexpect, E error) noexcept : Union<T, E>{InPlaceIndex<1>{}, error} {}

  template <typename... Args> explicit(false) constexpr Expected(Args&&... args) noexcept :
      Union<T, E>{InPlaceIndex<0>{}, fwd<Args>(args)...} {}

  constexpr Expected(Expected const& expected) : Union<T, E>{expected} {}
  constexpr Expected(Expected&& expected) noexcept : Union<T, E>{mv(expected)} {}
  ~Expected() = default;

  [[nodiscard]] constexpr auto hasValue() const noexcept -> bool {
    return this->template is<T>();
  }

  [[nodiscard]] explicit constexpr operator bool() const noexcept {
    return hasValue();
  }

  [[nodiscard]] constexpr auto operator*() const& noexcept -> T const& {
    assert(hasValue());
    return get<T>(*this);
  }

  [[nodiscard]] constexpr auto operator*()& noexcept -> T& {
    assert(hasValue());
    return get<T>(*this);
  }

  [[nodiscard]] constexpr auto operator*() const&& noexcept -> T const&& {
    assert(hasValue());
    return get<T>(mv(*this));
  }

  [[nodiscard]] constexpr auto operator*()&& noexcept -> T&& {
    assert(hasValue());
    return get<T>(mv(*this));
  }

  [[nodiscard]] constexpr auto operator->() noexcept -> T* {
    assert(hasValue());
    return &get<T>(*this);
  }

  [[nodiscard]] constexpr auto operator->() const noexcept -> T const* {
    assert(hasValue());
    return &get<T>(*this);
  }

  [[nodiscard]] constexpr auto value() const& noexcept -> T const& {
    assert(hasValue());
    return get<T>(*this);
  }

  [[nodiscard]] constexpr auto value()& noexcept -> T& {
    assert(hasValue());
    return get<T>(*this);
  }

  [[nodiscard]] constexpr auto value() const&& noexcept -> T const&& {
    assert(hasValue());
    return get<T>(mv(*this));
  }

  [[nodiscard]] constexpr auto value()&& noexcept -> T&& {
    assert(hasValue());
    return get<T>(mv(*this));
  }

  template <typename U> [[nodiscard]] constexpr auto valueOr(U&& defaultValue) const& -> T {
    return hasValue() ? **this : static_cast<T>(fwd<U>(defaultValue));
  }

  template <typename U> [[nodiscard]] constexpr auto valueOr(U&& defaultValue) && -> T {
    return hasValue() ? mv(**this) : static_cast<T>(fwd<U>(defaultValue));
  }

  template <typename G> [[nodiscard]] constexpr auto errorOr(G defaultValue) const noexcept -> E {
    return !hasValue() ? error() : static_cast<E>(defaultValue);
  }

  [[nodiscard]] constexpr auto error() const noexcept -> E {
    assert(!hasValue());
    return get<E>(*this);
  }

  template <typename F, typename E0 = InvokeReturnOf<F, T&>> [[nodiscard]] constexpr auto then(F&& fn)& -> E0 {
    return hasValue()
        ? fn::invoke(fwd<F>(fn), value())
        : E0{Unexpect{}, error()};
  }

  template <typename F, typename E0 = InvokeReturnOf<F, T&>> [[nodiscard]] constexpr auto then(F&& fn) const& -> E0 {
    return hasValue()
        ? fn::invoke(fwd<F>(fn), value())
        : E0{Unexpect{}, error()};
  }

  template <typename F, typename E0 = InvokeReturnOf<F, T&>> [[nodiscard]] constexpr auto then(F&& fn)&& -> E0 {
    return hasValue()
        ? fn::invoke(fwd<F>(fn), mv(value()))
        : E0{Unexpect{}, error()};
  }

  template <typename F, typename E0 = InvokeReturnOf<F, T&>> [[nodiscard]] constexpr auto then(F&& fn) const&& -> E0 {
    return hasValue()
        ? fn::invoke(fwd<F>(fn), mv(value()))
        : E0{Unexpect{}, error()};
  }

  template <typename F, typename U = RemoveRef<InvokeReturnOf<F, T&>>> [[nodiscard]] constexpr auto transform(F&& fn)&
      -> Expected<U, E> {
    return hasValue()
        ? Expected<U, E>{fn::invoke(fwd<F>(fn), value())}
        : Expected<U, E>{Unexpect{}, error()};
  }

  template <typename F, typename U = RemoveRef<InvokeReturnOf<F, T const&>>>
  [[nodiscard]] constexpr auto transform(F&& fn) const& -> Expected<U, E> {
    return hasValue()
        ? Expected<U, E>{fn::invoke(fwd<F>(fn), value())}
        : Expected<U, E>{Unexpect{}, error()};
  }

  template <typename F, typename U = RemoveRef<InvokeReturnOf<F, T&&>>>
  [[nodiscard]] constexpr auto transform(F&& fn)&& -> Expected<U, E> {
    return hasValue()
        ? Expected<U, E>{fn::invoke(fwd<F>(fn), mv(value()))}
        : Expected<U, E>{Unexpect{}, error()};
  }

  template <typename F, typename U = RemoveRef<InvokeReturnOf<F, T const&&>>>
  [[nodiscard]] constexpr auto transform(F&& fn) const&& -> Expected<U, E> {
    return hasValue()
        ? Expected<U, E>{fn::invoke(fwd<F>(fn), mv(value()))}
        : Expected<U, E>{Unexpect{}, error()};
  }

  template <typename F> [[nodiscard]] constexpr auto orElse(F&& fn)& -> Expected {
    return hasValue() ? *this : fn::invoke(fwd<F>(fn), error());
  }

  template <typename F> [[nodiscard]] constexpr auto orElse(F&& fn) const& -> Expected {
    return hasValue() ? *this : fn::invoke(fwd<F>(fn), error());
  }

  template <typename F> [[nodiscard]] constexpr auto orElse(F&& fn)&& -> Expected {
    return hasValue() ? mv(*this) : fn::invoke(fwd<F>(fn), error());
  }

  template <typename F> [[nodiscard]] constexpr auto orElse(F&& fn) const&& -> Expected {
    return hasValue() ? mv(*this) : fn::invoke(fwd<F>(fn), error());
  }

  template <typename F, typename G = RemoveRef<InvokeReturnOf<F, E>>>
  [[nodiscard]] constexpr auto transformError(F&& fn)& -> Expected<T, G> {
    return hasValue()
        ? Expected<T, G>{value()}
        : Expected<T, G>{Unexpect{}, fn::invoke(fwd<F>(fn), error())};
  }

  template <typename F, typename G = RemoveRef<InvokeReturnOf<F, E>>>
  [[nodiscard]] constexpr auto transformError(F&& fn) const& -> Expected<T, G> {
    return hasValue()
        ? Expected<T, G>{value()}
        : Expected<T, G>{Unexpect{}, fn::invoke(fwd<F>(fn), error())};
  }

  template <typename F, typename G = RemoveRef<InvokeReturnOf<F, E>>>
  [[nodiscard]] constexpr auto transformError(F&& fn)&& -> Expected<T, G> {
    return hasValue()
        ? Expected<T, G>{mv(value())}
        : Expected<T, G>{Unexpect{}, fn::invoke(fwd<F>(fn), error())};
  }

  template <typename F, typename G = RemoveRef<InvokeReturnOf<F, E>>>
  [[nodiscard]] constexpr auto transformError(F&& fn) const&& -> Expected<T, G> {
    return hasValue()
        ? Expected<T, G>{mv(value())}
        : Expected<T, G>{Unexpect{}, fn::invoke(fwd<F>(fn), error())};
  }

  template <typename... Args> [[nodiscard]] constexpr auto emplace(Args&&... args) -> T& {
    return Union<T, E>::template emplace<0>(fwd<Args>(args)...);
  }
};

template <typename E> class Expected<void, E> : private Optional<E> {
public:
  Expected() = default;
  explicit constexpr Expected(Unexpected<E> error) noexcept : Optional<E>{error.get()} {}
  constexpr Expected(Unexpect, E error) noexcept : Optional<E>{error} {}

  constexpr Expected(Expected const& expected) : Optional<E>{expected} {}
  constexpr Expected(Expected&& expected) noexcept : Optional<E>{mv(expected)} {}
  ~Expected() = default;

  [[nodiscard]] constexpr auto hasValue() const noexcept -> bool {
    return !Optional<E>::hasValue();
  }

  [[nodiscard]] explicit constexpr operator bool() const noexcept {
    return hasValue();
  }

  template <typename G> [[nodiscard]] constexpr auto errorOr(G defaultValue) const noexcept -> E {
    return !hasValue() ? error() : static_cast<E>(defaultValue);
  }

  [[nodiscard]] constexpr auto error() const noexcept -> E {
    assert(!hasValue());
    return get<E>(*this);
  }

  template <typename F> [[nodiscard]] constexpr auto then(F&& fn)& -> Expected {
    return hasValue() ? fn::invoke(fwd<F>(fn)) : error();
  }

  template <typename F> [[nodiscard]] constexpr auto then(F&& fn) const& -> Expected {
    return hasValue() ? fn::invoke(fwd<F>(fn)) : error();
  }

  template <typename F> [[nodiscard]] constexpr auto then(F&& fn)&& -> Expected {
    return hasValue() ? fn::invoke(fwd<F>(fn)) : error();
  }

  template <typename F> [[nodiscard]] constexpr auto then(F&& fn) const&& -> Expected {
    return hasValue() ? fn::invoke(fwd<F>(fn)) : error();
  }

  template <typename F, typename U = InvokeReturnOf<F>> [[nodiscard]] constexpr auto transform(F&& fn)&
      -> Expected<U, E> {
    return hasValue()
        ? Expected<U, E>{fn::invoke(fwd<F>(fn))}
        : Expected<U, E>{Unexpect{}, error()};
  }

  template <typename F, typename U = InvokeReturnOf<F>> [[nodiscard]] constexpr auto transform(F&& fn) const&
      -> Expected<U, E> {
    return hasValue()
        ? Expected<U, E>{fn::invoke(fwd<F>(fn))}
        : Expected<U, E>{Unexpect{}, error()};
  }

  template <typename F, typename U = InvokeReturnOf<F>> [[nodiscard]] constexpr auto transform(F&& fn)&&
      -> Expected<U, E> {
    return hasValue()
        ? Expected<U, E>{fn::invoke(fwd<F>(fn))}
        : Expected<U, E>{Unexpect{}, error()};
  }

  template <typename F, typename U = InvokeReturnOf<F>> [[nodiscard]] constexpr auto transform(F&& fn) const&&
      -> Expected<U, E> {
    return hasValue()
        ? Expected<U, E>{fn::invoke(fwd<F>(fn))}
        : Expected<U, E>{Unexpect{}, error()};
  }

  template <typename F> [[nodiscard]] constexpr auto orElse(F&& fn)& -> Expected {
    return hasValue() ? *this : fn::invoke(fwd<F>(fn), error());
  }

  template <typename F> [[nodiscard]] constexpr auto orElse(F&& fn) const& -> Expected {
    return hasValue() ? *this : fn::invoke(fwd<F>(fn), error());
  }

  template <typename F> [[nodiscard]] constexpr auto orElse(F&& fn)&& -> Expected {
    return hasValue() ? mv(*this) : fn::invoke(fwd<F>(fn), error());
  }

  template <typename F> [[nodiscard]] constexpr auto orElse(F&& fn) const&& -> Expected {
    return hasValue() ? mv(*this) : fn::invoke(fwd<F>(fn), error());
  }

  template <typename F, typename G = InvokeReturnOf<F, E>> [[nodiscard]] constexpr auto transformError(F&& fn)&
      -> Expected<void, G> {
    return hasValue()
        ? Expected<void, G>{}
        : Expected<void, G>{Unexpect{}, fn::invoke(fwd<F>(fn), error())};
  }

  template <typename F, typename G = InvokeReturnOf<F, E>> [[nodiscard]] constexpr auto transformError(F&& fn) const&
        -> Expected<void, G> {
    return hasValue()
        ? Expected<void, G>{}
        : Expected<void, G>{Unexpect{}, fn::invoke(fwd<F>(fn), error())};
  }

  template <typename F, typename G = InvokeReturnOf<F, E>> [[nodiscard]] constexpr auto transformError(F&& fn)&&
      -> Expected<void, G> {
    return hasValue()
        ? Expected<void, G>{}
        : Expected<void, G>{Unexpect{}, fn::invoke(fwd<F>(fn), error())};
  }

  template <typename F, typename G = InvokeReturnOf<F, E>> [[nodiscard]] constexpr auto transformError(F&& fn) const&&
      -> Expected<void, G> {
    return hasValue()
        ? Expected<void, G>{}
        : Expected<void, G>{Unexpect{}, fn::invoke(fwd<F>(fn), error())};
  }

  constexpr auto emplace() noexcept -> void {
    ignore = this;
  }
};

template <typename E> Unexpected(E) -> Unexpected<E>;
} // namespace impl

using impl::Expected;
using impl::Unexpected;
using impl::Unexpect;
} // namespace cds::experimental
