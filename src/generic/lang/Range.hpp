//
// Created by loghin on 11/5/24.
//

#pragma once

#include <cds/Optional>
#include <cds/Tuple>
#include <cds/functional/Invoke>
#include <cds/meta/IterableTraits>
#include <cds/iterator/Sentinel>

#include <generic/lang/Concepts.hpp>

namespace c_eng::generic::detail {
using cds::Optional;
using cds::Size;
using cds::Tuple;
using cds::iterator::Sentinel;

using cds::impl::fwd;

using cds::ignore;
using cds::nullopt;
using cds::tie;

using cds::meta::RemoveCVRef;
using cds::meta::rvalue;
using cds::meta::value;

namespace fn = cds::functional;

template <typename I, typename P> class ProjectionIterator {
public:
  template <typename Iterator, typename Projector>
  constexpr ProjectionIterator(Iterator&& iterator, Projector&& projector) :
      _iterator {fwd<Iterator>(iterator)}, _projector{fwd<Projector>(projector)} {}
  constexpr ProjectionIterator(ProjectionIterator const&) noexcept = default;
  constexpr ProjectionIterator(ProjectionIterator&&) noexcept = default;
  constexpr auto operator=(ProjectionIterator const&) noexcept -> ProjectionIterator& = default;
  constexpr auto operator=(ProjectionIterator&&) noexcept -> ProjectionIterator& = default;
  constexpr ~ProjectionIterator() noexcept = default;

  constexpr auto operator++() -> ProjectionIterator& {
    ++_iterator;
    return *this;
  }

  [[nodiscard]] constexpr auto base() const noexcept -> I const& {
    return _iterator;
  }

  [[nodiscard]] constexpr auto operator+(Size offset) const noexcept {
    return ProjectionIterator{_iterator + offset, _projector};
  }

  [[nodiscard]] constexpr auto operator-(Size offset) const noexcept {
    return ProjectionIterator{_iterator - offset, _projector};
  }

  constexpr decltype(auto) operator*() const {
    return fn::invoke(_projector, *_iterator);
  }

  constexpr auto* operator->() const {
    return &operator*();
  }

  template <typename OtherIt> constexpr auto operator==(ProjectionIterator<OtherIt, P> const& iterator) const noexcept
      -> bool {
    return _iterator == iterator.base();
  }

private:
  I _iterator;
  [[no_unique_address]] P _projector;
};

template <typename I, typename P> class IndexedProjectionIterator {
public:
  template <typename Iterator, typename Projector>
  constexpr IndexedProjectionIterator(Iterator&& iterator, Projector&& projector) :
      _iterator {fwd<Iterator>(iterator)}, _projector{fwd<Projector>(projector)}, _index{0u} {}

  template <typename Iterator, typename Projector>
  constexpr IndexedProjectionIterator(Iterator&& iterator, Projector&& projector, Size index) :
      _iterator {fwd<Iterator>(iterator)}, _projector{fwd<Projector>(projector)}, _index{index} {}
  constexpr IndexedProjectionIterator(IndexedProjectionIterator const&) noexcept = default;
  constexpr IndexedProjectionIterator(IndexedProjectionIterator&&) noexcept = default;
  constexpr auto operator=(IndexedProjectionIterator const&) noexcept -> IndexedProjectionIterator& = default;
  constexpr auto operator=(IndexedProjectionIterator&&) noexcept -> IndexedProjectionIterator& = default;
  constexpr ~IndexedProjectionIterator() noexcept = default;

  constexpr auto operator++() -> IndexedProjectionIterator& {
    ++_iterator;
    ++_index;
    return *this;
  }

  [[nodiscard]] constexpr auto base() const noexcept -> I const& {
    return _iterator;
  }

  [[nodiscard]] constexpr auto operator+(Size offset) const noexcept {
    return IndexedProjectionIterator{_iterator + offset, _projector, _index + offset};
  }

  [[nodiscard]] constexpr auto operator-(Size offset) const noexcept {
    return IndexedProjectionIterator{_iterator - offset, _projector, _index + offset};
  }

  constexpr decltype(auto) operator*() const {
    return fn::invoke(_projector, _index, *_iterator);
  }

  constexpr auto* operator->() const {
    return &operator*();
  }

  template <typename OtherIt> constexpr auto operator==(IndexedProjectionIterator<OtherIt, P> const& iterator) const noexcept
      -> bool {
    return _iterator == iterator.base();
  }

private:
  I _iterator;
  [[no_unique_address]] P _projector;
  Size _index;
};

template <typename I, typename S, typename P> class FilterIterator {
public:
  template <typename Iterator, typename Sentinel, typename Predicate>
  constexpr FilterIterator(Iterator&& begin, Sentinel&& sent, Predicate&& pred) :
      _it{fwd<Iterator>(begin)}, _sent{fwd<Sentinel>(sent)}, _pred{fwd<Predicate>(pred)} {
    adv();
  }

  constexpr FilterIterator(FilterIterator const&) noexcept = default;
  constexpr FilterIterator(FilterIterator&&) noexcept = default;
  constexpr auto operator=(FilterIterator const&) noexcept -> FilterIterator& = default;
  constexpr auto operator=(FilterIterator&&) noexcept -> FilterIterator& = default;
  constexpr ~FilterIterator() noexcept = default;

  constexpr auto operator++() -> FilterIterator& {
    ++_it;
    adv();
    return *this;
  }

  [[nodiscard]] constexpr auto base() const noexcept -> I const& {
    return _it;
  }

  constexpr decltype(auto) operator*() const {
    return *_it;
  }

  constexpr auto* operator->() const {
    return &operator*();
  }

  constexpr auto operator==(Sentinel) const noexcept -> bool {
    return _it == _sent;
  }

  constexpr auto operator!=(Sentinel) const noexcept -> bool {
    return _it != _sent;
  }

private:
  constexpr auto adv() noexcept -> void {
    while (_it != _sent && !fn::invoke(_pred, *_it)) {
      ++_it;
    }
  }

  I _it;
  [[no_unique_address]] S _sent;
  [[no_unique_address]] P _pred;
};

template <typename I, typename S> class FlattenerIterator {
public:
  template <typename Iterator, typename Sentinel>
  constexpr FlattenerIterator(Iterator&& begin, Sentinel&& sent) :
      _it{fwd<Iterator>(begin)},
      _sent{fwd<Sentinel>(sent)} {
    while (_it != _sent) {
      _subIt.emplace(cds::begin(*_it), cds::end(*_it));
      if (get<0>(*_subIt) != get<1>(*_subIt)) {
        break;
      }
      _subIt.reset();
      ++_it;
    }
  }

  constexpr FlattenerIterator(FlattenerIterator const&) noexcept = default;
  constexpr FlattenerIterator(FlattenerIterator&&) noexcept = default;
  constexpr auto operator=(FlattenerIterator const&) noexcept -> FlattenerIterator& = default;
  constexpr auto operator=(FlattenerIterator&&) noexcept -> FlattenerIterator& = default;
  constexpr ~FlattenerIterator() noexcept = default;

  constexpr auto operator++() -> FlattenerIterator& {
    if (!_subIt) {
      return *this;
    }

    while (_it != _sent) {
      if (get<0>(*_subIt) == get<1>(*_subIt)) {
        ++_it;
        if (_it == _sent) {
          break;
        }
        _subIt.emplace(cds::begin(*_it), cds::end(*_it));
      } else {
        ++get<0>(*_subIt);
      }

      if (get<0>(*_subIt) != get<1>(*_subIt)) {
        break;
      }
    }

    if (_it == _sent) {
      _subIt.reset();
    }

    return *this;
  }

  constexpr decltype(auto) operator*() const {
    return *get<0>(*_subIt);
  }

  constexpr auto* operator->() const {
    return &operator*();
  }

  constexpr auto operator==(Sentinel) const noexcept -> bool {
    return _it == _sent;
  }

  constexpr auto operator!=(Sentinel) const noexcept -> bool {
    return _it != _sent;
  }

private:
  using T = decltype(*rvalue<I>());
  using TI = decltype(cds::begin(value<T>()));
  using TS = decltype(cds::end(value<T>()));

  I _it;
  [[no_unique_address]] S _sent;
  Optional<Tuple<TI, TS>> _subIt;
};

template <typename I, typename P> ProjectionIterator(I&&, P&&) -> ProjectionIterator<I, P>;
template <typename I, typename P> IndexedProjectionIterator(I&&, P&&) -> IndexedProjectionIterator<I, P>;
template <typename I, typename S, typename P> FilterIterator(I&&, S&&, P&&) -> FilterIterator<I, S, P>;
template <typename I, typename S> FlattenerIterator(I&&, S&&) -> FlattenerIterator<I, S>;

template <typename Range, typename Projector> class ProjectionRange {
public:
  template <typename R, typename P> constexpr ProjectionRange(R&& range, P&& proj) noexcept :
      _range{fwd<R>(range)}, _projector{fwd<P>(proj)} {}

  constexpr auto begin() const noexcept {
    return ProjectionIterator{cds::begin(_range), _projector};
  }

  constexpr auto end() const noexcept {
    return ProjectionIterator{cds::end(_range), _projector};
  }

private:
  Range const& _range;
  [[no_unique_address]] Projector const _projector;
};

template <typename Range, typename Projector> class IndexedProjectionRange {
public:
  template <typename R, typename P> constexpr IndexedProjectionRange(R&& range, P&& proj) noexcept :
      _range{fwd<R>(range)}, _projector{fwd<P>(proj)} {}

  constexpr auto begin() const noexcept {
    return IndexedProjectionIterator{cds::begin(_range), _projector};
  }

  constexpr auto end() const noexcept {
    return IndexedProjectionIterator{cds::end(_range), _projector};
  }

private:
  Range const& _range;
  [[no_unique_address]] Projector const _projector;
};

template <typename Range, typename Predicate> class FilterRange {
public:
  template <typename R, typename P> constexpr FilterRange(R&& range, P&& pred) noexcept :
      _range{fwd<R>(range)}, _pred{fwd<P>(pred)} {}

  constexpr auto begin() const noexcept {
    return FilterIterator{cds::begin(_range), cds::end(_range), _pred};
  }

  constexpr auto end() const noexcept {
    ignore = this;
    return Sentinel{};
  }

private:
  Range const& _range;
  [[no_unique_address]] Predicate const _pred;
};

template <typename Range> class FlattenerRange {
public:
  template <typename R> constexpr FlattenerRange(R&& range) noexcept :
      _range{fwd<R>(range)} {}

  constexpr auto begin() const noexcept {
    return FlattenerIterator{cds::begin(_range), cds::end(_range)};
  }

  constexpr auto end() const noexcept {
    ignore = this;
    return Sentinel{};
  }

private:
  Range const& _range;
};

template <typename R, typename P> IndexedProjectionRange(R const&, P&&) -> IndexedProjectionRange<R, P>;
template <typename R, typename P> ProjectionRange(R const&, P&&) -> ProjectionRange<R, P>;
template <typename R, typename P> FilterRange(R const&, P&&) -> FilterRange<R, P>;
template <typename R> FlattenerRange(R const&) -> FlattenerRange<R>;

struct RangeModifierTag {};

template <typename P> struct IndexedProjector : RangeModifierTag {
  template <typename P0> explicit IndexedProjector(P0&& proj) noexcept : _proj{fwd<P0>(proj)} {}
  template <typename R> auto operator()(R const& range) const noexcept;
  P _proj;
};

template <typename P> struct Projector : RangeModifierTag {
  template <typename P0> explicit Projector(P0&& proj) noexcept : _proj{fwd<P0>(proj)} {}
  template <typename R> auto operator()(R const& range) const noexcept;
  P _proj;
};

template <typename P> struct Filter : RangeModifierTag {
  template <typename P0> explicit Filter(P0&& proj) noexcept : _pred{fwd<P0>(proj)} {}
  template <typename R> auto operator()(R const& range) const noexcept;
  P _pred;
};

struct Flattener : RangeModifierTag {
  template <typename R> auto operator()(R const& range) const noexcept;
};

template <typename F> struct ForEach : RangeModifierTag {
  template <typename F0> explicit ForEach(F0&& func) noexcept : _func{fwd<F0>(func)} {}
  template <typename R> auto operator()(R const& range) const noexcept;
  F _func;
};

struct FindAny : RangeModifierTag {
  template <typename R> auto operator()(R const& range) const noexcept;
};

struct IndexedProjectModifier : RangeModifierTag {
  template <typename P> auto operator()(P&& projector) const noexcept {
    return IndexedProjector<P&&>{fwd<P>(projector)};
  }

