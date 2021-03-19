//
// Created by Vlad on 07/09/2020.
//

#ifndef ENG1_VDESCRIPTORSET_HPP
#define ENG1_VDESCRIPTORSET_HPP

#include <engineVulkanPreproc.hpp>
#include <vkDefs/types/vulkanExplicitTypes.h>
#include <vkObj/instance/pipeline/shader/input/VDescriptorPool.hpp>
#include <vkObj/instance/pipeline/shader/input/VUniformBuffer.hpp>
#include <VTextureSampler.hpp>
#include <VTexture.hpp>
#include <vector>

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
     * @tparam T = type of Data Type to bind to CPU-GPU pipeline
     */
    template <class T>
    class VDescriptorSet {
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
        VDescriptorSet ( ) noexcept = delete;

        /**
         * @brief Constructor used when allocated from collection
         *
         * @param handle : VulkanDescriptorHandle = vulkan handle to be passed to this object
         * @param pLogicalDevice : engine::VLogicalDevice cptr = Address to Constant Logical Device
         *
         * @exceptsafe
         */
        explicit VDescriptorSet ( VulkanDescriptorSet handle, VLogicalDevice const * pLogicalDevice ) noexcept :
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
        [[nodiscard]] auto data() const noexcept -> VulkanDescriptorSet const & {
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
    };

    template <class T>
    class VDescriptorSetCollection {
    private:
        //// private variables
        const VLogicalDevice                * _pLogicalDevice {nullptr};
        std::vector < VDescriptorSet <T> >    _descriptorSets;
        uint32                                _autoIncrementDescriptorIndex {0U};

        //// private functions
    public:
        //// public variables

        //// public functions
        VDescriptorSetCollection () noexcept = default;
        VulkanResult allocate ( const VDescriptorPool & , const VulkanDescriptorSetLayout & ) noexcept;

        [[nodiscard]] const std::vector < VDescriptorSet <T> > & getDescriptorSets () const noexcept {
            return this->_descriptorSets;
        }

        [[nodiscard]] std::vector < VulkanDescriptorSet > getDescriptorSetHandles () const noexcept;

        [[nodiscard]] const VLogicalDevice * getLogicalDevicePtr () const noexcept {
            return this->_pLogicalDevice;
        }

        void configure ( const std::vector < VUniformBuffer <T> > &, uint32 = 0U ) noexcept;
        void configure ( const VTexture&, const VTextureSampler &, uint32 = 0U ) noexcept;
    };

    typedef VDescriptorSet < uint8 > VSamplerDescriptorSet;
    typedef VDescriptorSetCollection < uint8 > VSamplerDescriptorSetCollection;
}

template <class T>
[[nodiscard]] std::vector < VulkanDescriptorSet > engine::VDescriptorSetCollection<T>::getDescriptorSetHandles () const noexcept {
    std::vector < VulkanDescriptorSet > handles;

    for ( auto & descriptorSet : this->_descriptorSets )
        handles.push_back( descriptorSet.data() );

    return handles;
}

