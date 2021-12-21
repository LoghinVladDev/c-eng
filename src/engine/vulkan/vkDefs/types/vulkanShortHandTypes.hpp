//
// Created by Vlad on 14/08/2020.
//

#ifndef ENG1_VULKANSHORTHANDTYPES_HPP
#define ENG1_VULKANSHORTHANDTYPES_HPP


#include <VQueue.hpp>
#include <VMessenger.hpp>

namespace engine {

    using VQ   __CDS_MaybeUnused = VQueue;
    using VQF  __CDS_MaybeUnused = VQueueFamily;
    using VQFC __CDS_MaybeUnused = VQueueFamilyCollection;

    using VLD  __CDS_MaybeUnused = VLogicalDevice;
    using VLDF __CDS_MaybeUnused = VLogicalDevice::Factory;

    using VPD  __CDS_MaybeUnused = VPhysicalDevice;

    using VE   __CDS_MaybeUnused = VExtension;
    using VEC  __CDS_MaybeUnused = VExtensionCollection;

    using VM   __CDS_MaybeUnused = VMessenger;

    using VVL  __CDS_MaybeUnused = VValidationLayer;
    using VVLC __CDS_MaybeUnused = VValidationLayerCollection;

    using VI   __CDS_MaybeUnused = VInstance;

    using VS   __CDS_MaybeUnused = VSurface;

}

#endif //ENG1_VULKANSHORTHANDTYPES_HPP
