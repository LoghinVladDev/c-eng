//
// Created by vladl on 05/08/2020.
//

#include "VulkanTriangleApplication.hpp"
#include <VStdUtils.hpp>
#include <VStdUtilsDefs.h>
#include <map>
#include <SettingsSharedContainer.hpp>
#include <SettingOptionGraphics.hpp>

constexpr uint32 MAX_FRAMES_IN_FLIGHT = 2U;
const char* engine::VulkanTriangleApplication::DEFAULT_TITLE = "Vulkan Application";

uint32 currentFrame = 0U;

engine::VulkanTriangleApplication::VulkanTriangleApplication(uint32 width, uint32 height) noexcept :
    _width(width),
    _height(height){

}

/**
 * Vertices of a star, with colors
 */
const std::vector < engine::VVertex > starVertices = {

        { { -0.2f, -0.2f, 0.0f }, {0.3f, 0.3f, 0.3f} },
        { {  0.2f, -0.2f, 0.0f }, {0.3f, 0.3f, 0.3f} },
        { {  0.3f,  0.1f, 0.0f }, {0.3f, 0.3f, 0.3f} },
        { {  0.0f,  0.3f, 0.0f }, {0.3f, 0.3f, 0.3f} },
        { { -0.3f,  0.1f, 0.0f }, {0.3f, 0.3f, 0.3f} },

        { { 0.0f, -0.6f, 0.0f }, {1.0f, 0.0f, 0.0f} },
        { { 0.6f, -0.2f, 0.0f }, {0.0f, 1.0f, 0.0f} },
        { { 0.4f,  0.55f, 0.0f }, {0.0f, 0.0f, 1.0f} },
        { {-0.4f,  0.55f, 0.0f }, {0.0f, 1.0f, 1.0f} },
        { {-0.6f, -0.2f, 0.0f }, {1.0f, 1.0f, 0.3f} },
};

/**
 * Indices of the star object, triangles, in draw order CCW
 */
const std::vector < uint16 > starIndices = {

        0, 1, 4,
        1, 3, 4,
        1, 2, 3,

        0, 5, 1,
        1, 6, 2,
        2, 7, 3,
        3, 8, 4,
        4, 9, 0,
};

/**
 * Cube Vertices, with color ( 1.0, 1.0, 1.0 = no color modif. ), texture coords
 */
const std::vector < engine::VVertex > cubeVertices = {


        {{-0.5f, -0.5f,  0.5f}, {1.0f, 1.0f, 1.0f}, {0.0f, 0.0f}},
        {{ 0.5f, -0.5f,  0.5f}, {1.0f, 1.0f, 1.0f}, {1.0f, 0.0f}},
        {{ 0.5f,  0.5f,  0.5f}, {1.0f, 1.0f, 1.0f}, {1.0f, 1.0f}},
        {{-0.5f,  0.5f,  0.5f}, {1.0f, 1.0f, 1.0f}, {0.0f, 1.0f}},

        {{-0.5f, -0.5f, -0.5f}, {1.0f, 1.0f, 1.0f}, {0.0f, 1.0f}},
        {{ 0.5f, -0.5f, -0.5f}, {1.0f, 1.0f, 1.0f}, {1.0f, 1.0f}},
        {{ 0.5f,  0.5f, -0.5f}, {1.0f, 1.0f, 1.0f}, {1.0f, 0.0f}},
        {{-0.5f,  0.5f, -0.5f}, {1.0f, 1.0f, 1.0f}, {0.0f, 0.0f}},

        {{ 0.5f, -0.5f,  0.5f}, {1.0f, 1.0f, 1.0f}, {0.0f, 0.0f}},
        {{ 0.5f,  0.5f,  0.5f}, {1.0f, 1.0f, 1.0f}, {1.0f, 0.0f}},
        {{ 0.5f, -0.5f, -0.5f}, {1.0f, 1.0f, 1.0f}, {0.0f, 1.0f}},
        {{ 0.5f,  0.5f, -0.5f}, {1.0f, 1.0f, 1.0f}, {1.0f, 1.0f}},

        {{-0.5f, -0.5f,  0.5f}, {1.0f, 1.0f, 1.0f}, {0.0f, 1.0f}},  // 2
        {{-0.5f,  0.5f,  0.5f}, {1.0f, 1.0f, 1.0f}, {1.0f, 1.0f}}, // 3
        {{-0.5f, -0.5f, -0.5f}, {1.0f, 1.0f, 1.0f}, {0.0f, 0.0f}}, // 0
        {{-0.5f,  0.5f, -0.5f}, {1.0f, 1.0f, 1.0f}, {1.0f, 0.0f}}, // 1
};

/**
 * order of drawing, CCW, triangles
 */
const std::vector < uint16 > cubeIndices = {

        0,   1,  2,  2,  3,  0,
        1,   0,  5,  4,  5,  0,
        9,   8,  10, 10, 11, 9,
        3,   2,  7,  6,  7,  2,
        12,  13, 14, 15, 14, 13,
        4,   6,  5,  7,  6,  4
};

/**
 * @brief internal tests for queue families, acquiring queues and releasing them
 *
 * @param collection : engine::VQueueFamilyCollection cref = on which collection to test
 *
 * @static
 *
 * @exceptsafe
 */
static auto queueFamilyTests ( engine::VQueueFamilyCollection const & collection ) noexcept -> void {
    std::cout << "Available Queue Families : \n";

#ifndef NDEBUG
    collection.debugPrintQueueFamilies( std::cout, "\t" );
#endif

    std::cout << "Graphics Capable Queue Families on Device : \n";

#ifndef NDEBUG
    for ( const auto & queueFamily : collection.getGraphicsCapableQueueFamilies() ) {
        queueFamily->debugPrintQueueFamily(std::cout, "\t");
    }
#endif

/**
 * Do some queue reservation - free tests
 */

#ifndef NDEBUG
    collection.debugPrintQueueFamiliesReservations( std::cout );
#endif

    for ( const auto & queueFamily : collection.getQueueFamilies() ) {
        uint32 reservationTarget = 4U; /// reserve 4 queues if possible
        uint32 reservations = queueFamily.reserveQueues(reservationTarget);

        std::cout << "Managed to reserve " << reservations << " out of " << reservationTarget << " requested\n";
    }

#ifndef NDEBUG
    collection.debugPrintQueueFamiliesReservations( std::cout );
#endif

    const auto & selectedQueueFamily = collection.getQueueFamilies()[0];

    uint32 queuesToFree = 2U;

    std::cout << "Attempting to free " << queuesToFree << " queues from family with index " << selectedQueueFamily.getQueueFamilyIndex() << '\n';
    selectedQueueFamily.freeQueues(queuesToFree);

    for ( const auto & queueFamily : collection.getQueueFamilies()){
        uint32 reservationTarget = 8U;
        uint32 reservations = queueFamily.reserveQueues(reservationTarget);

        std::cout << "Managed to reserve " << reservations << " out of " << reservationTarget << " requested\n";
    }

    std::cout << "Freeing back all queues :\n";
    for ( const auto & queueFamily : collection.getQueueFamilies() ) {
        queueFamily.freeQueues( queueFamily.getQueueCount() );
    }

#ifndef NDEBUG
    collection.debugPrintQueueFamiliesReservations( std::cout );
#endif
}

