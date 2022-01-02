//
// Created by loghin on 28.12.2021.
//

#ifndef __C_ENG_VULKANAPICALLS_HPP
#define __C_ENG_VULKANAPICALLS_HPP

namespace engine { // NOLINT(modernize-concat-nested-namespaces)

    namespace vulkan {

        __C_ENG_NO_DISCARD extern auto enumerateInstanceVersion ( cds :: uint32 * ) noexcept -> __C_ENG_TYPE ( Result );
        __C_ENG_NO_DISCARD extern auto enumerateInstanceLayerProperties ( cds :: uint32 *, __C_ENG_TYPE ( LayerProperties ) * = nullptr ) noexcept -> __C_ENG_TYPE ( Result );
        __C_ENG_NO_DISCARD extern auto enumerateDeviceLayerProperties ( __C_ENG_TYPE ( PhysicalDeviceHandle ) handle, cds :: uint32 *, __C_ENG_TYPE ( LayerProperties ) * = nullptr ) noexcept -> __C_ENG_TYPE ( Result );
        __C_ENG_NO_DISCARD extern auto enumerateInstanceExtensionProperties ( cds :: StringLiteral, cds :: uint32 *, __C_ENG_TYPE ( ExtensionProperties ) * = nullptr ) noexcept -> __C_ENG_TYPE ( Result );
        __C_ENG_NO_DISCARD extern auto enumeratePhysicalDevices ( __C_ENG_TYPE ( InstanceHandle ), cds :: uint32 *, __C_ENG_TYPE ( PhysicalDeviceHandle ) * = nullptr ) noexcept -> __C_ENG_TYPE ( Result );

        __C_ENG_NO_DISCARD extern auto createInstance ( __C_ENG_TYPE ( InstanceCreateInfo ) const *, __C_ENG_TYPE ( AllocationCallbacks ) const *, __C_ENG_TYPE ( InstanceHandle ) * ) noexcept -> __C_ENG_TYPE ( Result );
        __C_ENG_NO_DISCARD extern auto createDebugMessenger ( __C_ENG_TYPE ( InstanceHandle ) , __C_ENG_TYPE ( DebugMessengerCreateInfo ) const *, __C_ENG_TYPE ( AllocationCallbacks ) const *, __C_ENG_TYPE ( DebugMessengerHandle ) * ) noexcept -> __C_ENG_TYPE ( Result );
        __C_ENG_NO_DISCARD extern auto createSurface ( __C_ENG_TYPE ( InstanceHandle ), GLFWwindow *, __C_ENG_TYPE ( AllocationCallbacks ) const *, __C_ENG_TYPE ( SurfaceHandle ) * ) noexcept -> __C_ENG_TYPE ( Result );

        __C_ENG_NO_DISCARD extern auto destroyInstance ( __C_ENG_TYPE ( InstanceHandle ), __C_ENG_TYPE ( AllocationCallbacks ) const * ) noexcept -> __C_ENG_TYPE ( Result );
        __C_ENG_NO_DISCARD extern auto destroyDebugMessenger ( __C_ENG_TYPE ( InstanceHandle ), __C_ENG_TYPE ( DebugMessengerHandle ), __C_ENG_TYPE ( AllocationCallbacks ) const * ) noexcept -> __C_ENG_TYPE ( Result );
        __C_ENG_NO_DISCARD extern auto destroySurface ( __C_ENG_TYPE ( InstanceHandle ), __C_ENG_TYPE ( SurfaceHandle ), __C_ENG_TYPE ( AllocationCallbacks ) const * ) noexcept -> __C_ENG_TYPE ( Result );

        __C_ENG_NO_DISCARD extern auto getPhysicalDeviceProperties ( __C_ENG_TYPE ( PhysicalDeviceHandle ), __C_ENG_TYPE ( PhysicalDeviceProperties ) * ) noexcept -> __C_ENG_TYPE ( Result );
        __C_ENG_NO_DISCARD extern auto getPhysicalDeviceProperties ( __C_ENG_TYPE ( PhysicalDeviceHandle ), __C_ENG_TYPE ( PhysicalDeviceExtendedProperties ) * ) noexcept -> __C_ENG_TYPE ( Result );

    }

}

#endif //__C_ENG_VULKANAPICALLS_HPP
