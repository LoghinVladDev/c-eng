#include "Queue.hpp"
#include <QueueFamily.hpp>
#include <Device.hpp>
#include <VulkanAPI.hpp>


using namespace cds;
using namespace engine;


#define C_ENG_MAP_START     CLASS ( Queue, ENGINE_PARENT ( VulkanRenderObject ) )
#include <ObjectMapping.hpp>

auto vulkan :: Self :: init (
    Type ( Device )         const * pDevice,
    Type ( QueueFamily )    const * pQueueFamily,
    uint32                          queueIndex,
    Type ( QueueFlag )              type
) noexcept -> Self & {

    auto result = vulkan :: getDeviceQueue (
        pDevice->handle(),
        pQueueFamily->familyIndex()
        queueIndex,
        & this->_handle
    );

    if ( result != ResultSuccess ) {
        __C_ENG_LOG_AND_THROW_DETAILED_API_CALL_EXCEPTION(error, "getDeviceQueue", result);
    }

    this->_type         = type;
    this->_index        = queueIndex;
    this->_queueFamily  = pQueueFamily;

    return * this;
}

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>