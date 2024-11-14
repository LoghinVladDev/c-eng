//
// Created by loghin on 11/10/24.
//

#pragma once

#include <cds/collection/Vector>

namespace c_eng::generic::detail {
using cds::Vector;
using cds::ignore;

template <typename Event> class EventSubscriber {
public:
  virtual ~EventSubscriber() noexcept = default;
  virtual auto notify(Event& event) noexcept -> void = 0;
};

template <typename... Events> class MultiEventSubscriber : public EventSubscriber<Events>... {
public:
  ~MultiEventSubscriber() noexcept override = default;
};

template <typename Event> class EventNotifier {
public:
  virtual ~EventNotifier() noexcept = default;
  auto subscribe(EventSubscriber<Event>* subscriber) noexcept -> void {
    _subscribers.emplaceBack(subscriber);
  }

protected:
  auto notify(Event& event) const noexcept -> void {
    _subscribers.forEach([&event](auto* subscriber) {
      return subscriber->notify(event);
    });
  }

private:
  Vector<EventSubscriber<Event>*> _subscribers;
};

template <typename CompatibleEvent>
auto subscribeToOne(auto* notifier, EventSubscriber<CompatibleEvent>* subscriber) noexcept -> void {
  notifier->subscribe(subscriber);
}

template <typename IncompatibleSubscriber>
auto subscribeToOne(auto* notifier, IncompatibleSubscriber* subscriber) noexcept -> void {
  ignore = notifier;
  ignore = subscriber;
}

template <typename E0, typename E1, typename... En>
auto subscribeToAll(auto* notifier, auto* subscriber) noexcept -> void {
  subscribeToOne<E0>(notifier, subscriber);
  subscribeToAll<E1, En...>(notifier, subscriber);
}

template <typename E0>
auto subscribeToAll(auto* notifier, auto* subscriber) noexcept -> void {
  subscribeToOne<E0>(notifier, subscriber);
}

template <typename... Events> class MultiEventNotifier : public EventNotifier<Events>... {
protected:
  template <typename CompatibleEvent> static auto notifyOne(auto* notifier, CompatibleEvent& event) noexcept -> void {
    notifier->template EventNotifier<CompatibleEvent>::notify(event);
  }

  template <typename> static auto notifyOne(auto* notifier, ...) noexcept -> void {
    ignore = notifier;
  }

  template <typename E0, typename E1, typename... En> static auto notifyAll(auto* notifier, auto& event) noexcept -> void {
    notifyOne<E0>(notifier, event);
    notifyAll<E1, En...>(notifier, event);
  }

  template <typename E0> static auto notifyAll(auto* notifier, auto& event) noexcept -> void {
    notifyOne<E0>(notifier, event);
  }

  template <typename Event> auto notify(Event& event) noexcept -> void {
    notifyAll<Events...>(this, event);
  }

public:
  using EventNotifier<Events>::subscribe...;

  ~MultiEventNotifier() noexcept override = default;
  template <typename... SubscriberEvents> auto subscribe(MultiEventSubscriber<SubscriberEvents...>* subscriber) noexcept
     -> void {
    subscribeToAll<SubscriberEvents...>(this, subscriber);
  }
};
} // namespace c_eng::generic::detail

namespace c_eng::generic {

} // namespace c_eng::generic
