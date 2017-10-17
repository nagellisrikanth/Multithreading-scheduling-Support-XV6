#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"
#include "spinlock.h"

//--project2--//
struct {
  struct spinlock lock;
  struct proc proc[NPROC];
} ptable;
int
sys_fork(void)
{
  return fork();
}

int
sys_exit(void)
{
  exit();
  return 0;  // not reached
}

int
sys_wait(void)
{
  return wait();
}

int
sys_kill(void)
{
  int pid;

  if(argint(0, &pid) < 0)
    return -1;
  return kill(pid);
}

int
sys_getpid(void)
{
  return proc->pid;
}

int
sys_sbrk(void)
{
  int addr;
  int n;

  if(argint(0, &n) < 0)
    return -1;
  addr = proc->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

int
sys_sleep(void)
{
  int n;
  uint ticks0;
  
  if(argint(0, &n) < 0)
    return -1;
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(proc->killed){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

// return how many clock tick interrupts have occurred
// since start.
int
sys_uptime(void)
{
  uint xticks;
  
  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}
extern int flag;  //project2

//----*project2*----//

//--To represent the process scheduling graphically--//
int sys_schedgraph(void)
{
  if (argint(0, &flag) < 0)
  {
    cprintf("graph failed!\n");
  }
  return 0;
}

//--To select the scheduler type 0-Round Robin 1-priority based scheduler--//
int sys_sched_type(void)
{
 int n;
 if(argint(0,&n)<0)
	 return -1;
 return sched_type(n);
}

//--To assign the priority for each processes--//
int
sys_setpriority(void)
{
  int pid;
  int priority;
  argint(0,&pid);
  argint(1,&priority);
  acquire(&ptable.lock); 
   struct proc *p;
   for(p = ptable.proc; p < &ptable.proc[NPROC]; p++)
    {
        if(p->pid==pid)
        {
	        p->priority=priority;
	        proc->state=RUNNABLE;
		    sched();  
			release(&ptable.lock);
	        return 0;
  		} 
    }
   for(p= ptable.proc;p<&ptable.proc[NPROC];p++)
     cprintf("scanning, current pid%d,priority:%d\n",p->pid,p->priority);
	release(&ptable.lock);
	return -1;
}
//**MUltithreading**//
int
sys_clone(void)
{
    void * fcn = 0;
    void * arg = 0;
    void * stack = 0;
    
    if(argint(0, (int *) &fcn) < 0)
        return -1;
    
    if(argint(1, (int *) &arg) < 0)
        return -1;
    
    if(argint(2, (int *) &stack) < 0)
        return -1;
    
    return clone(fcn, arg, stack);
}

int
sys_join(void)
{
    void ** stack = 0;
    
    if(argint(0, (int *) &stack) < 0)
        return -1;
    
    return join(stack);
//   return wait();
}
