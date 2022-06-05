#ifndef VKMA_BINDINGS_HPP
#define VKMA_BINDINGS_HPP

#ifdef VKMA_IMPLEMENTATION
  #define VMA_IMPLEMENTATION
#endif

/*
In every place where you want to use Vulkan Memory Allocator, define appropriate
macros if you want to configure the library and then include its header to
include all public interface declarations. Example:
*/

//#define VMA_HEAVY_ASSERT(expr) assert(expr)
//#define VMA_USE_STL_CONTAINERS 1
//#define VMA_DEDICATED_ALLOCATION 0
//#define VMA_DEBUG_MARGIN 16
//#define VMA_DEBUG_DETECT_CORRUPTION 1
//#define VMA_DEBUG_INITIALIZE_ALLOCATIONS 1
//#define VMA_DEBUG_MIN_BUFFER_IMAGE_GRANULARITY 256
//#define VMA_USE_STL_SHARED_MUTEX 0
//#define VMA_DEBUG_GLOBAL_MUTEX 1
//#define VMA_MEMORY_BUDGET 0
//#define VMA_STATIC_VULKAN_FUNCTIONS 0
//#define VMA_DYNAMIC_VULKAN_FUNCTIONS 1

//#define VMA_VULKAN_VERSION 1002000 // Vulkan 1.2
//#define VMA_VULKAN_VERSION 1001000 // Vulkan 1.1
//#define VMA_VULKAN_VERSION 1000000 // Vulkan 1.0

/*
#define VMA_DEBUG_LOG(format, ...) do { \
        printf(format, __VA_ARGS__); \
        printf("\n"); \
    } while(false)
*/

#ifdef _MSVC_LANG
  #pragma warning(push, 4)
  #pragma warning(disable : 4127) // conditional expression is constant
  #pragma warning(disable : 4100) // unreferenced formal parameter
  #pragma warning(disable : 4189) // local variable is initialized but not referenced
  #pragma warning(disable : 4324) // structure was padded due to alignment specifier
#endif
#ifdef __clang__
  #pragma clang diagnostic push
  #pragma clang diagnostic ignored                                                                 \
    "-Wtautological-compare" // comparison of unsigned expression < 0 is always false
  #pragma clang diagnostic ignored "-Wunused-private-field"
  #pragma clang diagnostic ignored "-Wunused-parameter"
  #pragma clang diagnostic ignored "-Wmissing-field-initializers"
  #pragma clang diagnostic ignored "-Wnullability-completeness"
#endif

#include "vk_mem_alloc.h"

#ifdef __clang__
  #pragma clang diagnostic pop
#endif
#ifdef _MSVC_LANG
  #pragma warning(pop)
#endif

#ifndef VKMA_ASSERT
  #define VKMA_ASSERT VMA_ASSERT
#endif

#define VKMA_NULL_HANDLE VK_NULL_HANDLE

VK_DEFINE_HANDLE(VkmaAllocator)                               // parent: none
VK_DEFINE_HANDLE(VkmaBuffer)                                  // parent: VkmaAllocator
VK_DEFINE_HANDLE(VkmaImage)                                   // parent: VkmaAllocator
VK_DEFINE_NON_DISPATCHABLE_HANDLE(VkmaAllocation)             // parent: VkmaAllocator
VK_DEFINE_NON_DISPATCHABLE_HANDLE(VkmaDefragmentationContext) // parent: VkmaAllocator
VK_DEFINE_NON_DISPATCHABLE_HANDLE(VkmaPool)                   // parent: VkmaAllocator
VK_DEFINE_HANDLE(VkmaVirtualBlock)                            // parent: none
VK_DEFINE_NON_DISPATCHABLE_HANDLE(VkmaVirtualAllocation)      // parent: VkmaVirtualBlock

struct VkmaBuffer_T {
  VkBuffer buffer;
  VkmaAllocation allocation;
};
static_assert(sizeof(VkmaBuffer_T) == sizeof(VkBuffer) + sizeof(VkmaAllocation),
              "struct and wrapper have different size!");
static_assert(std::is_standard_layout<VkmaBuffer_T>::value,
              "struct wrapper is not a standard layout!");

struct VkmaImage_T {
  VkImage image;
  VkmaAllocation allocation;
};
static_assert(sizeof(VkmaImage_T) == sizeof(VkImage) + sizeof(VkmaAllocation),
              "struct and wrapper have different size!");
static_assert(std::is_standard_layout<VkmaImage_T>::value,
              "struct wrapper is not a standard layout!");

using VkmaResult = VkResult;

using VkmaAllocatorCreateFlagBits = VmaAllocatorCreateFlagBits;
using VkmaMemoryUsage = VmaMemoryUsage;
using VkmaAllocationCreateFlagBits = VmaAllocationCreateFlagBits;
using VkmaPoolCreateFlagBits = VmaPoolCreateFlagBits;
using VkmaDefragmentationFlagBits = VmaDefragmentationFlagBits;
using VkmaDefragmentationMoveOperation = VmaDefragmentationMoveOperation;
using VkmaVirtualAllocationCreateFlagBits = VmaVirtualAllocationCreateFlagBits;
using VkmaVirtualBlockCreateFlagBits = VmaVirtualBlockCreateFlagBits;