inline static void populateDescriptorSetAllocateInfo (
        VulkanDescriptorSetAllocateInfo * pAllocateInfo,
        VulkanDescriptorPool              descriptorPool,
        uint32                            descriptorSetCount,
        const VulkanDescriptorSetLayout * pSetLayouts
) noexcept {
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
VulkanResult engine::VDescriptorSetCollection<T>::allocate(
        const VDescriptorPool & descriptorPool,
        const VulkanDescriptorSetLayout & descriptorSetBaseLayout
) noexcept {
    this->_autoIncrementDescriptorIndex = 0U;
    this->_pLogicalDevice = descriptorPool.getLogicalDevicePtr();
    auto swapChainImageCount = static_cast < uint32 > ( this->_pLogicalDevice->getSwapChain()->getImages().size() );

    std::vector < VulkanDescriptorSet >         descriptorSetHandles ( swapChainImageCount );
    std::vector < VulkanDescriptorSetLayout >   layouts ( swapChainImageCount, descriptorSetBaseLayout );

    VulkanDescriptorSetAllocateInfo             allocateInfo {};
    populateDescriptorSetAllocateInfo(
            & allocateInfo,
            descriptorPool.data(),
            swapChainImageCount,
            layouts.data()
    );

    VulkanResult allocateResult = vkAllocateDescriptorSets(
            this->_pLogicalDevice->data(),
            & allocateInfo,
            descriptorSetHandles.data()
    );

    if ( allocateResult != VulkanResult::VK_SUCCESS )
        return allocateResult;

    this->_descriptorSets.clear();
    for ( const auto & descriptorSetHandle : descriptorSetHandles )
        this->_descriptorSets.emplace_back( descriptorSetHandle, this->_pLogicalDevice );

    return VulkanResult::VK_SUCCESS;
}

static inline void populateDescriptorBufferInfo (
    VulkanDescriptorBufferInfo * pBufferInfo,
    VulkanBuffer                 uniformBufferHandle,
    uint32                       offset,
    uint32                       size
) noexcept {
    if ( pBufferInfo == nullptr )
        return;

    * pBufferInfo = VulkanDescriptorBufferInfo {
        .buffer = uniformBufferHandle,
        .offset = offset,
        .range  = size
    };
}

static inline void populateDescriptorImageInfo (
    VulkanDescriptorImageInfo * pImageInfo,
    VulkanImageLayout           layout,
    VulkanImageView             imageView,
    VulkanSampler               sampler
) noexcept {
    if ( pImageInfo == nullptr )
        return;

    * pImageInfo = VulkanDescriptorImageInfo {
            .sampler     = sampler,
            .imageView   = imageView,
            .imageLayout = layout
    };
}

static inline void populateWriteDescriptorSet (
    VulkanWriteDescriptorSet          * pWriteDescriptorSet,
    VulkanDescriptorSet                 destinationDescriptorSetHandle,
    VulkanDescriptorType                descriptorType,
    uint32                              destinationBinding,
    uint32                              destinationArrayElementIndex,
    const VulkanDescriptorBufferInfo  * pDescriptorBufferInfo,
    const VulkanDescriptorImageInfo   * pDescriptorImageInfo
) noexcept {
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
        .pTexelBufferView   = nullptr
    };
}

template <class T>
void engine::VDescriptorSetCollection<T>::configure(const std::vector<VUniformBuffer<T>> & uniformBuffers, uint32 descriptorIndex) noexcept {
    for ( uint32 it = 0; it < this->_descriptorSets.size(); it++ )
        this->_descriptorSets[it].configure ( uniformBuffers[ it ], this->_autoIncrementDescriptorIndex );
    this->_autoIncrementDescriptorIndex ++;
}

template <class T>
void engine::VDescriptorSetCollection<T>::configure(const VTexture & texture, const VTextureSampler & textureSampler, uint32 descriptorIndex) noexcept {
    for ( auto & descriptorSet : this->_descriptorSets )
        descriptorSet.configure ( texture, textureSampler, this->_autoIncrementDescriptorIndex );
    this->_autoIncrementDescriptorIndex ++;
}

template <class T>
auto engine::VDescriptorSet<T>::configure(
        VTexture        const & texture,
        VTextureSampler const & textureSampler,
        uint32                  descriptorIndex
) noexcept -> void {
    VulkanDescriptorImageInfo imageInfo {};
    populateDescriptorImageInfo(
        & imageInfo,
        texture.getLayout(),
        texture.getImageView().data(),
        textureSampler.data()
    );

    VulkanWriteDescriptorSet writeDescriptorSet{ };
    populateWriteDescriptorSet(
        & writeDescriptorSet,
        this->_handle,
        VulkanDescriptorType::VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER,
        descriptorIndex,
        0U,
        nullptr,
        & imageInfo
    );

    vkUpdateDescriptorSets( this->_pLogicalDevice->data(), 1U, & writeDescriptorSet, 0U, nullptr );
}

template <class T>
auto engine::VDescriptorSet<T>::configure(
        VUniformBuffer<T>   const & uniformBuffer,
        uint32                      descriptorIndex
) noexcept -> void {
    VulkanDescriptorBufferInfo bufferInfo {};
    populateDescriptorBufferInfo(
        & bufferInfo,
        uniformBuffer.data(),
        0U,
        sizeof ( T )
    );

    VulkanWriteDescriptorSet writeDescriptorSet{ };
    populateWriteDescriptorSet(
        & writeDescriptorSet,
        this->_handle,
        VulkanDescriptorType::VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,
        descriptorIndex,
        0U,
        & bufferInfo,
        nullptr
    );

    vkUpdateDescriptorSets( this->_pLogicalDevice->data() , 1U, & writeDescriptorSet, 0U, nullptr );
}

#endif //ENG1_VDESCRIPTORSET_HPP
