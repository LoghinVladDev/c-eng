//
// Created by Vlad-Andrei Loghin on 15.06.23.
//

#ifndef C_ENG_RESOURCETRACKER_HPP
#define C_ENG_RESOURCETRACKER_HPP

namespace engine {
template <typename Resource>
class ResourceTracker {
public:
  [[nodiscard]] static auto tracker() noexcept(false) -> ResourceTracker& {
    static cds::UniquePointer <ResourceTracker> instanceTracker;
    if (!instanceTracker) {
      instanceTracker = new ResourceTracker();
    }

    return *instanceTracker;
  }

  auto track(Resource* pInstance) noexcept(false) {
    return _instances.pushBack(pInstance);
  }

  auto untrack(Resource const* pInstance) noexcept(false) {
    return _instances.removeAllThat([pInstance](auto instance){return instance == pInstance;});
  }

  [[nodiscard]] auto instances() noexcept -> auto& {
    return _instances;
  }

private:
  ResourceTracker() noexcept = default;
  cds::Array <Resource*> _instances;
};
} // namespace engine

#endif // C_ENG_RESOURCETRACKER_HPP
