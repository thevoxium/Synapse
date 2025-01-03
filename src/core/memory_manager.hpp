#pragma once
#include "memory_types.hpp"
#include <optional>

namespace MemoryManager {
struct AllocationResult {
  size_t blockIndex, offset;
};

std::optional<AllocationResult> allocate(MemoryPool &pool, size_t size);

bool deallocate(MemoryPool &pool, size_t blockIndex, size_t offset);
bool defragment(MemoryPool &pool);

struct MemoryRef {
  MemoryPool &pool;
  size_t blockIndex, offset, size;

  MemoryRef(MemoryPool &p, size_t bi, size_t of, size_t sz)
      : pool(p), blockIndex(bi), offset(of), size(sz) {}

  uint8_t &operator[](size_t index) {
    if (index >= size)
      std::out_of_range("Memory access out of bounds!");
    else {
      return pool.blocks[blockIndex].data[offset + index];
    }
  }

  uint8_t &operator[](size_t index) const {
    if (index >= size)
      std::out_of_range("Memory access out of bounds!");
    else {
      return pool.blocks[blockIndex].data[offset + index];
    }
  }
};

} // namespace MemoryManager