using VkmaAllocatorCreateFlags = VmaAllocatorCreateFlags;
using VkmaAllocationCreateFlags = VmaAllocationCreateFlags;
using VkmaPoolCreateFlags = VmaPoolCreateFlags;
using VkmaDefragmentationFlags = VmaDefragmentationFlags;
using VkmaVirtualBlockCreateFlags = VmaVirtualBlockCreateFlags;
using VkmaVirtualAllocationCreateFlags = VmaVirtualAllocationCreateFlags;

typedef void(VKAPI_PTR *PFN_vkmaAllocateDeviceMemoryFunction)(VkmaAllocator allocator,
                                                              uint32_t memoryType,
                                                              VkDeviceMemory memory,
                                                              VkDeviceSize size, void *pUserData);
typedef void(VKAPI_PTR *PFN_vkmaFreeDeviceMemoryFunction)(VkmaAllocator allocator,
                                                          uint32_t memoryType,
                                                          VkDeviceMemory memory, VkDeviceSize size,
                                                          void *pUserData);

using VkmaAllocationInfo = VmaAllocationInfo;
using VkmaDefragmentationStats = VmaDefragmentationStats;

typedef struct VkmaAllocationCreateInfo {
  VkmaAllocationCreateFlags flags;
  VkmaMemoryUsage usage;
  VkMemoryPropertyFlags requiredFlags;
  VkMemoryPropertyFlags preferredFlags;
  uint32_t memoryTypeBits;
  VkmaPool VMA_NULLABLE pool;
  void *VMA_NULLABLE pUserData;
  float priority;
} VkmaAllocationCreateInfo;
static_assert(sizeof(VkmaAllocationCreateInfo) == sizeof(VmaAllocationCreateInfo),
              "struct and wrapper have different size!");
static_assert(std::is_standard_layout<VkmaAllocationCreateInfo>::value,
              "struct wrapper is not a standard layout!");

typedef struct VkmaDeviceMemoryCallbacks {
  PFN_vkmaAllocateDeviceMemoryFunction VMA_NULLABLE pfnAllocate;
  PFN_vkmaFreeDeviceMemoryFunction VMA_NULLABLE pfnFree;
  void *VMA_NULLABLE pUserData;
} VkmaDeviceMemoryCallbacks;
static_assert(sizeof(VkmaDeviceMemoryCallbacks) == sizeof(VmaDeviceMemoryCallbacks),
              "struct and wrapper have different size!");
static_assert(std::is_standard_layout<VkmaDeviceMemoryCallbacks>::value,
              "struct wrapper is not a standard layout!");

typedef struct VkmaVulkanFunctions {
  PFN_vkGetInstanceProcAddr vkGetInstanceProcAddr;
  PFN_vkGetDeviceProcAddr vkGetDeviceProcAddr;
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

  PFN_vkGetDeviceBufferMemoryRequirements vkGetDeviceBufferMemoryRequirements;
  PFN_vkGetDeviceImageMemoryRequirements vkGetDeviceImageMemoryRequirements;
} VkmaVulkanFunctions;
static_assert(sizeof(VkmaVulkanFunctions) >= sizeof(VmaVulkanFunctions),
              "struct and wrapper have different size!");
static_assert(std::is_standard_layout<VkmaVulkanFunctions>::value,
              "struct wrapper is not a standard layout!");

typedef struct VkmaAllocatorCreateInfo {
  VkmaAllocatorCreateFlags flags;
  VkPhysicalDevice VMA_NOT_NULL physicalDevice;
  VkDevice VMA_NOT_NULL device;
  VkDeviceSize preferredLargeHeapBlockSize;
  const VkAllocationCallbacks *VMA_NULLABLE pAllocationCallbacks;
  const VkmaDeviceMemoryCallbacks *VMA_NULLABLE pDeviceMemoryCallbacks;
  const VkDeviceSize *VMA_NULLABLE pHeapSizeLimit;
  const VkmaVulkanFunctions *VMA_NULLABLE pVulkanFunctions;
  VkInstance VMA_NOT_NULL instance;
  uint32_t vulkanApiVersion;
  const VkExternalMemoryHandleTypeFlagsKHR *VMA_NULLABLE pTypeExternalMemoryHandleTypes;
} VkmaAllocatorCreateInfo;
static_assert(sizeof(VkmaAllocatorCreateInfo) == sizeof(VmaAllocatorCreateInfo),
              "struct and wrapper have different size!");
static_assert(std::is_standard_layout<VkmaAllocatorCreateInfo>::value,
              "struct wrapper is not a standard layout!");

using VkmaStatistics = VmaStatistics;

