//
// Created by loghin on 8/21/25.
//

#include "VulkanShaderModule.hpp"
#include <device/VulkanLogicalDevice.hpp>
#include <fstream>
#include <core/VulkanHandles.hpp>


namespace c_eng::api::vk::detail {
using cds::Unexpected;

ShaderModule::~ShaderModule() noexcept {
  assert(device().functions().vkDestroyShaderModule && "undefined behavior");
  device().functions().vkDestroyShaderModule(device().handle(), handle(), allocationCallbacks());
}

auto ShaderModuleBuilder::buildFromByteCode(VectorView<char> code) const noexcept -> Expected<ShaderModule, VkResult> {
  auto const& fns = _device.functions();
  auto const allocationCallbacks = _allocationCallbacks.getOr(_device.allocationCallbacks());
  assert(fns.vkCreateShaderModule && fns.vkDestroyShaderModule && "undefined behavior");

  auto const createInfo = VkShaderModuleCreateInfo {
      .sType = VkStructureType::VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO,
      .pNext = nullptr,
      .flags = 0u,
      .codeSize = code.size() * sizeof(char),
      .pCode = static_cast<std::uint32_t const*>(static_cast<void const*>(code.data()))
  };

  VkShaderModule handle;
  if (auto const result = fns.vkCreateShaderModule(_device.handle(), &createInfo, allocationCallbacks, &handle);
      result != VkResult::VK_SUCCESS) {
    return Unexpected{result};
  }

  return {_device, allocationCallbacks, handle};
}

auto ShaderModuleBuilder::buildFromPrecompiledShaderAt(Path const& path) const noexcept -> Expected<ShaderModule, VkResult> {
  std::ifstream file(path.str().data(), std::ios::ate | std::ios::binary);
  if (!file.is_open()) {
    return Unexpected{VkResult::VK_ERROR_NOT_PERMITTED};
  }

  Vector<char> buffer(file.tellg());
  file.seekg(0, std::ios::beg);
  file.read(buffer.data(), static_cast<std::streamsize>(buffer.size()));
  return buildFromByteCode(buffer);
}
} // namespace c_eng::api::vk::detail
