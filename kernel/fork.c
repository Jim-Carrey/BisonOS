#include "sched.h"
#include "memory.h"
#include "string.h"
#include "traps.h"

/* 把0号进程的内核栈 编译链接到.data.init_proc段中 */
#define __init_proc_data __attribute__((__section__(".data.init_proc")))

/* 0号进程为init进程 */
union proc_union init_proc_union __init_proc_data = {INIT_PROC(proc)};

struct proc *current = &init_proc_union.proc;

struct proc *g_proc[NUM_PROC] = {&init_proc_union.proc,};

static int find_empty_proc(void)
{
	int i;

	for (i = 0 ; i < NUM_PROC; i++) {
		if (!g_proc[i])
			return i;
	}

	return -1;
}

/*
 * excp_regs存储在栈顶
 */
static struct excp_regs *proc_excp_regs(struct proc *proc)
{
	unsigned long p;

	p = (unsigned long)proc + KTHREAD_SIZE - sizeof(struct excp_regs);

	return (struct excp_regs *)p;
}

/*
 * 设置子进程的上下文信息
 */
static int copy_thread(unsigned long clone_flags, struct proc *p,
		unsigned long fn, unsigned long arg)
{
	struct excp_regs *childregs;

	childregs = proc_excp_regs(p);
	memset(childregs, 0, sizeof(struct excp_regs));
	memset(&p->cpu_context, 0, sizeof(struct cpu_context));

	if (clone_flags & PF_KTHREAD) {
		childregs->pstate = PSR_MODE_EL1h;
		p->cpu_context.x19 = fn;
		p->cpu_context.x20 = arg;
	}

	p->cpu_context.pc = (unsigned long)ret_from_fork;
	p->cpu_context.sp = (unsigned long)childregs;

	return 0;
}

/*
 * fork一个新进程
 * 1. 新建一个 proc,分配 4KB 页面用来存储内核栈, proc 在栈底。
 * 2. 分配 PID
 * 3. 设置进程的上下文
 */
int do_fork(u64 clone_flags, u64 func_cb, u64 arg)
{
    struct proc *p;
    int pid;

    p = (struct proc *)get_avail_page();
    if (!p)
        goto error;

    pid = find_empty_proc();
    if (pid < 0)
        goto error;

	/* the default func_cb arg is struct proc itself */
    if (copy_thread(clone_flags, p, func_cb, (unsigned long)p))
        goto error;

	p->state = RUNNING;
	p->pid = pid;
	g_proc[pid] = p;

	return pid;

error:
    return -1;
}

void switch_to(struct proc *next)
{
	struct proc *prev = current;

	if (current == next)
		return;

	current = next;
	cpu_switch_to(prev, next);
}