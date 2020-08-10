//
// Created by vladl on 08/08/2020.
//

#ifndef ENG1_VQUEUEFAMILY_H
#define ENG1_VQUEUEFAMILY_H
#include <engineVulkanPreproc.h>
#include <vkDefs/vkDefinitions.h>
#include <vkDefs/types/vulkanExplicitTypes.h>
#include <vkObj/instance/device/VPhysicalDevice.h>
#include <map>

namespace engine {

    class VQueueFamilyCollection;

    class VQueueFamily {
    private:
        //// private variables
        uint32                                      _familyIndex            {0};
//        VkQueueFamilyProperties _queueFamilyProperties  { };
//        std::vector < VulkanQueueFamilyProperties > _vulkanQueueFamilyProperties;
        VulkanQueueFamilyProperties                 _queueFamilyProperties  { };
//        const VPhysicalDevice                     * _physicalDevice         { nullptr };
        VQueueFamilyCollection                    * _parentCollection       { nullptr };

        //// private functions
        [[nodiscard]] constexpr static bool queueFamilyPropertiesTransferBit( const VulkanQueueFamilyProperties& properties ) noexcept {
            return (bool) ( properties.queueFlags & VQueueFamily::TRANSFER_FLAG);
        }

        [[nodiscard]] constexpr static bool queueFamilyPropertiesGraphicsBit( const VulkanQueueFamilyProperties& properties ) noexcept {
            return (bool) ( properties.queueFlags & VQueueFamily::GRAPHICS_FLAG);
        }

        [[nodiscard]] constexpr static bool queueFamilyPropertiesComputeBit( const VulkanQueueFamilyProperties& properties ) noexcept {
            return (bool) ( properties.queueFlags & VQueueFamily::COMPUTE_FLAG);
        }

        [[nodiscard]] constexpr static bool queueFamilyPropertiesProtectedBit( const VulkanQueueFamilyProperties& properties ) noexcept {
            return (bool) ( properties.queueFlags & VQueueFamily::PROTECTED_FLAG);
        }

        [[nodiscard]] constexpr static bool queueFamilyPropertiesSparseBindingBit( const VulkanQueueFamilyProperties& properties ) noexcept {
            return (bool) ( properties.queueFlags & VQueueFamily::SPARSE_BINDING_FLAG);
        }

        [[nodiscard]] constexpr static bool queueFamilyPropertiesCompatibleFlagBits( const VulkanQueueFamilyProperties& properties, VulkanQueueFlags flags ) noexcept {
            return (bool) ( ( properties.queueFlags & flags ) == flags );
        }
        //        void queryAvailableQueueFamilies ( const VPhysicalDevice& ) noexcept;
    public:
        //// public variables
        constexpr static VulkanQueueFlags GRAPHICS_FLAG       = VK_QUEUE_GRAPHICS_BIT;
        constexpr static VulkanQueueFlags COMPUTE_FLAG        = VK_QUEUE_COMPUTE_BIT;
        constexpr static VulkanQueueFlags TRANSFER_FLAG       = VK_QUEUE_TRANSFER_BIT;
        constexpr static VulkanQueueFlags PROTECTED_FLAG      = VK_QUEUE_PROTECTED_BIT;
        constexpr static VulkanQueueFlags SPARSE_BINDING_FLAG = VK_QUEUE_SPARSE_BINDING_BIT;

        //// public functions
        VQueueFamily() noexcept = default;
        explicit VQueueFamily (VQueueFamilyCollection * parent, const VulkanQueueFamilyProperties & properties, uint32 family) noexcept {
//            this->_physicalDevice = ( & physicalDevice );
            this->_parentCollection = parent;
            this->_queueFamilyProperties = properties;
            this->_familyIndex = family;
        }

        [[nodiscard]] uint32 reserveQueues(uint32 ) const noexcept;
        void                 freeQueues(   uint32 ) const noexcept;

        [[nodiscard]] uint32 getQueueFamilyIndex ( ) const noexcept {
            return this->_familyIndex;
        }

        [[nodiscard]] uint32 getQueueCount ( ) const noexcept {
            return this->_queueFamilyProperties.queueCount;
        }

        [[nodiscard]] const VulkanQueueFamilyProperties & getQueueFamilyProperties ( ) const noexcept {
            return this->_queueFamilyProperties;
        }

        [[maybe_unused]] [[nodiscard]] constexpr bool queueFamilyTransferCapable() const noexcept {
            return VQueueFamily::queueFamilyPropertiesTransferBit(this->_queueFamilyProperties);
        }

        [[maybe_unused]] [[nodiscard]] constexpr bool queueFamilyGraphicsCapable() const noexcept {
            return VQueueFamily::queueFamilyPropertiesGraphicsBit(this->_queueFamilyProperties);
        }

