//
// Created by vladl on 08/08/2020.
//

#ifndef ENG1_VQUEUEFAMILY_HPP
#define ENG1_VQUEUEFAMILY_HPP
#include <engineVulkanPreproc.hpp>
#include <vkDefinitions.h>
#include <vulkanExplicitTypes.h>
#include <VPhysicalDevice.hpp>
#include <map>
#include <set>
#include <string>
#include <VSurface.hpp>

#include <CDS/String>

namespace engine {

    /**
     * @class engine::EngineVQueueFamilyNoQueuesAvailable, inherits std::exception
     *
     * @brief Exception Class marking an exception thrown when a queue requested cannot be allocated due to no free queues being left
     */
    class EngineVQueueFamilyNoQueuesAvailable : public std::exception {
    private:
        /// message of the exception
        std::string _message;
    public:
        /**
         * @brief Constructor, without parameters
         *
         * @exceptsafe
         */
        EngineVQueueFamilyNoQueuesAvailable() noexcept {
            this->_message = "Could not reserve the requested queue count";
        }

        /**
         * @brief Constructor
         *
         * @param reqQueueCount : uint32 = number of requested queues
         * @param availableQueueCount : uint32 = number of free queues
         *
         * @exceptsafe
         */
        explicit EngineVQueueFamilyNoQueuesAvailable( uint32 reqQueueCount, uint32 availableQueueCount ) noexcept {
            this->_message = "Could not reserve the requested queue count. Requested : " + std::to_string(reqQueueCount) + ", Available : " + std::to_string(availableQueueCount);
        }

        /**
         * @brief getter for the exception message
         *
         * @exceptsafe
         *
         * @return StringLiteral = Exception message
         */
        [[nodiscard]] auto what() const noexcept -> StringLiteral override {
            return this->_message.c_str();
        }
    };

    /**
     * Predeclare class VQueueFamilyCollection to avoid circular/recursive includes
     */
    class VQueueFamilyCollection;

    /**
     * @class engine::VQueueFamily
     *
     * @brief Family of VQueues - Collection ( internal, GPU ) of Queues (buses), each with same behaviour.
     * A Queue can be "requested" from the Family, Resulting in allocation of said queue to the requester program
     */
    class VQueueFamily {
    private:
        //// private variables

        /// index of the family in all of the queue families
        uint32                                      _familyIndex            {0};

        /// properties of the queue family
        VulkanQueueFamilyProperties                 _queueFamilyProperties  { };

        /// pointer to the collection owning all the queue families
        VQueueFamilyCollection                    * _parentCollection       { nullptr };

        /// boolean variable mentioning whether queue family supports present operations or not
        VulkanBool32                                _presentSupport         { false };

        //// private functions

        /**
         * @brief Function testing whether queue family properties include Transfer Capabilities
         *
         * @param properties : VulkanQueueFamilyProperties cref = Structure containing the properties of a queue family
         *
         * @exceptsafe
         *
         * @static
         *
         * @return bool = true if properties include Transfer Capabilities, false otherwise
         */
        [[nodiscard]] constexpr static auto queueFamilyPropertiesTransferBit( VulkanQueueFamilyProperties const & properties ) noexcept -> bool {
            return (bool) ( properties.queueFlags & VQueueFamily::TRANSFER_FLAG);
        }

        /**
         * @brief Function testing whether queue family properties include Graphics Capabilities
         *
         * @param properties : VulkanQueueFamilyProperties cref = Structure containing the properties of a queue family
         *
         * @exceptsafe
         *
         * @static
         *
         * @return bool = true if properties include Graphics Capabilities, false otherwise
         */
        [[nodiscard]] constexpr static auto queueFamilyPropertiesGraphicsBit( VulkanQueueFamilyProperties const & properties ) noexcept -> bool {
            return (bool) ( properties.queueFlags & VQueueFamily::GRAPHICS_FLAG);
        }

