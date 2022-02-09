//
// Created by loghin on 03.02.2022.
//

#ifndef __C_ENG_PRESENT_HANDLER_HPP__
#define __C_ENG_PRESENT_HANDLER_HPP__


#include <Preprocess.hpp>
#include <VulkanRenderObject.hpp>
#include <VulkanCore.hpp>

#include <CDS/Pointer>


#define C_ENG_MAP_START     CLASS ( PresentHandler, ENGINE_PARENT ( VulkanRenderObject ) )
#include <ObjectMapping.hpp>

namespace engine { // NOLINT(modernize-concat-nested-namespaces)
    namespace vulkan {

        __C_ENG_PRE_DECLARE_CLASS ( Device );

        Class {
        public:
            struct SurfaceFormats {
                Type ( SurfaceFormat )    * pFormats;
                cds :: uint32               count;
            };

            struct PresentModes {
                Type ( PresentMode )  * pPresentModes;
                cds :: uint32           count;
            };

            struct SurfaceProperties {
                Type ( SurfaceCapabilities )    surfaceCapabilities;
                SurfaceFormats                  formats;
                PresentModes                    presentModes;
            };

            struct ImageViews {
                Type ( ImageViewHandle )  * pImageViews;
                cds :: uint32               count;
            };

            Field ( TYPE ( ImageViews ),    imageViews, DEFAULT_VALUE ( nullptr, 0U ),  GET_DEFAULT,    SET_DEFAULT_PROTECTED )

        private:
            static auto deviceSupportsSurfacePresent ( Type ( Device ) const *, Type ( SurfaceHandle ) ) noexcept (false) -> bool;

        protected:
            static auto propertiesForDevice ( Type ( PhysicalDeviceHandle ), Type ( SurfaceHandle ) ) noexcept (false) -> SurfaceProperties const *;
            auto acquireImageViews () noexcept -> Type ( ImageViewHandle ) *;
            auto releaseImageViews () noexcept -> void;

        public:
            virtual auto init ( Type ( Device ) const * ) noexcept (false) -> Self & = 0;
            auto clear () noexcept -> Self & override = 0;

            __C_ENG_NO_DISCARD static auto createSuitablePresentHandler (
                    Type ( Device )         const *,
                    Type ( SurfaceHandle )
            ) noexcept -> cds :: UniquePointer < Type ( PresentHandler ) >;

            Destructor () noexcept override = default;
        };

    }
}

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>


#endif //__C_ENG_PRESENT_HANDLER_HPP__
