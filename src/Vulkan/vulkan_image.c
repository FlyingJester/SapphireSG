#pragma once
#include "vulkan_image.h"
#include "../backend.h"

void VulkanSG_DestroyImage(struct SapphireSG_Context *ctx, struct SapphireSG_Image *im) {
    vkDestroyImageView(device, im->view, NULL);
    vkDestroyImage(device, im->image, NULL);
    vkDestroySampler(device, im->sampler, NULL);

    vkFreeMemory(device, im->devmem, NULL);

}