typedef struct VkmaDetailedStatistics {
  VkmaStatistics statistics;
  uint32_t unusedRangeCount;
  VkDeviceSize allocationSizeMin;
  VkDeviceSize allocationSizeMax;
  VkDeviceSize unusedRangeSizeMin;
  VkDeviceSize unusedRangeSizeMax;
} VkmaDetailedStatistics;
static_assert(sizeof(VkmaDetailedStatistics) == sizeof(VmaDetailedStatistics),
              "struct and wrapper have different size!");
static_assert(std::is_standard_layout<VkmaDetailedStatistics>::value,
              "struct wrapper is not a standard layout!");

typedef struct VkmaTotalStatistics {
  VkmaDetailedStatistics memoryType[VK_MAX_MEMORY_TYPES];
  VkmaDetailedStatistics memoryHeap[VK_MAX_MEMORY_HEAPS];
  VkmaDetailedStatistics total;
} VkmaTotalStatistics;
static_assert(sizeof(VkmaTotalStatistics) == sizeof(VmaTotalStatistics),
              "struct and wrapper have different size!");
static_assert(std::is_standard_layout<VkmaTotalStatistics>::value,
              "struct wrapper is not a standard layout!");

typedef struct VkmaBudget {
  VkmaStatistics statistics;
  VkDeviceSize usage;
  VkDeviceSize budget;
} VkmaBudget;
static_assert(sizeof(VkmaBudget) == sizeof(VmaBudget), "struct and wrapper have different size!");
static_assert(std::is_standard_layout<VkmaBudget>::value,
              "struct wrapper is not a standard layout!");

typedef struct VkmaDefragmentationInfo {
  VkmaDefragmentationFlags flags;
  VkmaPool VMA_NULLABLE pool;
  VkDeviceSize maxBytesPerPass;
  uint32_t maxAllocationsPerPass;
} VkmaDefragmentationInfo2;
static_assert(sizeof(VkmaDefragmentationInfo) == sizeof(VmaDefragmentationInfo),
              "struct and wrapper have different size!");
static_assert(std::is_standard_layout<VkmaDefragmentationInfo>::value,
              "struct wrapper is not a standard layout!");

typedef struct VkmaDefragmentationMove {
  VkmaDefragmentationMoveOperation operation;
  VkmaAllocation VMA_NOT_NULL srcAllocation;
  VkmaAllocation VMA_NOT_NULL dstTmpAllocation;
} VkmaDefragmentationMove;
static_assert(sizeof(VkmaDefragmentationMove) == sizeof(VmaDefragmentationMove),
              "struct and wrapper have different size!");
static_assert(std::is_standard_layout<VkmaDefragmentationMove>::value,
              "struct wrapper is not a standard layout!");

typedef struct VkmaDefragmentationPassMoveInfo {
  uint32_t moveCount;
  VkmaDefragmentationMove *VMA_NULLABLE VMA_LEN_IF_NOT_NULL(moveCount) pMoves;
} VkmaDefragmentationPassMoveInfo;
static_assert(sizeof(VkmaDefragmentationPassMoveInfo) == sizeof(VmaDefragmentationPassMoveInfo),
              "struct and wrapper have different size!");
static_assert(std::is_standard_layout<VkmaDefragmentationPassMoveInfo>::value,
              "struct wrapper is not a standard layout!");

typedef struct VkmaPoolCreateInfo {
  uint32_t memoryTypeIndex;
  VkmaPoolCreateFlags flags;
  VkDeviceSize blockSize;
  size_t minBlockCount;
  size_t maxBlockCount;
  float priority;
  VkDeviceSize minAllocationAlignment;
  void *VMA_NULLABLE pMemoryAllocateNext;
} VkmaPoolCreateInfo;
static_assert(sizeof(VkmaPoolCreateInfo) == sizeof(VmaPoolCreateInfo),
              "struct and wrapper have different size!");
static_assert(std::is_standard_layout<VkmaPoolCreateInfo>::value,
              "struct wrapper is not a standard layout!");

typedef struct VkmaVirtualBlockCreateInfo {
  VkDeviceSize size;
  VkmaVirtualBlockCreateFlags flags;
  const VkAllocationCallbacks *VMA_NULLABLE pAllocationCallbacks;
} VkmaVirtualBlockCreateInfo;
static_assert(sizeof(VkmaVirtualBlockCreateInfo) == sizeof(VmaVirtualBlockCreateInfo),
              "struct and wrapper have different size!");
static_assert(std::is_standard_layout<VkmaVirtualBlockCreateInfo>::value,
              "struct wrapper is not a standard layout!");

typedef struct VkmaVirtualAllocationCreateInfo {
  VkDeviceSize size;
  VkDeviceSize alignment;
  VkmaVirtualAllocationCreateFlags flags;
  void *VMA_NULLABLE pUserData;
} VkmaVirtualAllocationCreateInfo;
static_assert(sizeof(VkmaVirtualAllocationCreateInfo) == sizeof(VmaVirtualAllocationCreateInfo),
              "struct and wrapper have different size!");
static_assert(std::is_standard_layout<VkmaVirtualAllocationCreateInfo>::value,
              "struct wrapper is not a standard layout!");

using VkmaVirtualAllocationInfo = VmaVirtualAllocationInfo;