        /**
         * @brief Function testing whether queue family properties include Compute Capabilities
         *
         * @param properties : VulkanQueueFamilyProperties cref = Structure containing the properties of a queue family
         *
         * @exceptsafe
         *
         * @static
         *
         * @return bool = true if properties include Compute Capabilities, false otherwise
         */
        [[nodiscard]] constexpr static auto queueFamilyPropertiesComputeBit( VulkanQueueFamilyProperties const & properties ) noexcept -> bool {
            return (bool) ( properties.queueFlags & VQueueFamily::COMPUTE_FLAG);
        }

        /**
         * @brief Function testing whether queue family properties include Protection of Memory Capabilities
         *
         * @param properties : VulkanQueueFamilyProperties cref = Structure containing the properties of a queue family
         *
         * @exceptsafe
         *
         * @static
         *
         * @return bool = true if properties include Protection of Memory Capabilities, false otherwise
         */
        [[nodiscard]] constexpr static auto queueFamilyPropertiesProtectedBit( VulkanQueueFamilyProperties const & properties ) noexcept -> bool {
            return (bool) ( properties.queueFlags & VQueueFamily::PROTECTED_FLAG);
        }

        /**
         * @brief Function testing whether queue family properties include Sparse Binding Capabilities - binding memory to pages instead of blocks, flexible
         *
         * @param properties : VulkanQueueFamilyProperties cref = Structure containing the properties of a queue family
         *
         * @exceptsafe
         *
         * @static
         *
         * @return bool = true if properties include Sparse Binding Capabilities, false otherwise
         */
        [[nodiscard]] constexpr static auto queueFamilyPropertiesSparseBindingBit( VulkanQueueFamilyProperties const & properties ) noexcept -> bool {
            return (bool) ( properties.queueFlags & VQueueFamily::SPARSE_BINDING_FLAG);
        }

        /**
         * @brief Function testing whether queue family properties include several Property Flags
         *
         * @param properties : VulkanQueueFamilyProperties cref = Structure containing the properties of a queue family
         * @param VulkanQueueFlags : Flags obtaining by bitwise OR-ing several VulkanQueueFlagBits
         *
         * @exceptsafe
         *
         * @static
         *
         * @return bool = true if properties include the properties described by the flags, false otherwise
         */
        [[nodiscard]] constexpr static auto queueFamilyPropertiesCompatibleFlagBits( VulkanQueueFamilyProperties const & properties, VulkanQueueFlags flags ) noexcept -> bool {
            return (bool) ( ( properties.queueFlags & flags ) == flags );
        }

    public:
        //// public variables

        /// flag definition for Graphics Capabilities
        constexpr static VulkanQueueFlags GRAPHICS_FLAG       = VkQueueFlagBits::VK_QUEUE_GRAPHICS_BIT;

        /// flag definition for Compute Capabilities
        constexpr static VulkanQueueFlags COMPUTE_FLAG        = VkQueueFlagBits::VK_QUEUE_COMPUTE_BIT;

        /// flag definition for Transfer Capabilities
        constexpr static VulkanQueueFlags TRANSFER_FLAG       = VkQueueFlagBits::VK_QUEUE_TRANSFER_BIT;

        /// flag definition for Sparse Binding Capabilities
        constexpr static VulkanQueueFlags SPARSE_BINDING_FLAG = VkQueueFlagBits::VK_QUEUE_SPARSE_BINDING_BIT;

        /// flag definition for Protected Memory Capabilities
        constexpr static VulkanQueueFlags PROTECTED_FLAG      = VkQueueFlagBits::VK_QUEUE_PROTECTED_BIT;

        /// flag definition for Present Capabilities
        constexpr static VulkanQueueFlags PRESENT_FLAG        = VkQueueFlagBits::VK_QUEUE_PROTECTED_BIT * 2;

