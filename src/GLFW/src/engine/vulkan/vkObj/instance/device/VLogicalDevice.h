//
// Created by Vlad on 10/08/2020.
//

#ifndef ENG1_VLOGICALDEVICE_H
#define ENG1_VLOGICALDEVICE_H

#include <vkObj/instance/device/queue/VQueueFamily.h>
#include <cstring>
#include <vkObj/instance/validationLayer/VValidationLayer.h>
#include <vkObj/instance/device/queue/VQueue.h>

namespace engine {

    class VQueue;

    class EngineVLogicalDeviceQueuePhysicalDeviceMismatch : public std::exception {
        [[nodiscard]] const char * what() const noexcept override {
            return "Queue families attached are from a separate physical device";
        }
    };

//    class VQueue;

    class VLogicalDevice {
    private:
        //// private variables
        static float _internal_explicitWrapper_DEFAULT_QUEUE_PRIORITY;

        VulkanDevice                        _vulkanDevice               {};
        std::vector < VQueue >              _queues;

        const VValidationLayerCollection *  _validationLayerCollection  {nullptr};

        //// private functions
        VulkanResult setup( const VPhysicalDevice & ) noexcept (false);
        void setupQueues () noexcept;
    public:
        class [[maybe_unused]] VLogicalDeviceFactory {
        private:
            //// private variables
            static bool                         _exceptionsToggle;
            const VValidationLayerCollection *  _validationLayerCollection  {nullptr};
            std::vector < VQueue >              _queues;

        public:
            //// public variables

            //// public functions
            static void setExceptionEnableStatus ( bool toggle ) noexcept {
                VLogicalDevice::VLogicalDeviceFactory::_exceptionsToggle = toggle;
            }

            static void enableExceptions ( ) noexcept {
                VLogicalDevice::VLogicalDeviceFactory::_exceptionsToggle = true;
            }

            static void disableExceptions ( ) noexcept {
                VLogicalDevice::VLogicalDeviceFactory::_exceptionsToggle = false;
            }

            VLogicalDeviceFactory& withValidationLayers ( const VValidationLayerCollection& collection ) noexcept {
                this->_validationLayerCollection = ( & collection );
                return *this;
            }

            VLogicalDeviceFactory& addQueue( const VQueueFamily&, float = _internal_explicitWrapper_DEFAULT_QUEUE_PRIORITY) noexcept (false);
            VLogicalDeviceFactory& addQueues( const VQueueFamily&, uint32, const float* ) noexcept (false);

            VLogicalDevice build ( const VPhysicalDevice& ) noexcept (false);

            ~VLogicalDeviceFactory() noexcept = default;

        };

        //// public variables

        //// public functions

        [[nodiscard]] const std::vector < VQueue > & getQueues() const noexcept {
            return this->_queues;
        }

        [[nodiscard]] const VulkanDevice & data() const noexcept {
            return this->_vulkanDevice;
        }

        void cleanup () noexcept;

        ~VLogicalDevice() noexcept = default;
    };

}


#endif //ENG1_VLOGICALDEVICE_H
