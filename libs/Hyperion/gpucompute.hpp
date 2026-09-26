#pragma once

#include <vulkan/vulkan.h>

#include <vector>

void setupVulkanForIapetus()
{
    VkApplicationInfo vkAppInfo = VkApplicationInfo(VK_STRUCTURE_TYPE_APPLICATION_INFO,NULL,NULL,0,"Iapetus",0,VK_API_VERSION_1_4);
    VkApplicationInfo* vkAppInfoPtr = &vkAppInfo;

    /* uint32_t propertyCount {};
    uint32_t* propertyCountPtr = &propertyCount;

    VkResult EnumerationErrorResult = vkEnumerateInstanceExtensionProperties(NULL,propertyCountPtr,NULL);
    if (EnumerationErrorResult != VK_SUCCESS)
    {
        return;
    }

    std::vector<VkExtensionProperties> vkExtensionProperties(propertyCount);
    VkExtensionProperties* vkExtensionPropertiesPtr = &vkExtensionProperties[0];

    VkResult Enumeration2ErrorResult = vkEnumerateInstanceExtensionProperties(NULL,propertyCountPtr,vkExtensionPropertiesPtr);
    if (Enumeration2ErrorResult != VK_SUCCESS)
    {
        return;
    } */

    //currently no extensions are used because i dont use this as a way to contact with the window and purely as a computational thing

    /*
        currently this validation layer isnt in use

        const char* layerPtr {VK_LAYER_KHRONOS_validation};
        const char* const* layerPtrPtr = &layerPtr;
    */

    VkInstanceCreateInfo vkInstanceCreateInfo = VkInstanceCreateInfo(VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,NULL,0,vkAppInfoPtr,0,nullptr,0,nullptr);

    VkInstance vkInstance {};
    VkResult vkCreationErrorResult = vkCreateInstance(&vkInstanceCreateInfo,nullptr,&vkInstance);

    if (vkCreationErrorResult != VK_SUCCESS)
    {
        return;
    }

    uint32_t deviceCount {};
    uint32_t* deviceCountPtr = &deviceCount;

    VkResult vkEnumeratingDevicesErrorResult = vkEnumeratePhysicalDevices(vkInstance,deviceCountPtr,NULL);

    if (vkEnumeratingDevicesErrorResult != VK_SUCCESS)
    {
        return;
    }

    std::vector<VkPhysicalDevice> vkDevices(deviceCount);
    VkPhysicalDevice* vkDevicesPtr = vkDevices.data();

    VkResult vkEnumeratingDevicesErrorResult2 = vkEnumeratePhysicalDevices(vkInstance,deviceCountPtr,vkDevicesPtr);

    if (vkEnumeratingDevicesErrorResult2 != VK_SUCCESS)
    {
        return;
    }

    VkPhysicalDeviceProperties vkDeviceProperties;

    VkPhysicalDevice vkDevice {};

    for (uint32_t i=0;i<deviceCount;i++)
    {
        vkGetPhysicalDeviceProperties(vkDevices[i],&vkDeviceProperties);

        if (vkDeviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU)
        {
            vkDevice =vkDevices[i];
            break;
        }
    }

    if (!vkDevice)
    {
        for (uint32_t i=0;i<deviceCount;i++)
        {   
            vkGetPhysicalDeviceProperties(vkDevices[i],&vkDeviceProperties);

            if (vkDeviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU)
            {
                vkDevice =vkDevices[i];
                break;
            }  
        }
    }

    if (!vkDevice)
    {
        return;
    }

    uint32_t queueFamilyPropertyCounter {};

    vkGetPhysicalDeviceQueueFamilyProperties(vkDevice,&queueFamilyPropertyCounter,NULL);

    std::vector<VkQueueFamilyProperties> vkQueueProperties(queueFamilyPropertyCounter);
    VkQueueFamilyProperties* vkQueuePropertiesPtr = vkQueueProperties.data();

    uint32_t computeQueueFamilyIndex {};

    bool foundComputeQueueFamilyIndex = false;

    for (uint32_t i=0;i<queueFamilyPropertyCounter;i++)
    {
        if ((vkQueueProperties[i].queueFlags & VK_QUEUE_COMPUTE_BIT) != 0)
        {
            computeQueueFamilyIndex = i;
            foundComputeQueueFamilyIndex = true;
            break;
        }
    }

    if (foundComputeQueueFamilyIndex == false)
    {
        return;
    }

    float queuePriority {1.0f};

    VkDeviceQueueCreateInfo vkDeviceQueueCreateInfo = VkDeviceQueueCreateInfo(VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO,NULL,0,computeQueueFamilyIndex,1,&queuePriority);

    VkDeviceCreateInfo vkDeviceCreateInfo = VkDeviceCreateInfo(VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO,NULL,0,1,&vkDeviceQueueCreateInfo,0,NULL,0,NULL,NULL);

    VkDevice vkActualDevice {};

    VkResult vkResultForActualDeviceCreation = vkCreateDevice(vkDevice,&vkDeviceCreateInfo,nullptr,&vkActualDevice);

    if (vkResultForActualDeviceCreation != VK_SUCCESS)
    {
        return;
    }

    VkQueue vkQueue {};

    vkGetDeviceQueue(vkActualDevice,computeQueueFamilyIndex,0,&vkQueue);

    VkCommandPoolCreateInfo vkCommandPoolInfo = VkCommandPoolCreateInfo(VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO,NULL,0,computeQueueFamilyIndex);

    VkCommandPool vkCommandPool {};

    VkResult vkCommandPoolResult = vkCreateCommandPool(vkActualDevice,&vkCommandPoolInfo,nullptr,&vkCommandPool);

    if (vkCommandPoolResult != VK_SUCCESS)
    {
        return;
    }
}