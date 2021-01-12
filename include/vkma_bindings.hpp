#ifndef VKMA_BINDINGS_HPP
#define VKMA_BINDINGS_HPP

#ifdef VKMA_IMPLEMENTATION
# define VMA_IMPLEMENTATION
#endif

#include <vk_mem_alloc.h>

#ifdef VMA_RECORDING_ENABLED
# define VKMA_RECORDING_ENABLED VMA_RECORDING_ENABLED
#endif
#ifdef VMA_VULKAN_VERSION
# define VKMA_VULKAN_VERSION VMA_VULKAN_VERSION
#endif
#ifdef VMA_DEDICATED_ALLOCATION
# define VKMA_DEDICATED_ALLOCATION VMA_DEDICATED_ALLOCATION
#endif
#ifdef VMA_BIND_MEMORY2
# define VKMA_BIND_MEMORY2 VMA_BIND_MEMORY2
#endif
#ifdef VMA_MEMORY_BUDGET
# define VKMA_MEMORY_BUDGET VMA_MEMORY_BUDGET
#endif
#ifdef VMA_STATS_STRING_ENABLED
# define VKMA_STATS_STRING_ENABLED VMA_STATS_STRING_ENABLED
#endif

VK_DEFINE_HANDLE(VkmaAllocator)
VK_DEFINE_HANDLE(VkmaBuffer)
VK_DEFINE_HANDLE(VkmaImage)
VK_DEFINE_NON_DISPATCHABLE_HANDLE(VkmaAllocation)
VK_DEFINE_NON_DISPATCHABLE_HANDLE(VkmaDefragmentationContext)
VK_DEFINE_NON_DISPATCHABLE_HANDLE(VkmaPool)

struct VkmaBuffer_T {
    VkBuffer buffer;
    VkmaAllocation allocation;
};
static_assert(sizeof(VkmaBuffer_T) == sizeof(VkBuffer) + sizeof(VkmaAllocation), "struct and wrapper have different size!");
static_assert(std::is_standard_layout<VkmaBuffer_T>::value, "struct wrapper is not a standard layout!");

struct VkmaImage_T {
    VkImage image;
    VkmaAllocation allocation;
};
static_assert(sizeof(VkmaImage_T) == sizeof(VkImage) + sizeof(VkmaAllocation), "struct and wrapper have different size!");
static_assert(std::is_standard_layout<VkmaImage_T>::value, "struct wrapper is not a standard layout!");

using VkmaResult = VkResult;

using VkmaAllocatorCreateFlagBits = VmaAllocatorCreateFlagBits;
using VkmaRecordFlagBits = VmaRecordFlagBits;
using VkmaMemoryUsage = VmaMemoryUsage;
using VkmaAllocationCreateFlagBits = VmaAllocationCreateFlagBits;
using VkmaPoolCreateFlagBits = VmaPoolCreateFlagBits;
using VkmaDefragmentationFlagBits = VmaDefragmentationFlagBits;

using VkmaAllocatorCreateFlags = VmaAllocatorCreateFlags;
using VkmaRecordFlags = VmaRecordFlags;
using VkmaAllocationCreateFlags = VmaAllocationCreateFlags;
using VkmaPoolCreateFlags = VmaPoolCreateFlags;
using VkmaDefragmentationFlags = VmaDefragmentationFlags;

using PFN_vkmaAllocateDeviceMemoryFunction = PFN_vmaAllocateDeviceMemoryFunction;
using PFN_vkmaFreeDeviceMemoryFunction = PFN_vmaFreeDeviceMemoryFunction;

using VkmaAllocationCreateInfo = VmaAllocationCreateInfo;
using VkmaAllocationInfo = VmaAllocationInfo;
using VkmaAllocatorCreateInfo = VmaAllocatorCreateInfo;
using VkmaBudget = VmaBudget;
using VkmaDefragmentationInfo2 = VmaDefragmentationInfo2;
using VkmaDefragmentationStats = VmaDefragmentationStats;
using VkmaDeviceMemoryCallbacks = VmaDeviceMemoryCallbacks;
using VkmaPoolCreateInfo = VmaPoolCreateInfo;
using VkmaPoolStats = VmaPoolStats;
using VkmaRecordSettings = VmaRecordSettings;
using VkmaStatInfo = VmaStatInfo;
using VkmaStats = VmaStats;
using VkmaVulkanFunctions = VmaVulkanFunctions;

