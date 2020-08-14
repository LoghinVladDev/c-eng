//
// Created by Vlad on 10/08/2020.
//

#ifndef ENG1_VLOGICALDEVICE_H
#define ENG1_VLOGICALDEVICE_H

#include <vkObj/instance/device/queue/VQueueFamily.h>
#include <cstring>
#include <vkObj/instance/validationLayer/VValidationLayer.h>
#include <vkObj/instance/device/queue/VQueue.h>
#include <vkObj/instance/extension/VExtension.h>

namespace engine {

    class VQueue;

    class EngineVLogicalDeviceQueuePhysicalDeviceMismatch : public std::exception {
    public:
        [[nodiscard]] const char * what() const noexcept override {
            return "Queue families attached are from a separate physical device";
        }
    };

    class EngineVLogicalDeviceUnsupportedExtension : public std::exception {
    private:
        std::string _message;
    public:
        EngineVLogicalDeviceUnsupportedExtension () noexcept {
            this->_message = "Physical Device given to Logical Device Factory does not support given Extension";
        }

        explicit EngineVLogicalDeviceUnsupportedExtension ( const VExtension& problematicExtension ) noexcept {
            this->_message = "Physical Device given to Logical Device Factory does not support given Extension : { Name : " << problematicExtension.getName() << ", spec version : " << problematicExtension.getSpecVersion() << "} ";   
        }

        [[nodiscard]] const char * what() const noexcept override {
            return this->_message.c_str();
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
        const VExtensionCollection          _enabledExtensions;

        //// private functions
        VulkanResult setup( const VPhysicalDevice &, const VExtensionCollection& ) noexcept (false);
        void setupQueues () noexcept;
    public:
        class [[maybe_unused]] VLogicalDeviceFactory {
        private:
            //// private variables
            static bool                         _exceptionsToggle;
            const VValidationLayerCollection *  _validationLayerCollection  {nullptr};
            std::vector < VQueue >              _queues;
            VExtensionCollection                _extensions;

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

            VLogicalDeviceFactory& addQueue         ( const VQueueFamily&, float = _internal_explicitWrapper_DEFAULT_QUEUE_PRIORITY) noexcept (false);
            VLogicalDeviceFactory& addQueues        ( const VQueueFamily&, uint32, const float* ) noexcept (false);
            VLogicalDeviceFactory& addExtension     ( const VExtension& ) noexcept;
            VLogicalDeviceFactory& addExtensions    ( const VExtensionCollection& ) noexcept;

            VLogicalDevice build ( const VPhysicalDevice& ) noexcept (false);

            ~VLogicalDeviceFactory() noexcept = default;

        };

        //// public variables

        //// public functions

        VLogicalDevice () noexcept = default;

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
