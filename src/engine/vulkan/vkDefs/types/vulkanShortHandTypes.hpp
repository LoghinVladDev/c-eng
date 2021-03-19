//
// Created by Vlad on 14/08/2020.
//

#ifndef ENG1_VULKANSHORTHANDTYPES_HPP
#define ENG1_VULKANSHORTHANDTYPES_HPP


#include <VQueue.hpp>
#include <VMessenger.hpp>

namespace engine {
    typedef VQueue                                  VQ;
    typedef VQueueFamily                            VQF;
    typedef VQueueFamilyCollection                  VQFC;

    typedef VLogicalDevice                          VLD;
    typedef VLogicalDevice::Factory   VLDF;

    typedef VPhysicalDevice                         VPD;

    typedef VExtension                              VE;
    typedef VExtensionCollection                    VEC;

    typedef VMessenger                              VM;

    typedef VValidationLayer                        VVL;
    typedef VValidationLayerCollection              VVLC;

    typedef VInstance                               VI;

    typedef VSurface                                VS;
}

#endif //ENG1_VULKANSHORTHANDTYPES_HPP
