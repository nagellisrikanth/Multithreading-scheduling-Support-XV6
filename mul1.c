#include "types.h"
#include "user.h"
#include "fs.h"
#include "fcntl.h"
#include "syscall.h"
#include "traps.h"
#define NTHREADS 6
int count=0;
lock_t lock;

void child(void * t)
{
 lock_acquire(&lock);
    printf(1,"thread %d: begins\n",*(int *)t);   
int i;
for (i=0;i<100000;i++)
{
    count++;
}
printf(1,"%d \n", count);
  printf(1,"thread  %d: ends\n",*(int *)t);
 lock_release(&lock);
 exit ();
}

int
main(int argc, char *argv[])
{
int i;
int para[NTHREADS];
lock_init(&lock);
for (i=0;i<NTHREADS;i++)
{
	para[i]=i;
	thread_create(&child,&para[i]);
} 
//thread_create(&child,"B");
for(i=0;i<NTHREADS;i++)
{
	thread_join();
} 
//printf(1, "\njoined");
//thread_join();
//printf(1, "\njoined");
exit();
}
