//
// Created by loghin on 08.03.2022.
//

#ifndef __C_ENG_CONTEXT_MANAGER_HPP__
#define __C_ENG_CONTEXT_MANAGER_HPP__

#include <calls/VulkanAPICallsTypes.hpp>
#include <CDS/Mutex>
#include <CDS/LockGuard>
#include <CDS/Long>
#include <CDS/Double>
#include <Logger.hpp>

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
#define C_ENG_MAP_START     HEADER
#include <ObjectMapping.hpp>

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED
inline static auto dumpToString ( SharedContext const & ) noexcept -> cds :: String;
#endif


class ContextManager {
private:
    struct Context {
    private:
        bool            inUse;
        friend class ContextManager;

    public:
        SharedContext   data;
    };

    static inline Context       contexts [ engine :: vulkan :: config :: contextCount ];
    static inline cds :: Mutex  contextLock;
    static inline bool          firstCall = true;

    class ContextHolder {
    private:
        friend class ContextManager;
        Context * pContext { nullptr };

        explicit ContextHolder ( Context * pContext ) noexcept :
                pContext ( pContext ) {

        }

    public:
        ~ContextHolder () noexcept {
            cds :: LockGuard guard ( contextLock );

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED
            if ( this->pContext->data.common.common.diag.error != engine :: vulkan :: ResultSuccess ) {
                engine :: Type ( Logger ) :: instance().error ( cds :: String::f (
                        "API Error logged in context at release : %s, in %s -> %s : %d ---> %s",
                        toString ( pContext->data.common.common.diag.error ),
                        pContext->data.common.common.diag.file,
                        pContext->data.common.common.diag.function,
                        pContext->data.common.common.diag.line,
                        pContext->data.common.common.diag.pMessage == nullptr ? "no details given" : pContext->data.common.common.diag.pMessage->cStr()
                ));

                cds :: Memory :: instance().destroy ( pContext->data.common.common.diag.pMessage );

                this->pContext->data.common.common.diag.error = engine :: vulkan :: ResultSuccess;
            }

            switch ( engine :: vulkan :: config :: coreDumpType ) {
                case engine :: vulkan :: config :: CoreDumpType :: DumpOnError:
                    if ( this->pContext->data.common.common.diag.error == engine :: vulkan :: ResultSuccess ) {
                        break;
                    }

                    __CDS_Fallthrough;
                case engine :: vulkan :: config :: CoreDumpType :: DumpAll:
                    (void) engine :: Type ( Logger ) :: instance().debug (
                            dumpToString ( pContext->data )
                    );

                case engine :: vulkan :: config :: CoreDumpType :: NoDump:
                    break;
            }

            pContext->data.common.common.dump.contextType            = ContextType :: None;
            pContext->data.common.common.dump.apiFunction            = nullptr;
            pContext->data.common.common.dump.apiFunctionDescription = nullptr;
            pContext->data.common.common.dump.paramCount             = 0U;
#endif

            if ( this->pContext->data.common.common.ruleSet.onDelete != nullptr ) {
                this->pContext->data.common.common.ruleSet.onDelete ( reinterpret_cast < GenericContext * > ( & this->pContext->data ) );
            }

            this->pContext->data.common.common.ruleSet.onDelete = nullptr;

            this->pContext->inUse = false;
        }

        ContextHolder ( ContextHolder && holder ) noexcept :
                pContext ( cds :: exchange ( holder.pContext, nullptr ) ) {

        }

        inline auto operator = ( ContextHolder && holder ) noexcept -> ContextHolder & {
            if ( this == & holder ) {
                return * this;
            }

            this->pContext = cds :: exchange ( holder.pContext, nullptr );
            return * this;
        }

        constexpr auto data () noexcept -> SharedContext & {
            return this->pContext->data;
        }

        constexpr auto operator -> () noexcept -> SharedContext * {
            return & this->pContext->data;
        }
    };

public:
    static auto logContextSizes () noexcept -> void {

#define LOG_CONTEXT_SIZE(_context, _depth) (void) engine :: Type ( Logger ) :: instance().debug ( cds :: String :: f ( "%sContext '%s' size : %d", (" "_s * (_depth * 4)).cStr(), # _context, sizeof ( _context ) ) );

        LOG_CONTEXT_SIZE ( SharedContext, 0 )
            LOG_CONTEXT_SIZE ( CommonContext, 1 )
                LOG_CONTEXT_SIZE ( DiagnosticContext, 2 )
            LOG_CONTEXT_SIZE ( CreateSharedContext, 1 )
                LOG_CONTEXT_SIZE ( CreateInstanceContext, 2 )
                LOG_CONTEXT_SIZE ( CreateDeviceContext, 2 )
                LOG_CONTEXT_SIZE ( CreateSwapChainContext, 2 )
                LOG_CONTEXT_SIZE ( CreateCommandPoolContext, 2 )
                LOG_CONTEXT_SIZE ( CreateFenceContext, 2 )
                LOG_CONTEXT_SIZE ( CreateSemaphoreContext, 2 )
                LOG_CONTEXT_SIZE ( CreateEventContext, 2 )
                LOG_CONTEXT_SIZE ( CreateRenderPassContext, 2 )
                LOG_CONTEXT_SIZE ( CreateRenderPass2Context, 2 )
                LOG_CONTEXT_SIZE ( CreateShaderModuleContext, 2 )
                LOG_CONTEXT_SIZE ( CreateValidationCacheContext, 2 )
                LOG_CONTEXT_SIZE ( CreatePipelineSharedContext, 2 )
                    LOG_CONTEXT_SIZE ( CreateComputePipelineContext, 3 )
                    LOG_CONTEXT_SIZE ( CreateGraphicsPipelineContext, 3 )
                    LOG_CONTEXT_SIZE ( CreateRayTracingPipelineSharedContext, 3 )
                        LOG_CONTEXT_SIZE ( CreateRayTracingPipelineNVidiaContext, 4 )
                        LOG_CONTEXT_SIZE ( CreateRayTracingPipelineContext, 4 )
                LOG_CONTEXT_SIZE ( CreateBufferSharedContext, 2 )
                    LOG_CONTEXT_SIZE ( CreateBufferContext, 3 )
                    LOG_CONTEXT_SIZE ( CreateBufferViewContext, 3 )
                    LOG_CONTEXT_SIZE ( CreateFrameBufferContext, 3 )
                LOG_CONTEXT_SIZE ( CreateImageSharedContext, 2 )
                    LOG_CONTEXT_SIZE ( CreateImageContext, 3 )
                    LOG_CONTEXT_SIZE ( CreateImageViewContext, 3 )
                LOG_CONTEXT_SIZE ( CreateAccelerationStructureSharedContext, 2 )
                    LOG_CONTEXT_SIZE ( CreateAccelerationStructureKhronosContext, 3 )
                    LOG_CONTEXT_SIZE ( CreateAccelerationStructureNVidiaContext, 3 )
            LOG_CONTEXT_SIZE ( EnumerateSharedContext, 1 )
                LOG_CONTEXT_SIZE ( EnumerateLayerPropertiesContext, 2 )
                LOG_CONTEXT_SIZE ( EnumerateExtensionPropertiesContext, 2 )
                LOG_CONTEXT_SIZE ( EnumeratePhysicalDevicesContext, 2 )
                LOG_CONTEXT_SIZE ( EnumeratePhysicalDeviceQueueFamilyPerformanceQueryCountersContext, 2 )
                LOG_CONTEXT_SIZE ( EnumeratePhysicalDeviceGroupsContext, 2 )
            LOG_CONTEXT_SIZE ( GetSharedContext, 1 )
                LOG_CONTEXT_SIZE ( GetPhysicalDeviceSharedContext, 2 )
                    LOG_CONTEXT_SIZE ( GetPhysicalDevicePropertiesContext, 3 )
                    LOG_CONTEXT_SIZE ( GetPhysicalDeviceFeaturesContext, 3 )
                    LOG_CONTEXT_SIZE ( GetPhysicalDeviceQueueFamilyPropertiesContext, 3 )
                    LOG_CONTEXT_SIZE ( GetPhysicalDeviceCooperativeMatrixPropertiesContext, 3 )
                    LOG_CONTEXT_SIZE ( GetPhysicalDeviceMemoryPropertiesContext, 3 )
                LOG_CONTEXT_SIZE ( GetDeviceQueueContext, 2 )
                LOG_CONTEXT_SIZE ( GetSurfaceContext, 2 )
                LOG_CONTEXT_SIZE ( GetSwapChainContext, 2 )
                LOG_CONTEXT_SIZE ( GetFenceContext, 2 )
                LOG_CONTEXT_SIZE ( GetSemaphoreContext, 2 )
                LOG_CONTEXT_SIZE ( GetPipelineSharedContext, 2 )
                    LOG_CONTEXT_SIZE ( GetPipelineCommonContext, 3 )
                    LOG_CONTEXT_SIZE ( GetPipelinePropertiesContext, 3 )
                    LOG_CONTEXT_SIZE ( GetPipelineStatisticsContext, 3 )
                    LOG_CONTEXT_SIZE ( GetPipelineInternalRepresentationsContext, 3 )
                LOG_CONTEXT_SIZE ( GetMemorySharedContext, 2 )
                    LOG_CONTEXT_SIZE ( GetMemoryWin32Context, 3 )
                    LOG_CONTEXT_SIZE ( GetMemoryFdContext, 3 )
                LOG_CONTEXT_SIZE ( GetImageSharedContext, 2 )
                    LOG_CONTEXT_SIZE ( GetImageSubresourceLayoutContext, 3 )
                LOG_CONTEXT_SIZE ( GetAccelerationStructureSharedContext, 2 )
                    LOG_CONTEXT_SIZE ( GetAccelerationStructureBuildSizesContext, 3 )
                    LOG_CONTEXT_SIZE ( BindAccelerationStructureMemoryContext, 3 )
                    LOG_CONTEXT_SIZE ( GetAccelerationStructureDeviceAddressContext, 3 )
            LOG_CONTEXT_SIZE ( SetSharedContext, 1 )
                LOG_CONTEXT_SIZE ( SetCommandBufferSharedContext, 2 )
                    LOG_CONTEXT_SIZE ( SetCommandBufferEventContext, 3 )
            LOG_CONTEXT_SIZE ( AllocateSharedContext, 1 )
                LOG_CONTEXT_SIZE ( AllocateCommandBuffersContext, 2 )
                LOG_CONTEXT_SIZE ( AllocateMemoryContext, 2 )
            LOG_CONTEXT_SIZE ( BeginSharedContext, 1 )
                LOG_CONTEXT_SIZE ( BeginCommandBufferContext, 2 )
                LOG_CONTEXT_SIZE ( BeginCommandBufferRenderingContext, 2 )
                LOG_CONTEXT_SIZE ( BeginRenderPassContext, 2 )
            LOG_CONTEXT_SIZE ( SubmitSharedContext, 1 )
                LOG_CONTEXT_SIZE ( SubmitQueueContext, 2 )
            LOG_CONTEXT_SIZE ( OthersSharedContext, 1 )
                LOG_CONTEXT_SIZE ( RegisterEventContext, 2 )
                LOG_CONTEXT_SIZE ( NextSubpassContext, 2 )
            LOG_CONTEXT_SIZE ( ImportSharedContext, 1 )
                LOG_CONTEXT_SIZE ( ImportFenceSharedContext, 2 )
                LOG_CONTEXT_SIZE ( ImportSemaphoreSharedContext, 2 )
            LOG_CONTEXT_SIZE ( WaitSharedContext, 1 )
                LOG_CONTEXT_SIZE ( WaitSemaphoreContext, 2 )
                    LOG_CONTEXT_SIZE ( WaitCommandBufferSharedContext, 2 )
                    LOG_CONTEXT_SIZE ( WaitCommandBufferEventContext, 3 )
                    LOG_CONTEXT_SIZE ( WaitCommandBufferEvent2Context, 3 )
            LOG_CONTEXT_SIZE ( SignalSharedContext, 1 )
                LOG_CONTEXT_SIZE ( SignalSemaphoreContext, 2 )
            LOG_CONTEXT_SIZE ( BindSharedContext, 1 )
                LOG_CONTEXT_SIZE ( BindAccelerationStructureMemoryContext, 2 )

#undef LOG_CONTEXT_SIZE

    }

