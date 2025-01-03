#include "memory_manager.hpp"
#include <algorithm>

namespace MemoryManager {

std::optional<AllocationResult> allocate(MemoryPool &pool, size_t size) {
  if (size < MIN_ALLOCATION_SIZE) {
    size = MIN_ALLOCATION_SIZE;
  }
  size = (size + MIN_ALLOCATION_SIZE - 1) / MIN_ALLOCATION_SIZE *
         MIN_ALLOCATION_SIZE;
}
} // namespace MemoryManager