        /// mask for all flags, except PRESENT_FLAG <- not part of standard Vulkan Suite
        constexpr static VulkanQueueFlags STANDARD_QUEUE_PROPERTIES_MASK =
                VQueueFamily::GRAPHICS_FLAG         |
                VQueueFamily::COMPUTE_FLAG          |
                VQueueFamily::TRANSFER_FLAG         |
                VQueueFamily::PROTECTED_FLAG        |
                VQueueFamily::SPARSE_BINDING_FLAG;

        //// public functions

        /**
         * @brief Default Constructor
         *
         * @exceptsafe
         */
        VQueueFamily() noexcept = default;

        /**
         * @brief Constructor with initialisation of parent family collection, properties and family index
         *
         * @param parent : engine::VQueueFamilyCollection ptr = Address of the Family Collection
         * @param properties : VulkanQueueFamilyProperties cref = Reference to the properties structure
         * @param family : uint32 = Index of the Queue Family in the Queue Family Collection
         *
         * @exceptsafe
         */
        explicit VQueueFamily (VQueueFamilyCollection * parent, VulkanQueueFamilyProperties const & properties, uint32 family) noexcept {
            this->_parentCollection = parent;
            this->_queueFamilyProperties = properties;
            this->_familyIndex = family;
        }

        /**
         * @brief Copy Constructor
         *
         * @param obj : VQueueFamily cref = VQueueFamily to initialise from
         *
         * @exceptsafe
         */
        VQueueFamily(VQueueFamily const & obj) noexcept {
            this->_parentCollection = obj._parentCollection;
            this->_queueFamilyProperties = obj._queueFamilyProperties;
            this->_familyIndex = obj._familyIndex;
            this->_presentSupport = obj._presentSupport;
        }

        /**
         * @brief Destructor, default Implementation
         *
         * @exceptsafe
         */
        ~VQueueFamily() noexcept = default;

        /**
         * @brief reserve number of queues from the family, to be acquired later
         * Will reserve from parent queue family
         *
         * @param targetQueueCount : uint32 = number of queues to reserve
         *
         * @exceptsafe
         *
         * @return uint32 = number of queues that were actuall reserved. <= targetQueueCount
         */
        [[nodiscard]] auto reserveQueues          ( uint32 ) const noexcept -> uint32;

        /**
         * @brief free number of queues from the family that have been previously reserved
         *
         * @exceptsafe
         *
         * @param targetQueueCount : uint32 = number of queues to free
         */
        auto               freeQueues             ( uint32 ) const noexcept -> void;

        /**
         * @brief getter for the first index of an available queue
         *
         * @exceptsafe
         *
         * @return uint32 = index of the first available queue
         */
        [[nodiscard]] auto getAvailableQueueIndex ( )        const noexcept -> uint32;

        /**
         * @brief free queue with index given
         *
         * @param index : uint32 = index of the queue to be freed
         *
         * @exceptsafe
         */
        auto               freeQueueIndex         ( uint32 ) const noexcept -> void;

        /**
         * @brief getter for the physical device owning from which the queue will be allocated
         *
         * @exceptsafe
         *
         * @return engine::VPhysicalDevice cref = Reference to the Physical Device
         */
        [[nodiscard]] auto getPhysicalDevice () const noexcept -> VPhysicalDevice const &;

        /**
         * @brief getter for the index of this family in the family collection
         *
         * @exceptsafe
         *
         * @return uint32 = index of this family in the family collection
         */
        [[nodiscard]] auto getQueueFamilyIndex ( ) const noexcept -> uint32 {
            return this->_familyIndex;
        }

        /**
         * @brief getter for the queue count in this queue family
         *
         * @exceptsafe
         *
         * @return uint32 = number of queues this family controls / owns
         */
        [[nodiscard]] auto getQueueCount ( ) const noexcept -> uint32 {
            return this->_queueFamilyProperties.queueCount;
        }