    static auto acquire () noexcept -> ContextHolder {

        if ( firstCall ) {
            cds :: LockGuard guard ( contextLock );

            if ( firstCall ) {

#ifndef NDEBUG
                ContextManager :: logContextSizes ();
#endif

                for ( auto & context : contexts ) {
                    context.inUse = false;

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED
                    context.data.common.common.diag.error = engine :: vulkan :: ResultSuccess;

                    context.data.common.common.dump.contextType             = ContextType :: None;
                    context.data.common.common.dump.apiFunction             = nullptr;
                    context.data.common.common.dump.apiFunctionDescription  = nullptr;
                    context.data.common.common.dump.paramCount              = 0U;
#endif

                    context.data.common.common.ruleSet = {
                            .onDelete = nullptr
                    };

                }
            }

            firstCall = false;
        }

        while ( true ) {
            cds :: LockGuard guard ( contextLock );
            for ( auto & context : contexts ) {
                if ( ! context.inUse ) {
                    context.inUse = true;
                    return ContextHolder ( & context );
                }
            }
        }
    }
};

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED
inline static auto representChain ( engine :: vulkan :: Type ( GenericInStructure ) const & structure ) noexcept -> cds :: String;

inline static auto paramToString (
        Parameter const & parameter
) noexcept -> cds :: String {

    switch ( parameter.type ) {

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
        case ParameterType :: BoolPtr: {
            auto pValue = * reinterpret_cast < bool * const * > ( parameter.pParam );
            return "0x" + cds :: Long ( reinterpret_cast < cds :: uint64 > ( pValue ) ).toString(16) +
                   ", value = " + ( pValue == nullptr ? "null"_s : ( * reinterpret_cast < bool * > ( pValue ) ? "true" : "false" ) );
        }

        case ParameterType :: UInt32Ptr: {
            auto pValue = * reinterpret_cast < cds :: uint32 * const * > ( parameter.pParam );
            return "0x" + cds :: Long ( reinterpret_cast < cds :: uint64 > ( pValue ) ).toString(16) +
                   ", value = " + ( pValue == nullptr ? "null"_s : cds :: Long ( * reinterpret_cast < cds :: uint32 * > ( pValue ) ).toString() );
        }

        case ParameterType :: UInt32: {
            auto pValue = reinterpret_cast < cds :: uint32 const * > ( parameter.pParam );
            return ( pValue == nullptr ? "null"_s : cds :: Long ( * pValue ).toString() );
        }

        case ParameterType :: Float: {
            auto pValue = reinterpret_cast < float const * > ( parameter.pParam );
            return ( pValue == nullptr ? "null"_s : cds :: Double ( * pValue ).toString() );
        }

        case ParameterType :: UInt64Ptr: {
            auto pValue = * reinterpret_cast < cds :: uint64 * const * > ( parameter.pParam );
            return "0x" + cds :: Long ( reinterpret_cast < cds :: uint64 > ( pValue ) ).toString(16) +
                   ", value = " + ( pValue == nullptr ? "null"_s : cds :: Long ( * reinterpret_cast < cds :: uint64 * > ( pValue ) ).toString() );
        }

        case ParameterType :: UInt64: {
            auto pValue = reinterpret_cast < cds :: uint64 const * > ( parameter.pParam );
            return ( pValue == nullptr ? "null"_s : cds :: Long ( * pValue ).toString() );
        }

        case ParameterType :: StringLiteral: {
            auto pValue = * reinterpret_cast < cds :: StringLiteral const * > ( parameter.pParam );
            return pValue == nullptr ? "null" : pValue;
        }

        case ParameterType :: AllocationCallbacksPtr: {
            auto pAllocationCallbacks = * reinterpret_cast < engine :: vulkan :: Type ( AllocationCallbacks ) const * const * > ( parameter.pParam );
            return "0x" + cds :: Long ( reinterpret_cast < cds :: uint64 > ( pAllocationCallbacks ) ).toString(16) +
                    " -> " + ( pAllocationCallbacks == nullptr ? "null"_s : engine :: vulkan :: toString ( * pAllocationCallbacks ) );
        }

        case ParameterType :: PhysicalDevicePropertiesPtr: {
            auto pStructure = * reinterpret_cast < engine :: vulkan :: Type ( PhysicalDeviceProperties ) const * const * > ( parameter.pParam );
            return "0x" + cds :: Long ( reinterpret_cast < cds :: uint64 > ( pStructure ) ).toString(16) +
                    " -> " + ( pStructure == nullptr ? "null"_s : engine :: vulkan :: toString ( * pStructure ) );
        }

        case ParameterType :: PhysicalDeviceFeaturesPtr: {
            auto pStructure = * reinterpret_cast < engine :: vulkan :: Type ( PhysicalDeviceFeatures ) const * const * > ( parameter.pParam );
            return "0x" + cds :: Long ( reinterpret_cast < cds :: uint64 > ( pStructure ) ).toString(16) +
                    " -> " + ( pStructure == nullptr ? "null"_s : engine :: vulkan :: toString ( * pStructure ) );
        }

        case ParameterType :: StructurePtr: {
            auto pStructure = * reinterpret_cast < engine :: vulkan :: Type ( GenericInStructure ) const * const * > ( parameter.pParam );
            return "0x" + cds :: Long ( reinterpret_cast < cds :: uint64 > ( pStructure ) ).toString(16) +
                    " -> " + ( pStructure == nullptr ? "null"_s : representChain ( * pStructure ) );
        }

        case ParameterType :: Structure: {
            auto pStructure = reinterpret_cast < engine :: vulkan :: Type ( GenericInStructure ) const * > ( parameter.pParam );
            return "0x" + cds :: Long ( reinterpret_cast < cds :: uint64 > ( pStructure ) ).toString(16) +
                    " -> " + ( pStructure == nullptr ? "null"_s : representChain ( * pStructure ) );
        }

        case ParameterType :: HandlePtr: {
            auto pHandle = * reinterpret_cast < engine :: vulkan :: Type ( InstanceHandle ) const * const * > ( parameter.pParam );
            return "0x" + cds :: Long ( reinterpret_cast < cds :: uint64 > ( pHandle ) ).toString(16) +
                   ", value = 0x" + ( pHandle == nullptr ? "null"_s : cds :: Long ( * reinterpret_cast < cds :: uint64 const * > ( pHandle ) ).toString(16) );
        }

        case ParameterType :: Handle: {
            auto pHandle = * reinterpret_cast < engine :: vulkan :: Type ( InstanceHandle ) const * > ( parameter.pParam );
            return "0x" + ( pHandle == nullptr ? "null"_s : cds :: Long ( reinterpret_cast < cds :: uint64 const > ( pHandle ) ).toString(16) );
        }

        case ParameterType :: LayerProperties: {
            auto pProperties = reinterpret_cast < engine :: vulkan :: Type ( LayerProperties ) const * > ( parameter.pParam );
            return toString ( * pProperties );
        }

        case ParameterType :: ExtensionProperties: {
            auto pProperties = reinterpret_cast < engine :: vulkan :: Type ( ExtensionProperties ) const * > ( parameter.pParam );
            return toString ( * pProperties );
        }

        case ParameterType :: PerformanceCounter: {
            auto pProperties = reinterpret_cast < engine :: vulkan :: Type ( PerformanceCounter ) const * > ( parameter.pParam );
            return toString ( * pProperties );
        }

        case ParameterType :: PerformanceCounterDescription: {
            auto pProperties = reinterpret_cast < engine :: vulkan :: Type ( PerformanceCounterDescription ) const * > ( parameter.pParam );
            return toString ( * pProperties );
        }

        case ParameterType :: PhysicalDeviceGroupProperties: {
            auto pProperties = reinterpret_cast < engine :: vulkan :: Type ( PhysicalDeviceGroupProperties ) const * > ( parameter.pParam );
            return toString ( * pProperties );
        }

        case ParameterType :: QueueFamilyProperties: {
            auto pProperties = reinterpret_cast < engine :: vulkan :: Type ( QueueFamilyProperties ) const * > ( parameter.pParam );
            return toString ( * pProperties );
        }

        case ParameterType :: SurfaceFormat: {
            auto pProperties = reinterpret_cast < engine :: vulkan :: Type ( SurfaceFormat ) const * > ( parameter.pParam );
            return toString ( * pProperties );
        }

        case ParameterType :: Extent2DPtr: {
            auto pProperties = reinterpret_cast < engine :: vulkan :: Type ( Extent2D ) const * > ( parameter.pParam );
            return cds :: String :: f (
                    "Extent { width = %d, height = %d }",
                    pProperties->width,
                    pProperties->height
            );
        }

        case ParameterType :: Flags: {
            auto pProperties = reinterpret_cast < Flags const * > ( parameter.pParam );
            return pProperties->toString();
        }

        case ParameterType :: DumpArrayPack: {
            auto pPack = reinterpret_cast < DumpedArray const * > ( parameter.pParam );
            if ( pPack->pArray == nullptr ) {
                return "[ ]"_s;
            }

            cds :: String str = "[ "_s;
            for ( cds :: uint32 i = 0U; i < * pPack->pCount; ++ i ) {
                str += paramToString ( Parameter {
                    .type       = pPack->type,
                    .pParam     = reinterpret_cast < cds :: Byte const * > ( pPack->pArray ) + i * pPack->size
                } ) + ", ";
            }

            return str.removeSuffix(", "_s) + " ]";
        }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_COOPERATIVE_MATRIX_AVAILABLE

        case ParameterType :: CooperativeMatrixPropertiesNVidia: {
            auto pProperties = reinterpret_cast < engine :: vulkan :: Type ( CooperativeMatrixPropertiesNVidia ) const * > ( parameter.pParam );
            return toString ( * pProperties );
        }

#endif

        case ParameterType :: Unknown:
            return "Unknown"_s;
    }

    return "Invalid"_s;
}

