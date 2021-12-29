//
// Created by loghin on 28.12.2021.
//

#include "Instance.hpp"
#include <VulkanAPIExceptions.hpp>
#include <Logger.hpp>


using namespace cds; // NOLINT(clion-misra-cpp2008-7-3-4)
using namespace engine; // NOLINT(clion-misra-cpp2008-7-3-4)


#define C_ENG_MAP_START     CLASS ( Instance, EXTERNAL_PARENT ( cds :: Object ) )
#include <ObjectMapping.hpp>

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE

auto vulkan :: Self :: supportedVulkanVersion () noexcept (false) -> __C_ENG_TYPE ( Version ) {
    uint32                      rawInstanceVersion;

    auto result = enumerateInstanceVersion( & rawInstanceVersion );
    if ( result != ResultSuccess ) {
        __C_ENG_LOG_AND_THROW_DETAILED_API_CALL_EXCEPTION(warning, "enumerateInstanceVersion", result);
    }

    return uInt32ToInstanceVersion ( rawInstanceVersion );
}

#endif