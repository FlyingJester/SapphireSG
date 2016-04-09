#include "vulkan_context.h"

void VulkanSGCreateInstance

struct SapphireSG_ContextGuts *VulkanSG_CreateContext() {
	struct SapphireSG_ContextGuts *guts = malloc(sizeof(struct SapphireSG_ContextGuts));



	vkEnumeratePhysicalDevices()

	VkDeviceQueueCreateInfo queues;
	VkDeviceCreateInfo device_create_info;

	memset(&device_create_info, 0, sizeof(VkDeviceCreateInfo));

	device_create_info.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
	device_create_info.pNext = NULL;
	device_create_info.queueCreateInfoCount = 1;
	device_create_info.pQueueCreateInfos = &queues;
	device_create_info.pEnabledFeatures = NULL;

	vkCreateDevice(physical_device, &device_create_info, NULL, &guts->device);

}