inline static auto dumpParamsToString (
        cds :: StringLiteral    prefix,
        cds :: uint32           count,
        Parameter       const * pParameters
) noexcept -> cds :: String {
    cds :: String str;

    for ( cds :: uint32 i = 0U; i < count; ++ i ) {
        str += prefix;
        str += paramToString ( pParameters[i] );
        str += ",\n";
    }

    return str;
}

inline static auto contextToString (
        cds :: StringLiteral            prefix,
        SharedContext           const & context
) noexcept -> cds :: String {

    switch ( context.common.common.dump.contextType ) {
        case ContextType :: None:
            return prefix + "No Context Used"_s;
        case ContextType :: Shared:
            return prefix + "Shared Context -> "_s + toString ( context.common.common.dump.specializedContextType.shared );
    }
}

inline static auto dumpToString ( SharedContext const & context ) noexcept -> cds :: String {
    if ( context.common.common.dump.apiFunction == nullptr ) {
        return cds :: String :: f (
                "[API DUMP, result = %s] API Function Call dump not configured",
                engine :: vulkan :: toString ( context.common.common.diag.error )
        );
    }

    auto contextAsString = contextToString ( "\t\t", context );
    auto paramsAsString = dumpParamsToString ( "\t\t\t", context.common.common.dump.paramCount, & context.common.common.dump.params[0] );

    return cds :: String :: f (
            "[API DUMP, result = %s]\n"
            "\tAPI Call : %s\n"
            "\tDescription : %s\n"
            "\tContext : \n"
            "%s\n"
            "\tParameters :\n"
            "\t\tCount : %d\n"
            "\t\tValues : \n"
            "%s\n",
            engine :: vulkan ::toString ( context.common.common.diag.error ),
            ( context.common.common.dump.apiFunction == nullptr ? "Unknown" : context.common.common.dump.apiFunction ),
            ( context.common.common.dump.apiFunctionDescription == nullptr ? "Unknown" : context.common.common.dump.apiFunctionDescription ),
            contextAsString.cStr(),
            context.common.common.dump.paramCount,
            paramsAsString.cStr()
    );
}

