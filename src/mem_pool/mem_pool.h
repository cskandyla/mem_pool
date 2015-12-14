#include <stdlib.h>//malloc
#include <stdint.h>

#ifndef __MEM_POOL__
#define __MEM_POOL__ 

 typedef struct mem_pool
 {
   uint32_t num_blocks;
   uint32_t block_size;
   uint32_t num_free_blocks;
   uint32_t num_initialized;
   uint8_t  *mem_start;
   uint8_t  *mem_next;
   
 }mem_pool;


void mem_pool_create(mem_pool *pool,size_t block_size,uint32_t num_blocks);
void mem_pool_destroy(mem_pool *pool);
uint8_t* mem_pool_idx_to_addr(mem_pool *pool,uint32_t idx);
uint32_t mem_pool_addr_to_idx(mem_pool *pool,uint8_t* addr);
void* mem_pool_alloc(mem_pool *pool);
void mem_pool_free(mem_pool *pool,void *addr);


#endif