        /**
         * @brief getter for this family's properties
         *
         * @exceptsafe
         *
         * @return VulkanQueueFamilyProperties cref = Reference to structure containing properties
         */
        [[nodiscard]] auto getQueueFamilyProperties ( ) const noexcept -> VulkanQueueFamilyProperties const & {
            return this->_queueFamilyProperties;
        }

        /**
         * @brief function checking whether this family is Transfer Capable
         *
         * @exceptsafe
         *
         * @return bool = true if family is Transfer Capable, false otherwise
         */
        [[maybe_unused]] [[nodiscard]] constexpr auto isTransferCapable() const noexcept -> bool {
            return VQueueFamily::queueFamilyPropertiesTransferBit(this->_queueFamilyProperties);
        }

        /**
         * @brief function checking whether this family is Graphics Capable
         *
         * @exceptsafe
         *
         * @return bool = true if family is Graphics Capable, false otherwise
         */
        [[maybe_unused]] [[nodiscard]] constexpr auto isGraphicsCapable() const noexcept -> bool {
            return VQueueFamily::queueFamilyPropertiesGraphicsBit(this->_queueFamilyProperties);
        }

        /**
         * @brief function checking whether this family is Compute Capable
         *
         * @exceptsafe
         *
         * @return bool = true if family is Compute Capable, false otherwise
         */
        [[maybe_unused]] [[nodiscard]] constexpr auto isComputeCapable() const noexcept -> bool {
            return VQueueFamily::queueFamilyPropertiesComputeBit(this->_queueFamilyProperties);
        }

        /**
         * @brief function checking whether this family is Protected Memory Capable
         *
         * @exceptsafe
         *
         * @return bool = true if family is Protected Memory Capable, false otherwise
         */
        [[maybe_unused]] [[nodiscard]] constexpr auto isProtectedCapable() const noexcept -> bool {
            return VQueueFamily::queueFamilyPropertiesProtectedBit(this->_queueFamilyProperties);
        }

        /**
         * @brief function checking whether this family is Sparse Binding Capable
         *
         * @exceptsafe
         *
         * @return bool = true if family is Sparse Binding Capable, false otherwise
         */
        [[maybe_unused]] [[nodiscard]] constexpr auto isSparseBindingCapable() const noexcept -> bool {
            return VQueueFamily::queueFamilyPropertiesSparseBindingBit(this->_queueFamilyProperties);
        }

        /**
         * @brief function checking whether this family is Present Capable
         *
         * @exceptsafe
         *
         * @return bool = true if family is Present Capable, false otherwise
         */
        [[maybe_unused]] [[nodiscard]] constexpr auto isPresentCapable () const noexcept -> bool {
            return ( (bool) this->_presentSupport );
        }

        /**
         * @brief functions checking whether this family is capable of property flags
         *
         * @param flags : VulkanQueueFlags = flags for queues
         *
         * @exceptsafe
         *
         * @return bool = true if family is capable of all properties mentioned in flags, false otherwise
         */
        [[nodiscard]] constexpr auto isCapableOfPropertiesFlags ( VulkanQueueFlags flags ) const noexcept -> bool {
            return VQueueFamily::queueFamilyPropertiesCompatibleFlagBits( this->_queueFamilyProperties, flags );
        }

        /**
         * @brief function synchronises this queue's utilised capabilities with the surface, enabling features on the surface
         *
         * @param surface : engine::VSurface cref = Reference to the Surface to sync with
         *
         * @exceptsafe
         */
        auto syncWithSurface ( VSurface const & ) noexcept -> void;

#ifndef NDEBUG
        /**
         * @brief Debug Function for printing queue family data
         *
         * @param buffer : std::ostream ref = Reference to an Output Stream to place the data in
         * @param prefix : StringLiteral = Prefix before each line ( ex. no. of tabs )
         *
         * @exceptsafe
         */
        auto debugPrintQueueFamily ( std::ostream &, StringLiteral = "" ) const noexcept -> void;

