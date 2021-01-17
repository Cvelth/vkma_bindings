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

#define VKMA_NULL_HANDLE VK_NULL_HANDLE

VK_DEFINE_HANDLE(VkmaAllocator) // parent: none
VK_DEFINE_HANDLE(VkmaBuffer) // parent: VkmaAllocator
VK_DEFINE_HANDLE(VkmaImage) // parent: VkmaAllocator
VK_DEFINE_NON_DISPATCHABLE_HANDLE(VkmaAllocation) // parent: VkmaAllocator
VK_DEFINE_NON_DISPATCHABLE_HANDLE(VkmaDefragmentationContext) // parent: VkmaAllocator
VK_DEFINE_NON_DISPATCHABLE_HANDLE(VkmaPool) // parent: VkmaAllocator

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

typedef void(VKAPI_PTR * PFN_vkmaAllocateDeviceMemoryFunction) (VkmaAllocator allocator, uint32_t memoryType, VkDeviceMemory memory, VkDeviceSize size, void *pUserData);
typedef void(VKAPI_PTR * PFN_vkmaFreeDeviceMemoryFunction) (VkmaAllocator allocator, uint32_t memoryType, VkDeviceMemory memory, VkDeviceSize size, void *pUserData);

using VkmaAllocationInfo = VmaAllocationInfo;
using VkmaBudget = VmaBudget;
using VkmaDefragmentationStats = VmaDefragmentationStats;
using VkmaPoolStats = VmaPoolStats;
using VkmaStatInfo = VmaStatInfo;

typedef struct VkmaAllocationCreateInfo {
    VkmaAllocationCreateFlags flags;
    VkmaMemoryUsage usage;
    VkMemoryPropertyFlags requiredFlags;
    VkMemoryPropertyFlags preferredFlags;
    uint32_t memoryTypeBits;
    VkmaPool VMA_NULLABLE pool;
    void* VMA_NULLABLE pUserData;
    float priority;
} VkmaAllocationCreateInfo;
static_assert(sizeof(VkmaAllocationCreateInfo) == sizeof(VmaAllocationCreateInfo), "struct and wrapper have different size!");
static_assert(std::is_standard_layout<VkmaAllocationCreateInfo>::value, "struct wrapper is not a standard layout!");

typedef struct VkmaDeviceMemoryCallbacks {
    PFN_vkmaAllocateDeviceMemoryFunction VMA_NULLABLE pfnAllocate;
    PFN_vkmaFreeDeviceMemoryFunction VMA_NULLABLE pfnFree;
    void *VMA_NULLABLE pUserData;
} VkmaDeviceMemoryCallbacks;
static_assert(sizeof(VkmaDeviceMemoryCallbacks) == sizeof(VmaDeviceMemoryCallbacks), "struct and wrapper have different size!");
static_assert(std::is_standard_layout<VkmaDeviceMemoryCallbacks>::value, "struct wrapper is not a standard layout!");

typedef struct VkmaRecordSettings {
    VkmaRecordFlags flags;
    const char *VMA_NOT_NULL pFilePath;
} VkmaRecordSettings;
static_assert(sizeof(VkmaRecordSettings) == sizeof(VmaRecordSettings), "struct and wrapper have different size!");
static_assert(std::is_standard_layout<VkmaRecordSettings>::value, "struct wrapper is not a standard layout!");