inline VkmaResult vkmaCreateAllocator(const VkmaAllocatorCreateInfo *pCreateInfo,
                                      VkmaAllocator *pAllocator) {
  return vmaCreateAllocator(reinterpret_cast<const VmaAllocatorCreateInfo *>(pCreateInfo),
                            reinterpret_cast<VmaAllocator *>(pAllocator));
}
inline void vkmaDestroyAllocator(VkmaAllocator allocator) {
  return vmaDestroyAllocator(reinterpret_cast<VmaAllocator>(allocator));
}

inline void vkmaGetPhysicalDeviceProperties(VkmaAllocator allocator,
                                            VkPhysicalDeviceProperties *pPhysicalDeviceProperties) {
  VKMA_ASSERT(pPhysicalDeviceProperties);
  const VkPhysicalDeviceProperties *temp = nullptr;
  vmaGetPhysicalDeviceProperties(reinterpret_cast<VmaAllocator>(allocator), &temp);

  VKMA_ASSERT(temp);
  memcpy(pPhysicalDeviceProperties, temp, sizeof(VkPhysicalDeviceProperties));
}
inline void vkmaGetMemoryProperties(
  VkmaAllocator allocator, VkPhysicalDeviceMemoryProperties *pPhysicalDeviceMemoryProperties) {
  VKMA_ASSERT(pPhysicalDeviceMemoryProperties);
  const VkPhysicalDeviceMemoryProperties *temp = nullptr;
  vmaGetMemoryProperties(reinterpret_cast<VmaAllocator>(allocator), &temp);

  VKMA_ASSERT(temp);
  memcpy(pPhysicalDeviceMemoryProperties, temp, sizeof(VkPhysicalDeviceMemoryProperties));
}
inline void vkmaGetMemoryTypeProperties(VkmaAllocator allocator, uint32_t memoryTypeIndex,
                                        VkMemoryPropertyFlags *pFlags) {
  vmaGetMemoryTypeProperties(reinterpret_cast<VmaAllocator>(allocator), memoryTypeIndex, pFlags);
}

inline void vkmaSetCurrentFrameIndex(VkmaAllocator allocator, uint32_t frameIndex) {
  vmaSetCurrentFrameIndex(reinterpret_cast<VmaAllocator>(allocator), frameIndex);
}

inline void vkmaCalculateStatistics(VkmaAllocator allocator, VkmaTotalStatistics *pStats) {
  vmaCalculateStatistics(reinterpret_cast<VmaAllocator>(allocator),
                         reinterpret_cast<VmaTotalStatistics *>(pStats));
}

inline void vkmaGetHeapBudgets(VkmaAllocator allocator, VkmaBudget *pBudgets) {
  vmaGetHeapBudgets(reinterpret_cast<VmaAllocator>(allocator),
                    reinterpret_cast<VmaBudget *>(pBudgets));
}

inline VkmaResult vkmaFindMemoryTypeIndex(VkmaAllocator allocator, uint32_t memoryTypeBits,
                                          const VkmaAllocationCreateInfo *pAllocationCreateInfo,
                                          uint32_t *pMemoryTypeIndex) {
  return vmaFindMemoryTypeIndex(reinterpret_cast<VmaAllocator>(allocator), memoryTypeBits,
                                reinterpret_cast<const VmaAllocationCreateInfo *>(
                                  pAllocationCreateInfo),
                                pMemoryTypeIndex);
}
inline VkmaResult vkmaFindMemoryTypeIndexForBufferInfo(
  VkmaAllocator allocator, const VkBufferCreateInfo *pBufferCreateInfo,
  const VkmaAllocationCreateInfo *pAllocationCreateInfo, uint32_t *pMemoryTypeIndex) {
  return vmaFindMemoryTypeIndexForBufferInfo(reinterpret_cast<VmaAllocator>(allocator),
                                             pBufferCreateInfo,
                                             reinterpret_cast<const VmaAllocationCreateInfo *>(
                                               pAllocationCreateInfo),
                                             pMemoryTypeIndex);
}
inline VkmaResult vkmaFindMemoryTypeIndexForImageInfo(
  VkmaAllocator allocator, const VkImageCreateInfo *pImageCreateInfo,
  const VkmaAllocationCreateInfo *pAllocationCreateInfo, uint32_t *pMemoryTypeIndex) {
  return vmaFindMemoryTypeIndexForImageInfo(reinterpret_cast<VmaAllocator>(allocator),
                                            pImageCreateInfo,
                                            reinterpret_cast<const VmaAllocationCreateInfo *>(
                                              pAllocationCreateInfo),
                                            pMemoryTypeIndex);
}

