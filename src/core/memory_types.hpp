#pragma once
#include <cstddef>
#include <unordered_map>
#include <vector>

constexpr size_t BLOCK_SIZE = 4096;
constexpr size_t MIN_ALLOCATION_SIZE = 16;

struct MemoryBlock {
  std::vector<uint8_t> data;
  size_t usedSize;
  bool isFree;

  MemoryBlock() : data(BLOCK_SIZE), usedSize(0), isFree(true) {}
};

struct MemoryPool {
  std::vector<MemoryBlock> blocks;
  std::unordered_map<size_t, std::vector<size_t>> freeBlocks;
  size_t totalBlocks, freeBlocksCount;

  MemoryPool(size_t initialBlocks = 10)
      : totalBlocks(initialBlocks), freeBlocksCount(initialBlocks),
        blocks.resize(initialBlocks);
  for (size_t i = 0; i < initialBlocks; i++) {
    freeBlocks[BLOCK_SIZE].push_back(i);
  }
};