  template <typename R, typename P> auto operator()(R const& range, P&& projector) const noexcept {
    return IndexedProjectionRange{range, fwd<P>(projector)};
  }
};

struct ProjectModifier {
  template <typename P> auto operator()(P&& projector) const noexcept {
    return Projector<P&&>{fwd<P>(projector)};
  }

  template <typename R, typename P> auto operator()(R const& range, P&& projector) const noexcept {
    return ProjectionRange{range, fwd<P>(projector)};
  }
};

struct FilterModifier {
  template <typename P> auto operator()(P&& filter) const noexcept {
    return Filter<P&&>{fwd<P>(filter)};
  }

  template <typename R, typename P> auto operator()(R const& range, P&& filter) const noexcept {
    return FilterRange{range, fwd<P>(filter)};
  }
};

struct FlattenModifier {
  auto operator()() const noexcept {
    return Flattener{};
  }

  template <typename R> auto operator()(R const& range) const noexcept {
    return FlattenerRange{range};
  }
};

struct ForEachModifier {
  template <typename F> auto operator()(F&& func) const noexcept {
    return ForEach<F&&>{fwd<F>(func)};
  }

  template <typename R, typename F> auto operator()(R const& range, F&& func) const noexcept {
    for (auto const& e : range) {
      fn::invoke(fwd<F>(func), e);
    }
  }
};

struct FindAnyModifier {
  constexpr auto operator()() const noexcept {
    return FindAny{};
  }