#if !defined(_MSC_VER)
#pragma clang diagnostic push
#pragma ide diagnostic ignored "Simplify"
#pragma ide diagnostic ignored "UnreachableCode"
#endif
auto engine::VulkanTriangleApplication::setupDebugMessenger() noexcept (false) -> void {

    /// if validation layers are not enabled, do not setup messenger
    if ( ! enableValidationLayers ) return;

    VulkanResult res;

    if( ( res = this->_vulkanMessenger.setup ( & this->_vulkanInstance ) ) != VK_SUCCESS )
        throw std::runtime_error("debug messenger setup failure : " + engine::VStandardUtils::to_string(res));
}
#if !defined(_MSC_VER)
#pragma clang diagnostic pop
#endif

auto engine::VulkanTriangleApplication::initSettings() const noexcept -> void {
    auto resolution = engine::ResolutionSetting( this->_width, this->_height ); /// Create Resolution Setting based on current resolution from Class Variables

    engine::SettingsSharedContainer::getInstance().put( & resolution ); /// Save Resolution for reuse later in other classes
}

auto engine::VulkanTriangleApplication::updateResolutionSettings() noexcept -> void {
    int width = 0, height = 0;
    glfwGetFramebufferSize( this->_window, & width, & height ); // get current resolution
    while ( width == 0 || height == 0 ) { // while window is too small to render, acquire resolution
        glfwGetFramebufferSize( this->_window, & width, & height );
        glfwWaitEvents();
    }

    auto resolution = engine::ResolutionSetting( width, height );

    engine::SettingsSharedContainer::getInstance().put( & resolution ); //update resolution
}

auto engine::VulkanTriangleApplication::run() noexcept (false) -> void {
    this->initSettings();                   /// initialisation of settings ( resolution ... )
    this->initWindow();                     /// creation of window context
    this->initVulkan();                     /// creation of vulkan instance
    this->createShaderModules();            /// creation of shaders - Deprecated. Will be built by Precompiler
    this->createDescriptorSetLayout();      /// creation of layout of descriptors for CPU-GPU data - Deprecated. Will be build by Precompiler
    this->createGraphicsPipeline();         /// creation of graphical pipeline - A single Shader - ( GPU - queue - swapchain - screen )
    this->createCommandPool();              /// creation of command pool - any draw commands, allocated from a pool ( cached on gpu )
    this->createDepthBuffer();              /// creation of depth buffer - so that objects do not overlap. Objects closer to the camera will be rendered first
    this->createFrameBuffers();             /// creation of frame buffers - drawable buffers
    this->createTextureSampler();                 /// creation of texture objects - GPU data
    this->createGameObjects();              /// creation of EC Game Objects
    this->createBuffers();                  /// creation of Data Buffers - GPU - Vertex + Index + Uniform.
    this->createCommandBuffers();           /// creation of command buffers - GPU draw commands, pre-recorder for optimisation
    this->freeStagingBuffers();             /// free of staging buffers - copy buffers for CPU-GPU. Deprecated
    this->createSynchronizationElements();  /// creation of CPU-GPU sync elements - semaphores, fences, barriers
    this->mainLoop();                       /// start of MVC application
    this->cleanup();                        /// cleanup of all data created
}

auto static processInputCallback (GLFWwindow*, int, int, int, int) noexcept -> void;
auto static rawMouseInputCallback (GLFWwindow *, double, double ) noexcept -> void;

auto engine::VulkanTriangleApplication::initWindow() noexcept (false) -> void {
    if(glfwInit() == GLFW_FALSE) {
        throw engine::EngineVulkanTestException("GLFW Init failure"); /// if GLFW could not initialise, we cannot draw on a window
    }

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API); /// No OpenGL API, Vulkan is not self-configurable

    this->_window = glfwCreateWindow( /// Create Window from GLFW
        this->_width, // with width
        this->_height,// height
        VulkanTriangleApplication::DEFAULT_TITLE, // title
        nullptr, // any monitor
        nullptr    // not shared to any other instance / application
    );

    glfwSetInputMode(this->_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetWindowUserPointer( this->_window, this ); /// Set "this" as owner of window. Will be used to re-acquire "this" address in callback, since it is static
    glfwSetFramebufferSizeCallback( this->_window, engine::VulkanTriangleApplication::frameBufferResizeCallback ); /// Set Window Resize Callback
    glfwSetKeyCallback( this->_window, processInputCallback ); /// Set Keyboard Callback
    glfwSetCursorPosCallback(this->_window, rawMouseInputCallback);
}

auto engine::VulkanTriangleApplication::createSurface() noexcept(false) -> void {
    // surface created on window, linked to vulkan instance
    if( this->_vulkanSurface.setup(this->_window, this->_vulkanInstance) != VK_SUCCESS )
        throw std::runtime_error("failed to create vulkan surface");
}

/**
 * @brief getter for optimal queue families
 *
 * @param collection : engine::VQueueFamilyCollection cref = where to get queue families from
 *
 * @exceptsafe
 *
 * @static
 *
 * @return std::vector < engine::VQueueFamily const pointer > = vector of pointers to constant queue family
 */
static inline auto internalGatherGraphicsAndPresentQueueFamilies( engine::VQueueFamilyCollection const & collection ) noexcept -> std::vector < engine::VQueueFamily const * > {
    auto queueFamilies = collection.getFlagsCapableQueueFamilies(
            engine::VQueueFamily::GRAPHICS_FLAG |
            engine::VQueueFamily::PRESENT_FLAG |
            engine::VQueueFamily::TRANSFER_FLAG
    );  /// try gathering queue families capable of graphics, present and transfer. Rarely happens in specialised GPUs


    if( queueFamilies.empty() ) { /// if no jack-of-all-trades queue family is available, gather them individually
        queueFamilies.push_back( collection.getGraphicsCapableQueueFamilies()[0] ); // get first graphics capable queue family
        queueFamilies.push_back( collection.getPresentCapableQueueFamilies()[0] );  // get first present capable queue family
    }

    return queueFamilies;
}

