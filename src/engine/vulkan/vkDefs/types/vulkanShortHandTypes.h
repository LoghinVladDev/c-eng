//
// Created by Vlad on 14/08/2020.
//

#ifndef ENG1_VULKANSHORTHANDTYPES_H
#define ENG1_VULKANSHORTHANDTYPES_H


#include <src/GLFW/src/engine/vulkan/vkObj/instance/device/queue/VQueue.h>
#include <src/GLFW/src/engine/vulkan/vkObj/instance/messenger/VMessenger.h>

namespace engine {
    typedef VQueue                                  VQ;
    typedef VQueueFamily                            VQF;
    typedef VQueueFamilyCollection                  VQFC;

    typedef VLogicalDevice                          VLD;
    typedef VLogicalDevice::VLogicalDeviceFactory   VLDF;

    typedef VPhysicalDevice                         VPD;

    typedef VExtension                              VE;
    typedef VExtensionCollection                    VEC;

    typedef VMessenger                              VM;

    typedef VValidationLayer                        VVL;
    typedef VValidationLayerCollection              VVLC;

    typedef VInstance                               VI;

    typedef VSurface                                VS;
}

#endif //ENG1_VULKANSHORTHANDTYPES_H
