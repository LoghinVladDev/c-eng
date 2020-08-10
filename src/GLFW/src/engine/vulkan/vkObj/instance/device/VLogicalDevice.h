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

    class EngineVLDFactoryPriorityIndexOutOfBounds : public std::exception {
    private:
        std::string _message;
    public:
        EngineVLDFactoryPriorityIndexOutOfBounds() noexcept {
            this->_message = "Given Index is out of Queue Priorities Array Bounds";
        }

        explicit EngineVLDFactoryPriorityIndexOutOfBounds( uint32 givenIndex, uint32 bounds ) noexcept {
            this->_message = std::string("Index ")
                    .append(std::to_string(givenIndex))
                    .append(" is out of ")
                    .append(std::to_string(bounds))
                    .append(", Queue Priorities Array Range");
        }

        [[nodiscard]] const char * what() const noexcept override {
            return this->_message.c_str();
        }
    };

    class VLogicalDevice {
    private:
        //// private variables

        VulkanDevice                        _vulkanDevice               {};
        uint32                              _queueCount                 {0U};
        uint32                              _queueFamilyIndex           {0U};
        float*                              _queuePriorities            {nullptr};
        const VValidationLayerCollection *  _validationLayerCollection  {nullptr};

        //// private functions
        VLogicalDevice() noexcept = default;
        VulkanResult setup( const VPhysicalDevice & ) noexcept;
    public:
        class [[maybe_unused]] VLogicalDeviceFactory {
        private:
            //// private variables
            static bool                         _exceptionsToggle;
            uint32                              _queueCount       {VLogicalDeviceFactory::DEFAULT_QUEUE_COUNT_FROM_POOL};
            float*                              _queuePriorities  {nullptr};
            const VValidationLayerCollection *  _validationLayerCollection { nullptr };

            constexpr static float  DEFAULT_MIN_QUEUE_PRIORITY = 0.0f;
            constexpr static float  DEFAULT_MAX_QUEUE_PRIORITY = 1.0f;

            //// private functions
            void updatePrioritiesArray ( uint32 newSize ) noexcept {
                auto * newArray = new float[newSize];

                bool prioritiesInitialized = this->_queuePriorities != nullptr;

                for ( uint32 it = 0; it < newSize; it++ ) {
                    if( it < this->_queueCount && prioritiesInitialized )
                        newArray[it] = this->_queuePriorities[it];
                    else
                        newArray[it] = VLogicalDevice::VLogicalDeviceFactory::DEFAULT_QUEUE_PRIORITY;
                }

                delete [] this->_queuePriorities;
                this->_queuePriorities = newArray;
            }

        public:
            //// public variables
            constexpr static uint32 DEFAULT_QUEUE_COUNT_FROM_POOL = 1U;
            constexpr static float  DEFAULT_QUEUE_PRIORITY        = 1.0f;

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

            VLogicalDeviceFactory& withQueueCount ( uint32 targetQueueCount ) noexcept {
                this->updatePrioritiesArray( targetQueueCount );
                this->_queueCount = targetQueueCount;
                return *this;
            }

            VLogicalDeviceFactory& setPriorityAllQueues ( float priority ) noexcept {
                if( priority < VLogicalDevice::VLogicalDeviceFactory::DEFAULT_MIN_QUEUE_PRIORITY ) priority = VLogicalDevice::VLogicalDeviceFactory::DEFAULT_MIN_QUEUE_PRIORITY;
                if( priority > VLogicalDevice::VLogicalDeviceFactory::DEFAULT_MAX_QUEUE_PRIORITY ) priority = VLogicalDevice::VLogicalDeviceFactory::DEFAULT_MAX_QUEUE_PRIORITY;

                for( uint32 it = 0; it < this->_queueCount; it++ )
                    this->_queuePriorities[it] = priority;

                return *this;
            }

            VLogicalDeviceFactory& setPriorityForQueue ( float priority, uint32 queueIndex ) noexcept (false) {
                if( queueIndex > this->_queueCount ) {
                    if( VLogicalDevice::VLogicalDeviceFactory::_exceptionsToggle )
                        throw engine::EngineVLDFactoryPriorityIndexOutOfBounds(queueIndex, this->_queueCount);
                    else
                        queueIndex = this->_queueCount - 1;
                }

                this->_queuePriorities[queueIndex] = priority;
                return *this;
            }

            VLogicalDevice build ( const VQueueFamily & queueFamily, const VPhysicalDevice & physicalDevice ) noexcept (false) {
                if ( this->_queuePriorities == nullptr )
                    this->updatePrioritiesArray( this->_queueCount );

                VLogicalDevice builtObject;

                builtObject._queueCount = queueFamily.reserveQueues( this->_queueCount );
                builtObject._queuePriorities = new float[builtObject._queueCount];
                builtObject._queueFamilyIndex = queueFamily.getQueueFamilyIndex();
                builtObject._validationLayerCollection = this->_validationLayerCollection;
                for(uint32 it = 0; it < builtObject._queueCount; it++) {
                    builtObject._queuePriorities[it] = this->_queuePriorities[it];
                }

                if( builtObject.setup( physicalDevice ) != VK_SUCCESS )
                    throw std::runtime_error("failed to create logical device!");

                return builtObject;
            }

            ~VLogicalDeviceFactory() noexcept {
                delete [] this->_queuePriorities;
            }
        };

        //// public variables

        //// public functions

        [[nodiscard]] uint32 getQueueFamilyIndex () const noexcept {
            return this->_queueFamilyIndex;
        }

        [[nodiscard]] const VulkanDevice & data() const noexcept {
            return this->_vulkanDevice;
        }

        void cleanup () noexcept {
            vkDestroyDevice( this->_vulkanDevice, nullptr );
        }

        ~VLogicalDevice() noexcept {
//            vkDestroyDevice ( this->_vulkanDevice, nullptr ); implement later for destruction
            delete [] this->_queuePriorities;
        }
    };

}


#endif //ENG1_VLOGICALDEVICE_H