inline VkmaResult vkmaCreatePool(VkmaAllocator allocator, const VkmaPoolCreateInfo *pCreateInfo,
                                 VkmaPool *pPool) {
  return vmaCreatePool(reinterpret_cast<VmaAllocator>(allocator),
                       reinterpret_cast<const VmaPoolCreateInfo *>(pCreateInfo),
                       reinterpret_cast<VmaPool *>(pPool));
}
inline void vkmaDestroyPool(VkmaAllocator allocator, VkmaPool pool) {
  vmaDestroyPool(reinterpret_cast<VmaAllocator>(allocator), reinterpret_cast<VmaPool>(pool));
}
inline void vkmaGetPoolStatistics(VkmaAllocator allocator, VkmaPool pool,
                                  VkmaStatistics *pPoolStats) {
  vmaGetPoolStatistics(reinterpret_cast<VmaAllocator>(allocator), reinterpret_cast<VmaPool>(pool),
                       reinterpret_cast<VmaStatistics *>(pPoolStats));
}
inline void vkmaCalculatePoolStatistics(VkmaAllocator allocator, VkmaPool pool,
                                        VkmaDetailedStatistics *pPoolStats) {
  vmaCalculatePoolStatistics(reinterpret_cast<VmaAllocator>(allocator),
                             reinterpret_cast<VmaPool>(pool),
                             reinterpret_cast<VmaDetailedStatistics *>(pPoolStats));
}
inline VkmaResult vkmaCheckPoolCorruption(VkmaAllocator allocator, VkmaPool pool) {
  return vmaCheckPoolCorruption(reinterpret_cast<VmaAllocator>(allocator),
                                reinterpret_cast<VmaPool>(pool));
}
inline void vkmaGetPoolName(VkmaAllocator allocator, VkmaPool pool, const char **ppName) {
  vmaGetPoolName(reinterpret_cast<VmaAllocator>(allocator), reinterpret_cast<VmaPool>(pool),
                 ppName);
}
inline void vkmaSetPoolName(VkmaAllocator allocator, VkmaPool pool, const char *pName) {
  vmaSetPoolName(reinterpret_cast<VmaAllocator>(allocator), reinterpret_cast<VmaPool>(pool), pName);
}

inline VkmaResult vkmaAllocateMemory(VkmaAllocator allocator,
                                     const VkMemoryRequirements *pVkMemoryRequirements,
                                     const VkmaAllocationCreateInfo *pCreateInfo,
                                     VkmaAllocation *pAllocation) {
  return vmaAllocateMemory(reinterpret_cast<VmaAllocator>(allocator), pVkMemoryRequirements,
                           reinterpret_cast<const VmaAllocationCreateInfo *>(pCreateInfo),
                           reinterpret_cast<VmaAllocation *>(pAllocation), nullptr);
}
inline VkmaResult vkmaAllocateMemoryPages(VkmaAllocator allocator,
                                          const VkMemoryRequirements *pVkMemoryRequirements,
                                          const VkmaAllocationCreateInfo *pCreateInfo,
                                          size_t allocationCount, VkmaAllocation *pAllocations) {
  return vmaAllocateMemoryPages(reinterpret_cast<VmaAllocator>(allocator), pVkMemoryRequirements,
                                reinterpret_cast<const VmaAllocationCreateInfo *>(pCreateInfo),
                                allocationCount, reinterpret_cast<VmaAllocation *>(pAllocations),
                                nullptr);
}
inline VkmaResult vkmaAllocateMemoryForBuffer(VkmaAllocator allocator, VkBuffer buffer,
                                              const VkmaAllocationCreateInfo *pCreateInfo,
                                              VkmaAllocation *pAllocation) {
  return vmaAllocateMemoryForBuffer(reinterpret_cast<VmaAllocator>(allocator), buffer,
                                    reinterpret_cast<const VmaAllocationCreateInfo *>(pCreateInfo),
                                    reinterpret_cast<VmaAllocation *>(pAllocation), nullptr);
}
inline VkmaResult vkmaAllocateMemoryForImage(VkmaAllocator allocator, VkImage image,
                                             const VkmaAllocationCreateInfo *pCreateInfo,
                                             VkmaAllocation *pAllocation) {
  return vmaAllocateMemoryForImage(reinterpret_cast<VmaAllocator>(allocator), image,
                                   reinterpret_cast<const VmaAllocationCreateInfo *>(pCreateInfo),
                                   reinterpret_cast<VmaAllocation *>(pAllocation), nullptr);
}
inline void vkmaFreeMemory(VkmaAllocator allocator, const VkmaAllocation allocation) {
  vmaFreeMemory(reinterpret_cast<VmaAllocator>(allocator),
                reinterpret_cast<VmaAllocation>(allocation));
}
inline void vkmaFreeMemoryPages(VkmaAllocator allocator, size_t allocationCount,
                                const VkmaAllocation *pAllocations) {
  vmaFreeMemoryPages(reinterpret_cast<VmaAllocator>(allocator), allocationCount,
                     reinterpret_cast<const VmaAllocation *>(pAllocations));
}

