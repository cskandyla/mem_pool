#include "mem_pool.h"

void mem_pool_create(mem_pool *pool,size_t block_size,uint32_t num_blocks)
{
  pool->num_blocks=num_blocks;
  pool->block_size=block_size;
  pool->mem_start=malloc(block_size*num_blocks*sizeof(uint8_t));
  pool->num_free_blocks=num_blocks;
  pool->num_initialized=0;
  pool->mem_next=pool->mem_start;

}

void mem_pool_destroy(mem_pool *pool)
{
  free(pool->mem_start);
  pool->mem_start=NULL;

}


uint8_t* mem_pool_idx_to_addr(mem_pool *pool,uint32_t idx)
{

  return pool->mem_start+(idx*pool->block_size);
}

uint32_t mem_pool_addr_to_idx(mem_pool *pool,uint8_t* addr)
{


  return ((uint32_t)(addr-pool->mem_start))/pool->block_size;

}


void* mem_pool_alloc(mem_pool *pool)
{

  if(pool->num_initialized<pool->num_blocks)
    {
      uint8_t *addr=mem_pool_idx_to_addr(pool,pool->num_initialized);
      *addr=pool->num_initialized+1;
      pool->num_initialized++;
       
    }
  void *ret=NULL;
  if(pool->num_free_blocks>0)
    {
      ret=(void*)pool->mem_next;
      pool->num_free_blocks--;
      if(pool->num_free_blocks!=0)
	{
	  pool->mem_next=mem_pool_idx_to_addr(pool,*((uint8_t*)pool->mem_next));

	}
      else
	{
	  pool->mem_next=NULL;
	}
      

    }
  return ret;
  
}

void mem_pool_free(mem_pool *pool,void *addr)
{

  if(pool->mem_next!=NULL)
    {
      (*(uint8_t*)addr)=mem_pool_addr_to_idx(pool,pool->mem_next);
      pool->mem_next=(uint8_t*)addr;
    }
  else
    {
      *((uint8_t*)addr)=pool->num_blocks;
      pool->mem_next=(uint8_t*)addr;
    }

  pool->num_free_blocks++;


}
