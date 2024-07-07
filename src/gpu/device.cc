#include "device.h"

#include <set>
#include <stdexcept>

#include "gpu/instance.h"
#include "util/memory.h"
#include "vulkan/vulkan_core.h"

using namespace villa;

Device::Device(const PhysicalDevice &physical_device) {
   std::set<uint32_t> unique_queue_families = {
       physical_device.graphics_queue(), physical_device.present_queue()
   };

   std::vector<VkDeviceQueueCreateInfo> create_queues;
   create_queues.reserve(unique_queue_families.size());

   const float queue_priority = 1.0f;
   for (const uint32_t queue_family : unique_queue_families) {
      create_queues.push_back({
          .sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO,
          .queueFamilyIndex = queue_family,
          .queueCount = 1,
          .pQueuePriorities = &queue_priority,
      });
   }

   VkPhysicalDeviceFeatures physical_device_features = {};

   static const char *swapchain_extension = VK_KHR_SWAPCHAIN_EXTENSION_NAME;
   VkDeviceCreateInfo create_info = {
       .sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO,
       .queueCreateInfoCount = static_cast<uint32_t>(create_queues.size()),
       .pQueueCreateInfos = create_queues.data(),
#ifdef VILLA_DEBUG
       .enabledLayerCount = VILLA_ARRAY_LEN(validation_layers),
       .ppEnabledLayerNames = validation_layers,
#endif
       .enabledExtensionCount = 1,
       .ppEnabledExtensionNames = &swapchain_extension,
       .pEnabledFeatures = &physical_device_features,
   };

   if (vkCreateDevice(physical_device.handle(), &create_info, nullptr, &device_) != VK_SUCCESS) {
      throw std::runtime_error("failed to create logical device");
   }

   vkGetDeviceQueue(device_, physical_device.graphics_queue(), 0, &graphics_queue_);
   vkGetDeviceQueue(device_, physical_device.present_queue(), 0, &present_queue_);
}

Device::~Device() {
   vkDestroyDevice(device_, nullptr);
}