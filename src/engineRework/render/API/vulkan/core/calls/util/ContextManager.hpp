//
// Created by loghin on 08.03.2022.
//

#ifndef __C_ENG_CONTEXT_MANAGER_HPP__
#define __C_ENG_CONTEXT_MANAGER_HPP__

#include <calls/VulkanAPICallsTypes.hpp>
#include <CDS/Mutex>
#include <CDS/LockGuard>
#include <Logger.hpp>

#define C_ENG_MAP_START     HEADER
#include <ObjectMapping.hpp>


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
            this->pContext->inUse = false;

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED
            if ( this->pContext->data.common.diag.error != engine :: vulkan :: ResultSuccess ) {
                engine :: Type ( Logger ) :: instance().error ( cds :: String::f (
                        "API Error logged in context at release : %s, in %s -> %s : %d ---> %s",
                        toString ( pContext->data.common.diag.error ),
                        pContext->data.common.diag.file,
                        pContext->data.common.diag.function,
                        pContext->data.common.diag.line,
                        pContext->data.common.diag.pMessage == nullptr ? "no details given" : pContext->data.common.diag.pMessage->cStr()
                ));

                cds :: Memory :: instance().destroy ( pContext->data.common.diag.pMessage );

                this->pContext->data.common.diag.error = engine :: vulkan :: ResultSuccess;
            }
#endif

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
                    context.data.common.diag.error = engine :: vulkan :: ResultSuccess;
#endif

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

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#endif //__C_ENG_CONTEXT_MANAGER_HPP__
