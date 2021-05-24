//
// Created by Vlad on 07/09/2020.
//

#ifndef ENG1_VDESCRIPTORSET_HPP
#define ENG1_VDESCRIPTORSET_HPP

#include <VRenderObject.hpp>
#include <VDescriptorPool.hpp>
#include <VUniformBuffer.hpp>
#include <VTextureSampler.hpp>
#include <VTexture.hpp>
#include <vector>
#include <sstream>

namespace engine {

    /**
     * @brief Predeclare class to avoid circular / recursive include
     */
    template <class T>
    class VDescriptorSetCollection;

    /**
     * @class engine::VDescriptorSet
     *
     * @brief Represents a CPU-GPU Memory Layout Binding of a Data Type ( shared variable location between CPU and GPU, i.e. MVP Matrix )
     *
     * @tparam T = Data Type to bind to CPU-GPU pipeline
     */
    template <class T>
    class VDescriptorSet : public VRenderObject {
        /// give access to collection class
        friend class VDescriptorSetCollection<T>;
    private:
        //// private variables

        /// Vulkan Internal Allocated Handle
        VulkanDescriptorSet     _handle;

        /// Address to Logical Device
        VLogicalDevice  const * _pLogicalDevice {nullptr};

        //// private functions

    public:
        //// public variables

        //// public functions

        /**
         * @brief Default Constructor
         *
         * @exceptsafe
         *
         * @deleted
         */
        VDescriptorSet () noexcept = delete;
        ~VDescriptorSet() noexcept override = default;

        /**
         * @brief Constructor used when allocated from collection
         *
         * @param handle : VulkanDescriptorHandle = vulkan handle to be passed to this object
         * @param pLogicalDevice : engine::VLogicalDevice cptr = Address to Constant Logical Device
         *
         * @exceptsafe
         */
        explicit VDescriptorSet (
                VulkanDescriptorSet handle,
                VLogicalDevice const * pLogicalDevice
        ) noexcept :
            VRenderObject(),
            _handle ( handle ),
            _pLogicalDevice ( pLogicalDevice ) {

        }

        /**
         * @brief Getter Function for Internal Vulkan Allocated Handle
         *
         * @exceptsafe
         *
         * @return VulkanDescriptorSet cref = Constant Reference to the Vulkan Handle
         */
        [[nodiscard]] constexpr auto data() const noexcept -> VulkanDescriptorSet const & {
            return this->_handle;
        }

        /**
         * @brief Function Configures Descriptor Set based on uniform buffer and index of buffer in layout
         *
         * @param uniformBuffer : engine::VUniformBuffer cref = Constant Reference to Uniform Buffer to configure Descriptor Set for
         * @param descriptorIndex : uint32 = Index of Descriptor Set in Layout
         *
         * @exceptsafe
         */
        auto configure ( VUniformBuffer <T> const &, uint32 ) noexcept -> void;

        /**
         * @brief Function Configures Descriptor Set for Texture Buffer at given index in Layout
         *
         * @param texture : engine::VTexture cref = Constant Reference to the Texture to create a Set for
         * @param textureSampler : engine::VTextureSampler cref = Constant Reference to the used Texture Sampler
         * @param descriptorIndex : uint32 = Index of Descriptor Set in Layout
         *
         * @exceptsafe
         */
        auto configure ( VTexture const & , VTextureSampler const &, uint32 ) noexcept -> void;

        auto clear () noexcept -> void {}

        [[nodiscard]] auto toString () const noexcept -> String override {
            std::stringstream  oss;
            oss << "VDescriptorSet { " <<
                "handle = 0x" << std::hex << reinterpret_cast < AddressValueType > ( this->_handle ) <<
                ", pLogicalDevice = 0x" << reinterpret_cast < AddressValueType > ( this->_pLogicalDevice ) << " }";

            return oss.str();
        }

        [[nodiscard]] auto operator == (Object const & o) const noexcept -> bool override {
            if ( this == & o ) return true;
            auto p = dynamic_cast < decltype(this) > ( & o );
            if ( p == nullptr ) return false;

            return this->_handle == p->_handle;
        }

        [[nodiscard]] auto hash () const noexcept -> Index override {
            return dataTypes::hash(reinterpret_cast<AddressValueType>(this->_handle));
        }

