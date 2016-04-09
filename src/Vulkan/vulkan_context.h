#pragma once
#include <vulkan/vulkan.h>
#include "../backend.h"

struct SapphireSG_ContextGuts {
	VkDevice device;
	VkPhysicalDevice physical_device;
};

struct SapphireSG_ContextGuts *VulkanSG_CreateContext();