// [[deprecated]]
// using VkmaDefragmentationInfo = VmaDefragmentationInfo;

inline VkmaResult vkmaCreateAllocator(VkmaAllocatorCreateInfo const *pCreateInfo, VkmaAllocator *pAllocator) {
    return vmaCreateAllocator(pCreateInfo, reinterpret_cast<VmaAllocator *>(pAllocator));
}
inline void vkmaDestroyAllocator(VkmaAllocator allocator) {
    return vmaDestroyAllocator(reinterpret_cast<VmaAllocator>(allocator));
}

inline void vkmaGetPhysicalDeviceProperties(VkmaAllocator allocator, VkPhysicalDeviceProperties *pPhysicalDeviceProperties) {
    VMA_ASSERT(pPhysicalDeviceProperties);
    VkPhysicalDeviceProperties const *temp = nullptr;
    vmaGetPhysicalDeviceProperties(reinterpret_cast<VmaAllocator>(allocator), &temp);

    VMA_ASSERT(temp);
    memcpy(pPhysicalDeviceProperties, temp, sizeof(VkPhysicalDeviceProperties));
}
inline void vkmaGetMemoryProperties(VkmaAllocator allocator, VkPhysicalDeviceMemoryProperties *pPhysicalDeviceMemoryProperties) {
    VMA_ASSERT(pPhysicalDeviceMemoryProperties);
    VkPhysicalDeviceMemoryProperties const *temp = nullptr;
    vmaGetMemoryProperties(reinterpret_cast<VmaAllocator>(allocator), &temp);

    VMA_ASSERT(temp);
    memcpy(pPhysicalDeviceMemoryProperties, temp, sizeof(VkPhysicalDeviceMemoryProperties));
}
inline void vkmaGetMemoryTypeProperties(VkmaAllocator allocator, uint32_t memoryTypeIndex, VkMemoryPropertyFlags *pFlags) {
    vmaGetMemoryTypeProperties(reinterpret_cast<VmaAllocator>(allocator), memoryTypeIndex, pFlags);
}

inline void vkmaSetCurrentFrameIndex(VkmaAllocator allocator, uint32_t frameIndex) {
    vmaSetCurrentFrameIndex(reinterpret_cast<VmaAllocator>(allocator), frameIndex);
}

inline void vkmaCalculateStats(VkmaAllocator allocator, VkmaStats *pStats) {
    vmaCalculateStats(reinterpret_cast<VmaAllocator>(allocator), pStats);
}
inline void vkmaGetBudget(VkmaAllocator allocator, VkmaBudget *pBudget) {
    vmaGetBudget(reinterpret_cast<VmaAllocator>(allocator), pBudget);
}
inline void vkmaBuildStatsString(VkmaAllocator allocator, VkBool32 detailedMap, char **ppStatsString) {
    vmaBuildStatsString(reinterpret_cast<VmaAllocator>(allocator), ppStatsString, detailedMap);
}
inline void vkmaFreeStatsString(VkmaAllocator allocator, char *pStatsString) {
    vmaFreeStatsString(reinterpret_cast<VmaAllocator>(allocator), pStatsString);
}

inline VkmaResult vkmaFindMemoryTypeIndex(VkmaAllocator allocator, uint32_t memoryTypeBits, VkmaAllocationCreateInfo const *pAllocationCreateInfo, uint32_t *pMemoryTypeIndex) {
    return vmaFindMemoryTypeIndex(reinterpret_cast<VmaAllocator>(allocator), memoryTypeBits, pAllocationCreateInfo, pMemoryTypeIndex);
}
inline VkmaResult vkmaFindMemoryTypeIndexForBufferInfo(VkmaAllocator allocator, VkBufferCreateInfo const *pBufferCreateInfo, VkmaAllocationCreateInfo const *pAllocationCreateInfo, uint32_t *pMemoryTypeIndex) {
    return vmaFindMemoryTypeIndexForBufferInfo(reinterpret_cast<VmaAllocator>(allocator), pBufferCreateInfo, pAllocationCreateInfo, pMemoryTypeIndex);
}
inline VkmaResult vkmaFindMemoryTypeIndexForImageInfo(VkmaAllocator allocator, VkImageCreateInfo const *pImageCreateInfo, VkmaAllocationCreateInfo const *pAllocationCreateInfo, uint32_t *pMemoryTypeIndex) {
    return vmaFindMemoryTypeIndexForImageInfo(reinterpret_cast<VmaAllocator>(allocator), pImageCreateInfo, pAllocationCreateInfo, pMemoryTypeIndex);
}

