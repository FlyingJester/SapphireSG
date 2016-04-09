#pragma once
#include <vulkan/vulkan.h>
#include "../image.h"

struct SapphireSG_ImageGuts {
    VkSampler sampler;
    VkImage image;
    VkImageLayout layout;
    VkDeviceMemory devmem;
    VkImageView view;
};

void VulkanSG_DestroyImage(struct SapphireSG_Context *ctx, struct SapphireSG_Image *im);
