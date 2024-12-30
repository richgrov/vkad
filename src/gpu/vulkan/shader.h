#ifndef VKAD_GPU_VULKAN_SHADER_H_
#define VKAD_GPU_VULKAN_SHADER_H_

#include <cstdint>
#include <span>
#include <vulkan/vulkan_core.h>

#include "device.h"

namespace vkad {

class Shader {
public:
   Shader(Device &device, std::span<uint8_t> code);
   Shader(Shader &&other);
   Shader(const Shader &other) = delete;

   ~Shader();

   Shader &operator=(const Shader &other) = delete;

   VkShaderModule module() const {
      return module_;
   }

private:
   VkDevice device_;
   VkShaderModule module_;
};

} // namespace vkad

#endif // !VKAD_GPU_VULKAN_SHADER_H_