typedef struct VkmaVulkanFunctions {
    PFN_vkGetPhysicalDeviceProperties vkGetPhysicalDeviceProperties;
    PFN_vkGetPhysicalDeviceMemoryProperties vkGetPhysicalDeviceMemoryProperties;
    PFN_vkAllocateMemory vkAllocateMemory;
    PFN_vkFreeMemory vkFreeMemory;
    PFN_vkMapMemory vkMapMemory;
    PFN_vkUnmapMemory vkUnmapMemory;
    PFN_vkFlushMappedMemoryRanges vkFlushMappedMemoryRanges;
    PFN_vkInvalidateMappedMemoryRanges vkInvalidateMappedMemoryRanges;
    PFN_vkBindBufferMemory vkBindBufferMemory;
    PFN_vkBindImageMemory vkBindImageMemory;
    PFN_vkGetBufferMemoryRequirements vkGetBufferMemoryRequirements;
    PFN_vkGetImageMemoryRequirements vkGetImageMemoryRequirements;
    PFN_vkCreateBuffer vkCreateBuffer;
    PFN_vkDestroyBuffer vkDestroyBuffer;
    PFN_vkCreateImage vkCreateImage;
    PFN_vkDestroyImage vkDestroyImage;
    PFN_vkCmdCopyBuffer vkCmdCopyBuffer;
    
    PFN_vkGetBufferMemoryRequirements2KHR vkGetBufferMemoryRequirements2KHR;
    PFN_vkGetImageMemoryRequirements2KHR vkGetImageMemoryRequirements2KHR;
    
    PFN_vkBindBufferMemory2KHR vkBindBufferMemory2KHR;
    PFN_vkBindImageMemory2KHR vkBindImageMemory2KHR;
    
    PFN_vkGetPhysicalDeviceMemoryProperties2KHR vkGetPhysicalDeviceMemoryProperties2KHR;
} VkmaVulkanFunctions;
static_assert(sizeof(VkmaVulkanFunctions) >= sizeof(VmaVulkanFunctions), "struct and wrapper have different size!");
static_assert(std::is_standard_layout<VkmaVulkanFunctions>::value, "struct wrapper is not a standard layout!");

typedef struct VkmaAllocatorCreateInfo {
    VkmaAllocatorCreateFlags flags;
    VkPhysicalDevice VMA_NOT_NULL physicalDevice;
    VkDevice VMA_NOT_NULL device;
    VkDeviceSize preferredLargeHeapBlockSize;
    const VkAllocationCallbacks* VMA_NULLABLE pAllocationCallbacks;
    const VkmaDeviceMemoryCallbacks* VMA_NULLABLE pDeviceMemoryCallbacks;
    uint32_t frameInUseCount;
    const VkDeviceSize* VMA_NULLABLE VMA_LEN_IF_NOT_NULL("VkPhysicalDeviceMemoryProperties::memoryHeapCount") pHeapSizeLimit;
    const VkmaVulkanFunctions* VMA_NULLABLE pVulkanFunctions;
    const VkmaRecordSettings* VMA_NULLABLE pRecordSettings;
    VkInstance VMA_NOT_NULL instance;
    uint32_t vulkanApiVersion;
} VkmaAllocatorCreateInfo;
static_assert(sizeof(VkmaAllocatorCreateInfo) == sizeof(VmaAllocatorCreateInfo), "struct and wrapper have different size!");
static_assert(std::is_standard_layout<VkmaAllocatorCreateInfo>::value, "struct wrapper is not a standard layout!");

typedef struct VkmaDefragmentationInfo2 {
    VkmaDefragmentationFlags flags;
    uint32_t allocationCount;
    const VkmaAllocation VMA_NOT_NULL * VMA_NULLABLE VMA_LEN_IF_NOT_NULL(allocationCount) pAllocations;
    VkBool32* VMA_NULLABLE VMA_LEN_IF_NOT_NULL(allocationCount) pAllocationsChanged;
    uint32_t poolCount;
    const VkmaPool VMA_NOT_NULL * VMA_NULLABLE VMA_LEN_IF_NOT_NULL(poolCount) pPools;
    VkDeviceSize maxCpuBytesToMove;
    uint32_t maxCpuAllocationsToMove;
    VkDeviceSize maxGpuBytesToMove;
    uint32_t maxGpuAllocationsToMove;
    VkCommandBuffer VMA_NULLABLE commandBuffer;
} VkmaDefragmentationInfo2;
static_assert(sizeof(VkmaDefragmentationInfo2) == sizeof(VmaDefragmentationInfo2), "struct and wrapper have different size!");
static_assert(std::is_standard_layout<VkmaDefragmentationInfo2>::value, "struct wrapper is not a standard layout!");

typedef struct VkmaPoolCreateInfo {
    uint32_t memoryTypeIndex;
    VkmaPoolCreateFlags flags;
    VkDeviceSize blockSize;
    size_t minBlockCount;
    size_t maxBlockCount;
    uint32_t frameInUseCount;
    float priority;
} VkmaPoolCreateInfo;
static_assert(sizeof(VkmaPoolCreateInfo) == sizeof(VmaPoolCreateInfo), "struct and wrapper have different size!");
static_assert(std::is_standard_layout<VkmaPoolCreateInfo>::value, "struct wrapper is not a standard layout!");

