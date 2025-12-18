#include "FixedBlockMemoryResource.h"
#include <iostream>
#include <cstdlib>
#include <algorithm>

FixedBlockMemoryResource::FixedBlockMemoryResource(size_t total_pool_size, 
                                                 size_t default_block_size)
    : pool_size(total_pool_size)
    , block_size(default_block_size)
    , current_offset(0)
{
    memory_pool = std::aligned_alloc(DEFAULT_ALIGNMENT, pool_size);
    if (!memory_pool) {
        throw std::bad_alloc();
    }
    
    std::cout << "FixedBlockMemoryResource created: pool_size=" << pool_size 
              << ", block_size=" << block_size << std::endl;
}

FixedBlockMemoryResource::~FixedBlockMemoryResource() {
    allocated_blocks.clear();
    free_blocks.clear();
    std::free(memory_pool);
    std::cout << "FixedBlockMemoryResource destroyed" << std::endl;
}

void* FixedBlockMemoryResource::allocate_new_block(std::size_t bytes, std::size_t alignment) {
    if (bytes > block_size) {
        std::cerr << "Requested size " << bytes << " exceeds block size " << block_size << std::endl;
        return nullptr;
    }
    
    std::size_t aligned_offset = current_offset;
    if (aligned_offset % alignment != 0) {
        aligned_offset += alignment - (aligned_offset % alignment);
    }
    
    if (aligned_offset + bytes > pool_size) {
        std::cerr << "Memory pool exhausted!" << std::endl;
        return nullptr;
    }
    
    void* block = static_cast<char*>(memory_pool) + aligned_offset;
    current_offset = aligned_offset + bytes;
    
    return block;
}

void* FixedBlockMemoryResource::reuse_free_block(std::size_t bytes, std::size_t /*alignment*/) {
    for (auto it = free_blocks.begin(); it != free_blocks.end(); ++it) {
        if (bytes <= block_size) {
            void* block = *it;
            free_blocks.erase(it);
            return block;
        }
    }
    return nullptr;
}

void FixedBlockMemoryResource::add_to_free_blocks(void* p) {
    if (p >= memory_pool && p < static_cast<char*>(memory_pool) + pool_size) {
        free_blocks.push_back(p);
    }
}

void* FixedBlockMemoryResource::do_allocate(std::size_t bytes, std::size_t alignment) {
    void* block = reuse_free_block(bytes, alignment);
    
    if (!block) {
        block = allocate_new_block(bytes, alignment);
    }
    
    if (block) {
        allocated_blocks.push_back(block);
        std::cout << "Allocated " << bytes << " bytes at " << block 
                  << " (alignment: " << alignment << ")" << std::endl;
    }
    
    return block;
}

void FixedBlockMemoryResource::do_deallocate(void* p, std::size_t bytes, std::size_t /*alignment*/) {
    auto it = std::find(allocated_blocks.begin(), allocated_blocks.end(), p);
    
    if (it != allocated_blocks.end()) {
        allocated_blocks.erase(it);
        add_to_free_blocks(p);
        std::cout << "Deallocated " << bytes << " bytes at " << p 
                  << " (now free blocks: " << free_blocks.size() << ")" << std::endl;
    } else {
        std::cerr << "Attempt to deallocate non-allocated block!" << std::endl;
    }
}

bool FixedBlockMemoryResource::do_is_equal(const std::pmr::memory_resource& other) const noexcept {
    return this == &other;
}