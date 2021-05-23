//
// Created by Vlad on 21/08/2020.
//

#ifndef ENG1_VSEMAPHORE_HPP
#define ENG1_VSEMAPHORE_HPP

#include <VRenderObject.hpp>
#include <VLogicalDevice.hpp>
#include <vector>

namespace engine {

    class VLogicalDevice;

    class VSemaphore : public VRenderObject {
    private:
        //// private variables
        VulkanSemaphore           _handle         {nullptr};
        VLogicalDevice    const * _pLogicalDevice {nullptr};

        //// private functions

    public:
        //// public variables

        //// public functions
        VSemaphore () noexcept = default;
        ~VSemaphore() noexcept override = default;

        auto setup ( VLogicalDevice const & ) noexcept -> VulkanResult;
        auto clear () noexcept -> void override;

        [[nodiscard]] constexpr auto data () const noexcept -> VulkanSemaphore const & {
            return this->_handle;
        }

        [[nodiscard]] auto toString () const noexcept -> String override;

        [[nodiscard]] auto operator == (Object const & o) const noexcept -> bool override {
            if ( this == & o ) return true;
            auto p = dynamic_cast < decltype ( this ) > ( & o );
            if ( p == nullptr ) return false;
            return this->_handle == p->_handle;
        }

        [[nodiscard]] auto copy () const noexcept -> VSemaphore * override {
            return new VSemaphore(* this);
        }

        [[nodiscard]] auto hash () const noexcept -> Index override {
            return dataTypes::hash(reinterpret_cast<AddressValueType>(this->_handle));
        }
    };

    class VSemaphoreCollection : public VRenderObject {
    private:
        //// private variables
        std::vector < VSemaphore > _semaphores;
        VLogicalDevice     const * _pLogicalDevice  {nullptr};

        //// private functions

    public:
        //// public variables

        //// public functions
        VSemaphoreCollection () noexcept = default;
        ~VSemaphoreCollection() noexcept override = default;

        [[nodiscard]] constexpr auto getSemaphores () const noexcept -> std::vector < VSemaphore > const & {
            return this->_semaphores;
        }

        [[nodiscard]] constexpr auto getLogicalDevicePtr () const noexcept -> VLogicalDevice const * {
            return this->_pLogicalDevice;
        }

        [[nodiscard]] inline auto size () const noexcept -> uint32 {
            return static_cast<uint32>(this->_semaphores.size());
        }

        [[nodiscard]] inline auto operator [] (uint32 index) const noexcept -> VSemaphore const & {
            return this->_semaphores[ index ];
        }

        [[nodiscard]] inline auto operator [] (uint32 index) noexcept -> VSemaphore & {
            return this->_semaphores[ index ];
        }

        auto setup ( VLogicalDevice const &, uint32 ) noexcept -> VulkanResult;
        auto resize ( VLogicalDevice const &, uint32 ) noexcept -> VulkanResult;

        auto cleanup () noexcept -> void override;

        [[nodiscard]] auto toString () const noexcept -> String override;
        [[nodiscard]] auto operator == (Object const & o) const noexcept -> bool override {
            if ( this == & o ) return true;
            auto p = reinterpret_cast < decltype (this) > (& o);
            if ( p == nullptr ) return false;

            return this->_semaphores == p->_semaphores;
        }

        [[nodiscard]] auto copy () const noexcept -> VSemaphoreCollection * override {
            return new VSemaphoreCollection(* this);
        }

        [[nodiscard]] auto hash () const noexcept -> Index override {
            Index hashSum = 0;
            std::for_each(this->_semaphores.begin(), this->_semaphores.end(),[& hashSum](auto const & o){hashSum += o.hash();});
        }
    };

}




#endif //ENG1_VSEMAPHORE_HPP