        [[maybe_unused]] [[nodiscard]] constexpr bool queueFamilyComputeCapable() const noexcept {
            return VQueueFamily::queueFamilyPropertiesComputeBit(this->_queueFamilyProperties);
        }

        [[maybe_unused]] [[nodiscard]] constexpr bool queueFamilyProtectedCapable() const noexcept {
            return VQueueFamily::queueFamilyPropertiesProtectedBit(this->_queueFamilyProperties);
        }

        [[maybe_unused]] [[nodiscard]] constexpr bool queueFamilySparseBindingCapable() const noexcept {
            return VQueueFamily::queueFamilyPropertiesSparseBindingBit(this->_queueFamilyProperties);
        }

        [[nodiscard]] constexpr bool queueFamilyIsCapableOf ( VulkanQueueFlags flags ) const noexcept {
            return VQueueFamily::queueFamilyPropertiesCompatibleFlagBits( this->_queueFamilyProperties, flags );
        }

#ifndef NDEBUG
        void debugPrintQueueFamily ( std::ostream&, const char * = "" ) const noexcept;
        void debugPrintQueueFamilyReservation( std::ostream&, const char* = "" ) const noexcept;
        static void debugPrintQueueFamilyPropertiesStructureQueueFlags ( const VulkanQueueFamilyProperties & ,std::ostream&, const char * = "" ) noexcept;
        static void debugPrintQueueFamilyPropertiesStructure ( const VulkanQueueFamilyProperties &, std::ostream&, const char * = "" ) noexcept;
#endif
    };

    class VQueueFamilyCollection {
    private:
        //// private variables
        const VPhysicalDevice         * _physicalDevice { nullptr };
        std::vector < VQueueFamily >    _queueFamilies;
        std::map < uint32, uint32 >     _reservedQueuesForFamilies;
//        std::vector < VQueueFamily * >  _graphicsCapableQueueFamilies; ptr implementation is the most logical

        //// private functions
        void unReserveAllQueueFamilies ( ) noexcept (false);
        void queryAvailableQueueFamilies ( ) noexcept (false);
    public:
        //// public variables

        //// public functions
        VQueueFamilyCollection () noexcept = delete;
        explicit VQueueFamilyCollection ( const VPhysicalDevice & physicalDevice ) noexcept (false) {
            this->_physicalDevice = (& physicalDevice);
            this->queryAvailableQueueFamilies();
            this->unReserveAllQueueFamilies();
        }

//        [[nodiscard]] uint32 reserveQueues( uint32, uint32) noexcept;
        [[nodiscard]] uint32 reserveQueues( const VQueueFamily&, uint32 ) noexcept;
        void                 freeQueues(    const VQueueFamily&, uint32 ) noexcept;

        [[nodiscard]] const std::map < uint32, uint32 > & getReservedQueueFamiliesMap () const noexcept {
            return this->_reservedQueuesForFamilies;
        }

        [[nodiscard]] const VPhysicalDevice & getPhysicalDevice ( ) const noexcept {
            return * this->_physicalDevice;
        }

        [[nodiscard]] const std::vector < VQueueFamily > & getQueueFamilies () const noexcept {
            return this->_queueFamilies;
        }

        [[nodiscard]] std::vector < VQueueFamily > getGraphicsCapableQueueFamilies () const noexcept {
            return this->getFlagsCapableQueueFamilies( VQueueFamily::GRAPHICS_FLAG );
        }

        [[nodiscard]] std::vector < VQueueFamily > getComputeCapableQueueFamilies () const noexcept {
            return this->getFlagsCapableQueueFamilies( VQueueFamily::COMPUTE_FLAG );
        }

        [[nodiscard]] std::vector < VQueueFamily > getTransferCapableQueueFamilies () const noexcept {
            return this->getFlagsCapableQueueFamilies( VQueueFamily::TRANSFER_FLAG );
        }

        [[nodiscard]] std::vector < VQueueFamily > getProtectedCapableQueueFamilies () const noexcept {
            return this->getFlagsCapableQueueFamilies( VQueueFamily::PROTECTED_FLAG );
        }

        [[nodiscard]] std::vector < VQueueFamily > getSparseBindingCapableQueueFamilies () const noexcept {
            return this->getFlagsCapableQueueFamilies( VQueueFamily::SPARSE_BINDING_FLAG );
        }

        [[nodiscard]] std::vector < VQueueFamily > getFlagsCapableQueueFamilies ( VulkanQueueFlags ) const noexcept;

#ifndef NDEBUG
        void debugPrintQueueFamilies ( std::ostream&, const char* = "" ) const noexcept;
        void debugPrintQueueFamiliesReservations ( std::ostream&, const char * = "" ) const noexcept;
#endif
    };

}


#endif //ENG1_VQUEUEFAMILY_H