#if !defined(_MSC_VER)
#pragma clang diagnostic push
#pragma ide diagnostic ignored "Simplify"
#pragma ide diagnostic ignored "UnreachableCode"
#endif
inline auto engine::VulkanTriangleApplication::initVulkan() noexcept (false) -> void {
    VExtensionCollection availableExtensions = VExtensionCollection::getAllAvailableExtensions(); /// Acquire supported Vulkan SDK Extensions

#ifndef NDEBUG
    if( VulkanTriangleApplication::VULKAN_EXT_CHECK ) // in debug, print extensions
        availableExtensions.debugPrint(std::cout );
#endif

    if( enableValidationLayers ) { // enabled in debug, disabled in release
        VValidationLayer::debugPrintAvailableValidationLayers(std::cout);

        std::cout << "\nRequested Validation Layers : \n";

        for( const auto & layer : this->_vulkanValidationLayerCollection.getValidationLayers() ) {
            std::cout << '\t' << layer.getLiteral() << '\n';
        }

        if( ! VValidationLayer::checkValidationLayerSupport(this->_vulkanValidationLayerCollection) ) {
            throw std::runtime_error("requested validation layers are not available!");
        }

        std::cout << "\nRequested Layers are available!\n";

        /// Initialise Vulkan WITH Validation Layers
        if ( this->_vulkanInstance.setup( this->_vulkanValidationLayerCollection ) != VK_SUCCESS ) {
            throw std::runtime_error ("failed to create Vulkan instance");
        }
    } else {
        /// Initialise Vulkan WITHOUT Validation Layers
        if ( this->_vulkanInstance.setup() != VK_SUCCESS )
            throw std::runtime_error ("failed to create Vulkan instance");
    }


    this->setupDebugMessenger(); /// Setup a Validation Layer Violation Error Callback
    this->createSurface();  /// Create a printable surface on the window for ImageBuffers
    this->autoPickPhysicalDevice(); /// Select Best GPU for the Engine

    std::cout << "Most Suitable GPU : \n";

#ifndef NDEBUG
    this->_vulkanPhysicalDevice.debugPrintPhysicalDeviceProperties( std::cout, true, "\t"); /// In debug, print best GPU
#endif

    /// Acquire Queue Families
    this->_vulkanQueueFamilyCollection = new VQueueFamilyCollection ( this->_vulkanPhysicalDevice, &this->_vulkanSurface );

    /// Do basic tests for Queue Allocation
    queueFamilyTests( * this->_vulkanQueueFamilyCollection );

    engine::VLogicalDevice::Factory::enableExceptions();
    engine::VLogicalDevice::Factory deviceFactory; /// Factory For Logical Device. Logical Device =
    ///                                              Physical Device (GPU) +
    ///                                              Queues Interface (CPU-GPU buses)
    ///                                              Swapchain Interface (GPU - Surface buses)

    /// If using validationLayers, build Logical Device + Validation Layers. We need the callbacks on the GPU
    if( enableValidationLayers )
        deviceFactory.withValidationLayers( this->_vulkanValidationLayerCollection );

    /// Gather CPU-GPU Buses capable of
    ///         Graphic Transfers ( Vertex, Index, Texture, Compression etc )
    ///         Present Transfers ( GPU Image -> Window Surface )
    auto queues = internalGatherGraphicsAndPresentQueueFamilies ( * this->_vulkanQueueFamilyCollection );

    if( queues.size() == 1 ) { // graphics & present queues in same family
    /// if only one queue capable of Graphics + Present, use exclusivity of memory for one queue family
        deviceFactory.addQueue(*queues[0], 1.0f);
        deviceFactory.addQueue(* this->_vulkanQueueFamilyCollection->getTransferCapableQueueFamilies()[0], 1.0f);
    }
    else {
    /// if one graphics and one present queue have been found, use concurrency of memory for both queue families
        deviceFactory.addQueue( * queues[0], 1.0f );
        deviceFactory.addQueue( * queues[1], 1.0f );
        deviceFactory.addQueue(* this->_vulkanQueueFamilyCollection->getTransferCapableQueueFamilies()[0], 1.0f);
    }

    /// Link to-be-created SwapChain to the Surface Created Previously
    deviceFactory.createSwapChainToSurface( & this->_vulkanSurface );

    this->_vulkanLogicalDevice = deviceFactory.build( this->_vulkanPhysicalDevice ); /// Build Logical Device
    std::cout << "Logical Device Handle : " << this->_vulkanLogicalDevice.data() << '\n';


    std::cout << "Queues : \n";
    for(const auto & queue : this->_vulkanLogicalDevice.getQueues()) {
        std::cout << "\tQueue :\n";
        std::cout << "\t\tHandler : " << queue.data() << "\n";
        std::cout << "\t\tFamily index : " << queue.getQueueFamily()->getQueueFamilyIndex() << '\n';
        std::cout << "\t\tIndex in Family : " << queue.getIndex() << '\n';
        std::cout << "\t\tPriority : " << queue.getPriority() << '\n';
    }

    std::cout << "Device Capable of Swapchain Ext : " << this->_vulkanPhysicalDevice.supportsExtension ( VExtension( VExtension::KHRONOS_SWAPCHAIN ) ) << '\n';

    std::cout << "Logical Device Capable of Swap Chain : " << this->_vulkanLogicalDevice.isSwapChainAdequate() << '\n';

    auto setting = engine::SettingsSharedContainer::getInstance().get(engine::SettingOption::RESOLUTION);

    if(setting != nullptr ) {
        auto resolution = dynamic_cast < const engine::ResolutionSetting* > ( setting );

        if ( resolution != nullptr ) {
            std::cout << "Saved res : " << resolution->getWidth() << ',' << resolution->getHeight() << '\n';
        }
    }
}