inline static auto representChain ( engine :: vulkan :: Type ( GenericInStructure ) const & structure ) noexcept -> cds :: String {
    cds :: String rep = "\n\t\t\t\t";
    switch ( structure.structureType ) {

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
        case engine::vulkan::StructureTypeInstanceCreateInfo:
            rep += toString ( reinterpret_cast < engine :: vulkan :: Type ( InstanceCreateInfo ) const & > ( structure ) );
            break;

        case engine::vulkan::StructureTypeApplicationInfo:
            rep += toString ( reinterpret_cast < engine :: vulkan :: Type ( ApplicationInfo ) const & > ( structure ) );
            break;
        case engine::vulkan::StructureTypeDeviceQueueCreateInfo:
            rep += toString ( reinterpret_cast < engine :: vulkan :: Type ( DeviceQueueCreateInfo ) const & > ( structure ) );
            break;
        case engine::vulkan::StructureTypeDeviceCreateInfo:
            rep += toString ( reinterpret_cast < engine :: vulkan :: Type ( DeviceCreateInfo ) const & > ( structure ) );
            break;
        case engine::vulkan::StructureTypeSubmitInfo:
            rep += toString ( reinterpret_cast < engine :: vulkan :: Type ( SubmitInfo ) const & > ( structure ) );
            break;
        case engine::vulkan::StructureTypeMemoryAllocateInfo:
            rep += toString ( reinterpret_cast < engine :: vulkan :: Type ( MemoryAllocateInfo ) const & > ( structure ) );
            break;
        case engine::vulkan::StructureTypeMappedMemoryRange:
            rep += toString ( reinterpret_cast < engine :: vulkan :: Type ( MappedMemoryRange ) const & > ( structure ) );
            break;
//        case engine::vulkan::StructureTypeBindSparseInfo:
//            rep += toString ( reinterpret_cast < engine :: vulkan :: Type ( BindSparseInfo ) const & > ( structure ) );
//            break;
        case engine::vulkan::StructureTypeFenceCreateInfo:
            rep += toString ( reinterpret_cast < engine :: vulkan :: Type ( FenceCreateInfo ) const & > ( structure ) );
            break;
        case engine::vulkan::StructureTypeSemaphoreCreateInfo:
            rep += toString ( reinterpret_cast < engine :: vulkan :: Type ( SemaphoreCreateInfo ) const & > ( structure ) );
            break;
        case engine::vulkan::StructureTypeEventCreateInfo:
            rep += toString ( reinterpret_cast < engine :: vulkan :: Type ( EventCreateInfo ) const & > ( structure ) );
            break;
//        case engine::vulkan::StructureTypeQueryPoolCreateInfo:
//            rep += toString ( reinterpret_cast < engine :: vulkan :: Type ( QueryPoolCreateInfo ) const & > ( structure ) );
//            break;
        case engine::vulkan::StructureTypeBufferCreateInfo:
            rep += toString ( reinterpret_cast < engine :: vulkan :: Type ( BufferCreateInfo ) const & > ( structure ) );
            break;
        case engine::vulkan::StructureTypeBufferViewCreateInfo:
            rep += toString ( reinterpret_cast < engine :: vulkan :: Type ( BufferViewCreateInfo ) const & > ( structure ) );
            break;
        case engine::vulkan::StructureTypeImageCreateInfo:
            rep += toString ( reinterpret_cast < engine :: vulkan :: Type ( ImageCreateInfo ) const & > ( structure ) );
            break;
        case engine::vulkan::StructureTypeImageViewCreateInfo:
            rep += toString ( reinterpret_cast < engine :: vulkan :: Type ( ImageViewCreateInfo ) const & > ( structure ) );
            break;
        case engine::vulkan::StructureTypeShaderModuleCreateInfo:
            rep += toString ( reinterpret_cast < engine :: vulkan :: Type ( ShaderModuleCreateInfo ) const & > ( structure ) );
            break;
        case engine::vulkan::StructureTypePipelineCacheCreateInfo:
            rep += toString ( reinterpret_cast < engine :: vulkan :: Type ( PipelineCacheCreateInfo ) const & > ( structure ) );
            break;
        case engine::vulkan::StructureTypePipelineShaderStageCreateInfo:
            rep += toString ( reinterpret_cast < engine :: vulkan :: Type ( PipelineShaderStageCreateInfo ) const & > ( structure ) );
            break;
        case engine::vulkan::StructureTypePipelineVertexInputStateCreateInfo:
            rep += toString ( reinterpret_cast < engine :: vulkan :: Type ( PipelineVertexInputStateCreateInfo ) const & > ( structure ) );
            break;
        case engine::vulkan::StructureTypePipelineInputAssemblyStateCreateInfo:
            rep += toString ( reinterpret_cast < engine :: vulkan :: Type ( PipelineInputAssemblyStateCreateInfo ) const & > ( structure ) );
            break;
//        case engine::vulkan::StructureTypePipelineTesselationStateCreateInfo:
//            rep += toString ( reinterpret_cast < engine :: vulkan :: Type ( PipelineTesselationStateCreateInfo ) const & > ( structure ) );
//            break;
        case engine::vulkan::StructureTypePipelineViewportStateCreateInfo:
            rep += toString ( reinterpret_cast < engine :: vulkan :: Type ( PipelineViewportStateCreateInfo ) const & > ( structure ) );
            break;
        case engine::vulkan::StructureTypePipelineRasterizationStateCreateInfo:
            rep += toString ( reinterpret_cast < engine :: vulkan :: Type ( PipelineRasterizationStateCreateInfo ) const & > ( structure ) );
            break;
        case engine::vulkan::StructureTypePipelineMultisampleStateCreateInfo:
            rep += toString ( reinterpret_cast < engine :: vulkan :: Type ( PipelineMultisampleStateCreateInfo ) const & > ( structure ) );
            break;
        case engine::vulkan::StructureTypePipelineDepthStencilStateCreateInfo:
            rep += toString ( reinterpret_cast < engine :: vulkan :: Type ( PipelineDepthStencilStateCreateInfo ) const & > ( structure ) );
            break;
        case engine::vulkan::StructureTypePipelineColorBlendStateCreateInfo:
            rep += toString ( reinterpret_cast < engine :: vulkan :: Type ( PipelineColorBlendStateCreateInfo ) const & > ( structure ) );
            break;
        case engine::vulkan::StructureTypePipelineDynamicStateCreateInfo:
            rep += toString ( reinterpret_cast < engine :: vulkan :: Type ( PipelineDynamicStateCreateInfo ) const & > ( structure ) );
            break;
        case engine::vulkan::StructureTypeGraphicsPipelineCreateInfo:
            rep += toString ( reinterpret_cast < engine :: vulkan :: Type ( GraphicsPipelineCreateInfo ) const & > ( structure ) );
            break;
        case engine::vulkan::StructureTypeComputePipelineCreateInfo:
            rep += toString ( reinterpret_cast < engine :: vulkan :: Type ( ComputePipelineCreateInfo ) const & > ( structure ) );
            break;
//        case engine::vulkan::StructureTypePipelineLayoutCreateInfo:
//            rep += toString ( reinterpret_cast < engine :: vulkan :: Type ( PipelineLayoutCreateInfo ) const & > ( structure ) );
//            break;
//        case engine::vulkan::StructureTypeSamplerCreateInfo:
//            rep += toString ( reinterpret_cast < engine :: vulkan :: Type ( SamplerCreateInfo ) const & > ( structure ) );
//            break;
//        case engine::vulkan::StructureTypeDescriptorSetLayoutCreateInfo:
//            rep += toString ( reinterpret_cast < engine :: vulkan :: Type ( DescriptorSetLayoutCreateInfo ) const & > ( structure ) );
//            break;
//        case engine::vulkan::StructureTypeDescriptorPoolCreateInfo:
//            rep += toString ( reinterpret_cast < engine :: vulkan :: Type ( DescriptorPoolCreateInfo ) const & > ( structure ) );
//            break;
//        case engine::vulkan::StructureTypeDescriptorSetAllocateInfo:
//            rep += toString ( reinterpret_cast < engine :: vulkan :: Type ( DescriptorSetAllocateInfo ) const & > ( structure ) );
//            break;
//        case engine::vulkan::StructureTypeWriteDescriptorSet:
//            rep += toString ( reinterpret_cast < engine :: vulkan :: Type ( WriteDescriptorSet ) const & > ( structure ) );
//            break;
//        case engine::vulkan::StructureTypeCopyDescriptorSet:
//            rep += toString ( reinterpret_cast < engine :: vulkan :: Type ( CopyDescriptorSet ) const & > ( structure ) );
//            break;
        case engine::vulkan::StructureTypeFrameBufferCreateInfo:
            rep += toString ( reinterpret_cast < engine :: vulkan :: Type ( FrameBufferCreateInfo ) const & > ( structure ) );
            break;
        case engine::vulkan::StructureTypeRenderPassCreateInfo:
            rep += toString ( reinterpret_cast < engine :: vulkan :: Type ( RenderPassCreateInfo ) const & > ( structure ) );
            break;
        case engine::vulkan::StructureTypeCommandPoolCreateInfo:
            rep += toString ( reinterpret_cast < engine :: vulkan :: Type ( CommandPoolCreateInfo ) const & > ( structure ) );
            break;
        case engine::vulkan::StructureTypeCommandBufferAllocateInfo:
            rep += toString ( reinterpret_cast < engine :: vulkan :: Type ( CommandBufferAllocateInfo ) const & > ( structure ) );
            break;
        case engine::vulkan::StructureTypeCommandBufferInheritanceInfo:
            rep += toString ( reinterpret_cast < engine :: vulkan :: Type ( CommandBufferInheritanceInfo ) const & > ( structure ) );
            break;
        case engine::vulkan::StructureTypeCommandBufferBeginInfo:
            rep += toString ( reinterpret_cast < engine :: vulkan :: Type ( CommandBufferBeginInfo ) const & > ( structure ) );
            break;
        case engine::vulkan::StructureTypeRenderPassBeginInfo:
            rep += toString ( reinterpret_cast < engine :: vulkan :: Type ( RenderPassBeginInfo ) const & > ( structure ) );
            break;
        case engine::vulkan::StructureTypeBufferMemoryBarrier:
            rep += toString ( reinterpret_cast < engine :: vulkan :: Type ( BufferMemoryBarrier ) const & > ( structure ) );
            break;
        case engine::vulkan::StructureTypeImageMemoryBarrier:
            rep += toString ( reinterpret_cast < engine :: vulkan :: Type ( ImageMemoryBarrier ) const & > ( structure ) );
            break;
        case engine::vulkan::StructureTypeMemoryBarrier:
            rep += toString ( reinterpret_cast < engine :: vulkan :: Type ( MemoryBarrier ) const & > ( structure ) );
            break;
//        case engine::vulkan::StructureTypeLoaderInstanceCreateInfo:
//            rep += toString ( reinterpret_cast < engine :: vulkan :: Type ( LoaderInstanceCreateInfo ) const & > ( structure ) );
//            break;
//        case engine::vulkan::StructureTypeLoaderDeviceCreateInfo:
//            rep += toString ( reinterpret_cast < engine :: vulkan :: Type ( LoaderDeviceCreateInfo ) const & > ( structure ) );
//            break;
#endif
#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE
        case engine::vulkan::StructureTypePhysicalDeviceSubgroupProperties:
            rep += toString ( reinterpret_cast < engine :: vulkan :: Type ( PhysicalDeviceSubgroupProperties ) const & > ( structure ) );
            break;
//        case engine::vulkan::StructureTypeBindBufferMemoryInfo:
//            rep += toString ( reinterpret_cast < engine :: vulkan :: Type ( BindBufferMemoryInfo ) const & > ( structure ) );
//            break;
//        case engine::vulkan::StructureTypeBindImageMemoryInfo:
//            rep += toString ( reinterpret_cast < engine :: vulkan :: Type ( BindImageMemoryInfo ) const & > ( structure ) );
//            break;
        case engine::vulkan::StructureTypePhysicalDevice16BitStorageFeatures:
            rep += toString ( reinterpret_cast < engine :: vulkan :: Type ( PhysicalDevice16BitStorageFeatures ) const & > ( structure ) );
            break;
        case engine::vulkan::StructureTypeMemoryDedicatedRequirements:
            rep += toString ( reinterpret_cast < engine :: vulkan :: Type ( MemoryDedicatedRequirements ) const & > ( structure ) );
            break;
        case engine::vulkan::StructureTypeMemoryDedicatedAllocateInfo:
            rep += toString ( reinterpret_cast < engine :: vulkan :: Type ( MemoryDedicatedAllocateInfo ) const & > ( structure ) );
            break;
        case engine::vulkan::StructureTypeMemoryAllocateFlagsInfo:
            rep += toString ( reinterpret_cast < engine :: vulkan :: Type ( MemoryAllocateFlagsInfo ) const & > ( structure ) );
            break;
        case engine::vulkan::StructureTypeDeviceGroupRenderPassBeginInfo:
            rep += toString ( reinterpret_cast < engine :: vulkan :: Type ( DeviceGroupRenderPassBeginInfo ) const & > ( structure ) );
            break;
        case engine::vulkan::StructureTypeDeviceGroupCommandBufferBeginInfo:
            rep += toString ( reinterpret_cast < engine :: vulkan :: Type ( DeviceGroupCommandBufferBeginInfo ) const & > ( structure ) );
            break;
        case engine::vulkan::StructureTypeDeviceGroupSubmitInfo:
            rep += toString ( reinterpret_cast < engine :: vulkan :: Type ( DeviceGroupSubmitInfo ) const & > ( structure ) );
            break;
//        case engine::vulkan::StructureTypeDeviceGroupBindSparseInfo:
//            rep += toString ( reinterpret_cast < engine :: vulkan :: Type ( DeviceGroupBindSparseInfo ) const & > ( structure ) );
//            break;
//        case engine::vulkan::StructureTypeBindBufferMemoryDeviceGroupInfo:
//            rep += toString ( reinterpret_cast < engine :: vulkan :: Type ( BindBufferMemoryDeviceGroupInfo ) const & > ( structure ) );
//            break;
//        case engine::vulkan::StructureTypeBindImageMemoryDeviceGroupInfo:
//            rep += toString ( reinterpret_cast < engine :: vulkan :: Type ( BindImageMemoryDeviceGroupInfo ) const & > ( structure ) );
//            break;
        case engine::vulkan::StructureTypePhysicalDeviceGroupProperties:
            rep += toString ( reinterpret_cast < engine :: vulkan :: Type ( PhysicalDeviceGroupProperties ) const & > ( structure ) );
            break;
        case engine::vulkan::StructureTypeDeviceGroupDeviceCreateInfo:
            rep += toString ( reinterpret_cast < engine :: vulkan :: Type ( DeviceGroupDeviceCreateInfo ) const & > ( structure ) );
            break;
//        case engine::vulkan::StructureTypeBufferMemoryRequirementsInfo:
//            rep += toString ( reinterpret_cast < engine :: vulkan :: Type ( BufferMemoryRequirementsInfo ) const & > ( structure ) );
//            break;
//        case engine::vulkan::StructureTypeImageMemoryRequirementsInfo:
//            rep += toString ( reinterpret_cast < engine :: vulkan :: Type ( ImageMemoryRequirementsInfo ) const & > ( structure ) );
//            break;
//        case engine::vulkan::StructureTypeImageSparseMemoryRequirementsInfo:
//            rep += toString ( reinterpret_cast < engine :: vulkan :: Type ( ImageSparseMemoryRequirementsInfo ) const & > ( structure ) );
//            break;
        case engine::vulkan::StructureTypeMemoryRequirements:
            rep += toString ( reinterpret_cast < engine :: vulkan :: Type ( MemoryRequirements ) const & > ( structure ) );
            break;
//        case engine::vulkan::StructureTypeSparseImageMemoryRequirements:
//            rep += toString ( reinterpret_cast < engine :: vulkan :: Type ( SparseImageMemoryRequirements ) const & > ( structure ) );
//            break;
        case engine::vulkan::StructureTypePhysicalDeviceFeatures:
            rep += toString ( reinterpret_cast < engine :: vulkan :: Type ( PhysicalDeviceExtendedFeatures ) const & > ( structure ) );
            break;
        case engine::vulkan::StructureTypePhysicalDeviceProperties:
            rep += toString ( reinterpret_cast < engine :: vulkan :: Type ( PhysicalDeviceExtendedProperties ) const & > ( structure ) );
            break;
//        case engine::vulkan::StructureTypeFormatProperties:
//            rep += toString ( reinterpret_cast < engine :: vulkan :: Type ( FormatProperties ) const & > ( structure ) );
//            break;
//        case engine::vulkan::StructureTypeImageFormatProperties:
//            rep += toString ( reinterpret_cast < engine :: vulkan :: Type ( ImageFormatProperties ) const & > ( structure ) );
//            break;
//        case engine::vulkan::StructureTypePhysicalDeviceImageFormatInfo:
//            rep += toString ( reinterpret_cast < engine :: vulkan :: Type ( PhysicalDeviceImageFormatInfo ) const & > ( structure ) );
//            break;
        case engine::vulkan::StructureTypeQueueFamilyProperties:
            rep += toString ( reinterpret_cast < engine :: vulkan :: Type ( QueueFamilyExtendedProperties ) const & > ( structure ) );
            break;
        case engine::vulkan::StructureTypePhysicalDeviceMemoryProperties:
            rep += toString ( reinterpret_cast < engine :: vulkan :: Type ( PhysicalDeviceMemoryProperties ) const & > ( structure ) );
            break;
//        case engine::vulkan::StructureTypeSparseImageFormatProperties:
//            rep += toString ( reinterpret_cast < engine :: vulkan :: Type ( SparseImageFormatProperties ) const & > ( structure ) );
//            break;
//        case engine::vulkan::StructureTypePhysicalDeviceSparseImageFormatInfo:
//            rep += toString ( reinterpret_cast < engine :: vulkan :: Type ( PhysicalDeviceSparseImageFormatInfo ) const & > ( structure ) );
//            break;
        case engine::vulkan::StructureTypePhysicalDevicePointClippingProperties:
            rep += toString ( reinterpret_cast < engine :: vulkan :: Type ( PhysicalDevicePointClippingProperties ) const & > ( structure ) );
            break;
        case engine::vulkan::StructureTypeRenderPassInputAttachmentAspectCreateInfo:
            rep += toString ( reinterpret_cast < engine :: vulkan :: Type ( RenderPassInputAttachmentAspectCreateInfo ) const & > ( structure ) );
            break;
        case engine::vulkan::StructureTypeImageViewUsageCreateInfo:
            rep += toString ( reinterpret_cast < engine :: vulkan :: Type ( ImageViewUsageCreateInfo ) const & > ( structure ) );
            break;
        case engine::vulkan::StructureTypePipelineTessellationDomainOriginStateCreateInfo:
            rep += toString ( reinterpret_cast < engine :: vulkan :: Type ( PipelineTessellationDomainOriginStateCreateInfo ) const & > ( structure ) );
            break;
        case engine::vulkan::StructureTypeRenderPassMultiviewCreateInfo:
            rep += toString ( reinterpret_cast < engine :: vulkan :: Type ( RenderPassMultiviewCreateInfo ) const & > ( structure ) );
            break;
        case engine::vulkan::StructureTypePhysicalDeviceMultiviewFeatures:
            rep += toString ( reinterpret_cast < engine :: vulkan :: Type ( PhysicalDeviceMultiviewFeatures ) const & > ( structure ) );
            break;
        case engine::vulkan::StructureTypePhysicalDeviceMultiviewProperties:
            rep += toString ( reinterpret_cast < engine :: vulkan :: Type ( PhysicalDeviceMultiviewProperties ) const & > ( structure ) );
            break;
        case engine::vulkan::StructureTypePhysicalDeviceVariablePointersFeatures:
            rep += toString ( reinterpret_cast < engine :: vulkan :: Type ( PhysicalDeviceVariablePointersFeatures ) const & > ( structure ) );
            break;
        case engine::vulkan::StructureTypeProtectedSubmitInfo:
            rep += toString ( reinterpret_cast < engine :: vulkan :: Type ( ProtectedSubmitInfo ) const & > ( structure ) );
            break;
        case engine::vulkan::StructureTypePhysicalDeviceProtectedMemoryFeatures:
            rep += toString ( reinterpret_cast < engine :: vulkan :: Type ( PhysicalDeviceProtectedMemoryFeatures ) const & > ( structure ) );
            break;
        case engine::vulkan::StructureTypePhysicalDeviceProtectedMemoryProperties:
            rep += toString ( reinterpret_cast < engine :: vulkan :: Type ( PhysicalDeviceProtectedMemoryProperties ) const & > ( structure ) );
            break;
        case engine::vulkan::StructureTypeDeviceQueueInfo:
            rep += toString ( reinterpret_cast < engine :: vulkan :: Type ( DeviceQueueInfo ) const & > ( structure ) );
            break;
//        case engine::vulkan::StructureTypeSamplerYCBCRConversionCreateInfo:
//            rep += toString ( reinterpret_cast < engine :: vulkan :: Type ( SamplerYCBCRConversionCreateInfo ) const & > ( structure ) );
//            break;
        case engine::vulkan::StructureTypeSamplerYCBCRConversionInfo:
            rep += toString ( reinterpret_cast < engine :: vulkan :: Type ( SamplerYCBCRConversionInfo ) const & > ( structure ) );
            break;
//        case engine::vulkan::StructureTypeBindImagePlaneMemoryInfo:
//            rep += toString ( reinterpret_cast < engine :: vulkan :: Type ( BindImagePlaneMemoryInfo ) const & > ( structure ) );
//            break;
//        case engine::vulkan::StructureTypeImagePlaneMemoryRequirementsInfo:
//            rep += toString ( reinterpret_cast < engine :: vulkan :: Type ( ImagePlaneMemoryRequirementsInfo ) const & > ( structure ) );
//            break;
        case engine::vulkan::StructureTypePhysicalDeviceSamplerYCBCRConversionFeatures:
            rep += toString ( reinterpret_cast < engine :: vulkan :: Type ( PhysicalDeviceSamplerYCBCRConversionFeatures ) const & > ( structure ) );
            break;
//        case engine::vulkan::StructureTypeSamplerYCBCRConversionImageFormatProperties:
//            rep += toString ( reinterpret_cast < engine :: vulkan :: Type ( SamplerYCBCRConversionImageFormatProperties ) const & > ( structure ) );
//            break;
//        case engine::vulkan::StructureTypeDescriptorUpdateTemplateCreateInfo:
//            rep += toString ( reinterpret_cast < engine :: vulkan :: Type ( DescriptorUpdateTemplateCreateInfo ) const & > ( structure ) );
//            break;
//        case engine::vulkan::StructureTypePhysicalDeviceExternalImageFormatInfo:
//            rep += toString ( reinterpret_cast < engine :: vulkan :: Type ( PhysicalDeviceExternalImageFormatInfo ) const & > ( structure ) );
//            break;
//        case engine::vulkan::StructureTypeExternalImageFormatProperties:
//            rep += toString ( reinterpret_cast < engine :: vulkan :: Type ( ExternalImageFormatProperties ) const & > ( structure ) );
//            break;
//        case engine::vulkan::StructureTypePhysicalDeviceExternalBufferInfo:
//            rep += toString ( reinterpret_cast < engine :: vulkan :: Type ( PhysicalDeviceExternalBufferInfo ) const & > ( structure ) );
//            break;
//        case engine::vulkan::StructureTypeExternalBufferProperties:
//            rep += toString ( reinterpret_cast < engine :: vulkan :: Type ( ExternalBufferProperties ) const & > ( structure ) );
//            break;
        case engine::vulkan::StructureTypePhysicalDeviceIDProperties:
            rep += toString ( reinterpret_cast < engine :: vulkan :: Type ( PhysicalDeviceIDProperties ) const & > ( structure ) );
            break;
        case engine::vulkan::StructureTypeExternalMemoryBufferCreateInfo:
            rep += toString ( reinterpret_cast < engine :: vulkan :: Type ( ExternalMemoryBufferCreateInfo ) const & > ( structure ) );
            break;
        case engine::vulkan::StructureTypeExternalMemoryImageCreateInfo:
            rep += toString ( reinterpret_cast < engine :: vulkan :: Type ( ExternalMemoryImageCreateInfo ) const & > ( structure ) );
            break;
        case engine::vulkan::StructureTypeExportMemoryAllocateInfo:
            rep += toString ( reinterpret_cast < engine :: vulkan :: Type ( ExportMemoryAllocateInfo ) const & > ( structure ) );
            break;
//        case engine::vulkan::StructureTypePhysicalDeviceExternalFenceInfo:
//            rep += toString ( reinterpret_cast < engine :: vulkan :: Type ( PhysicalDeviceExternalFenceInfo ) const & > ( structure ) );
//            break;
//        case engine::vulkan::StructureTypeExternalFenceProperties:
//            rep += toString ( reinterpret_cast < engine :: vulkan :: Type ( ExternalFenceProperties ) const & > ( structure ) );
//            break;
        case engine::vulkan::StructureTypeExportFenceCreateInfo:
            rep += toString ( reinterpret_cast < engine :: vulkan :: Type ( ExportFenceCreateInfo ) const & > ( structure ) );
            break;
        case engine::vulkan::StructureTypeExportSemaphoreCreateInfo:
            rep += toString ( reinterpret_cast < engine :: vulkan :: Type ( ExportSemaphoreCreateInfo ) const & > ( structure ) );
            break;
//        case engine::vulkan::StructureTypePhysicalDeviceExternalSemaphoreInfo:
//            rep += toString ( reinterpret_cast < engine :: vulkan :: Type ( PhysicalDeviceExternalSemaphoreInfo ) const & > ( structure ) );
//            break;
//        case engine::vulkan::StructureTypeExternalSemaphoreProperties:
//            rep += toString ( reinterpret_cast < engine :: vulkan :: Type ( ExternalSemaphoreProperties ) const & > ( structure ) );
//            break;
        case engine::vulkan::StructureTypePhysicalDeviceMaintenanceProperties:
            rep += toString ( reinterpret_cast < engine :: vulkan :: Type ( PhysicalDeviceMaintenanceProperties ) const & > ( structure ) );
            break;
//        case engine::vulkan::StructureTypeDescriptorSetLayoutSupport:
//            rep += toString ( reinterpret_cast < engine :: vulkan :: Type ( DescriptorSetLayoutSupport ) const & > ( structure ) );
//            break;
        case engine::vulkan::StructureTypePhysicalDeviceShaderDrawParametersFeatures:
            rep += toString ( reinterpret_cast < engine :: vulkan :: Type ( PhysicalDeviceShaderDrawParametersFeatures ) const & > ( structure ) );
            break;
#endif
#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE
        case engine::vulkan::StructureTypePhysicalDeviceVulkan_1_1_Features:
            rep += toString ( reinterpret_cast < engine :: vulkan :: Type ( PhysicalDeviceVulkan11Features ) const & > ( structure ) );
            break;
        case engine::vulkan::StructureTypePhysicalDeviceVulkan_1_1_Properties:
            rep += toString ( reinterpret_cast < engine :: vulkan :: Type ( PhysicalDeviceVulkan11Properties ) const & > ( structure ) );
            break;
        case engine::vulkan::StructureTypePhysicalDeviceVulkan_1_2_Features:
            rep += toString ( reinterpret_cast < engine :: vulkan :: Type ( PhysicalDeviceVulkan12Features ) const & > ( structure ) );
            break;
        case engine::vulkan::StructureTypePhysicalDeviceVulkan_1_2_Properties:
            rep += toString ( reinterpret_cast < engine :: vulkan :: Type ( PhysicalDeviceVulkan12Properties ) const & > ( structure ) );
            break;
        case engine::vulkan::StructureTypeImageFormatListCreateInfo:
            rep += toString ( reinterpret_cast < engine :: vulkan :: Type ( ImageFormatListCreateInfo ) const & > ( structure ) );
            break;
        case engine::vulkan::StructureTypeAttachmentDescription:
            rep += toString ( reinterpret_cast < engine :: vulkan :: Type ( AttachmentDescription ) const & > ( structure ) );
            break;
        case engine::vulkan::StructureTypeAttachmentReference:
            rep += toString ( reinterpret_cast < engine :: vulkan :: Type ( AttachmentReference ) const & > ( structure ) );
            break;
        case engine::vulkan::StructureTypeSubpassDescription:
            rep += toString ( reinterpret_cast < engine :: vulkan :: Type ( SubpassDescription ) const & > ( structure ) );
            break;
        case engine::vulkan::StructureTypeSubpassDependency:
            rep += toString ( reinterpret_cast < engine :: vulkan :: Type ( SubpassDependency ) const & > ( structure ) );
            break;
        case engine::vulkan::StructureTypeRenderPassCreateInfo2:
            rep += toString ( reinterpret_cast < engine :: vulkan :: Type ( RenderPassCreateInfo2 ) const & > ( structure ) );
            break;
        case engine::vulkan::StructureTypeSubpassBeginInfo:
            rep += toString ( reinterpret_cast < engine :: vulkan :: Type ( SubpassBeginInfo ) const & > ( structure ) );
            break;
        case engine::vulkan::StructureTypeSubpassEndInfo:
            rep += toString ( reinterpret_cast < engine :: vulkan :: Type ( SubpassEndInfo ) const & > ( structure ) );
            break;
        case engine::vulkan::StructureTypePhysicalDevice8BitStorageFeatures:
            rep += toString ( reinterpret_cast < engine :: vulkan :: Type ( PhysicalDevice8BitStorageFeatures ) const & > ( structure ) );
            break;
        case engine::vulkan::StructureTypePhysicalDeviceDriverProperties:
            rep += toString ( reinterpret_cast < engine :: vulkan :: Type ( PhysicalDeviceDriverProperties ) const & > ( structure ) );
            break;
        case engine::vulkan::StructureTypePhysicalDeviceShaderAtomicInt64Features:
            rep += toString ( reinterpret_cast < engine :: vulkan :: Type ( PhysicalDeviceShaderAtomicInt64Features ) const & > ( structure ) );
            break;
        case engine::vulkan::StructureTypePhysicalDeviceShaderFloat16Int8Features:
            rep += toString ( reinterpret_cast < engine :: vulkan :: Type ( PhysicalDeviceShaderFloat16Int8Features ) const & > ( structure ) );
            break;
        case engine::vulkan::StructureTypePhysicalDeviceFloatControlsProperties:
            rep += toString ( reinterpret_cast < engine :: vulkan :: Type ( PhysicalDeviceFloatControlsProperties ) const & > ( structure ) );
            break;
//        case engine::vulkan::StructureTypeDescriptorSetLayoutBindingFlagsCreateInfo:
//            rep += toString ( reinterpret_cast < engine :: vulkan :: Type ( DescriptorSetLayoutBindingFlagsCreateInfo ) const & > ( structure ) );
            break;
        case engine::vulkan::StructureTypePhysicalDeviceDescriptorIndexingFeatures:
            rep += toString ( reinterpret_cast < engine :: vulkan :: Type ( PhysicalDeviceDescriptorIndexingFeatures ) const & > ( structure ) );
            break;
        case engine::vulkan::StructureTypePhysicalDeviceDescriptorIndexingProperties:
            rep += toString ( reinterpret_cast < engine :: vulkan :: Type ( PhysicalDeviceDescriptorIndexingProperties ) const & > ( structure ) );
            break;
//        case engine::vulkan::StructureTypeDescriptorSetVariableDescriptorCountAllocateInfo:
//            rep += toString ( reinterpret_cast < engine :: vulkan :: Type ( DescriptorSetVariableDescriptorCountAllocateInfo ) const & > ( structure ) );
//            break;
//        case engine::vulkan::StructureTypeDescriptorSetVariableDescriptorCountLayoutSupport:
//            rep += toString ( reinterpret_cast < engine :: vulkan :: Type ( DescriptorSetVariableDescriptorCountLayoutSupport ) const & > ( structure ) );
//            break;
        case engine::vulkan::StructureTypePhysicalDeviceDepthStencilResolveProperties:
            rep += toString ( reinterpret_cast < engine :: vulkan :: Type ( PhysicalDeviceDepthStencilResolveProperties ) const & > ( structure ) );
            break;
        case engine::vulkan::StructureTypeSubpassDescriptionDepthStencilResolve:
            rep += toString ( reinterpret_cast < engine :: vulkan :: Type ( SubpassDescriptionDepthStencilResolve ) const & > ( structure ) );
            break;
        case engine::vulkan::StructureTypePhysicalDeviceScalarBlockLayoutFeatures:
            rep += toString ( reinterpret_cast < engine :: vulkan :: Type ( PhysicalDeviceScalarBlockLayoutFeatures ) const & > ( structure ) );
            break;
        case engine::vulkan::StructureTypeImageStencilUsageCreateInfo:
            rep += toString ( reinterpret_cast < engine :: vulkan :: Type ( ImageStencilUsageCreateInfo ) const & > ( structure ) );
            break;
        case engine::vulkan::StructureTypePhysicalDeviceSamplerFilterMinMaxProperties:
            rep += toString ( reinterpret_cast < engine :: vulkan :: Type ( PhysicalDeviceSamplerFilterMinmaxProperties ) const & > ( structure ) );
            break;
//        case engine::vulkan::StructureTypeSamplerReductionModeCreateInfo:
//            rep += toString ( reinterpret_cast < engine :: vulkan :: Type ( SamplerReductionModeCreateInfo ) const & > ( structure ) );
//            break;
        case engine::vulkan::StructureTypePhysicalDeviceVulkanMemoryModelFeatures:
            rep += toString ( reinterpret_cast < engine :: vulkan :: Type ( PhysicalDeviceVulkanMemoryModelFeatures ) const & > ( structure ) );
            break;
        case engine::vulkan::StructureTypePhysicalDeviceImagelessFrameBufferFeatures:
            rep += toString ( reinterpret_cast < engine :: vulkan :: Type ( PhysicalDeviceImagelessFrameBufferFeatures ) const & > ( structure ) );
            break;
        case engine::vulkan::StructureTypeFrameBufferAttachmentsCreateInfo:
            rep += toString ( reinterpret_cast < engine :: vulkan :: Type ( FrameBufferAttachmentsCreateInfo ) const & > ( structure ) );
            break;
        case engine::vulkan::StructureTypeFrameBufferAttachmentImageInfo:
            rep += toString ( reinterpret_cast < engine :: vulkan :: Type ( FrameBufferAttachmentImageInfo ) const & > ( structure ) );
            break;
        case engine::vulkan::StructureTypeRenderPassAttachmentBeginInfo:
            rep += toString ( reinterpret_cast < engine :: vulkan :: Type ( RenderPassAttachmentBeginInfo ) const & > ( structure ) );
            break;
        case engine::vulkan::StructureTypePhysicalDeviceUniformBufferStandardLayoutFeatures:
            rep += toString ( reinterpret_cast < engine :: vulkan :: Type ( PhysicalDeviceUniformBufferStandardLayoutFeatures ) const & > ( structure ) );
            break;
        case engine::vulkan::StructureTypePhysicalDeviceShaderSubgroupExtendedTypesFeatures:
            rep += toString ( reinterpret_cast < engine :: vulkan :: Type ( PhysicalDeviceShaderSubgroupExtendedTypesFeatures ) const & > ( structure ) );
            break;
        case engine::vulkan::StructureTypePhysicalDeviceSeparateDepthStencilLayoutsFeatures:
            rep += toString ( reinterpret_cast < engine :: vulkan :: Type ( PhysicalDeviceSeparateDepthStencilLayoutsFeatures ) const & > ( structure ) );
            break;
        case engine::vulkan::StructureTypeAttachmentReferenceStencilLayout:
            rep += toString ( reinterpret_cast < engine :: vulkan :: Type ( AttachmentReferenceStencilLayout ) const & > ( structure ) );
            break;
        case engine::vulkan::StructureTypeAttachmentDescriptionStencilLayout:
            rep += toString ( reinterpret_cast < engine :: vulkan :: Type ( AttachmentDescriptionStencilLayout ) const & > ( structure ) );
            break;
        case engine::vulkan::StructureTypePhysicalDeviceHostQueryResetFeatures:
            rep += toString ( reinterpret_cast < engine :: vulkan :: Type ( PhysicalDeviceHostQueryResetFeatures ) const & > ( structure ) );
            break;
        case engine::vulkan::StructureTypePhysicalDeviceTimelineSemaphoreFeatures:
            rep += toString ( reinterpret_cast < engine :: vulkan :: Type ( PhysicalDeviceTimelineSemaphoreFeatures ) const & > ( structure ) );
            break;
        case engine::vulkan::StructureTypePhysicalDeviceTimelineSemaphoreProperties:
            rep += toString ( reinterpret_cast < engine :: vulkan :: Type ( PhysicalDeviceTimelineSemaphoreProperties ) const & > ( structure ) );
            break;
        case engine::vulkan::StructureTypeSemaphoreTypeCreateInfo:
            rep += toString ( reinterpret_cast < engine :: vulkan :: Type ( SemaphoreTypeCreateInfo ) const & > ( structure ) );
            break;
        case engine::vulkan::StructureTypeTimelineSemaphoreSubmitInfo:
            rep += toString ( reinterpret_cast < engine :: vulkan :: Type ( TimelineSemaphoreSubmitInfo ) const & > ( structure ) );
            break;
        case engine::vulkan::StructureTypeSemaphoreWaitInfo:
            rep += toString ( reinterpret_cast < engine :: vulkan :: Type ( SemaphoreWaitInfo ) const & > ( structure ) );
            break;
        case engine::vulkan::StructureTypeSemaphoreSignalInfo:
            rep += toString ( reinterpret_cast < engine :: vulkan :: Type ( SemaphoreSignalInfo ) const & > ( structure ) );
            break;
        case engine::vulkan::StructureTypePhysicalDeviceBufferDeviceAddressFeatures:
            rep += toString ( reinterpret_cast < engine :: vulkan :: Type ( PhysicalDeviceBufferDeviceAddressFeatures ) const & > ( structure ) );
            break;
//        case engine::vulkan::StructureTypeBufferDeviceAddressInfo:
//            rep += toString ( reinterpret_cast < engine :: vulkan :: Type ( BufferDeviceAddressInfo ) const & > ( structure ) );
//            break;
        case engine::vulkan::StructureTypeBufferOpaqueCaptureAddressCreateInfo:
            rep += toString ( reinterpret_cast < engine :: vulkan :: Type ( BufferOpaqueCaptureAddressCreateInfo ) const & > ( structure ) );
            break;
        case engine::vulkan::StructureTypeMemoryOpaqueCaptureAddressAllocateInfo:
            rep += toString ( reinterpret_cast < engine :: vulkan :: Type ( MemoryOpaqueCaptureAddressAllocateInfo ) const & > ( structure ) );
            break;
        case engine::vulkan::StructureTypeDeviceMemoryOpaqueCaptureAddressInfo:
            rep += toString ( reinterpret_cast < engine :: vulkan :: Type ( DeviceMemoryOpaqueCaptureAddressInfo ) const & > ( structure ) );
            break;
#endif
#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE
        case engine::vulkan::StructureTypePhysicalDeviceVulkan_1_3_Features:
            rep += toString ( reinterpret_cast < engine :: vulkan :: Type ( PhysicalDeviceVulkan13Features ) const & > ( structure ) );
            break;
        case engine::vulkan::StructureTypePhysicalDeviceVulkan_1_3_Properties:
            rep += toString ( reinterpret_cast < engine :: vulkan :: Type ( PhysicalDeviceVulkan13Properties ) const & > ( structure ) );
            break;
        case engine::vulkan::StructureTypePipelineCreationFeedbackCreateInfo:
            rep += toString ( reinterpret_cast < engine :: vulkan :: Type ( PipelineCreationFeedbackCreateInfo ) const & > ( structure ) );
            break;
        case engine::vulkan::StructureTypePhysicalDeviceShaderTerminateInvocationFeatures:
            rep += toString ( reinterpret_cast < engine :: vulkan :: Type ( PhysicalDeviceShaderTerminateInvocationFeatures ) const & > ( structure ) );
            break;
//        case engine::vulkan::StructureTypePhysicalDeviceToolProperties:
//            rep += toString ( reinterpret_cast < engine :: vulkan :: Type ( PhysicalDeviceToolProperties ) const & > ( structure ) );
//            break;
        case engine::vulkan::StructureTypePhysicalDeviceShaderDemoteToHelperInvocationFeatures:
            rep += toString ( reinterpret_cast < engine :: vulkan :: Type ( PhysicalDeviceShaderDemoteToHelperInvocationFeatures ) const & > ( structure ) );
            break;
        case engine::vulkan::StructureTypePhysicalDevicePrivateDataFeatures:
            rep += toString ( reinterpret_cast < engine :: vulkan :: Type ( PhysicalDevicePrivateDataFeatures ) const & > ( structure ) );
            break;
        case engine::vulkan::StructureTypeDevicePrivateDataCreateInfo:
            rep += toString ( reinterpret_cast < engine :: vulkan :: Type ( DevicePrivateDataCreateInfo ) const & > ( structure ) );
            break;
//        case engine::vulkan::StructureTypePrivateDataSlotCreateInfo:
//            rep += toString ( reinterpret_cast < engine :: vulkan :: Type ( PrivateDataSlotCreateInfo ) const & > ( structure ) );
//            break;
        case engine::vulkan::StructureTypePhysicalDevicePipelineCreationCacheControlFeatures:
            rep += toString ( reinterpret_cast < engine :: vulkan :: Type ( PhysicalDevicePipelineCreationCacheControlFeatures ) const & > ( structure ) );
            break;
        case engine::vulkan::StructureTypeMemoryBarrier2:
            rep += toString ( reinterpret_cast < engine :: vulkan :: Type ( MemoryBarrier2 ) const & > ( structure ) );
            break;
        case engine::vulkan::StructureTypeBufferMemoryBarrier2:
            rep += toString ( reinterpret_cast < engine :: vulkan :: Type ( BufferMemoryBarrier2 ) const & > ( structure ) );
            break;
        case engine::vulkan::StructureTypeImageMemoryBarrier2:
            rep += toString ( reinterpret_cast < engine :: vulkan :: Type ( ImageMemoryBarrier2 ) const & > ( structure ) );
            break;
        case engine::vulkan::StructureTypeDependencyInfo:
            rep += toString ( reinterpret_cast < engine :: vulkan :: Type ( DependencyInfo ) const & > ( structure ) );
            break;
        case engine::vulkan::StructureTypeSubmitInfo2:
            rep += toString ( reinterpret_cast < engine :: vulkan :: Type ( SubmitInfo2 ) const & > ( structure ) );
            break;
        case engine::vulkan::StructureTypeSemaphoreSubmitInfo:
            rep += toString ( reinterpret_cast < engine :: vulkan :: Type ( SemaphoreSubmitInfo ) const & > ( structure ) );
            break;
        case engine::vulkan::StructureTypeCommandBufferSubmitInfo:
            rep += toString ( reinterpret_cast < engine :: vulkan :: Type ( CommandBufferSubmitInfo ) const & > ( structure ) );
            break;
        case engine::vulkan::StructureTypePhysicalDeviceSynchronizationFeatures:
            rep += toString ( reinterpret_cast < engine :: vulkan :: Type ( PhysicalDeviceSynchronizationFeatures ) const & > ( structure ) );
            break;
        case engine::vulkan::StructureTypePhysicalDeviceZeroInitializeWorkgroupMemoryFeatures:
            rep += toString ( reinterpret_cast < engine :: vulkan :: Type ( PhysicalDeviceZeroInitializeWorkgroupMemoryFeatures ) const & > ( structure ) );
            break;
        case engine::vulkan::StructureTypePhysicalDeviceImageRobustnessFeatures:
            rep += toString ( reinterpret_cast < engine :: vulkan :: Type ( PhysicalDeviceImageRobustnessFeatures ) const & > ( structure ) );
            break;
//        case engine::vulkan::StructureTypeCopyBufferInfo:
//            rep += toString ( reinterpret_cast < engine :: vulkan :: Type ( CopyBufferInfo ) const & > ( structure ) );
//            break;
//        case engine::vulkan::StructureTypeCopyImageInfo:
//            rep += toString ( reinterpret_cast < engine :: vulkan :: Type ( CopyImageInfo ) const & > ( structure ) );
//            break;
//        case engine::vulkan::StructureTypeCopyBufferToImageInfo:
//            rep += toString ( reinterpret_cast < engine :: vulkan :: Type ( CopyBufferToImageInfo ) const & > ( structure ) );
//            break;
//        case engine::vulkan::StructureTypeCopyImageToBufferInfo:
//            rep += toString ( reinterpret_cast < engine :: vulkan :: Type ( CopyImageToBufferInfo ) const & > ( structure ) );
//            break;
//        case engine::vulkan::StructureTypeBlitImageInfo:
//            rep += toString ( reinterpret_cast < engine :: vulkan :: Type ( BlitImageInfo ) const & > ( structure ) );
//            break;
//        case engine::vulkan::StructureTypeResolveImageInfo:
//            rep += toString ( reinterpret_cast < engine :: vulkan :: Type ( ResolveImageInfo ) const & > ( structure ) );
//            break;
//        case engine::vulkan::StructureTypeBufferCopy:
//            rep += toString ( reinterpret_cast < engine :: vulkan :: Type ( BufferCopy ) const & > ( structure ) );
//            break;
//        case engine::vulkan::StructureTypeImageCopy:
//            rep += toString ( reinterpret_cast < engine :: vulkan :: Type ( ImageCopy ) const & > ( structure ) );
//            break;
//        case engine::vulkan::StructureTypeImageBlit:
//            rep += toString ( reinterpret_cast < engine :: vulkan :: Type ( ImageBlit ) const & > ( structure ) );
//            break;
//        case engine::vulkan::StructureTypeBufferImageCopy:
//            rep += toString ( reinterpret_cast < engine :: vulkan :: Type ( BufferImageCopy ) const & > ( structure ) );
//            break;
//        case engine::vulkan::StructureTypeImageResolve:
//            rep += toString ( reinterpret_cast < engine :: vulkan :: Type ( ImageResolve ) const & > ( structure ) );
//            break;
        case engine::vulkan::StructureTypePhysicalDeviceSubgroupSizeControlFeatures:
            rep += toString ( reinterpret_cast < engine :: vulkan :: Type ( PhysicalDeviceSubgroupSizeControlFeatures ) const & > ( structure ) );
            break;
        case engine::vulkan::StructureTypePhysicalDeviceSubgroupSizeControlProperties:
            rep += toString ( reinterpret_cast < engine :: vulkan :: Type ( PhysicalDeviceSubgroupSizeControlProperties ) const & > ( structure ) );
            break;
        case engine::vulkan::StructureTypePipelineShaderStageRequiredSubgroupSizeCreateInfo:
            rep += toString ( reinterpret_cast < engine :: vulkan :: Type ( PipelineShaderStageRequiredSubgroupSizeCreateInfo ) const & > ( structure ) );
            break;
        case engine::vulkan::StructureTypePhysicalDeviceInlineUniformBlockFeatures:
            rep += toString ( reinterpret_cast < engine :: vulkan :: Type ( PhysicalDeviceInlineUniformBlockFeatures ) const & > ( structure ) );
            break;
        case engine::vulkan::StructureTypePhysicalDeviceInlineUniformBlockProperties:
            rep += toString ( reinterpret_cast < engine :: vulkan :: Type ( PhysicalDeviceInlineUniformBlockProperties ) const & > ( structure ) );
            break;
//        case engine::vulkan::StructureTypeWriteDescriptorSetInlineUniformBlock:
//            rep += toString ( reinterpret_cast < engine :: vulkan :: Type ( WriteDescriptorSetInlineUniformBlock ) const & > ( structure ) );
//            break;
//        case engine::vulkan::StructureTypeDescriptorPoolInlineUniformBlockCreateInfo:
//            rep += toString ( reinterpret_cast < engine :: vulkan :: Type ( DescriptorPoolInlineUniformBlockCreateInfo ) const & > ( structure ) );
//            break;
        case engine::vulkan::StructureTypePhysicalDeviceTextureCompressionASTCHDRFeatures:
            rep += toString ( reinterpret_cast < engine :: vulkan :: Type ( PhysicalDeviceTextureCompressionASTCHDRFeatures ) const & > ( structure ) );
            break;
        case engine::vulkan::StructureTypeRenderingInfo:
            rep += toString ( reinterpret_cast < engine :: vulkan :: Type ( RenderingInfo ) const & > ( structure ) );
            break;
        case engine::vulkan::StructureTypeRenderingAttachmentInfo:
            rep += toString ( reinterpret_cast < engine :: vulkan :: Type ( RenderingAttachmentInfo ) const & > ( structure ) );
            break;
        case engine::vulkan::StructureTypePipelineRenderingCreateInfo:
            rep += toString ( reinterpret_cast < engine :: vulkan :: Type ( PipelineRenderingCreateInfo ) const & > ( structure ) );
            break;
        case engine::vulkan::StructureTypePhysicalDeviceDynamicRenderingFeatures:
            rep += toString ( reinterpret_cast < engine :: vulkan :: Type ( PhysicalDeviceDynamicRenderingFeatures ) const & > ( structure ) );
            break;
        case engine::vulkan::StructureTypeCommandBufferInheritanceRenderingInfo:
            rep += toString ( reinterpret_cast < engine :: vulkan :: Type ( CommandBufferInheritanceRenderingInfo ) const & > ( structure ) );
            break;
        case engine::vulkan::StructureTypePhysicalDeviceShaderIntegerDotProductFeatures:
            rep += toString ( reinterpret_cast < engine :: vulkan :: Type ( PhysicalDeviceShaderIntegerDotProductFeatures ) const & > ( structure ) );
            break;
        case engine::vulkan::StructureTypePhysicalDeviceShaderIntegerDotProductProperties:
            rep += toString ( reinterpret_cast < engine :: vulkan :: Type ( PhysicalDeviceShaderIntegerDotProductProperties ) const & > ( structure ) );
            break;
        case engine::vulkan::StructureTypePhysicalDeviceTexelBufferAlignmentFeatures:
            rep += toString ( reinterpret_cast < engine :: vulkan :: Type ( PhysicalDeviceTexelBufferAlignmentFeatures ) const & > ( structure ) );
            break;
        case engine::vulkan::StructureTypePhysicalDeviceTexelBufferAlignmentProperties:
            rep += toString ( reinterpret_cast < engine :: vulkan :: Type ( PhysicalDeviceTexelBufferAlignmentProperties ) const & > ( structure ) );
            break;
//        case engine::vulkan::StructureTypeFormatProperties3:
//            rep += toString ( reinterpret_cast < engine :: vulkan :: Type ( FormatProperties3 ) const & > ( structure ) );
//            break;
        case engine::vulkan::StructureTypePhysicalDeviceMaintenance4Features:
            rep += toString ( reinterpret_cast < engine :: vulkan :: Type ( PhysicalDeviceMaintenance4Features ) const & > ( structure ) );
            break;
        case engine::vulkan::StructureTypePhysicalDeviceMaintenance4Properties:
            rep += toString ( reinterpret_cast < engine :: vulkan :: Type ( PhysicalDeviceMaintenance4Properties ) const & > ( structure ) );
            break;
//        case engine::vulkan::StructureTypePhysicalDeviceBufferMemoryRequirements:
//            rep += toString ( reinterpret_cast < engine :: vulkan :: Type ( PhysicalDeviceBufferMemoryRequirements ) const & > ( structure ) );
//            break;
//        case engine::vulkan::StructureTypePhysicalDeviceImageMemoryRequirements:
//            rep += toString ( reinterpret_cast < engine :: vulkan :: Type ( PhysicalDeviceImageMemoryRequirements ) const & > ( structure ) );
//            break;
#endif
#if __C_ENG_VULKAN_API_EXTENSION_DEBUG_UTILS_AVAILABLE
        case engine::vulkan::StructureTypeDebugUtilsMessengerCreateInfo:
            rep += toString ( reinterpret_cast < engine :: vulkan :: Type ( DebugMessengerCreateInfo ) const & > ( structure ) );
            break;
#endif
#if __C_ENG_VULKAN_API_EXTENSION_VALIDATION_FEATURES_AVAILABLE
        case engine::vulkan::StructureTypeValidationFeatures:
            rep += toString ( reinterpret_cast < engine :: vulkan :: Type ( ValidationFeatures ) const & > ( structure ) );
            break;
#endif

        default:
            rep += toString ( structure.structureType ) + ""_s;
    }

    return rep + " -> " + ( structure.pNext == nullptr ? "null"_s : representChain ( * structure.pNext ) );
}
#endif

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif

#endif //__C_ENG_CONTEXT_MANAGER_HPP__