        /**
         * @brief Debug Function for printing no. of reserved queues in this family
         *
         * @param buffer : std::ostream ref = Reference to an Output Stream to place the data in
         * @param prefix : StringLiteral = Prefix before each line ( ex. no. of tabs )
         *
         * @exceptsafe
         */
        auto debugPrintQueueFamilyReservation( std::ostream &, StringLiteral = "" ) const noexcept -> void;

        /**
         * @brief Debug Function for printing Queue Family Flags Capabilities
         *
         * @param properties : VulkanQueueFamilyProperties cref = properties of a Queue Family
         * @param buffer : std::ostream ref = Reference to an Output Stream to place the data in
         * @param prefix : StringLiteral = Prefix before each line ( ex. no. of tabs )
         *
         * @static
         *
         * @exceptsafe
         */
        static auto debugPrintQueueFamilyPropertiesStructureQueueFlags ( VulkanQueueFamilyProperties const & ,std::ostream &, StringLiteral ) noexcept -> void;

        /**
         * @brief Debug Function for printing Queue Family Properties Structure
         *
         * @param properties : VulkanQueueFamilyProperties cref = properties of a Queue Family
         * @param buffer : std::ostream ref = Reference to an Output Stream to place the data in
         * @param prefix : StringLiteral = Prefix before each line ( ex. no. of tabs )
         *
         * @static
         *
         * @exceptsafe
         */
        static auto debugPrintQueueFamilyPropertiesStructure ( VulkanQueueFamilyProperties const &, std::ostream &, StringLiteral ) noexcept -> void;
#endif
    };

    /**
     * @class engine::VQueueFamilyCollection
     *
     * @brief A Collection of Queue Families
     */
    class VQueueFamilyCollection {
    private:
        //// private variables

        /// Pointer to the owner Physical Device
        const VPhysicalDevice         * _physicalDevice { nullptr };

        /// std::vector of VQueueFamily
        std::vector < VQueueFamily >    _queueFamilies;

        /// std::map of uint32, uint32 - queue family index -> reserved queue count
        std::map < uint32, uint32 >     _reservedQueuesForFamilies;

        /// std::map of uint32, std::set of uint32 - queue family index -> set of indices reserved
        std::map < uint32, std::set < uint32 > > _reservedQueueIndicesForFamilies;

        //// private functions

        /**
         * @brief function for de-allocating all of the queue families
         *
         * @exceptsafe
         */
        auto unReserveAllQueueFamilies ( ) noexcept -> void;

        /**
         * @brief function for acquiring all the queue families from the device to the collection
         *
         * @throws engine::EngineNullVPhysicalDevice if
         *      Queue Family Collection does not have a valid VPhysicalDevice address in _physicalDevice
         */
        auto queryAvailableQueueFamilies ( ) noexcept (false) -> void;
    public:
        //// public variables

        //// public functions

        /**
         * @brief Default Constructor
         *
         * Deleted as to require use of the Explicit Constructor
         *
         * @exceptsafe
         *
         * @deprecated
         */
        VQueueFamilyCollection () noexcept = delete;

        /**
         * @brief Explicit Constructor, acquiring a physical device and, optionally, a surface address
         *
         * @param physicalDevice : engine::VPhysicalDevice cref = Reference to the Physical Device the Queue Family Collection is initialised from
         * @param surfaceToSync : engine::VSurface cptr = Address of a Surface to synchronise features with. Default nullptr
         *
         * @throws engine::EngineNullVPhysicalDevice if
         *      queryAvailableQueueFamilies() throws
         */
        explicit VQueueFamilyCollection ( VPhysicalDevice const & physicalDevice , VSurface const * surfaceToSync = nullptr ) noexcept (false) {
            this->_physicalDevice = (& physicalDevice);
            this->queryAvailableQueueFamilies();
            this->unReserveAllQueueFamilies();
            if ( surfaceToSync != nullptr )
                this->syncWithSurface( * surfaceToSync );
        }