auto engine::VulkanTriangleApplication::createSynchronizationElements() noexcept(false) -> void {
    /// A semaphore for image draw finish per frame buffer
    if ( this->_imageAvailableSemaphores.setup( this->_vulkanLogicalDevice, MAX_FRAMES_IN_FLIGHT ) != VulkanResult::VK_SUCCESS )
        throw std::runtime_error ( "Semaphore Creation Failure : Image Availability" );
    /// A semaphore for each render on surface per each frame buffer
    if ( this->_renderFinishedSemaphores.setup( this->_vulkanLogicalDevice, MAX_FRAMES_IN_FLIGHT ) != VulkanResult::VK_SUCCESS )
        throw std::runtime_error ( "Semaphore Creation Failure : Render Finish" );

    /// Fences for synchronising semaphores and Logical Device busy scheduling. One per frame
    if ( this->_inFlightFences.setup( this->_vulkanLogicalDevice, MAX_FRAMES_IN_FLIGHT, engine::VFence::START_SIGNALED ) != VulkanResult::VK_SUCCESS )
        throw std::runtime_error ( "Fence Creation Failure" );
    this->_imagesInFlight.resize( static_cast<uint32>(this->_vulkanLogicalDevice.getSwapChain()->getImages().size()) );
}

#if !defined(_MSC_VER)
#pragma clang diagnostic pop
#endif

static HashMap < engine::VGameObject *, std::vector < engine::VVertex > const * > objectVertices;
static HashMap < engine::VGameObject *, std::vector < uint16 > const * > objectIndices;
static HashMap < engine::VGameObject *, String > objectTextureNames;

auto engine::VulkanTriangleApplication::createGameObjects() noexcept -> void {
    /***
     * Create Two Objects and Add them to the Active Scene
     * Will be loaded later from configurations - Saved Scenes -> json containing hierarchical data
     */

    auto cube = new VGameObject("cube");
    cube->add(new VTransform());
    cube->add(new VMesh());
    cube->add(new VMeshRenderer());

    auto cube2 = new VGameObject("cube2");
    cube2->add(new VTransform());
    cube2->add(new VMesh());
    cube2->add(new VMeshRenderer());

    auto star = new VGameObject("star");
    star->add(new VTransform());
    star->add(new VMesh());
    star->add(new VMeshRenderer());


    /// Move the star a bit above and to the left
    star->transform()->location().x -= 2.0f;
    star->transform()->location().z += 1.0f;
    star->transform()->location().y += 1.0f;

//    cube->transform()->location().y += 1.0f;
//    cube->transform()->location().z += 0.5;

    objectVertices[cube] = & cubeVertices;
    objectIndices[cube] = & cubeIndices;

    objectVertices[cube2] = & cubeVertices;
    objectIndices[cube2] = & cubeIndices;

    objectVertices[star] = & starVertices;
    objectIndices[star] = & starIndices;

    objectTextureNames[cube] = "container.jpg";
    objectTextureNames[cube2] = "container2.png";
    objectTextureNames[star] = "container3.jpg";

    star->add(cube);

//    this->_activeScene.add(cube);
    this->_activeScene.add(star); /// Add object to scene
    this->_activeScene.add(cube2);
    this->_activeScene.setActiveCamera(new VCamera({0.0f, 0.0f, 3.0f}));
}

auto engine::VulkanTriangleApplication::recreateSwapChain() noexcept(false) -> void {
    vkDeviceWaitIdle( this->_vulkanLogicalDevice.data() ); /// wait until GPU finishes drawing

    this->cleanupSwapChain(); /// Cleanup previous swapchain objects

    this->updateResolutionSettings(); /// Update global resolution according to new resolution

    /// attempt to recreate the swapchain. Throw std::runtime_error if not successful
    if ( this->_vulkanLogicalDevice.recreateSwapChain() != VulkanResult::VK_SUCCESS )
        throw std::runtime_error ( "Swap Chain Recreation Error" );

    /// attempt to recreate the pipeline used. Throw std::runtime_error if not successful
    ENG_THROW_IF_NOT_SUCCESS (
            this->_objectShader.recreateShader(),
            ENG_STD_THROW( "shader recreation failure" )
    )

    this->createDepthBuffer(); /// recreate the depth test buffer
    this->createFrameBuffers();/// recreate the frame buffers

    this->createDescriptorPool();/// recreate the descriptor pools and mesh renderers ( descriptor pool sets )

    for ( auto * pComponent : this->_activeScene.componentsOfClass("VMeshRenderer") )
        dynamic_cast<VMeshRenderer *>(pComponent)->recreate();

    this->createCommandBuffers(); /// recreate draw commands
}

auto engine::VulkanTriangleApplication::cleanupSwapChain() noexcept -> void {
    this->_depthBuffer.cleanup(); /// clean depth test buffer
    this->_frameBufferCollection.cleanup(); /// clean all framebuffers
    this->_drawCommandBufferCollection.free(); /// free all draw buffers

    for ( auto * pComponent : this->_activeScene.componentsOfClass("VMeshRenderer") )
        dynamic_cast<VMeshRenderer *>(pComponent)->cleanupUniformBuffers(); /// cleanup all uniform buffers

    this->_descriptorPool.cleanup(); /// cleanup all descriptors

    this->_objectShader.getPipeline().cleanup(); /// cleanup pipeline

    this->_vulkanLogicalDevice.cleanupSwapChain(); /// cleanup swap chain from logical device
}

auto engine::VulkanTriangleApplication::frameBufferResizeCallback(GLFWwindow * pWindow, [[maybe_unused]] int32 width, [[maybe_unused]] int32 height) noexcept -> void {
    auto * baseObj = reinterpret_cast< engine::VulkanTriangleApplication * > ( glfwGetWindowUserPointer( pWindow ) );
    baseObj->_framebufferResized = true;

    /// we get "this" address by obtaining the address associated with the window and toggle the resized variable
    /// specifying that next draw has to recreate the swapchain
}