inline VkmaResult vkmaCreatePool(VkmaAllocator allocator, VkmaPoolCreateInfo const *pCreateInfo, VkmaPool *pPool) {
    return vmaCreatePool(reinterpret_cast<VmaAllocator>(allocator), pCreateInfo, reinterpret_cast<VmaPool *>(pPool));
}
inline void vkmaDestroyPool(VkmaAllocator allocator, VkmaPool pool) {
    vmaDestroyPool(reinterpret_cast<VmaAllocator>(allocator), reinterpret_cast<VmaPool>(pool));
}
inline void vkmaGetPoolStats(VkmaAllocator allocator, VkmaPool pool, VkmaPoolStats *pPoolStats) {
    vmaGetPoolStats(reinterpret_cast<VmaAllocator>(allocator), reinterpret_cast<VmaPool>(pool), pPoolStats);
}
inline void vkmaMakePoolAllocationsLost(VkmaAllocator allocator, VkmaPool pool, size_t *pLostAllocationCount) {
    vmaMakePoolAllocationsLost(reinterpret_cast<VmaAllocator>(allocator), reinterpret_cast<VmaPool>(pool), pLostAllocationCount);
}
inline VkmaResult vkmaCheckPoolCorruption(VkmaAllocator allocator, VkmaPool pool) {
    return vmaCheckPoolCorruption(reinterpret_cast<VmaAllocator>(allocator), reinterpret_cast<VmaPool>(pool));
}
inline void vkmaGetPoolName(VkmaAllocator allocator, VkmaPool pool, char const **ppName) {
    vmaGetPoolName(reinterpret_cast<VmaAllocator>(allocator), reinterpret_cast<VmaPool>(pool), ppName);
}
inline void vkmaSetPoolName(VkmaAllocator allocator, VkmaPool pool, char const *pName) {
    vmaSetPoolName(reinterpret_cast<VmaAllocator>(allocator), reinterpret_cast<VmaPool>(pool), pName);
}