        [[nodiscard]] auto copy () const noexcept -> VDescriptorSet * override {
            return new VDescriptorSet (* this);
        }
    };

    /**
     * @class engine::VDescriptorSetCollection
     *
     * @brief Represents Multiple Descriptor Sets. Usually one for each frame
     *
     * @tparam T = Data Type to bind to CPU-GPU pipeline
     */
    template <class T>
    class VDescriptorSetCollection : public VRenderObject {
    private:
        //// private variables

        /// Address of Logical Device
        VLogicalDevice                const * _pLogicalDevice {nullptr};

        /// Vector of Descriptor Sets
        std::vector < VDescriptorSet <T> >    _descriptorSets;

        /// Descriptor Sequence Increment for Index Assignation
        uint32                                _autoIncrementDescriptorIndex {0U};

        //// private functions
    public:
        //// public variables

        //// public functions

        /**
         * @brief Default Constructor. Creates Empty Collection
         *
         * @exceptsafe
         */
        VDescriptorSetCollection () noexcept = default;

        ~VDescriptorSetCollection() noexcept override = default;

        /**
         * @brief Function Allocates Descriptor Sets from a Descriptor Pool based on a Descriptor Set Layout
         *
         * Descriptor Set Layout = In what order are parameters bound
         *
         * GPU GLSL Code :
         *
         *      layout(binding = 0) uniform UniformBufferObject {
         *          mat4 model;
         *          mat4 view;
         *          mat4 projection;
         *      } uniformBufferObject;
         *
         *      layout(binding = 1) uniform sampler2D textureSampler;
         *
         * Layout on CPU : Uniform Buffer Object will have binding 0, Texture Sampler will have binding 1
         *                 Order is strict, because of CPU-GPU required optimisations on data bus
         *
         * @param descriptorPool : engine::VDescriptorPool cref = Constant Reference to Pool to allocate Descriptors from
         * @param descriptorSetBaseLayout : VulkanDescriptorSetLayout cref = Constant Reference to Layout of Descriptor Sets on GPU, for shader program
         *
         * @exceptsafe
         *
         * @return VulkanResult::VK_SUCCESS if allocation was successful OR
         * @return VulkanResult returned by vkAllocateDescriptorSets if error occurred - vulkan internal function
         */
        auto allocate (
                VDescriptorPool             const &,
                VulkanDescriptorSetLayout   const &
        ) noexcept -> VulkanResult;

        /**
         * @brief Getter for Descriptor Sets contained in Collection
         *
         * @exceptsafe
         *
         * @return std::vector < engine::VDescriptorSet < T > > cref = Constant Reference to Descriptor Set vector
         */
        [[nodiscard]] constexpr auto getDescriptorSets () const noexcept -> std::vector < VDescriptorSet <T> > const & {
            return this->_descriptorSets;
        }

        /**
         * @brief Getter for Descriptor Set Handles inside Collection
         *
         * @exceptsafe
         *
         * @return std::vector < VulkanDescriptorSet > = vector of Descriptor Set Handles
         */
        [[nodiscard]] auto getDescriptorSetHandles () const noexcept -> std::vector < VulkanDescriptorSet >;

        /**
         * @brief Getter for Logical Device Address
         *
         * @exceptsafe
         *
         * @return engine::VLogicalDevice cptr = Address to Constant Logical Device
         */
        [[nodiscard]] auto getLogicalDevicePtr () const noexcept -> VLogicalDevice const * {
            return this->_pLogicalDevice;
        }

        /**
         * @brief Function configures contained Descriptor Sets for Uniform Buffers given
         *
         * @param uniformBuffers : std::vector < engine::VUniformBuffer < T > > cref = Constant Reference to vector of Uniform Buffers to be configured (bound) for Descriptor Sets
         * @param descriptorIndex : uint32 = unused parameter TODO : remove
         *
         * @exceptsafe
         */
        auto configure ( std::vector < VUniformBuffer <T> > const &, uint32 = 0U ) noexcept -> void;

        auto clear () noexcept -> void override {}

