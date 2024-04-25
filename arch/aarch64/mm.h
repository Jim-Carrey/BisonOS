#ifndef	_MM_H_
#define	_MM_H_

#define SZ_1K				0x00000400
#define SZ_4K				0x00001000
#define SZ_1M				0x00100000
#define SZ_1G				0x40000000

#define PAGE_SHIFT 12
#define TABLE_SHIFT 9
#define SECTION_SHIFT (PAGE_SHIFT + TABLE_SHIFT)

#define PAGE_SIZE (1 << PAGE_SHIFT)
#define SECTION_SIZE (1 << SECTION_SHIFT)

#define PAGE_MASK (~(PAGE_SIZE-1))
/* to align the pointer to the (next) page boundary */
#define PAGE_ALIGN(addr) (((addr)+PAGE_SIZE-1)&PAGE_MASK)

#define LOW_MEMORY (2 * SECTION_SIZE)
#define TOTAL_MEMORY (SZ_1G)

#ifndef __ASSEMBLER__
void memzero(unsigned long src, unsigned long n);
#endif

#endif  /*_MM_H_ */
