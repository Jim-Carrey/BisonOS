#ifndef _SCHED_H_
#define _SCHED_H_

/* 支持的进程数量 */
#define NUM_PROC 128

/* 暂时使用1个4KB页面来当作内核栈 */
#define KTHREAD_SIZE  (1 * PAGE_SIZE)
#define KTHREAD_START_SP  (KTHREAD_SIZE - 8)

#include "type.h"
#include "mm.h"

enum proc_state {
	UNUSED = 0,
	USED = 1,
	SLEEPING = 2,
	RUNNABLE = 3,
	RUNNING = 4,
	ZOMBIE = 5,
};

enum proc_flags {
	PF_KTHREAD = 1,
};

/* 进程 cpu register 上下文 */
struct cpu_context {
	u64 x19;
	u64 x20;
	u64 x21;
	u64 x22;
	u64 x23;
	u64 x24;
	u64 x25;
	u64 x26;
	u64 x27;
	u64 x28;
	u64 fp;
	u64 sp;
	u64 pc;
};

/* process control block */
struct proc {
    enum proc_state state;
    enum proc_flags flags;
    s64 sched_time_count;
    s32 priority;
    s32 pid;
    struct cpu_context cpu_context;
};

/*
 * proc数据结构存储在内核栈的底部
 */
union proc_union {
	struct proc proc;
	u64 stack[KTHREAD_SIZE/sizeof(long)];
};

/* 0号进程即init进程 */
#define INIT_PROC(proc) \
{                      \
	.state = 4,     \
	.priority = 1,   \
	.flags = PF_KTHREAD,   \
	.pid = 0,     \
}

extern struct proc *g_proc[];

extern void ret_from_fork(void);
int do_fork(unsigned long clone_flags, unsigned long fn, unsigned long arg);
void switch_to(struct proc *next);
extern struct proc *cpu_switch_to(struct proc *prev,
					 struct proc *next);

#endif /* _SCHED_H_ */