        /**
         * @brief Function configures contained Descriptor Sets for Texture and Texture Sampler Given
         *
         * @param texture : engine::VTexture cref = Constant Reference to the Texture to be attached
         * @param textureSampler : engine::VTextureSampler cref = Constant Reference to the Texture Sampler to be attached
         * @param descriptorIndex : uint32 = unused parameter TODO : remove
         *
         * @exceptsafe
         */
        auto configure ( VTexture const &, VTextureSampler const &, uint32 = 0U ) noexcept -> void;

        [[nodiscard]] auto toString () const noexcept -> String override {
            std::stringstream  oss;
            oss << "VDescriptorSetCollection { " <<
                "pLogicalDevice = 0x" << std::hex << reinterpret_cast<AddressValueType>(this->_pLogicalDevice) <<
                ", descriptorSets = [ ";

            for ( auto const & o : this->_descriptorSets )
                oss << o.toString() << ", ";

            auto s = oss.str();
            return s.substr(s.size() - 2).append (" ]}");
        }

        [[nodiscard]] auto operator == (Object const & o) const noexcept -> bool override {
            if ( this == & o ) return true;
            auto p = dynamic_cast < decltype(this) > ( & o );
            if ( p == nullptr ) return false;

            return this->_descriptorSets == p->_descriptorSets;
        }

        [[nodiscard]] auto hash () const noexcept -> Index override {
            Index hashSum = 0;
            std::for_each(this->_descriptorSets.begin(), this->_descriptorSets.end(), [& hashSum](auto const & d){hashSum += d.hash();});
            return hashSum;
        }

        [[nodiscard]] auto copy () const noexcept -> VDescriptorSetCollection * override {
            return new VDescriptorSetCollection (* this);
        }
    };

    /// maybe unused
    typedef VDescriptorSet < uint8 > VSamplerDescriptorSet;
    /// maybe unused
    typedef VDescriptorSetCollection < uint8 > VSamplerDescriptorSetCollection;
}

/**
 * @brief Internal Function used to populate Descriptor Set Allocate Info
 *
 * @param pAllocateInfo : VulkanDescriptorSetAllocateInfo ptr = Address to Structure to populate
 * @param descriptorPool : VulkanDescriptorPool = Pool Handle to allocate from
 * @param descriptorSetCount : uint32 = Number of Descriptor Sets
 * @param pSetLayouts : VulkanDescriptorSetLayout cptr = Address to one / an array of Descriptor Set Layouts, one for each Set
 *
 * @static
 *
 * @exceptsafe
 */
inline static auto populateDescriptorSetAllocateInfo (
        VulkanDescriptorSetAllocateInfo * pAllocateInfo,
        VulkanDescriptorPool              descriptorPool,
        uint32                            descriptorSetCount,
        VulkanDescriptorSetLayout const * pSetLayouts
) noexcept -> void {
    if ( pAllocateInfo == nullptr || pSetLayouts == nullptr )
        return;

    * pAllocateInfo = VulkanDescriptorSetAllocateInfo {
            .sType              = VulkanStructureType::VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO,
            .pNext              = nullptr,
            .descriptorPool     = descriptorPool,
            .descriptorSetCount = descriptorSetCount,
            .pSetLayouts        = pSetLayouts,
    };
}

template <class T>
auto engine::VDescriptorSetCollection<T>::getDescriptorSetHandles () const noexcept -> std::vector < VulkanDescriptorSet > {
    std::vector < VulkanDescriptorSet > handles;

    for ( auto & descriptorSet : this->_descriptorSets )
        handles.push_back( descriptorSet.data() );

    return handles;
}