inline void vkmaGetAllocationInfo(VkmaAllocator allocator, VkmaAllocation allocation,
                                  VkmaAllocationInfo *pAllocationInfo) {
  vmaGetAllocationInfo(reinterpret_cast<VmaAllocator>(allocator),
                       reinterpret_cast<VmaAllocation>(allocation), pAllocationInfo);
}
inline void vkmaSetAllocationUserData(VkmaAllocator allocator, VkmaAllocation allocation,
                                      const void *pUserData) {
  vmaSetAllocationUserData(reinterpret_cast<VmaAllocator>(allocator),
                           reinterpret_cast<VmaAllocation>(allocation),
                           const_cast<void *>(pUserData));
}
inline void vkmaSetAllocationName(VkmaAllocator allocator, VkmaAllocation allocation,
                                  const char *pName) {
  vmaSetAllocationName(reinterpret_cast<VmaAllocator>(allocator),
                       reinterpret_cast<VmaAllocation>(allocation), pName);
}
inline void vkmaGetAllocationMemoryProperties(VkmaAllocator allocator, VkmaAllocation allocation,
                                              VkMemoryPropertyFlags *pFlags) {
  vmaGetAllocationMemoryProperties(reinterpret_cast<VmaAllocator>(allocator),
                                   reinterpret_cast<VmaAllocation>(allocation), pFlags);
}

inline VkmaResult vkmaMapMemory(VkmaAllocator allocator, VkmaAllocation allocation, void **ppData) {
  return vmaMapMemory(reinterpret_cast<VmaAllocator>(allocator),
                      reinterpret_cast<VmaAllocation>(allocation), ppData);
}
inline void vkmaUnmapMemory(VkmaAllocator allocator, VkmaAllocation allocation) {
  vmaUnmapMemory(reinterpret_cast<VmaAllocator>(allocator),
                 reinterpret_cast<VmaAllocation>(allocation));
}
inline VkmaResult vkmaFlushAllocation(VkmaAllocator allocator, VkmaAllocation allocation,
                                      VkDeviceSize offset, VkDeviceSize size) {
  return vmaFlushAllocation(reinterpret_cast<VmaAllocator>(allocator),
                            reinterpret_cast<VmaAllocation>(allocation), offset, size);
}
inline VkmaResult vkmaInvalidateAllocation(VkmaAllocator allocator, VkmaAllocation allocation,
                                           VkDeviceSize offset, VkDeviceSize size) {
  return vmaInvalidateAllocation(reinterpret_cast<VmaAllocator>(allocator),
                                 reinterpret_cast<VmaAllocation>(allocation), offset, size);
}
inline VkmaResult vkmaFlushAllocations(VkmaAllocator allocator, uint32_t allocationCount,
                                       const VkmaAllocation *allocations,
                                       const VkDeviceSize *offsets, const VkDeviceSize *sizes) {
  return vmaFlushAllocations(reinterpret_cast<VmaAllocator>(allocator), allocationCount,
                             reinterpret_cast<const VmaAllocation *>(allocations), offsets, sizes);
}
inline VkmaResult vkmaInvalidateAllocations(VkmaAllocator allocator, uint32_t allocationCount,
                                            const VkmaAllocation *allocations,
                                            const VkDeviceSize *offsets,
                                            const VkDeviceSize *sizes) {
  return vmaInvalidateAllocations(reinterpret_cast<VmaAllocator>(allocator), allocationCount,
                                  reinterpret_cast<const VmaAllocation *>(allocations), offsets,
                                  sizes);
}

inline VkmaResult vkmaCheckCorruption(VkmaAllocator allocator, uint32_t memoryTypeBits) {
  return vmaCheckCorruption(reinterpret_cast<VmaAllocator>(allocator), memoryTypeBits);
}
inline VkmaResult vkmaBeginDefragmentation(VkmaAllocator allocator,
                                           const VkmaDefragmentationInfo *pInfo,
                                           VkmaDefragmentationContext *pContext) {
  return vmaBeginDefragmentation(reinterpret_cast<VmaAllocator>(allocator),
                                 reinterpret_cast<const VmaDefragmentationInfo *>(pInfo),
                                 reinterpret_cast<VmaDefragmentationContext *>(pContext));
}
inline void vkmaEndDefragmentation(VkmaAllocator allocator, VkmaDefragmentationContext context,
                                   VkmaDefragmentationStats *pStats) {
  vmaEndDefragmentation(reinterpret_cast<VmaAllocator>(allocator),
                        reinterpret_cast<VmaDefragmentationContext>(context),
                        reinterpret_cast<VmaDefragmentationStats *>(pStats));
}
inline VkmaResult vkmaBeginDefragmentationPass(VkmaAllocator allocator,
                                               VkmaDefragmentationContext context,
                                               VkmaDefragmentationPassMoveInfo *pPassInfo) {
  return vmaBeginDefragmentationPass(reinterpret_cast<VmaAllocator>(allocator),
                                     reinterpret_cast<VmaDefragmentationContext>(context),
                                     reinterpret_cast<VmaDefragmentationPassMoveInfo *>(pPassInfo));
}
inline VkmaResult vkmaEndDefragmentationPass(VkmaAllocator allocator,
                                             VkmaDefragmentationContext context,
                                             VkmaDefragmentationPassMoveInfo *pPassInfo) {
  return vmaEndDefragmentationPass(reinterpret_cast<VmaAllocator>(allocator),
                                   reinterpret_cast<VmaDefragmentationContext>(context),
                                   reinterpret_cast<VmaDefragmentationPassMoveInfo *>(pPassInfo));
}

