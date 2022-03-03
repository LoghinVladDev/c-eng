//
// Created by loghin on 03.03.2022.
//

#ifndef __C_ENG_VALIDATION_CACHE_HPP__
#define __C_ENG_VALIDATION_CACHE_HPP__

#include <Preprocess.hpp>
#include <VulkanRenderObject.hpp>
#include <VulkanCore.hpp>
#include <CDS/Path>


#define C_ENG_MAP_START CLASS ( ValidationCache, ENGINE_PARENT ( VulkanRenderObject ) )
#include <ObjectMapping.hpp>


namespace engine :: vulkan {

    __C_ENG_PRE_DECLARE_CLASS ( Device );

    Class {

        Field ( ENGINE_PRIMITIVE_TYPE ( DeviceHandle ),             device,     DEFAULT_VALUE ( nullptr ),  GET_NONE,       SET_NONE )
        Field ( TYPE ( cds :: String ),                             deviceName, NO_INIT,                    GET_NONE,       SET_NONE )
        Field ( TYPE ( cds :: Path ),                               cachePath,  NO_INIT,                    GET_NONE,       SET_NONE )

#if __C_ENG_VULKAN_API_EXTENSION_VALIDATION_CACHE_AVAILABLE
        Field ( ENGINE_PRIMITIVE_TYPE ( ValidationCacheHandle ),    handle,     DEFAULT_VALUE ( nullptr ),  GET_DEFAULT,    SET_NONE )
#endif

    public:
        Constructor () noexcept = default;
        Constructor ( Self const & ) noexcept = delete;
        Constructor ( Self && ) noexcept;

        auto operator = ( Self const & ) noexcept -> Self & = delete;
        auto operator = ( Self && ) noexcept -> Self &;

        Destructor () noexcept;

        auto init ( Type ( Device ) const *, cds :: Path const & ) noexcept -> Self &;

        auto clear () noexcept -> Self & override;
    };

} // namespace engine::vulkan

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>


#endif //__C_ENG_VALIDATION_CACHE_HPP__