inline VkmaResult vkmaAllocateMemory(VkmaAllocator allocator, VkMemoryRequirements const *pVkMemoryRequirements, VkmaAllocationCreateInfo const *pCreateInfo, VkmaAllocation *pAllocation) {
    return vmaAllocateMemory(reinterpret_cast<VmaAllocator>(allocator), pVkMemoryRequirements, pCreateInfo, reinterpret_cast<VmaAllocation *>(pAllocation), nullptr);
}
inline VkmaResult vkmaAllocateMemoryPages(VkmaAllocator allocator, VkMemoryRequirements const *pVkMemoryRequirements, VkmaAllocationCreateInfo const *pCreateInfo, size_t allocationCount, VkmaAllocation *pAllocations) {
    return vmaAllocateMemoryPages(reinterpret_cast<VmaAllocator>(allocator), pVkMemoryRequirements, pCreateInfo, allocationCount, reinterpret_cast<VmaAllocation *>(pAllocations), nullptr);
}
inline VkmaResult vkmaAllocateMemoryForBuffer(VkmaAllocator allocator, VkBuffer buffer, VkmaAllocationCreateInfo const *pCreateInfo, VkmaAllocation *pAllocation) {
    return vmaAllocateMemoryForBuffer(reinterpret_cast<VmaAllocator>(allocator), buffer, pCreateInfo, reinterpret_cast<VmaAllocation *>(pAllocation), nullptr);
}
inline VkmaResult vkmaAllocateMemoryForImage(VkmaAllocator allocator, VkImage image, VkmaAllocationCreateInfo const *pCreateInfo, VkmaAllocation *pAllocation) {
    return vmaAllocateMemoryForImage(reinterpret_cast<VmaAllocator>(allocator), image, pCreateInfo, reinterpret_cast<VmaAllocation *>(pAllocation), nullptr);
}
inline void vkmaFreeMemory(VkmaAllocator allocator, VkmaAllocation const allocation) {
    vmaFreeMemory(reinterpret_cast<VmaAllocator>(allocator), reinterpret_cast<VmaAllocation>(allocation));
}
inline void vkmaFreeMemoryPages(VkmaAllocator allocator, size_t allocationCount, VkmaAllocation const *pAllocations) {
    vmaFreeMemoryPages(reinterpret_cast<VmaAllocator>(allocator), allocationCount, reinterpret_cast<VmaAllocation const *>(pAllocations));
}
inline VkmaResult vkmaResizeAllocation(VkmaAllocator allocator, VkmaAllocation allocation, VkDeviceSize newSize) {
    return vmaResizeAllocation(reinterpret_cast<VmaAllocator>(allocator), reinterpret_cast<VmaAllocation>(allocation), newSize);
}
inline void vkmaGetAllocationInfo(VkmaAllocator allocator, VkmaAllocation allocation, VkmaAllocationInfo *pAllocationInfo) {
    vmaGetAllocationInfo(reinterpret_cast<VmaAllocator>(allocator), reinterpret_cast<VmaAllocation>(allocation), pAllocationInfo);
}
VkBool32 vkmaTouchAllocation(VkmaAllocator allocator, VkmaAllocation allocation) {
    return vmaTouchAllocation(reinterpret_cast<VmaAllocator>(allocator), reinterpret_cast<VmaAllocation>(allocation));
}
inline void vkmaSetAllocationUserData(VkmaAllocator allocator, VkmaAllocation allocation, void const *pUserData) {
    vmaSetAllocationUserData(reinterpret_cast<VmaAllocator>(allocator), reinterpret_cast<VmaAllocation>(allocation), const_cast<void *>(pUserData));
}
inline void vkmaCreateLostAllocation(VkmaAllocator allocator, VkmaAllocation *pAllocation) {
    vmaCreateLostAllocation(reinterpret_cast<VmaAllocator>(allocator), reinterpret_cast<VmaAllocation *>(pAllocation));
}
inline VkmaResult vkmaMapMemory(VkmaAllocator allocator, VkmaAllocation allocation, void **ppData) {
    return vmaMapMemory(reinterpret_cast<VmaAllocator>(allocator), reinterpret_cast<VmaAllocation>(allocation), ppData);
}
inline void vkmaUnmapMemory(VkmaAllocator allocator, VkmaAllocation allocation) {
    vmaUnmapMemory(reinterpret_cast<VmaAllocator>(allocator), reinterpret_cast<VmaAllocation>(allocation));
}
inline VkmaResult vkmaFlushAllocation(VkmaAllocator allocator, VkmaAllocation allocation, VkDeviceSize offset, VkDeviceSize size) {
    return vmaFlushAllocation(reinterpret_cast<VmaAllocator>(allocator), reinterpret_cast<VmaAllocation>(allocation), offset, size);
}
inline VkmaResult vkmaInvalidateAllocation(VkmaAllocator allocator, VkmaAllocation allocation, VkDeviceSize offset, VkDeviceSize size) {
    return vmaInvalidateAllocation(reinterpret_cast<VmaAllocator>(allocator), reinterpret_cast<VmaAllocation>(allocation), offset, size);
}

inline VkmaResult vkmaCheckCorruption(VkmaAllocator allocator, uint32_t memoryTypeBits) {
    return vmaCheckCorruption(reinterpret_cast<VmaAllocator>(allocator), memoryTypeBits);
}
inline VkmaResult vkmaDefragmentationBegin(VkmaAllocator allocator, const VkmaDefragmentationInfo2 *pInfo, VkmaDefragmentationContext *pContext) {
    return vmaDefragmentationBegin(reinterpret_cast<VmaAllocator>(allocator), pInfo, nullptr, reinterpret_cast<VmaDefragmentationContext *>(pContext));
}
inline VkmaResult vkmaDefragmentationEnd(VkmaAllocator allocator, VkmaDefragmentationContext context) {
    return vmaDefragmentationEnd(reinterpret_cast<VmaAllocator>(allocator), reinterpret_cast<VmaDefragmentationContext>(context));
}

inline VkmaResult vkmaBindBufferMemory(VkmaAllocator allocator, VkmaAllocation allocation, VkBuffer buffer) {
    return vmaBindBufferMemory(reinterpret_cast<VmaAllocator>(allocator), reinterpret_cast<VmaAllocation>(allocation), buffer);
}
inline VkmaResult vkmaBindBufferMemory2(VkmaAllocator allocator, VkmaAllocation allocation, VkDeviceSize allocationLocalOffset, VkBuffer buffer, void const *pNext) {
    return vmaBindBufferMemory2(reinterpret_cast<VmaAllocator>(allocator), reinterpret_cast<VmaAllocation>(allocation), allocationLocalOffset, buffer, pNext);
}
inline VkmaResult vkmaBindImageMemory(VkmaAllocator allocator, VkmaAllocation allocation, VkImage image) {
    return vmaBindImageMemory(reinterpret_cast<VmaAllocator>(allocator), reinterpret_cast<VmaAllocation>(allocation), image);
}
inline VkmaResult vkmaBindImageMemory2(VkmaAllocator allocator, VkmaAllocation allocation, VkDeviceSize allocationLocalOffset, VkImage image, void const *pNext) {
    return vmaBindImageMemory2(reinterpret_cast<VmaAllocator>(allocator), reinterpret_cast<VmaAllocation>(allocation), allocationLocalOffset, image, pNext);
}