inline VkmaResult vkmaBindBufferMemory(VkmaAllocator allocator, VkmaAllocation allocation,
                                       VkBuffer buffer) {
  return vmaBindBufferMemory(reinterpret_cast<VmaAllocator>(allocator),
                             reinterpret_cast<VmaAllocation>(allocation), buffer);
}
inline VkmaResult vkmaBindBufferMemory2(VkmaAllocator allocator, VkmaAllocation allocation,
                                        VkDeviceSize allocationLocalOffset, VkBuffer buffer,
                                        const void *pNext) {
  return vmaBindBufferMemory2(reinterpret_cast<VmaAllocator>(allocator),
                              reinterpret_cast<VmaAllocation>(allocation), allocationLocalOffset,
                              buffer, pNext);
}
inline VkmaResult vkmaBindImageMemory(VkmaAllocator allocator, VkmaAllocation allocation,
                                      VkImage image) {
  return vmaBindImageMemory(reinterpret_cast<VmaAllocator>(allocator),
                            reinterpret_cast<VmaAllocation>(allocation), image);
}
inline VkmaResult vkmaBindImageMemory2(VkmaAllocator allocator, VkmaAllocation allocation,
                                       VkDeviceSize allocationLocalOffset, VkImage image,
                                       const void *pNext) {
  return vmaBindImageMemory2(reinterpret_cast<VmaAllocator>(allocator),
                             reinterpret_cast<VmaAllocation>(allocation), allocationLocalOffset,
                             image, pNext);
}

inline VkmaResult vkmaCreateBuffer(VkmaAllocator allocator,
                                   const VkBufferCreateInfo *pBufferCreateInfo,
                                   const VkmaAllocationCreateInfo *pAllocationCreateInfo,
                                   VkmaBuffer *pBuffer) {
  VKMA_ASSERT(pBuffer);
  *pBuffer = reinterpret_cast<VkmaBuffer>(new VkmaBuffer_T{});
  return vmaCreateBuffer(reinterpret_cast<VmaAllocator>(allocator), pBufferCreateInfo,
                         reinterpret_cast<const VmaAllocationCreateInfo *>(pAllocationCreateInfo),
                         &reinterpret_cast<VkmaBuffer_T *>(*pBuffer)->buffer,
                         reinterpret_cast<VmaAllocation *>(
                           &reinterpret_cast<VkmaBuffer_T *>(*pBuffer)->allocation),
                         nullptr);
}
inline void vkmaDestroyBuffer(VkmaAllocator allocator, VkmaBuffer buffer) {
  VKMA_ASSERT(buffer);
  vmaDestroyBuffer(reinterpret_cast<VmaAllocator>(allocator),
                   reinterpret_cast<VkmaBuffer_T *>(buffer)->buffer,
                   reinterpret_cast<VmaAllocation>(
                     reinterpret_cast<VkmaBuffer_T *>(buffer)->allocation));
  delete reinterpret_cast<VkmaBuffer_T *>(buffer);
}
inline VkmaResult vkmaCreateImage(VkmaAllocator allocator,
                                  const VkImageCreateInfo *pImageCreateInfo,
                                  const VkmaAllocationCreateInfo *pAllocationCreateInfo,
                                  VkmaImage *pImage) {
  VKMA_ASSERT(pImage);
  *pImage = reinterpret_cast<VkmaImage>(new VkmaImage_T{});
  return vmaCreateImage(reinterpret_cast<VmaAllocator>(allocator), pImageCreateInfo,
                        reinterpret_cast<const VmaAllocationCreateInfo *>(pAllocationCreateInfo),
                        &reinterpret_cast<VkmaImage_T *>(*pImage)->image,
                        reinterpret_cast<VmaAllocation *>(
                          &reinterpret_cast<VkmaImage_T *>(*pImage)->allocation),
                        nullptr);
}
inline void vkmaDestroyImage(VkmaAllocator allocator, VkmaImage image) {
  VKMA_ASSERT(image);
  vmaDestroyImage(reinterpret_cast<VmaAllocator>(allocator),
                  reinterpret_cast<VkmaImage_T *>(image)->image,
                  reinterpret_cast<VmaAllocation>(
                    reinterpret_cast<VkmaImage_T *>(image)->allocation));
  delete reinterpret_cast<VkmaImage_T *>(image);
}

inline VkmaResult vkmaCreateVirtualBlock(const VkmaVirtualBlockCreateInfo *pCreateInfo,
                                         VkmaVirtualBlock *pVirtualBlock) {
  return vmaCreateVirtualBlock(reinterpret_cast<const VmaVirtualBlockCreateInfo *>(pCreateInfo),
                               reinterpret_cast<VmaVirtualBlock *>(pVirtualBlock));
}
inline void vkmaDestroyVirtualBlock(VkmaVirtualBlock virtualBlock) {
  vmaDestroyVirtualBlock(reinterpret_cast<VmaVirtualBlock>(virtualBlock));
}
inline VkBool32 vkmaIsVirtualBlockEmpty(VkmaVirtualBlock virtualBlock) {
  return vmaIsVirtualBlockEmpty(reinterpret_cast<VmaVirtualBlock>(virtualBlock));
}