auto engine::VulkanTriangleApplication::drawImage () noexcept (false) -> void {
    vkWaitForFences(
        this->_vulkanLogicalDevice.data(), /// on this GPU
        1U,
        & this->_inFlightFences[ currentFrame ].data(), /// wait for this image's sync elements ( fence )
        VK_TRUE, /// TRUE = wait for all ( only waiting on 1 , this image's fence )
        UINT64_MAX /// timeout for wait
    ); /// wait for this image's fence to be available

    uint32 imageIndex;
    VulkanResult acquireImageResult = vkAcquireNextImageKHR(
        this->_vulkanLogicalDevice.data(), /// from this GPU
        this->_vulkanLogicalDevice.getSwapChain()->data(), /// from the swapchain
        UINT64_MAX, /// indefinetly
        this->_imageAvailableSemaphores[ currentFrame ].data(), /// trigger this when image is available
        VK_NULL_HANDLE, /// do not
        & imageIndex /// index of the acquired image
    ); /// acquire the current image

    if ( acquireImageResult == VulkanResult::VK_ERROR_OUT_OF_DATE_KHR ) {
        this->recreateSwapChain(); /// recreate swapchain if out of date
        return;
    } else if ( acquireImageResult != VulkanResult::VK_SUCCESS ) /// throw std::runtime_error if error
        throw std::runtime_error ( "Image Acquisition Failure" );

    if ( ! this->_imagesInFlight [ imageIndex ].empty() ) {
        vkWaitForFences(
            this->_vulkanLogicalDevice.data(), /// on this GPU
            1U,
            & this->_imagesInFlight[ imageIndex ].data(), /// this image's fence
            VK_TRUE, /// all fences
            UINT64_MAX /// wait indefinetly
        );
    } /// if an image is being sent to the surface, wait for it

    this->updateUniformBuffer( imageIndex );  /// update of uniform buffer data for the GPU

    this->_imagesInFlight[ imageIndex ] = this->_inFlightFences [ currentFrame ]; /// this becomes the image next to be sent

    VkPipelineStageFlags waitStages[] = { VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT }; /// semaphore wait stages : signal when
                                                                                        /// "color attachment" is output'ed - end of fragment shader

    /// submit draw command
    if ( this->_drawCommandBufferCollection.getCommandBuffers()[ imageIndex ].submit(
            waitStages, /// signal upon fragment shader end
            & this->_imageAvailableSemaphores[ currentFrame ], /// start when image is avaiable
            1U,
            & this->_renderFinishedSemaphores[ currentFrame ], /// trigger when render is finished
            1U,
            & this->_inFlightFences[ currentFrame ]            /// bind these to this image's status
        ) != VulkanResult::VK_SUCCESS
    ) /// if command submit fails, throw std::runtime_error
        throw std::runtime_error ( "Command Buffer Submit Failure" );

    /// present image on swap chain
    VulkanResult presentResult = this->_vulkanLogicalDevice.getSwapChain()->present(
            & this->_renderFinishedSemaphores[ currentFrame ], /// start when render is finished
            1U, imageIndex /// draw image associated with current synchronisation elements
    );

    if (
        presentResult == VulkanResult::VK_ERROR_OUT_OF_DATE_KHR || /// desynchronisation of the swapchain OR
        presentResult == VulkanResult::VK_SUBOPTIMAL_KHR ||        /// swapchain overloaded               OR
        this->_framebufferResized                                  /// window resized toggle
    ) {
        this->_framebufferResized = false;                         /// toggle off recreation
        this->recreateSwapChain();                                 /// recreate
    }
    else if ( presentResult != VulkanResult::VK_SUCCESS ) /// if any other error, throw std::runtime_error
        throw std::runtime_error ( "Swap Chain Present Failure" );

    currentFrame = ( currentFrame + 1 ) % MAX_FRAMES_IN_FLIGHT; /// increment frame index
}

/**
 * variables used in testing
 */
bool left = false; ///^
bool right = false;///<
bool up = false;   ///>
bool down = false; ///!^

static bool moveUp = false;
static bool moveDown = false;
static bool moveLeft = false;
static bool moveRight = false;

#include <chrono>
#include <glm/gtc/matrix_transform.hpp>
auto engine::VulkanTriangleApplication::updateUniformBuffer(uint32 uniformBufferIndex) noexcept -> void {
    static float FOV = 90.0f; /// Field Of View of Camera

    /**
     * Uniform Buffer =
     *  * at least an MVP
     *      Reason : Objects have static vertices on GPU
     *               Each GPU core will make calculations for ONE single vertex at a time
     *               GPU has to use data to "move" vertex, "color" vertex, etc.
     *
     *
     *      MVP matrix = Model View Projection Matrix
     *          - Contains one 4x4 matrix representing the current view - camera location
     *          - Contains one 4x4 matrix representing projection of the view
     *          - Contains one 4x4 matrix representing the model of the object
     *      When multiplied with the vertex coordinates, the output is the vertex coordinates as if seen
     *          from our eyes (located at 0,0,0 - screen coordinates)
     *      The equation <=> projVertex = projection * view * model * ( vertexCoordinates.xyz, 1.0f );
     *      The GPU's cores do matrix 4x4 * matrix 4x4 and matrix 4x4 * vector 4x4 fast, by default
     *
     *      3d coordinates are stored in a matrix like this :
     *
     *      vec3 (x, y, z) -> mat4 ( x, 0, 0, 0
     *                               0, y, 0, 0
     *                               0, 0, z, 0
     *                               0, 0, 0, 0 )
     */


    glm::mat4 view;

    if ( this->_activeScene.activeCamera() != nullptr )
        view = this->_activeScene.activeCamera()->viewMatrix();
    else
        view = glm::lookAt(
                glm::vec3(2.0f, 2.0f, 2.0f), /// current camera position ( "eyes" )
                glm::vec3(0.0f, 0.0f, 0.0f), /// center position ( "where we want to look, center" )
                glm::vec3(0.0f, 0.0f, 1.0f)   /// normal of the camera. Orientation
        ); /// view matrix = 4x4 matrix

    auto projection = glm::perspective (
            glm::radians ( FOV ), /// with this FOV in radians
            this->_vulkanLogicalDevice.getSwapChain()->getImagesInfo().extent.width / /// projected on our width / heigth ( aspect ratio )
            (float) this->_vulkanLogicalDevice.getSwapChain()->getImagesInfo().extent.height,
            0.1f, /// clip start ( objects behind will not be projected )
            10.0f  /// clip end ( objects far will not be projected )
    );

    projection[1][1] *= -1; /// reverse y component of projection, as GLM library was designed for OpenGL, and we use Vulkan
                            /// in OpenGL, the drawing is reversed at y axis level

    glm::mat4 baseModel (1.0f); /// all objects start as base model x = 1.0f, y = 1.0f, z = 1.0f

    /**
     * We will apply local transformations to the Uniform Buffer Object's model matrix as follows :
     *      base model = 1.0f
     *      translate to location()
     *      rotate with rotation() - needs to be done for each axis
     *          rotate yaw   - around x axis
     *          rotate pitch - around y axis
     *          rotate roll  - around z axis
     *      scale to scale()
     */
    for ( auto * pEntity : this->_activeScene.entitiesOfClass("VGameObject") ) {
        auto pGameObject = dynamic_cast < VGameObject * > (pEntity);
        if ( ! pGameObject->isDrawable() )
            continue;

        auto transform = this->_activeScene.transformInScene( pGameObject );

        engine::SUniformBufferObject UBO {
            .model = glm::scale( /// scale with scale
                glm::rotate( /// rotate roll
                    glm::rotate ( /// rotate pitch
                        glm::rotate( /// rotate yaw
                            glm::translate(baseModel, transform.location()),
                            glm::radians(transform.rotation().roll()), glm::vec3(1.0f, 0.0f, 0.0f)
                        ),
                        glm::radians(transform.rotation().yaw()), glm::vec3(0.0f, 1.0f, 0.0f)
                    ),
                    glm::radians(transform.rotation().pitch()), glm::vec3(0.0f, 0.0f, 1.0f)
                ),
                transform.scale()
            ),
            .view       = view,
            .projection = projection
        };

        /// acquire current renderer uniform buffer
        auto & currentBuffer = pGameObject->meshRendererPtr()->getMVPDescriptorBuffers()[ uniformBufferIndex ];
        currentBuffer.load( & UBO, 1U ); /// load the uniform buffer object
    }
}

