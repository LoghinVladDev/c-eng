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
//#include <vkObj/window/surface/VSurface.h>
#include <vkObj/instance/device/VSwapChain.h>

namespace engine {

    class VQueue;
    class VSwapChain;
    class VImageViewCollection;

    class EngineVLogicalDeviceFactoryInvalidSwapChain : public std::exception {
    public:
        [[nodiscard]] const char * what() const noexcept override {
            return "Given Swap Chain is not configured with a proper surface";
        }
    };

    class EngineVLogicalDeviceQueuePhysicalDeviceMismatch : public std::exception {
    public:
        [[nodiscard]] const char * what() const noexcept override {
            return "Queue families attached are from a separate physical device";
        }
    };

    class EngineVLogicalDeviceSwapChainIncompatible : public std::exception {
    public:
        [[nodiscard]] const char * what() const noexcept override {
            return "Swap Chain Failed to Configure. Either Device is Incompatible or Instantiation Failed";
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
            this->_message = std::string("Physical Device given to Logical Device Factory does not support given Extension : { Name : ")
                    .append(problematicExtension.getName())
                    .append(", spec version : ")
                    .append(std::to_string(problematicExtension.getSpecVersion()))
                    .append("} ");
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
        bool                                _swapChainAdequate          {false};

        const VValidationLayerCollection *  _validationLayerCollection  {nullptr};
        VExtensionCollection                _enabledExtensions;
        
        const VSurface                   *  _surfacePtr                 {nullptr};
        const VPhysicalDevice            *  _physicalDevice             {nullptr};
        VSwapChain                       *  _swapChain                  {nullptr};
        VImageViewCollection             *  _imageViewCollection        {nullptr};

        //// private functions
        VulkanResult setup( const VPhysicalDevice &) noexcept (false);
        void setupQueues () noexcept;
    public:

        class [[maybe_unused]] VLogicalDeviceFactory {
        private:
            //// private variables
            static bool                         _exceptionsToggle;
            const VValidationLayerCollection *  _validationLayerCollection  {nullptr};
            std::vector < VQueue >              _queues;
            VExtensionCollection                _extensions;
            const VSurface                   *  _surface                    {nullptr};
//            const VSwapChain                    _swapChain;

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

            VLogicalDeviceFactory& addQueue                 ( const VQueueFamily&, float = _internal_explicitWrapper_DEFAULT_QUEUE_PRIORITY) noexcept (false);
            VLogicalDeviceFactory& addQueues                ( const VQueueFamily&, uint32, const float* ) noexcept (false);
            VLogicalDeviceFactory& addExtension             ( const VExtension& ) noexcept;
            VLogicalDeviceFactory& addExtensions            ( const VExtensionCollection& ) noexcept;
//            VLogicalDeviceFactory& addSwapChainToSurface    ( const VSurface* ) noexcept;
            VLogicalDeviceFactory& createSwapChainToSurface ( const VSurface* ) noexcept (false);

            VLogicalDevice build ( const VPhysicalDevice& ) noexcept (false);

            ~VLogicalDeviceFactory() noexcept = default;

        };

        //// public variables

        //// public functions

        VLogicalDevice ( ) noexcept = default;
        VLogicalDevice ( const VLogicalDevice& ) noexcept;

        VLogicalDevice & operator = ( const VLogicalDevice& ) noexcept;

        [[nodiscard]] const VQueue * getFirstPresentQueuePtr () const noexcept;
        [[nodiscard]] const VQueue * getFirstGraphicsQueuePtr () const noexcept;
        [[nodiscard]] const VQueue * getFirstTransferQueuePtr () const noexcept;

        [[nodiscard]] const VPhysicalDevice * getBasePhysicalDevice () const noexcept {
            return this->_physicalDevice;
        }

        /**
         *
         * @return nullptr if device does not have a swap chain configured
         */
        [[nodiscard]] const VSurface * getSwapChainSurface() const noexcept {
            return this->_surfacePtr;
        }

        /**
         *
         * @return nullptr if device does not have a swap chain configured
         */
        [[nodiscard]] const VSwapChain * getSwapChain() const noexcept {
            return this->_swapChain;
        }

        /**
         *
         * @return nullptr if device does not have a swap chain configured
         */
        [[nodiscard]] const VImageViewCollection * getImageViewCollection () const noexcept {
            return this->_imageViewCollection;
        }

        [[nodiscard]] const std::vector < VQueue > & getQueues() const noexcept {
            return this->_queues;
        }

        [[nodiscard]] std::set < const VQueueFamily * > getQueueFamilies () const noexcept;

        [[nodiscard]] const VulkanDevice & data() const noexcept {
            return this->_vulkanDevice;
        }

        [[nodiscard]] bool isSwapChainAdequate () const noexcept {
            return this->_swapChainAdequate;
        }

        void cleanupSwapChain () noexcept;
        VulkanResult recreateSwapChain () noexcept;

        void cleanup () noexcept;

        ~VLogicalDevice() noexcept;
    };

}


#endif //ENG1_VLOGICALDEVICE_H
