//
// Created by vladl on 08/08/2020.
//

#ifndef ENG1_VQUEUEFAMILY_H
#define ENG1_VQUEUEFAMILY_H
#include <engineVulkanPreproc.h>
#include <vkDefs/vkDefinitions.h>
#include <vkDefs/types/vulkanExplicitTypes.h>
#include <vkObj/instance/device/VPhysicalDevice.h>

namespace engine {

    class VQueueFamily {
    private:
        //// private variables
        uint32                                      _graphicsFamily         {0};
//        VkQueueFamilyProperties _queueFamilyProperties  { };
//        std::vector < VulkanQueueFamilyProperties > _vulkanQueueFamilyProperties;
        VulkanQueueFamilyProperties                 _queueFamilyProperties  { };
        const VPhysicalDevice                     * _physicalDevice         { nullptr };

        //// private functions
        [[nodiscard]] constexpr static bool queueFamilyPropertiesTransferBit( const VulkanQueueFamilyProperties& properties ) noexcept {
            return (bool) ( properties.queueFlags & VK_QUEUE_TRANSFER_BIT);
        }

        [[nodiscard]] constexpr static bool queueFamilyPropertiesGraphicsBit( const VulkanQueueFamilyProperties& properties ) noexcept {
            return (bool) ( properties.queueFlags & VK_QUEUE_GRAPHICS_BIT);
        }

        [[nodiscard]] constexpr static bool queueFamilyPropertiesComputeBit( const VulkanQueueFamilyProperties& properties ) noexcept {
            return (bool) ( properties.queueFlags & VK_QUEUE_COMPUTE_BIT);
        }

        [[nodiscard]] constexpr static bool queueFamilyPropertiesProtectedBit( const VulkanQueueFamilyProperties& properties ) noexcept {
            return (bool) ( properties.queueFlags & VK_QUEUE_PROTECTED_BIT);
        }

        [[nodiscard]] constexpr static bool queueFamilyPropertiesSparseBindingBit( const VulkanQueueFamilyProperties& properties ) noexcept {
            return (bool) ( properties.queueFlags & VK_QUEUE_SPARSE_BINDING_BIT);
        }
//        void queryAvailableQueueFamilies ( const VPhysicalDevice& ) noexcept;
    public:
        //// public variables

        //// public functions
        VQueueFamily() noexcept = default;
        explicit VQueueFamily (const VPhysicalDevice & physicalDevice, const VulkanQueueFamilyProperties & properties) noexcept {
            this->_physicalDevice = ( & physicalDevice );
            this->_queueFamilyProperties = properties;
        }

        [[nodiscard]] const VPhysicalDevice & getPhysicalDevice ( ) const noexcept {
            return * this->_physicalDevice;
        }

        [[nodiscard]] const VulkanQueueFamilyProperties & getQueueFamilyProperties ( ) const noexcept {
            return this->_queueFamilyProperties;
        }

        [[nodiscard]] constexpr bool queueFamilyTransferCapable() const noexcept {
            return VQueueFamily::queueFamilyPropertiesTransferBit(this->_queueFamilyProperties);
        }

        [[nodiscard]] constexpr bool queueFamilyGraphicsCapable() const noexcept {
            return VQueueFamily::queueFamilyPropertiesGraphicsBit(this->_queueFamilyProperties);
        }

        [[nodiscard]] constexpr bool queueFamilyComputeCapable() const noexcept {
            return VQueueFamily::queueFamilyPropertiesComputeBit(this->_queueFamilyProperties);
        }

        [[nodiscard]] constexpr bool queueFamilyProtectedCapable() const noexcept {
            return VQueueFamily::queueFamilyPropertiesProtectedBit(this->_queueFamilyProperties);
        }

        [[nodiscard]] constexpr bool queueFamilySparseBindingCapable() const noexcept {
            return VQueueFamily::queueFamilyPropertiesSparseBindingBit(this->_queueFamilyProperties);
        }

#ifndef NDEBUG
        void debugPrintQueueFamily ( std::ostream&, const char * = "" ) const noexcept;
        static void debugPrintQueueFamilyPropertiesStructureQueueFlags ( const VulkanQueueFamilyProperties & ,std::ostream&, const char * = "" ) noexcept;
        static void debugPrintQueueFamilyPropertiesStructure ( const VulkanQueueFamilyProperties &, std::ostream&, const char * = "" ) noexcept;
#endif
    };

    class VQueueFamilyCollection {
    private:
        //// private variables
        VPhysicalDevice                 _physicalDevice;
        std::vector < VQueueFamily >    _queueFamilies;

        //// private functions
        void queryAvailableQueueFamilies ( ) noexcept;
    public:
        //// public variables

        //// public functions
        VQueueFamilyCollection () noexcept = delete;
        explicit VQueueFamilyCollection ( const VPhysicalDevice & physicalDevice ) noexcept {
            this->_physicalDevice = physicalDevice;
            this->queryAvailableQueueFamilies();
        }

        [[nodiscard]] const std::vector < VQueueFamily > & getQueueFamilies () const noexcept {
            return this->_queueFamilies;
        }

#ifndef NDEBUG
        void debugPrintQueueFamilies ( std::ostream&, const char* = "" ) const noexcept;
#endif
    };

}


#endif //ENG1_VQUEUEFAMILY_H
