#pragma once

#define VK_USE_PLATFORM_WIN32_KHR
#include <vulkan/vulkan.h>

#include "window.hpp"

#include <vector>
#include <iostream>

extern HWND window;

void setupVulkanForIapetus()
{
    VkApplicationInfo vkAppInfo = VkApplicationInfo(VK_STRUCTURE_TYPE_APPLICATION_INFO,NULL,NULL,0,"Iapetus",0,VK_API_VERSION_1_4);
    VkApplicationInfo* vkAppInfoPtr = &vkAppInfo;

    //extension in use

    const char* win32Extension {"VK_KHR_win32_surface"};
    const char* const* extensionArr = &win32Extension;

    uint32_t propertyCount {};
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
    }

    bool isWIN32extensionUsable {false};

    for (int i=0;i<propertyCount;i++)
    {
        VkExtensionProperties vkExtensionPropertiesValue = vkExtensionProperties[i];
        if (strcmp(vkExtensionPropertiesValue.extensionName,win32Extension)==0)
        {
            isWIN32extensionUsable = true;
            break;
        }
    }

    if (isWIN32extensionUsable == false)
    {
        return;
    }

    /*
    currently this validation layer isnt in use

    const char* layerPtr {VK_LAYER_KHRONOS_validation};
    const char* const* layerPtrPtr = &layerPtr;*/

    VkInstanceCreateInfo vkInstanceCreateInfo = VkInstanceCreateInfo(VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,NULL,0,vkAppInfoPtr,0,nullptr,1,extensionArr);
    VkInstanceCreateInfo* vkInstanceCreateInfoPtr = &vkInstanceCreateInfo;

    VkInstance vkInstance {};
    VkInstance* vkInstancePtr = &vkInstance;
    VkResult vkCreationErrorResult = vkCreateInstance(vkInstanceCreateInfoPtr,nullptr,vkInstancePtr);

    if (vkCreationErrorResult != VK_SUCCESS)
    {
        return;
    }
    
    VkWin32SurfaceCreateInfoKHR vkSurfaceCreateInfo = VkWin32SurfaceCreateInfoKHR(VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR,NULL,0,GetModuleHandleA(NULL),window);
    VkWin32SurfaceCreateInfoKHR* vkSurfaceCreateInfoPtr = &vkSurfaceCreateInfo;

    VkSurfaceKHR vkSurfaceKHR;
    VkSurfaceKHR* vkSurfaceKHRPtr = &vkSurfaceKHR;
    VkResult vkCreateWIN32SurfaceErrorResult = vkCreateWin32SurfaceKHR(vkInstance,vkSurfaceCreateInfoPtr,nullptr,vkSurfaceKHRPtr);

    if (vkCreateWIN32SurfaceErrorResult != VK_SUCCESS)
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
    VkPhysicalDeviceProperties* vkDevicePropertiesPtr =  &vkDeviceProperties;

    VkPhysicalDevice vkDevice {};

    for (int i=0;i<deviceCount;i++)
    {
        vkGetPhysicalDeviceProperties(vkDevices[i],vkDevicePropertiesPtr);

        if (vkDeviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU)
        {
            vkDevice =vkDevices[i];
            break;
        }
    }

    if (!vkDevice)
    {
        for (int i=0;i<deviceCount;i++)
        {   
            vkGetPhysicalDeviceProperties(vkDevices[i],vkDevicePropertiesPtr);

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
    uint32_t* queueFamilyPropertyCounterPtr = &queueFamilyPropertyCounter;

    vkGetPhysicalDeviceQueueFamilyProperties2(vkDevice,queueFamilyPropertyCounterPtr,NULL);

    std::vector<VkQueueFamilyProperties2> vkQueueProperties(queueFamilyPropertyCounter);
    VkQueueFamilyProperties2* vkQueuePropertiesPtr = vkQueueProperties.data();

    for (int i=0;i<queueFamilyPropertyCounter;i++)
    {
        vkQueueProperties[i].sType = VK_STRUCTURE_TYPE_QUEUE_FAMILY_PROPERTIES_2;
        vkQueueProperties[i].pNext = NULL;
    }

    vkGetPhysicalDeviceQueueFamilyProperties2(vkDevice,queueFamilyPropertyCounterPtr,vkQueuePropertiesPtr);

    VkBool32 isQueueAvailable {};
    VkBool32* isQueueAvailablePtr = &isQueueAvailable;

    uint32_t graphicsQueueFamilyIndex {};

    bool foundGraphicsQueueFamilyIndex = false;

    uint32_t propertyCountForEnumerationOfDeviceExtensionProperties {};
    uint32_t* propertyCountForEnumerationOfDeviceExtensionPropertiesPtr = &propertyCountForEnumerationOfDeviceExtensionProperties;

    for (uint32_t i=0;i<queueFamilyPropertyCounter;i++)
    {
        vkGetPhysicalDeviceSurfaceSupportKHR(vkDevice,i,vkSurfaceKHR,isQueueAvailablePtr);

        if ((vkQueueProperties[i].queueFamilyProperties.queueFlags & VK_QUEUE_GRAPHICS_BIT) != 0 && isQueueAvailable == VK_TRUE)
        {
            graphicsQueueFamilyIndex = i;
            foundGraphicsQueueFamilyIndex = true;
            break;
        }
    }

    if (foundGraphicsQueueFamilyIndex == false)
    {
        return;
    }

    float queuePriority {1.0f};
    float* queuePriorityPtr = &queuePriority;
    VkDeviceQueueCreateInfo vkDeviceQueueCreateInfo = VkDeviceQueueCreateInfo(VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO,NULL,0,graphicsQueueFamilyIndex,1,queuePriorityPtr);


    vkEnumerateDeviceExtensionProperties(vkDevice,NULL,propertyCountForEnumerationOfDeviceExtensionPropertiesPtr,NULL);

    std::vector<VkExtensionProperties> vkDeviceExtensionProperties(propertyCountForEnumerationOfDeviceExtensionProperties);
    VkExtensionProperties* vkDeviceExtensionPropertiesPtr = vkDeviceExtensionProperties.data();

    vkEnumerateDeviceExtensionProperties(vkDevice,NULL,propertyCountForEnumerationOfDeviceExtensionPropertiesPtr,vkDeviceExtensionPropertiesPtr);

    bool foundSwapchainDeviceExtensionProperty = false;
    
    const char* vkSwapchainExtension {};
    const char* const* ExtensionArrForvkDeviceCreateInfo = &vkSwapchainExtension;

    for (int i=0;i<propertyCountForEnumerationOfDeviceExtensionProperties;i++)
    {
        if (strcmp(vkDeviceExtensionProperties[i].extensionName,"VK_KHR_swapchain") == 0)
        {
            vkSwapchainExtension = "VK_KHR_swapchain";
            foundSwapchainDeviceExtensionProperty = true;
        }
    }

    if (foundSwapchainDeviceExtensionProperty == false)
    {
        return;
    }


    VkDeviceCreateInfo vkDeviceCreateInfo = VkDeviceCreateInfo(VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO,NULL,0,1,&vkDeviceQueueCreateInfo,0,NULL,1,ExtensionArrForvkDeviceCreateInfo,NULL);
    VkDeviceCreateInfo* vkDeviceCreateInfoPtr = &vkDeviceCreateInfo;

    VkDevice vkActualDevice {};
    VkDevice* vkActualDevicePtr = &vkActualDevice;
    VkResult vkResultForActualDeviceCreation = vkCreateDevice(vkDevice,vkDeviceCreateInfoPtr,nullptr,vkActualDevicePtr);

    if (vkResultForActualDeviceCreation != VK_SUCCESS)
    {
        return;
    }

    VkQueue vkQueue {};
    VkQueue* vkQueuePtr = &vkQueue;

    vkGetDeviceQueue(vkActualDevice,graphicsQueueFamilyIndex,0,vkQueuePtr);

    VkPhysicalDeviceSurfaceInfo2KHR vkPhysicalDeviceSurfaceInfo2KHR = VkPhysicalDeviceSurfaceInfo2KHR(VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SURFACE_INFO_2_KHR,NULL,vkSurfaceKHR);
    VkPhysicalDeviceSurfaceInfo2KHR* vkPhysicalDeviceSurfaceInfo2KHRptr = &vkPhysicalDeviceSurfaceInfo2KHR;

    VkSurfaceCapabilities2KHR vkSurfaceCapabilities2KHR {};
    vkSurfaceCapabilities2KHR.sType = VK_STRUCTURE_TYPE_SURFACE_CAPABILITIES_2_KHR;
    VkSurfaceCapabilities2KHR* vkSurfaceCapabilities2KHRptr = &vkSurfaceCapabilities2KHR;

    vkGetPhysicalDeviceSurfaceCapabilities2KHR(vkDevice,vkPhysicalDeviceSurfaceInfo2KHRptr,vkSurfaceCapabilities2KHRptr);

    uint32_t physicalDeviceSurfaceFormatCount {};
    uint32_t* physicalDeviceSurfaceFormatCountPtr = &physicalDeviceSurfaceFormatCount;
    
    vkGetPhysicalDeviceSurfaceFormats2KHR(vkDevice,vkPhysicalDeviceSurfaceInfo2KHRptr,physicalDeviceSurfaceFormatCountPtr,NULL)

    std::vector<VkSurfaceFormat2KHR> vkVectorSurfaceFormats2KHR(physicalDeviceSurfaceFormatCount);
    VkSurfaceFormat2KHR* vkVectorSurfaceFormats2KHRPtr = vkVectorSurfaceFormats2KHR.data();

    for (int i=0;i<physicalDeviceSurfaceFormatCount;i++)
    {
        vkVectorSurfaceFormats2KHR[i].sType = VK_STRUCTURE_TYPE_SURFACE_FORMAT_2_KHR;
    }

    vkGetPhysicalDeviceSurfaceFormats2KHR(vkDevice,vkPhysicalDeviceSurfaceInfo2KHRptr,physicalDeviceSurfaceFormatCountPtr,vkVectorSurfaceFormats2KHRPtr);

    VkSurfaceFormat2KHR vkChosenSurfaceFormat2KHR {};

    bool foundVkChosenSurfaceFormat2KHR = false;

    for (int i=0;i<physicalDeviceSurfaceFormatCount;i++)
    {
        if (vkVectorSurfaceFormats2KHR[i].surfaceFormat.format == VK_FORMAT_B8G8R8A8_SRGB)
        {
            if (vkVectorSurfaceFormats2KHR[i].surfaceFormat.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR)
            {
                vkChosenSurfaceFormat2KHR = vkVectorSurfaceFormats2KHR[i];
                foundVkChosenSurfaceFormat2KHR = true;
                break;
            }
        }
    }

    if (foundVkChosenSurfaceFormat2KHR == false)
    {
        return;
    }
}