typedef struct VkmaStats {
    VkmaStatInfo memoryType[VK_MAX_MEMORY_TYPES];
    VkmaStatInfo memoryHeap[VK_MAX_MEMORY_HEAPS];
    VkmaStatInfo total;
} VkmaStats;
static_assert(sizeof(VkmaStats) == sizeof(VmaStats), "struct and wrapper have different size!");
static_assert(std::is_standard_layout<VkmaStats>::value, "struct wrapper is not a standard layout!");

// [[deprecated]]
// using VkmaDefragmentationInfo = VmaDefragmentationInfo;

inline VkmaResult vkmaCreateAllocator(const VkmaAllocatorCreateInfo *pCreateInfo, VkmaAllocator *pAllocator) {
    return vmaCreateAllocator(reinterpret_cast<const VmaAllocatorCreateInfo *>(pCreateInfo), reinterpret_cast<VmaAllocator *>(pAllocator));
}
inline void vkmaDestroyAllocator(VkmaAllocator allocator) {
    return vmaDestroyAllocator(reinterpret_cast<VmaAllocator>(allocator));
}

inline void vkmaGetPhysicalDeviceProperties(VkmaAllocator allocator, VkPhysicalDeviceProperties *pPhysicalDeviceProperties) {
    VMA_ASSERT(pPhysicalDeviceProperties);
    const VkPhysicalDeviceProperties *temp = nullptr;
    vmaGetPhysicalDeviceProperties(reinterpret_cast<VmaAllocator>(allocator), &temp);

    VMA_ASSERT(temp);
    memcpy(pPhysicalDeviceProperties, temp, sizeof(VkPhysicalDeviceProperties));
}
inline void vkmaGetMemoryProperties(VkmaAllocator allocator, VkPhysicalDeviceMemoryProperties *pPhysicalDeviceMemoryProperties) {
    VMA_ASSERT(pPhysicalDeviceMemoryProperties);
    const VkPhysicalDeviceMemoryProperties *temp = nullptr;
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
    vmaCalculateStats(reinterpret_cast<VmaAllocator>(allocator), reinterpret_cast<VmaStats *>(pStats));
}
inline void vkmaGetBudget(VkmaAllocator allocator, VkmaBudget *pBudget) {
    vmaGetBudget(reinterpret_cast<VmaAllocator>(allocator), pBudget);
}
inline void vkmaBuildStatsString(VkmaAllocator allocator, VkBool32 detailedMap, char **ppStatsString) {
    vmaBuildStatsString(reinterpret_cast<VmaAllocator>(allocator), ppStatsString, detailedMap);
}
inline void vkmaFreeStatsString(VkmaAllocator allocator, const char *pStatsString) {
    vmaFreeStatsString(reinterpret_cast<VmaAllocator>(allocator), const_cast<char *>(pStatsString));
}

inline VkmaResult vkmaFindMemoryTypeIndex(VkmaAllocator allocator, uint32_t memoryTypeBits, const VkmaAllocationCreateInfo *pAllocationCreateInfo, uint32_t *pMemoryTypeIndex) {
    return vmaFindMemoryTypeIndex(reinterpret_cast<VmaAllocator>(allocator), memoryTypeBits, reinterpret_cast<const VmaAllocationCreateInfo *>(pAllocationCreateInfo), pMemoryTypeIndex);
}
inline VkmaResult vkmaFindMemoryTypeIndexForBufferInfo(VkmaAllocator allocator, const VkBufferCreateInfo *pBufferCreateInfo, const VkmaAllocationCreateInfo *pAllocationCreateInfo, uint32_t *pMemoryTypeIndex) {
    return vmaFindMemoryTypeIndexForBufferInfo(reinterpret_cast<VmaAllocator>(allocator), pBufferCreateInfo, reinterpret_cast<const VmaAllocationCreateInfo *>(pAllocationCreateInfo), pMemoryTypeIndex);
}
inline VkmaResult vkmaFindMemoryTypeIndexForImageInfo(VkmaAllocator allocator, const VkImageCreateInfo *pImageCreateInfo, const VkmaAllocationCreateInfo *pAllocationCreateInfo, uint32_t *pMemoryTypeIndex) {
    return vmaFindMemoryTypeIndexForImageInfo(reinterpret_cast<VmaAllocator>(allocator), pImageCreateInfo, reinterpret_cast<const VmaAllocationCreateInfo *>(pAllocationCreateInfo), pMemoryTypeIndex);
}