inline VkmaResult vkmaCreateBuffer(VkmaAllocator allocator, VkBufferCreateInfo const *pBufferCreateInfo, VkmaAllocationCreateInfo const *pAllocationCreateInfo, VkmaBuffer *pBuffer) {
    VMA_ASSERT(pBuffer && *pBuffer);
    *pBuffer = reinterpret_cast<VkmaBuffer>(new VkmaBuffer_T{});
    return vmaCreateBuffer(reinterpret_cast<VmaAllocator>(allocator), pBufferCreateInfo, pAllocationCreateInfo, &reinterpret_cast<VkmaBuffer_T *>(*pBuffer)->buffer, reinterpret_cast<VmaAllocation *>(&reinterpret_cast<VkmaBuffer_T *>(*pBuffer)->allocation), nullptr);
}
inline void vkmaDestroyBuffer(VkmaAllocator allocator, VkmaBuffer buffer) {
    VMA_ASSERT(buffer);
    vmaDestroyBuffer(reinterpret_cast<VmaAllocator>(allocator), reinterpret_cast<VkmaBuffer_T *>(buffer)->buffer, reinterpret_cast<VmaAllocation>(reinterpret_cast<VkmaBuffer_T *>(buffer)->allocation));
    delete reinterpret_cast<VkmaBuffer_T *>(buffer);
}
inline VkmaResult vkmaCreateImage(VkmaAllocator allocator, VkImageCreateInfo const *pImageCreateInfo, VkmaAllocationCreateInfo const *pAllocationCreateInfo, VkmaImage *pImage) {
    VMA_ASSERT(pImage && *pImage);
    *pImage = reinterpret_cast<VkmaImage>(new VkmaImage_T{});
    return vmaCreateImage(reinterpret_cast<VmaAllocator>(allocator), pImageCreateInfo, pAllocationCreateInfo, &reinterpret_cast<VkmaImage_T *>(*pImage)->image, reinterpret_cast<VmaAllocation *>(&reinterpret_cast<VkmaImage_T *>(*pImage)->allocation), nullptr);
}
inline void vkmaDestroyImage(VkmaAllocator allocator, VkmaImage image) {
    VMA_ASSERT(image);
    vmaDestroyImage(reinterpret_cast<VmaAllocator>(allocator), reinterpret_cast<VkmaImage_T *>(image)->image, reinterpret_cast<VmaAllocation>(reinterpret_cast<VkmaImage_T *>(image)->allocation));
    delete reinterpret_cast<VkmaImage_T *>(image);
}

inline void vkmaGetBuffer(VkmaBuffer buffer, VkBuffer *pBuffer) {
    VMA_ASSERT(pBuffer);
    *pBuffer = reinterpret_cast<VkmaBuffer_T *>(buffer)->buffer;
}
inline void vkmaGetBufferAllocation(VkmaBuffer buffer, VkmaAllocation *pAllocation) {
    VMA_ASSERT(pAllocation);
    *pAllocation = reinterpret_cast<VkmaBuffer_T *>(buffer)->allocation;
}
inline void vkmaGetImage(VkmaImage image, VkImage *pImage) {
    VMA_ASSERT(pImage);
    *pImage = reinterpret_cast<VkmaImage_T *>(image)->image;
}
inline void vkmaGetImageAllocation(VkmaImage image, VkmaAllocation *pAllocation) {
    VMA_ASSERT(pAllocation);
    *pAllocation = reinterpret_cast<VkmaImage_T *>(image)->allocation;
}

// [[deprecated]]
// VkmaResult vkmaDefragment(VkmaAllocator allocator, VkmaAllocation const *pAllocations, size_t allocationCount, VkBool32 *pAllocationsChanged, VkmaDefragmentationInfo const *pDefragmentationInfo, VkmaDefragmentationStats *pDefragmentationStats)

#endif // VKMA_BINDINGS_HPP