  template <typename R> auto operator()(R const& range) const noexcept
      -> Optional<RemoveCVRef<decltype(*range.begin())>> {
    for (auto const& e : range) {
      return e;
    }
    return nullopt;
  }
};

template <typename R, concepts::DerivedFrom<RangeModifierTag> Mod> auto operator|(R const& range, Mod&& modifier) {
  return modifier(range);
}

inline constexpr FilterModifier filter;
inline constexpr FlattenModifier flatten;
inline constexpr ForEachModifier forEach;
inline constexpr FindAnyModifier findAny;
inline constexpr IndexedProjectModifier indexedProject;
inline constexpr ProjectModifier project;

template <typename P> template <typename R> auto IndexedProjector<P>::operator()(R const& range) const noexcept {
  return indexedProject(range, fwd<P>(_proj));
}

template <typename P> template <typename R> auto Projector<P>::operator()(R const& range) const noexcept {
  return project(range, fwd<P>(_proj));
}

template <typename P> template <typename R> auto Filter<P>::operator()(R const& range) const noexcept {
  return filter(range, fwd<P>(_pred));
}

template <typename R> auto Flattener::operator()(R const& range) const noexcept {
  return flatten(range);
}

template <typename F> template <typename R> auto ForEach<F>::operator()(R const& range) const noexcept {
  return forEach(range, fwd<F>(_func));
}

template <typename R> auto FindAny::operator()(R const& range) const noexcept {
  return findAny(range);
}
} // namespace c_eng::generic::detail

namespace c_eng::generic {
using detail::filter;
using detail::findAny;
using detail::flatten;
using detail::indexedProject;
using detail::project;
using detail::forEach;
using detail::FilterRange;
using detail::ProjectionRange;
} // namespace c_eng::generic