        /**
         * @brief function used to reserve target amount of queues from a queue family, managed by collection
         *
         * @param queueFamily : engine::VQueueFamily cref = Reference to Queue Family from which to reserve
         * @param targetQueueCount : uint32 = number of queues to reserve
         *
         * @exceptsafe
         *
         * @return uint32 = number of queues that could be reserved
         */
        [[nodiscard]] auto reserveQueues ( VQueueFamily const &, uint32 ) noexcept -> uint32;

        /**
         * @brief function used to free a number of queues from a queue family
         *
         * @param queueFamily : engine::VQueueFamily cref = Reference to Queue Family from which to free
         * @param targetQueueCount : uint32 = number of queues to free
         *
         * @exceptsafe
         */
        auto freeQueues ( VQueueFamily const &, uint32 ) noexcept -> void;

        /**
         * @brief function used to get the index of the first free queue in a family
         *
         * @param queueFamily : engine::VQueueFamily cref = Reference to Queue Family from which to get the index from
         *
         * @exceptsafe
         *
         * @return uint32 = index of the first free queue
         */
        auto getAvailableQueueIndex ( VQueueFamily const & ) noexcept -> uint32;

        /**
         * @brief function used to free a queue with a given index in a queue family
         *
         * @param queueFamily : engine::VQueueFamily cref = Reference to Queue Family from which to free Queue from
         * @param index : uint32 = Index of the Queue to free
         *
         * @exceptsafe
         */
        auto freeQueueIndex ( VQueueFamily const & ,uint32 ) noexcept -> void;

        /**
         * @brief getter for the Reserved Queue Families Map
         *
         * @exceptsafe
         *
         * @return std::map < uint32, uint32 > cref = Reference to the Map
         */
        [[nodiscard]] auto getReservedQueueFamiliesMap () const noexcept -> std::map < uint32, uint32 > const & {
            return this->_reservedQueuesForFamilies;
        }

        /**
         * @brief getter for the parent Physical Device
         *
         * @exceptsafe
         *
         * @return engine::VPhysicalDevice cref = Reference to the Physical Device
         */
        [[nodiscard]] auto getPhysicalDevice ( ) const noexcept -> VPhysicalDevice const & {
            return * this->_physicalDevice;
        }

        /**
         * @brief getter for queue families owned by this object
         *
         * @exceptsafe
         *
         * @return std::vector < VQueueFamily > cref = Constant Reference to the queue families vector
         */
        [[nodiscard]] auto getQueueFamilies () const noexcept -> std::vector < VQueueFamily > const & {
            return this->_queueFamilies;
        }

        /**
         * @brief getter for queue family indices owned
         *
         * @exceptsafe
         *
         * @return std::vector < uint32 > = Vector containing queue family indices
         */
        [[nodiscard]] auto getQueueFamilyIndices () const noexcept -> std::vector < uint32 >;

        /**
         * @brief getter for graphics capable queue families
         * fix:0002 . Have to return *, otherwise duplicates that will destroy logical devices and queues will appear
         *
         * @exceptsafe
         *
         * @return std::vector < VQueueFamily cptr > = Vector containing addresses to constant VQueueFamily
         */
        [[nodiscard]] auto getGraphicsCapableQueueFamilies () const noexcept -> std::vector < VQueueFamily const * > {
            return this->getFlagsCapableQueueFamilies( VQueueFamily::GRAPHICS_FLAG );
        }

        /**
         * @brief getter for compute capable queue families
         * fix:0002 . Have to return *, otherwise duplicates that will destroy logical devices and queues will appear
         *
         * @exceptsafe
         *
         * @return std::vector < VQueueFamily cptr > = Vector containing addresses to constant VQueueFamily
         */
        [[nodiscard]] auto getComputeCapableQueueFamilies () const noexcept -> std::vector < VQueueFamily const * >  {
            return this->getFlagsCapableQueueFamilies( VQueueFamily::COMPUTE_FLAG );
        }