#include <VSwapChain.hpp>
template <class T>
auto engine::VDescriptorSetCollection<T>::allocate(
        VDescriptorPool             const & descriptorPool,
        VulkanDescriptorSetLayout   const & descriptorSetBaseLayout
) noexcept -> VulkanResult {
    this->_autoIncrementDescriptorIndex = 0U; /// start with index 0 for sequence. After allocation, configuration occurs
    this->_pLogicalDevice = descriptorPool.getLogicalDevicePtr();
    auto swapChainImageCount = static_cast < uint32 > ( this->_pLogicalDevice->getSwapChain()->getImages().size() ); /// image count from swap chain

    std::vector < VulkanDescriptorSet >         descriptorSetHandles ( swapChainImageCount );
    std::vector < VulkanDescriptorSetLayout >   layouts ( swapChainImageCount, descriptorSetBaseLayout ); /// create layout for each image

    VulkanDescriptorSetAllocateInfo             allocateInfo {};
    populateDescriptorSetAllocateInfo(
            & allocateInfo,
            descriptorPool.data(), /// allocate from this pool
            swapChainImageCount,   /// number of sets
            layouts.data()         /// pass layout for each set
    );

    VulkanResult allocateResult = vkAllocateDescriptorSets( /// allocate
            this->_pLogicalDevice->data(), /// on device
            & allocateInfo, /// with parameters
            descriptorSetHandles.data() /// save handles here
    );

    if ( allocateResult != VulkanResult::VK_SUCCESS )
        return allocateResult;

    this->_descriptorSets.clear(); /// clear any previous config
    for ( const auto & descriptorSetHandle : descriptorSetHandles ) /// emplace each set into vector
        this->_descriptorSets.emplace_back( descriptorSetHandle, this->_pLogicalDevice );

    return VulkanResult::VK_SUCCESS;
}

/**
 * @brief Internal Function used to populate Descriptor Buffer Info, for specifying uniform buffer for descriptor
 *
 * @param pBufferInfo : VulkanDescriptorBufferInfo ptr = Address of Structure to populate
 * @param uniformBufferHandle : VulkanBuffer = Buffer to Bind to Descriptor
 * @param offset : uint32 = Buffer's offset in Descriptor
 * @param size : uint32 = Size of Buffer Data
 *
 * @static
 *
 * @exceptsafe
 */
static inline auto populateDescriptorBufferInfo (
    VulkanDescriptorBufferInfo * pBufferInfo,
    VulkanBuffer                 uniformBufferHandle,
    uint32                       offset,
    uint32                       size
) noexcept -> void {
    if ( pBufferInfo == nullptr )
        return;

    * pBufferInfo = VulkanDescriptorBufferInfo {
        .buffer = uniformBufferHandle,
        .offset = offset,
        .range  = size
    };
}

/**
 * @brief Internal Function used to populate Descriptor Image Info, specifying Image Bound to Descriptor
 *
 * @param pImageInfo : VulkanDescriptorImageInfo ptr = Address of Structure to populate
 * @param layout : VulkanImageLayout = Layout of the Texture to be bound
 * @param imageView : VulkanImageView = Image View of the Texture
 * @param sampler : VulkanSampler = Handle of the Texture Sampler used
 *
 * @static
 *
 * @exceptsafe
 */
static inline auto populateDescriptorImageInfo (
    VulkanDescriptorImageInfo * pImageInfo,
    VulkanImageLayout           layout,
    VulkanImageView             imageView,
    VulkanSampler               sampler
) noexcept -> void {
    if ( pImageInfo == nullptr )
        return;

    * pImageInfo = VulkanDescriptorImageInfo {
            .sampler     = sampler,
            .imageView   = imageView,
            .imageLayout = layout
    };
}

/**
 * @brief Internal Function used to populate Write Descriptor Set Structure. Represents information required to write binding data to a Descriptor Set
 *
 * @param pWriteDescriptorSet : VulkanWriteDescriptorSet ptr = Address to the Structure to populate
 * @param destinationDescriptorSetHandle : Vulkan Descriptor Set = Descriptor Set to be bound
 * @param descriptorType : VulkanDescriptorType = Descriptor Type to be bound
 * @param destinationBinding : uint32 = Binding to bind
 * @param destinationArrayElementIndex : uint32 = Index of the Element to be Bound in the Descriptor Set
 * @param pDescriptorBufferInfo : VulkanDescriptorBufferInfo cptr = Address to one / an array of Uniform Buffers Descriptor Information to bind. If null, currently not binding Uniforms
 * @param pDescriptorImageInfo : VulkanDescriptorImageInfo cptr = Address to one / an array of Image Descriptor Info to bind. If null, currently not binidng images
 *
 * @static
 *
 * @exceptsafe
 */