auto rawMouseInputCallback (
        GLFWwindow * pWindow,
        double xPos,
        double yPos
) noexcept -> void {
    static bool firstCallback = true;
    static float lastXPos;
    static float lastYPos;
    static float xOffset;
    static float yOffset;

    constexpr static float sensitivity = 0.1f;

    if ( firstCallback ) {
        lastXPos = static_cast < float > (xPos);
        lastYPos = static_cast < float > (yPos);
        firstCallback = false;
    }

    xOffset = (static_cast < float > (xPos) - lastXPos) * sensitivity;
    yOffset = (lastYPos - static_cast < float > (yPos)) * sensitivity;

    lastXPos = static_cast < float > (xPos);
    lastYPos = static_cast < float > (yPos);

//    std::cout << ((engine::VulkanTriangleApplication *)glfwGetWindowUserPointer(pWindow))->scene().activeCamera()->toString() << '\n';
    ((engine::VulkanTriangleApplication *)glfwGetWindowUserPointer(pWindow))->scene().activeCamera()->collectRawInput(xOffset, yOffset);
}

/**
 * @brief internal callback function for key presses
 *
 * @param window : GLFWwindow pointer = window on which a keypress has been detected
 * @param key : int = keyPress in GLFW values
 * @param scanCode : int = actual scancode of key ( keyboard code )
 * @param action : int = action of the key = pressed, released, repeat
 * @param mods : int = modifiers of key = CTRL | SHIFT | ALT or any combination of these
 *
 * @static
 *
 * @exceptsafe
 */
auto processInputCallback (GLFWwindow* window, int key, int scanCode, int action, int mods) noexcept -> void { /// rudimentary input callback
    if ( action == GLFW_PRESS ) {
        if ( key == GLFW_KEY_LEFT )
            left = true;
        if ( key == GLFW_KEY_RIGHT )
            right = true;
        if ( key == GLFW_KEY_UP )
            up = true;
        if ( key == GLFW_KEY_DOWN )
            down = true;

        if ( key == GLFW_KEY_W )
            moveUp = true;
        if ( key == GLFW_KEY_S )
            moveDown = true;
        if ( key == GLFW_KEY_D )
            moveRight = true;
        if ( key == GLFW_KEY_A )
            moveLeft = true;
    } else if ( action == GLFW_RELEASE ) {
        if ( key == GLFW_KEY_LEFT )
            left = false;
        if ( key == GLFW_KEY_RIGHT )
            right = false;
        if ( key == GLFW_KEY_UP )
            up = false;
        if ( key == GLFW_KEY_DOWN )
            down = false;

        if ( key == GLFW_KEY_W )
            moveUp = false;
        if ( key == GLFW_KEY_S )
            moveDown = false;
        if ( key == GLFW_KEY_D )
            moveRight = false;
        if ( key == GLFW_KEY_A )
            moveLeft = false;
    }
}

auto engine::VulkanTriangleApplication::update() noexcept -> void {
    /// interactions with objects periodically
    auto pCube = dynamic_cast<VGameObject *>(this->_activeScene.getGameObjectByName("cube"));
    if ( pCube == nullptr ) return;

    if ( left )
        pCube->transform()->rotation().rotate(VRotor::ROLL, 90.0f * static_cast<float>(this->_deltaTime));

    if ( right )
        pCube->transform()->rotation().rotate(VRotor::ROLL, - 90.0f * static_cast<float>(this->_deltaTime));


    if ( up )
        pCube->transform()->rotation().rotate(VRotor::YAW, 90.0f * static_cast<float>(this->_deltaTime));

    if ( down )
        pCube->transform()->rotation().rotate(VRotor::YAW, - 90.0f * static_cast<float>(this->_deltaTime));

    auto pStar = dynamic_cast<VGameObject *>(this->_activeScene.getGameObjectByName("star"));

    pStar->transform()->rotation().rotate(VRotor::PITCH, 180.0f * static_cast<float>(this->_deltaTime));

    /// call of update for each GameObject
    for ( auto * pGameObject: this->_activeScene.entitiesOfClass("VGameObject") )
        dynamic_cast < VGameObject * > (pGameObject)->update( static_cast <float>(this->_deltaTime)  );

    constexpr static float movementSpeed = 3.0f;
    float velocity = movementSpeed * this->_deltaTime;
    float camY = this->_activeScene.activeCamera()->transform()->location().y;

    if ( moveUp && moveDown ) {
        /// do nothing
    } else if ( moveUp ) {
        this->_activeScene.activeCamera()->transform()->location() += this->_activeScene.activeCamera()->worldFront() * velocity;
    } else if ( moveDown ) {
        this->_activeScene.activeCamera()->transform()->location() -= this->_activeScene.activeCamera()->worldFront() * velocity;
    }

    if ( moveLeft && moveRight ) {
        /// do nothing
    } else if ( moveLeft ) {
        this->_activeScene.activeCamera()->transform()->location() -= this->_activeScene.activeCamera()->right() * velocity;
    } else if ( moveRight ) {
        this->_activeScene.activeCamera()->transform()->location() += this->_activeScene.activeCamera()->right() * velocity;
    }
}

auto engine::VulkanTriangleApplication::mainLoop() noexcept (false) -> void {
    while ( ! glfwWindowShouldClose( this->_window ) ) { /// while window is active
        double startFrameTime = glfwGetTime(); /// get current time accurately

        glfwPollEvents(); /// poll all interrupting events - Window Minimise, Window Resize, Key Press etc.
        this->update(); /// Periodic call per frame for each object
        this->drawImage(); /// Periodic call to draw a free image

        this->_deltaTime = ( glfwGetTime() - startFrameTime ); /// Calculate frame time

        this->_fpsTimer += this->_deltaTime;

        if ( this->_fpsTimer >= this->_fpsRefreshTimer ) {
            if ( VulkanTriangleApplication::SHOW_FPS_CONSOLE ) {
                std::cout << "FPS : " << (1.0 / this->_deltaTime) << '\n';
            }
            this->_fpsTimer = 0.0;
        }
    }
    vkDeviceWaitIdle( this->_vulkanLogicalDevice.data() ); /// Wait until GPU draw Task is finished before closing
}

