#ifndef _MEMORY_H_
#define _MEMORY_H_

#include "type.h"

u64 get_avail_page(void);
void free_page(u64 p);
void mem_init(u64 start_mem, u64 end_mem);

#endif /* _MEMORY_H_ */