#pragma once

#include <ATen/native/vulkan/api/Common.h>
#include <ATen/native/vulkan/api/Descriptor.h>
#include <ATen/native/vulkan/api/Pipeline.h>
#include <ATen/native/vulkan/api/Shader.h>

namespace at {
namespace native {
namespace vulkan {
namespace api {

//
// Vulkan Context holds onto all relevant Vulkan state as it pertains to our
// use of Vulkan in PyTorch.  The context is currently a global object, but
// technically it does not need to be if we were to make it explicit to the
// user.
//

class Context final {
 public:
  explicit Context(bool enable_validation_layers);
  ~Context() = default;

  inline VkInstance instance() const {
    return instance_.get();
  }

  inline VkPhysicalDevice physical_device() const {
    return physical_device_;
  }

  inline const VkPhysicalDeviceLimits& physical_device_limits() const {
    return physical_device_limits_;
  }

  inline VkDevice device() const {
    return device_.get();
  }

  inline VkQueue queue() const {
    return queue_;
  }

  inline Shader& shader() {
    return shader_;
  }

  inline Pipeline& pipeline() {
    return pipeline_;
  }

  inline Descriptor& descriptor() {
    return descriptor_;
  }

 private:
  // Construction and destruction order matters.  Do not move members around.
  Handle<VkInstance, decltype(&VK_DELETER(Instance))> instance_;
  VkPhysicalDevice physical_device_;
  VkPhysicalDeviceLimits physical_device_limits_;
  uint32_t compute_queue_family_index_;
  Handle<VkDevice, decltype(&VK_DELETER(Device))> device_;
  VkQueue queue_;
  Shader shader_;
  Pipeline pipeline_;
  Descriptor descriptor_;
};

bool available();
Context& context();

} // namespace api
} // namespace vulkan
} // namespace native
} // namespace at