auto engine::VulkanTriangleApplication::createBuffers() noexcept(false) -> void {
    /**
     * Based on configuration on logical device, we use memory exclusivity if only one graphics queue
     * has been found for Graphics and Present Transfers.
     * Otherwise, we use concurrency
     */
    if ( this->_vulkanQueueFamilyCollection->getQueueFamilies().size() == 1 ) {
        this->createExclusiveBuffers();
    } else if ( this->_vulkanQueueFamilyCollection->getQueueFamilies().size() > 1 ) {
        this->createConcurrentBuffers();
    }
}

auto engine::VulkanTriangleApplication::createDepthBuffer() noexcept(false) -> void {
    /// Create Depth Buffer, Deciding which object display order. Requires Queue Family Indices
    auto queueFamilyIndices = this->_vulkanQueueFamilyCollection->getQueueFamilyIndices();
    ENG_THROW_IF_NOT_SUCCESS(
            this->_depthBuffer.setup(
                    this->_transferCommandPool,
                    queueFamilyIndices.data(),
                    static_cast<uint32>(queueFamilyIndices.size()) /// queue families are required to select a queue
                                                                   /// for transfer
            ),
            std::runtime_error("depth buffer create failure")
    )
}

auto engine::VulkanTriangleApplication::createConcurrentBuffers() noexcept(false) -> void {
    this->_activeScene.entitiesOfClass("VGameObject").forEach([this](VEntity * pEntity){
        auto pGameObject = dynamic_cast < VGameObject * > (pEntity);

        if ( pGameObject == nullptr || ! pGameObject->isDrawable() )
            return;

        ENG_THROW_IF_NOT_SUCCESS(
            pGameObject->meshPtr()->setup(
                this->_transferCommandPool,
                * this->_vulkanQueueFamilyCollection,
                * objectVertices[pGameObject],
                * objectIndices[pGameObject]
            ),
            ENG_STD_THROW("Object Mesh Setup Error")
        )
    });

    this->createUniformBuffers();
}

auto engine::VulkanTriangleApplication::createTextureSampler() noexcept(false) -> void {
    /// Create and Load Texture Sampler. Use Default Anisotropy = 16. Configurable Later
    auto anisotropyLevel = 16.0f;

    ENG_THROW_IF_NOT_SUCCESS(
            this->_textureSampler.setup(
                this->_vulkanLogicalDevice, /// sample textures loaded on GPU
                true,                       /// anisotropy toggle
                anisotropyLevel             /// anisotropy value
            ),
            std::runtime_error("sampler create error")
    )
}

auto engine::VulkanTriangleApplication::createDescriptorSets() noexcept(false) -> void {
    this->_activeScene.entitiesOfClass("VGameObject").forEach([this](VEntity * pEntity){
        auto pGameObject = dynamic_cast<VGameObject *>(pEntity);

        if ( pGameObject == nullptr || ! pGameObject->isDrawable() )
            return;

        ENG_THROW_IF_NOT_SUCCESS(
            pGameObject->meshRendererPtr()->setup(
                this->_transferCommandPool,
                this->_descriptorPool,
                this->_objectShader,
                String(__TEXTURES_PATH__).append(objectTextureNames[pGameObject]).cStr(),
                this->_textureSampler,
                * this->_vulkanQueueFamilyCollection
            ),
            ENG_STD_THROW("Mesh Renderer Create Failure")
        )
    });
}

auto engine::VulkanTriangleApplication::createDescriptorPool() noexcept(false) -> void {
    std::vector < VulkanDescriptorType > descriptorTypes;

    for ( const auto & type : this->_objectShader.getDescriptorTypeLayout() ) {
        descriptorTypes.push_back( type ); /// to create the pool, get a layout from the pipeline
    }

    /// number of objects that will use individual descriptors - individual buffers on the pipeline.
    /// make a descriptor set for each
    uint32 objectCount = static_cast<uint32>(this->_activeScene.entitiesOfClass("VGameObject").count([](VEntity * pObj){return ((VGameObject *)pObj)->isDrawable();}));

    ENG_THROW_IF_NOT_SUCCESS (
        this->_descriptorPool.setup (
            this->_vulkanLogicalDevice, /// on this GPU
            descriptorTypes.data(),     /// with this layout
            static_cast < uint32 > (descriptorTypes.size()), /// number of sets described on layout
            objectCount                 /// number of objects
        ),
        std::runtime_error ( "Descriptor Pool Creation Failure" )
    )

}

auto engine::VulkanTriangleApplication::createUniformBuffers() noexcept(false) -> void {
    this->createDescriptorPool();
    this->createDescriptorSets();
}

auto engine::VulkanTriangleApplication::createExclusiveBuffers() noexcept(false) -> void {
    throw std::runtime_error("Exclusive Buffer Objects not Implemented");
    this->createUniformBuffers();
}

#if !defined(_MSC_VER)
#pragma clang diagnostic push
#pragma ide diagnostic ignored "Simplify"
#endif
auto engine::VulkanTriangleApplication::cleanup() noexcept -> void {
    /**
     * Free and cleanup objects in reverse allocation + creation order
     */

    this->_imageAvailableSemaphores.cleanup();
    this->_renderFinishedSemaphores.cleanup();
    this->_inFlightFences.cleanup();

    this->_commandPool.cleanup();
    this->_transferCommandPool.cleanup();

    this->_depthBuffer.cleanup();
    this->_frameBufferCollection.cleanup();

    for ( auto * pComponent : this->_activeScene.componentsOfClass("VMeshRenderer") )
        dynamic_cast<VMeshRenderer *>(pComponent)->cleanup();

    this->_textureSampler.cleanup();
    this->_descriptorPool.cleanup();
    this->_objectShader.cleanup();

    for ( auto * pComponent : this->_activeScene.componentsOfClass("VMesh") ) {
        auto * pMesh = dynamic_cast<VMesh *>(pComponent);

        pMesh->free();
        pMesh->cleanup();
    }

    this->_vulkanLogicalDevice.cleanup();

    delete this->_vulkanQueueFamilyCollection;

    if( enableValidationLayers )
        this->_vulkanMessenger.clean();

    this->_vulkanSurface.clean();
    this->_vulkanInstance.clean();

    glfwDestroyWindow(this->_window);

    glfwTerminate();
}

