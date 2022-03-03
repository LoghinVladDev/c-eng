//
// Created by loghin on 03.03.2022.
//

#include "ValidationCache.hpp"
#include <VulkanAPI.hpp>
#include <CDS/Path>
#include <fstream>
#include <Device.hpp>
#include <PhysicalDevice.hpp>
#include <Allocator.hpp>
#include <Logger.hpp>

using namespace cds;
using namespace engine;
using namespace engine :: vulkan;

#define C_ENG_MAP_START CLASS ( ValidationCache, ENGINE_PARENT ( VulkanRenderObject ) )
#include <ObjectMapping.hpp>

#if __C_ENG_VULKAN_API_EXTENSION_VALIDATION_CACHE_AVAILABLE
class ValidationCacheContents {
private:
    Byte * pData = nullptr;
    uint64 _size  = 0U;

public:
    static inline auto readContents (
            Path    const & path,
            String          deviceName
    ) noexcept -> ValidationCacheContents {

        deviceName.toLower().forEach([](auto & character){
            if ( " \t\r\f\n"_s.contains( character ) ) {
                character = '_';
            }
        });

        try {
            ValidationCacheContents contents;

            std :: fstream cacheFile ( ( path / deviceName ).toString().cStr(), std :: ios :: binary | std :: ios :: in | std :: ios :: ate );
            if ( cacheFile ) {
                contents._size = cacheFile.tellg();

                cacheFile.seekg ( 0, std :: ios :: beg );
                contents.pData = new Byte [ contents._size ];
                cacheFile.read ( reinterpret_cast < char * > ( contents.pData ), contents._size );
            }

            return contents;
        } catch ( Path :: InvalidPath const & exception ) {
            return ValidationCacheContents ();
        }
    }

    static inline auto saveContents (
            Type ( DeviceHandle )                   deviceHandle,
            Type ( ValidationCacheHandle )          cacheHandle,
            Path                            const & path,
            String                                  deviceName
    ) noexcept -> void {

        uint64 dataSize = 0U;
        Byte * pData = nullptr;

        if (
                auto result = vulkan :: getValidationCacheData (
                        deviceHandle,
                        cacheHandle,
                        & dataSize
                ); result != ResultSuccess
        ) {
            __C_ENG_LOG_DETAILED_API_CALL_EXCEPTION ( warning, "getValidationCacheData", result );
            return;
        }

        pData = new Byte [ dataSize ];

        if (
                auto result = vulkan :: getValidationCacheData (
                        deviceHandle,
                        cacheHandle,
                        & dataSize,
                        pData
                ); result != ResultSuccess
        ) {
            __C_ENG_LOG_DETAILED_API_CALL_EXCEPTION ( warning, "getValidationCacheData", result );
            delete [] pData;
            return;
        }

        deviceName.toLower().forEach([](auto & character){
            if ( " \t\r\f\n"_s.contains( character ) ) {
                character = '_';
            }
        });

        std :: fstream cacheFile ( ( path.toString() + Path :: directorySeparator() + deviceName ).cStr(), std :: ios :: out | std :: ios :: binary | std :: ios :: trunc );
        cacheFile.write ( reinterpret_cast < char const * > ( pData ), dataSize );

        delete [] pData;
    }

    constexpr auto data () const noexcept -> Byte * {
        return this->pData;
    }

    constexpr auto size () const noexcept -> uint64 {
        return this->_size;
    }

    ValidationCacheContents () noexcept = default;

    ValidationCacheContents ( ValidationCacheContents const & ) noexcept = delete;

    ValidationCacheContents ( ValidationCacheContents && contents ) noexcept :
            pData ( exchange ( contents.pData, nullptr ) ),
            _size ( exchange ( contents._size, 0U ) ) {

    }

    auto operator = ( ValidationCacheContents const & ) noexcept = delete;

    auto operator = ( ValidationCacheContents && contents ) noexcept -> ValidationCacheContents & {
        if ( & contents == this ) {
            return * this;
        }

        this->pData = exchange ( contents.pData, nullptr );
        this->_size = exchange ( contents._size, 0U );

        return * this;
    }

    ~ValidationCacheContents() noexcept {
        delete [] this->pData;
    }
};
#endif

#if __C_ENG_VULKAN_API_EXTENSION_VALIDATION_CACHE_AVAILABLE
static auto inline populateValidationCacheCreateInfo (
        Type ( ValidationCacheCreateInfo ) * pCreateInfo,
        uint64                               size,
        void const *                         data
) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

if ( pCreateInfo == nullptr ) {
        return;
    }

#endif

    * pCreateInfo = {
            .structureType      = StructureTypeValidationCacheCreateInfo,
            .pNext              = nullptr,
            .flags              = 0U,
            .initialDataSize    = size,
            .pInitialData       = data
    };
}
#endif

Self :: Constructor ( Self && object ) noexcept :

#if __C_ENG_VULKAN_API_EXTENSION_VALIDATION_CACHE_AVAILABLE
        _handle ( exchange ( object._handle, nullptr ) ),
#endif

        _device ( exchange ( object._device, nullptr ) ) {

}

auto Self :: operator = ( Self && object ) noexcept -> Self & {
    if ( this == & object ) {
        return * this;
    }

#if __C_ENG_VULKAN_API_EXTENSION_VALIDATION_CACHE_AVAILABLE
    this->_handle = exchange ( object._handle, nullptr );
#endif

    this->_device = exchange ( object._device, nullptr );

    return * this;
}

Self :: Destructor () noexcept {
    (void) this->Self :: clear();
}

auto Self :: init (
        Type ( Device ) const * pDevice,
        Path            const & path
) noexcept -> Self & {

#if __C_ENG_VULKAN_API_EXTENSION_VALIDATION_CACHE_AVAILABLE

    this->_device       = pDevice->handle();

    this->_cachePath    = path;
    this->_deviceName   = pDevice->physicalDevice()->details().basicProperties.deviceName;

    auto cacheContents = ValidationCacheContents :: readContents (
            this->_cachePath,
            this->_deviceName
    );

    Type ( ValidationCacheCreateInfo ) createInfo {};
    populateValidationCacheCreateInfo ( & createInfo, cacheContents.size(), cacheContents.data() );

    if (
            auto result = vulkan :: createValidationCache (
                    this->_device,
                    & createInfo,
                    Type ( Allocator ) :: instance().callbacks(),
                    & this->_handle
            ); result != ResultSuccess
    ) {
        __C_ENG_LOG_DETAILED_API_CALL_EXCEPTION ( warning, "createValidationCache", result );
        this->_handle = nullptr;
    }

#endif

    return * this;
}

auto Self :: clear () noexcept -> Self & {

#if __C_ENG_VULKAN_API_EXTENSION_VALIDATION_CACHE_AVAILABLE

    if ( this->_handle != nullptr ) {

        ValidationCacheContents :: saveContents (
                this->_device,
                this->_handle,
                this->_cachePath,
                this->_deviceName
        );

        if (
                auto result = vulkan :: destroyValidationCache (
                        this->_device,
                        this->handle(),
                        Type ( Allocator ) :: instance().callbacks()
                ); result != ResultSuccess
        ) {
            __C_ENG_LOG_DETAILED_API_CALL_EXCEPTION ( warning, "destroyValidationCache", result );
        }

        this->_handle = nullptr;
    }

#endif

    return * this;
}
