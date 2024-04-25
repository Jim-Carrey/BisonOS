#include "type.h"
#include "mm.h"
#include "printk.h"

#define NUM_PAGES (TOTAL_MEMORY / PAGE_SIZE)

static u8 mem_mark_map[NUM_PAGES] = {0,};

static u64 phy_start_addr;

void mem_init(u64 start_mem, u64 end_mem)
{
    u64 num_avail_pages = 0;
    u64 avail_mem;

    start_mem = PAGE_ALIGN(start_mem);
    phy_start_addr = start_mem;
    end_mem &= PAGE_MASK;
    avail_mem = end_mem - start_mem;

    while (start_mem < end_mem) {
        num_avail_pages++;
        start_mem += PAGE_SIZE;
    }

    printk("Total Memory: %u MB available, %uKB available, %u avail pages\n", avail_mem/SZ_1M, avail_mem/SZ_1K, num_avail_pages);
}

u64 get_avail_page(void)
{
    for(int i = 0; i < NUM_PAGES; i++) {
        if (mem_mark_map[i] == 0) {
            mem_mark_map[i] = 1;
            return LOW_MEMORY + i * PAGE_SIZE;
        }
    }
    return 0;
}

void free_page(u64 p)
{
    mem_mark_map[(p - LOW_MEMORY) / PAGE_SIZE] = 0;
}