auto engine::VulkanTriangleApplication::createCommandPool() noexcept(false) -> void {
    /// Create Two Command Pools. One for Drawing, One for Transfer to Screen
    if ( this->_commandPool.setup( this->_vulkanLogicalDevice ) != VulkanResult::VK_SUCCESS )
        throw std::runtime_error ( "Command Pool Creation Error" );
    if ( this->_transferCommandPool.setup( this->_vulkanLogicalDevice, this->_vulkanLogicalDevice.getFirstTransferQueuePtr()->getQueueFamily() ) != VulkanResult::VK_SUCCESS )
        throw std::runtime_error ( "Transfer Command Pool Creation Error" );
}

auto engine::VulkanTriangleApplication::createCommandBuffers() noexcept(false) -> void {
    /**
     * Creation of Command Buffers - Draw Commands
     *
     * First they are allocated onto the Frame Buffers, give an Output
     * Allocated from a Pool
     */
    if ( this->_drawCommandBufferCollection.allocate( this->_commandPool, this->_frameBufferCollection ) != VulkanResult::VK_SUCCESS )
        throw std::runtime_error ( "Command Buffers Allocation Error" );

    VulkanDeviceSize offsets [] = { 0 };

    auto drawableGameObjects = this->_activeScene.entitiesOfClass("VGameObject").view()
            .filter([](VEntity * pEntity) -> bool { return ((VGameObject * )pEntity)->isDrawable(); })
            .toArray();

    /// Input Data
    /**
     * Vertices of Objects - vertexBuffers
     * Indices of Vertices - Order of line drawing. - indexBuffers
     * layout of vertices, indices, model view projection matrix, textures on the CPU-GPU bus ( queue ) - object descriptor handles
     */
    auto vertexBuffers              = new VVertexBuffer[drawableGameObjects.size()];
    auto indexBuffers               = new VIndexBuffer[drawableGameObjects.size()];
    auto objectDescriptorSetHandles = new std::vector < VulkanDescriptorSet > [drawableGameObjects.size()];

    Index i = 0;
    for ( auto * o : drawableGameObjects ) {
        auto * pGameObject = dynamic_cast<VGameObject *>(o);

        vertexBuffers[i]                = pGameObject->meshPtr()->getVertexBuffer();
        indexBuffers[i]                 = pGameObject->meshPtr()->getIndexBuffer();
        objectDescriptorSetHandles[i]   = pGameObject->meshRendererPtr()->getDescriptorSets().getDescriptorSetHandles();

        i++;
    }

    /**
     * Same handles as above, but rearranged as follows :
     * Previous Arrangement : Array of [FrameBufferCount] Array per Object
     * Current Arrangement : Array of Object Descriptor Set Array per Frame Buffer Image
     */
    std::vector < VulkanDescriptorSet * > descriptorSetHandles ( this->_drawCommandBufferCollection.getCommandBuffers().size());
    for (uint32 j = 0; j < descriptorSetHandles.size(); j++ ) {
        descriptorSetHandles[j]     = new VulkanDescriptorSet[drawableGameObjects.size()];
        for (Index k = 0; k < drawableGameObjects.size(); k++ )
            descriptorSetHandles[j][k] = objectDescriptorSetHandles[k][j];
    }

    /**
     * Record Drawing Buffer for each FrameBuffer
     */
    if ( this->_drawCommandBufferCollection.startRecord(
            this->_objectShader.getPipeline(), /// on this shader's pipeline
            vertexBuffers,                     /// for all objects' vertices involved in this shader's drawing
            indexBuffers,                      /// draw in this order
            drawableGameObjects.size(),                /// for this many objects
            offsets,                           /// offsets ( if two objects have vertices in same buffer )
            1U,                                /// offset Count
            descriptorSetHandles.data(),       /// descriptor sets handles - to load Uniforms and Textures
            static_cast < uint32 > ( descriptorSetHandles.size() ) /// number of descriptor set handles
        ) != VulkanResult::VK_SUCCESS )
        throw std::runtime_error ( "Command Buffers Record Error" );

    /// clean up dynamically allocated resources
    for ( auto & handles : descriptorSetHandles )
        delete [] handles;

    delete [] vertexBuffers;
    delete [] indexBuffers;
    delete [] objectDescriptorSetHandles;
}

auto engine::VulkanTriangleApplication::autoPickPhysicalDevice() noexcept(false) -> void {
    /// acquire all the render devices the vulkan instance detects
    auto devices = VPhysicalDevice::getAvailablePhysicalDevices( this->_vulkanInstance );
    const VPhysicalDevice * bestDevice = nullptr;
    uint32 maxDeviceRating = 0U;

    /// get the device with the best rating. Heavy bias towards dedicated GPU's
    for ( const auto & device : devices ) {
        uint32 rating = device.getPhysicalDeviceRenderRating();
        if( rating > maxDeviceRating ) {
            maxDeviceRating = rating;
            bestDevice = & device;
        }
    }

    /// if no vulkan capable GPU is found, throw std::runtime_error
    if( bestDevice == nullptr )
        throw std::runtime_error ( "failed to find a suitable GPU" );

    this->_vulkanPhysicalDevice = ( * bestDevice );
}

auto engine::VulkanTriangleApplication::createGraphicsPipeline() noexcept(false) -> void {
    VShaderCompiler compiler; /// Create a Precompiler

    /// Use JSON Configuration for shader data
    compiler.setConfigurationFileJSON( std::string(__VULKAN_SHADERS_PATH__).append("/config/vkTriangleShaderComp.json") );
    compiler.build(); /// Build Shaders in outputs mentioned in JSON Configuration
    ENG_THROW_IF_NOT_SUCCESS (
            this->_objectShader.setup(  ///Setup Shader for GPU
                    this->_vulkanLogicalDevice, /// on this GPU
                    compiler,                   /// using this compiler
                    "defObj"                    /// tags to look for, this shader uses defObj as tag. it is vertex + fragment at the moment
            ),
            ENG_STD_THROW("shader creation error")
    )

}

auto engine::VulkanTriangleApplication::createFrameBuffers() noexcept(false) -> void {
    /// Create Frame Buffers - Images that will be swapped in flight, used by Double or Triple Buffering ( currently enabled - Triple )
    if ( this->_frameBufferCollection.setup ( this->_objectShader.getRenderPassPtr(), & this->_depthBuffer ) != VulkanResult::VK_SUCCESS )
        throw std::runtime_error ( "Frame Buffers Creation Failure" );
}

#if !defined(_MSC_VER)
#pragma clang diagnostic pop
#endif