        /**
         * @brief getter for transfer capable queue families
         * fix:0002 . Have to return *, otherwise duplicates that will destroy logical devices and queues will appear
         *
         * @exceptsafe
         *
         * @return std::vector < VQueueFamily cptr > = Vector containing addresses to constant VQueueFamily
         */
        [[nodiscard]] auto getTransferCapableQueueFamilies () const noexcept -> std::vector < VQueueFamily const * > {
            return this->getFlagsCapableQueueFamilies( VQueueFamily::TRANSFER_FLAG );
        }

        /**
         * @brief getter for protected memory capable queue families
         * fix:0002 . Have to return *, otherwise duplicates that will destroy logical devices and queues will appear
         *
         * @exceptsafe
         *
         * @return std::vector < VQueueFamily cptr > = Vector containing addresses to constant VQueueFamily
         */
        [[nodiscard]] auto getProtectedCapableQueueFamilies () const noexcept -> std::vector < VQueueFamily const * > {
            return this->getFlagsCapableQueueFamilies( VQueueFamily::PROTECTED_FLAG );
        }

        /**
         * @brief getter for Sparse Binding capable queue families
         * fix:0002 . Have to return *, otherwise duplicates that will destroy logical devices and queues will appear
         *
         * @exceptsafe
         *
         * @return std::vector < VQueueFamily cptr > = Vector containing addresses to constant VQueueFamily
         */
        [[nodiscard]] auto getSparseBindingCapableQueueFamilies () const noexcept -> std::vector < VQueueFamily const * > {
            return this->getFlagsCapableQueueFamilies( VQueueFamily::SPARSE_BINDING_FLAG );
        }

        /**
         * @brief getter for present capable queue families
         * fix:0002 . Have to return *, otherwise duplicates that will destroy logical devices and queues will appear
         *
         * @exceptsafe
         *
         * @return std::vector < VQueueFamily cptr > = Vector containing addresses to constant VQueueFamily
         */
        [[nodiscard]] auto getPresentCapableQueueFamilies () const noexcept -> std::vector < VQueueFamily const * > {
            return this->getFlagsCapableQueueFamilies( VQueueFamily::PRESENT_FLAG );
        }

        /**
         * @brief getter for flags capable queue families
         *
         * @exceptsafe
         *
         * @return std::vector < VQueueFamily cptr > = Vector containing addresses to constant VQueueFamily capable of flags given
         */
        [[nodiscard]] auto getFlagsCapableQueueFamilies ( VulkanQueueFlags ) const noexcept -> std::vector < VQueueFamily const * >;

        /**
         * @brief function syncing queue families to a surface, requesting surface to enable features on Surface
         *
         * @param surface : VSurface cref = Reference to the Surface Object
         *
         * @exceptsafe
         */
        auto syncWithSurface ( VSurface const & surface ) noexcept -> void {
            for ( auto & queueFamily : this->_queueFamilies )
                queueFamily.syncWithSurface( surface );
        }

#ifndef NDEBUG

        /**
         * @brief Debug Function used to print all Queue Families in the Collection
         *
         * @param buffer : std::ostream ref = Reference to an Output Stream to put the data in
         * @param prefix : StringLiteral = Prefix to be printed before each line ( eg. no. of tabs )
         *
         * @exceptsafe
         */
        auto debugPrintQueueFamilies ( std::ostream &, StringLiteral = "" ) const noexcept -> void;

        /**
         * @brief Debug Function used to print all Queue Families Reservations
         *
         * @param buffer : std::ostream ref = Reference to an Output Stream to put the data in
         * @param prefix : StringLiteral = Prefix to be printed before each line ( eg. no. of tabs )
         */
        auto debugPrintQueueFamiliesReservations ( std::ostream &, StringLiteral = "" ) const noexcept -> void;
#endif
    };

}


#endif //ENG1_VQUEUEFAMILY_HPP
