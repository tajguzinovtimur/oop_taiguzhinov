#ifndef FIXEDBLOCKMEMORYRESOURCE_H
#define FIXEDBLOCKMEMORYRESOURCE_H

#include <memory_resource>
#include <vector>
#include <cstddef>
#include <cstring>
#include <algorithm>

class FixedBlockMemoryResource : public std::pmr::memory_resource {
private:
    void* memory_pool;
    size_t pool_size;
    size_t block_size;
    std::size_t current_offset;
    

    std::vector<void*> allocated_blocks;
    

    std::vector<void*> free_blocks;
    
   
    static constexpr std::size_t DEFAULT_ALIGNMENT = alignof(std::max_align_t);
    
    
    void* allocate_new_block(std::size_t bytes, std::size_t alignment);
    void* reuse_free_block(std::size_t bytes, std::size_t alignment);
    void add_to_free_blocks(void* p);
    
protected:
    void* do_allocate(std::size_t bytes, std::size_t alignment) override;
    void do_deallocate(void* p, std::size_t bytes, std::size_t alignment) override;
    bool do_is_equal(const std::pmr::memory_resource& other) const noexcept override;

public:
    FixedBlockMemoryResource(size_t total_pool_size = 1024 * 1024, 
                            size_t default_block_size = 64);
    ~FixedBlockMemoryResource();
    
 
    FixedBlockMemoryResource(const FixedBlockMemoryResource&) = delete;
    FixedBlockMemoryResource& operator=(const FixedBlockMemoryResource&) = delete;
    
 
    size_t get_allocated_count() const { return allocated_blocks.size(); }
    size_t get_free_count() const { return free_blocks.size(); }
    size_t get_pool_size() const { return pool_size; }
    size_t get_used_memory() const { return current_offset; }
};

#endif // FIXEDBLOCKMEMORYRESOURCE_H