inline VkmaResult vkmaCreatePool(VkmaAllocator allocator, const VkmaPoolCreateInfo *pCreateInfo, VkmaPool *pPool) {
    return vmaCreatePool(reinterpret_cast<VmaAllocator>(allocator), reinterpret_cast<const VmaPoolCreateInfo *>(pCreateInfo), reinterpret_cast<VmaPool *>(pPool));
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
inline void vkmaGetPoolName(VkmaAllocator allocator, VkmaPool pool, const char **ppName) {
    vmaGetPoolName(reinterpret_cast<VmaAllocator>(allocator), reinterpret_cast<VmaPool>(pool), ppName);
}
inline void vkmaSetPoolName(VkmaAllocator allocator, VkmaPool pool, const char *pName) {
    vmaSetPoolName(reinterpret_cast<VmaAllocator>(allocator), reinterpret_cast<VmaPool>(pool), pName);
}

inline VkmaResult vkmaAllocateMemory(VkmaAllocator allocator, const VkMemoryRequirements *pVkMemoryRequirements, const VkmaAllocationCreateInfo *pCreateInfo, VkmaAllocation *pAllocation) {
    return vmaAllocateMemory(reinterpret_cast<VmaAllocator>(allocator), pVkMemoryRequirements, reinterpret_cast<const VmaAllocationCreateInfo *>(pCreateInfo), reinterpret_cast<VmaAllocation *>(pAllocation), nullptr);
}
inline VkmaResult vkmaAllocateMemoryPages(VkmaAllocator allocator, const VkMemoryRequirements *pVkMemoryRequirements, const VkmaAllocationCreateInfo *pCreateInfo, size_t allocationCount, VkmaAllocation *pAllocations) {
    return vmaAllocateMemoryPages(reinterpret_cast<VmaAllocator>(allocator), pVkMemoryRequirements, reinterpret_cast<const VmaAllocationCreateInfo *>(pCreateInfo), allocationCount, reinterpret_cast<VmaAllocation *>(pAllocations), nullptr);
}
inline VkmaResult vkmaAllocateMemoryForBuffer(VkmaAllocator allocator, VkBuffer buffer, const VkmaAllocationCreateInfo *pCreateInfo, VkmaAllocation *pAllocation) {
    return vmaAllocateMemoryForBuffer(reinterpret_cast<VmaAllocator>(allocator), buffer, reinterpret_cast<const VmaAllocationCreateInfo *>(pCreateInfo), reinterpret_cast<VmaAllocation *>(pAllocation), nullptr);
}
inline VkmaResult vkmaAllocateMemoryForImage(VkmaAllocator allocator, VkImage image, const VkmaAllocationCreateInfo *pCreateInfo, VkmaAllocation *pAllocation) {
    return vmaAllocateMemoryForImage(reinterpret_cast<VmaAllocator>(allocator), image, reinterpret_cast<const VmaAllocationCreateInfo *>(pCreateInfo), reinterpret_cast<VmaAllocation *>(pAllocation), nullptr);
}
inline void vkmaFreeMemory(VkmaAllocator allocator, const VkmaAllocation allocation) {
    vmaFreeMemory(reinterpret_cast<VmaAllocator>(allocator), reinterpret_cast<VmaAllocation>(allocation));
}
inline void vkmaFreeMemoryPages(VkmaAllocator allocator, size_t allocationCount, const VkmaAllocation *pAllocations) {
    vmaFreeMemoryPages(reinterpret_cast<VmaAllocator>(allocator), allocationCount, reinterpret_cast<const VmaAllocation *>(pAllocations));
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
inline void vkmaSetAllocationUserData(VkmaAllocator allocator, VkmaAllocation allocation, const void *pUserData) {
    vmaSetAllocationUserData(reinterpret_cast<VmaAllocator>(allocator), reinterpret_cast<VmaAllocation>(allocation), const_cast<void *>(pUserData));
}
inline VkmaResult vkmaCreateLostAllocation(VkmaAllocator allocator, VkmaAllocation *pAllocation) {
    vmaCreateLostAllocation(reinterpret_cast<VmaAllocator>(allocator), reinterpret_cast<VmaAllocation *>(pAllocation));
    return VK_SUCCESS;
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
inline VkmaResult vkmaCreateDefragmentationContext(VkmaAllocator allocator, const VkmaDefragmentationInfo2 *pInfo, VkmaDefragmentationContext *pContext) {
    return vmaDefragmentationBegin(reinterpret_cast<VmaAllocator>(allocator), reinterpret_cast<const VmaDefragmentationInfo2 *>(pInfo), nullptr, reinterpret_cast<VmaDefragmentationContext *>(pContext));
}
inline VkmaResult vkmaDestroyDefragmentationContext(VkmaAllocator allocator, VkmaDefragmentationContext context) {
    return vmaDefragmentationEnd(reinterpret_cast<VmaAllocator>(allocator), reinterpret_cast<VmaDefragmentationContext>(context));
}

inline VkmaResult vkmaBindBufferMemory(VkmaAllocator allocator, VkmaAllocation allocation, VkBuffer buffer) {
    return vmaBindBufferMemory(reinterpret_cast<VmaAllocator>(allocator), reinterpret_cast<VmaAllocation>(allocation), buffer);
}
inline VkmaResult vkmaBindBufferMemory2(VkmaAllocator allocator, VkmaAllocation allocation, VkDeviceSize allocationLocalOffset, VkBuffer buffer, const void *pNext) {
    return vmaBindBufferMemory2(reinterpret_cast<VmaAllocator>(allocator), reinterpret_cast<VmaAllocation>(allocation), allocationLocalOffset, buffer, pNext);
}
inline VkmaResult vkmaBindImageMemory(VkmaAllocator allocator, VkmaAllocation allocation, VkImage image) {
    return vmaBindImageMemory(reinterpret_cast<VmaAllocator>(allocator), reinterpret_cast<VmaAllocation>(allocation), image);
}
inline VkmaResult vkmaBindImageMemory2(VkmaAllocator allocator, VkmaAllocation allocation, VkDeviceSize allocationLocalOffset, VkImage image, const void *pNext) {
    return vmaBindImageMemory2(reinterpret_cast<VmaAllocator>(allocator), reinterpret_cast<VmaAllocation>(allocation), allocationLocalOffset, image, pNext);
}

inline VkmaResult vkmaCreateBuffer(VkmaAllocator allocator, const VkBufferCreateInfo *pBufferCreateInfo, const VkmaAllocationCreateInfo *pAllocationCreateInfo, VkmaBuffer *pBuffer) {
    VMA_ASSERT(pBuffer && *pBuffer);
    *pBuffer = reinterpret_cast<VkmaBuffer>(new VkmaBuffer_T{});
    return vmaCreateBuffer(reinterpret_cast<VmaAllocator>(allocator), pBufferCreateInfo, reinterpret_cast<const VmaAllocationCreateInfo *>(pAllocationCreateInfo), &reinterpret_cast<VkmaBuffer_T *>(*pBuffer)->buffer, reinterpret_cast<VmaAllocation *>(&reinterpret_cast<VkmaBuffer_T *>(*pBuffer)->allocation), nullptr);
}
inline void vkmaDestroyBuffer(VkmaAllocator allocator, VkmaBuffer buffer) {
    VMA_ASSERT(buffer);
    vmaDestroyBuffer(reinterpret_cast<VmaAllocator>(allocator), reinterpret_cast<VkmaBuffer_T *>(buffer)->buffer, reinterpret_cast<VmaAllocation>(reinterpret_cast<VkmaBuffer_T *>(buffer)->allocation));
    delete reinterpret_cast<VkmaBuffer_T *>(buffer);
}
inline VkmaResult vkmaCreateImage(VkmaAllocator allocator, const VkImageCreateInfo *pImageCreateInfo, const VkmaAllocationCreateInfo *pAllocationCreateInfo, VkmaImage *pImage) {
    VMA_ASSERT(pImage && *pImage);
    *pImage = reinterpret_cast<VkmaImage>(new VkmaImage_T{});
    return vmaCreateImage(reinterpret_cast<VmaAllocator>(allocator), pImageCreateInfo, reinterpret_cast<const VmaAllocationCreateInfo *>(pAllocationCreateInfo), &reinterpret_cast<VkmaImage_T *>(*pImage)->image, reinterpret_cast<VmaAllocation *>(&reinterpret_cast<VkmaImage_T *>(*pImage)->allocation), nullptr);
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
// VkmaResult vkmaDefragment(VkmaAllocator allocator, const VkmaAllocation *pAllocations, size_t allocationCount, VkBool32 *pAllocationsChanged, const VkmaDefragmentationInfo *pDefragmentationInfo, VkmaDefragmentationStats *pDefragmentationStats)

#endif // VKMA_BINDINGS_HPP