static inline auto populateWriteDescriptorSet (
    VulkanWriteDescriptorSet          * pWriteDescriptorSet,
    VulkanDescriptorSet                 destinationDescriptorSetHandle,
    VulkanDescriptorType                descriptorType,
    uint32                              destinationBinding,
    uint32                              destinationArrayElementIndex,
    const VulkanDescriptorBufferInfo  * pDescriptorBufferInfo,
    const VulkanDescriptorImageInfo   * pDescriptorImageInfo
) noexcept -> void {
    if ( pWriteDescriptorSet == nullptr )
        return;

    * pWriteDescriptorSet = VulkanWriteDescriptorSet {
        .sType              = VulkanStructureType::VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET,
        .pNext              = nullptr,
        .dstSet             = destinationDescriptorSetHandle,
        .dstBinding         = destinationBinding,
        .dstArrayElement    = destinationArrayElementIndex,
        .descriptorCount    = 1U,
        .descriptorType     = descriptorType,
        .pImageInfo         = pDescriptorImageInfo,
        .pBufferInfo        = pDescriptorBufferInfo,
        .pTexelBufferView   = nullptr /// not using texels
    };
}

template <class T>
auto engine::VDescriptorSetCollection<T>::configure(
        std::vector<VUniformBuffer<T>>  const & uniformBuffers,
        uint32                                  descriptorIndex /// unused param, to be removed
) noexcept -> void {
    for ( uint32 it = 0; it < this->_descriptorSets.size(); it++ )
        this->_descriptorSets[it].configure ( uniformBuffers[ it ], this->_autoIncrementDescriptorIndex ); /// configure for each descriptor set
    this->_autoIncrementDescriptorIndex ++; /// go to next descriptor set in layout
}

template <class T>
auto engine::VDescriptorSetCollection<T>::configure(
        VTexture        const & texture,
        VTextureSampler const & textureSampler,
        uint32                  descriptorIndex /// unused param
) noexcept -> void {
    for ( auto & descriptorSet : this->_descriptorSets ) /// same as above
        descriptorSet.configure ( texture, textureSampler, this->_autoIncrementDescriptorIndex );
    this->_autoIncrementDescriptorIndex ++;
}

template <class T>
auto engine::VDescriptorSet<T>::configure(
        VTexture        const & texture,
        VTextureSampler const & textureSampler,
        uint32                  descriptorIndex
) noexcept -> void {
    VulkanDescriptorImageInfo imageInfo {}; /// configuring texture, bind image
    populateDescriptorImageInfo(
        & imageInfo,
        texture.getLayout(), /// get layout of texture
        texture.getImageView().data(), /// get image view of texture
        textureSampler.data() /// acquire sampler handle
    );

    VulkanWriteDescriptorSet writeDescriptorSet{ }; /// populate descriptor write info
    populateWriteDescriptorSet(
        & writeDescriptorSet,
        this->_handle, /// write in this descriptor
        VulkanDescriptorType::VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, /// type is image sampler
        descriptorIndex, /// index is given index
        0U, /// in array ( array at binding ) it is 0
        nullptr, /// no uniform
        & imageInfo /// pass image info
    );

    vkUpdateDescriptorSets( this->_pLogicalDevice->data(), 1U, & writeDescriptorSet, 0U, nullptr ); /// write descriptor binding info
}

template <class T>
auto engine::VDescriptorSet<T>::configure(
        VUniformBuffer<T>   const & uniformBuffer,
        uint32                      descriptorIndex
) noexcept -> void {
    VulkanDescriptorBufferInfo bufferInfo {}; /// configure for uniform buffer
    populateDescriptorBufferInfo(
        & bufferInfo,
        uniformBuffer.data(), /// uniform buffer handle
        0U, /// inside buffer, data is at offset 0
        sizeof ( T ) /// one buffer contains one T for uniform. TODO : might be sizeof(T) * element Count
    );

    VulkanWriteDescriptorSet writeDescriptorSet{ }; /// write info
    populateWriteDescriptorSet(
        & writeDescriptorSet,
        this->_handle, /// bind to this set handle
        VulkanDescriptorType::VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, /// bind uniform buffer
        descriptorIndex, /// index of the descriptor, given
        0U, /// position 0 in binding array
        & bufferInfo, /// pass buffer info - uniform
        nullptr /// no image to bind
    );

    vkUpdateDescriptorSets( this->_pLogicalDevice->data() , 1U, & writeDescriptorSet, 0U, nullptr ); /// write binding to descriptor set
}

#endif //ENG1_VDESCRIPTORSET_HPP