inline void vkmaGetVirtualAllocationInfo(VkmaVirtualBlock virtualBlock,
                                         VkmaVirtualAllocation allocation,
                                         VkmaVirtualAllocationInfo *pVirtualAllocInfo) {
  vmaGetVirtualAllocationInfo(reinterpret_cast<VmaVirtualBlock>(virtualBlock),
                              reinterpret_cast<VmaVirtualAllocation>(allocation),
                              reinterpret_cast<VmaVirtualAllocationInfo *>(pVirtualAllocInfo));
}
inline VkmaResult vkmaVirtualAllocate(VkmaVirtualBlock virtualBlock,
                                      const VkmaVirtualAllocationCreateInfo *pCreateInfo,
                                      VkmaVirtualAllocation *pAllocation) {
  return vmaVirtualAllocate(reinterpret_cast<VmaVirtualBlock>(virtualBlock),
                            reinterpret_cast<const VmaVirtualAllocationCreateInfo *>(pCreateInfo),
                            reinterpret_cast<VmaVirtualAllocation *>(pAllocation), nullptr);
}
inline void vkmaVirtualFree(VkmaVirtualBlock virtualBlock, VkmaVirtualAllocation allocation) {
  vmaVirtualFree(reinterpret_cast<VmaVirtualBlock>(virtualBlock),
                 reinterpret_cast<VmaVirtualAllocation>(allocation));
}
inline void vkmaClearVirtualBlock(VkmaVirtualBlock virtualBlock) {
  vmaClearVirtualBlock(reinterpret_cast<VmaVirtualBlock>(virtualBlock));
}

inline void vkmaSetVirtualAllocationUserData(VkmaVirtualBlock virtualBlock,
                                             VkmaVirtualAllocation allocation, void *pUserData) {
  vmaSetVirtualAllocationUserData(reinterpret_cast<VmaVirtualBlock>(virtualBlock),
                                  reinterpret_cast<VmaVirtualAllocation>(allocation), pUserData);
}
inline void vkmaGetVirtualBlockStatistics(VkmaVirtualBlock virtualBlock, VkmaStatistics *pStats) {
  vmaGetVirtualBlockStatistics(reinterpret_cast<VmaVirtualBlock>(virtualBlock),
                               reinterpret_cast<VmaStatistics *>(pStats));
}
inline void vkmaCalculateVirtualBlockStatistics(VkmaVirtualBlock virtualBlock,
                                                VkmaDetailedStatistics *pStats) {
  vmaCalculateVirtualBlockStatistics(reinterpret_cast<VmaVirtualBlock>(virtualBlock),
                                     reinterpret_cast<VmaDetailedStatistics *>(pStats));
}
inline void vkmaBuildVirtualBlockStatsString(VkmaVirtualBlock virtualBlock, VkBool32 detailedMap,
                                             char **ppStatsString) {
  vmaBuildVirtualBlockStatsString(reinterpret_cast<VmaVirtualBlock>(virtualBlock), ppStatsString,
                                  detailedMap);
}
inline void vkmaFreeVirtualBlockStatsString(VkmaVirtualBlock virtualBlock,
                                            const char *pStatsString) {
  vmaFreeVirtualBlockStatsString(reinterpret_cast<VmaVirtualBlock>(virtualBlock),
                                 const_cast<char *>(pStatsString));
}

inline void vkmaBuildStatsString(VkmaAllocator allocator, VkBool32 detailedMap,
                                 char **ppStatsString) {
  vmaBuildStatsString(reinterpret_cast<VmaAllocator>(allocator), ppStatsString, detailedMap);
}
inline void vkmaFreeStatsString(VkmaAllocator allocator, const char *pStatsString) {
  vmaFreeStatsString(reinterpret_cast<VmaAllocator>(allocator), const_cast<char *>(pStatsString));
}

inline void vkmaGetBuffer(VkmaBuffer buffer, VkBuffer *pBuffer) {
  VKMA_ASSERT(pBuffer);
  *pBuffer = reinterpret_cast<VkmaBuffer_T *>(buffer)->buffer;
}
inline void vkmaGetBufferAllocation(VkmaBuffer buffer, VkmaAllocation *pAllocation) {
  VKMA_ASSERT(pAllocation);
  *pAllocation = reinterpret_cast<VkmaBuffer_T *>(buffer)->allocation;
}
inline void vkmaGetImage(VkmaImage image, VkImage *pImage) {
  VKMA_ASSERT(pImage);
  *pImage = reinterpret_cast<VkmaImage_T *>(image)->image;
}
inline void vkmaGetImageAllocation(VkmaImage image, VkmaAllocation *pAllocation) {
  VKMA_ASSERT(pAllocation);
  *pAllocation = reinterpret_cast<VkmaImage_T *>(image)->allocation;
}

#endif // VKMA_BINDINGS_HPP
