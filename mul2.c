#include "types.h"
#include "user.h"
#include "fs.h"
#include "fcntl.h"
#include "syscall.h"
#include "traps.h"

int count=0;
lock_t lock;

void child(void * t)
{
 lock_acquire(&lock);
   // sleep(2);
    printf(1,"%s: begins\n",(char *)t);   
int i;
for (i=0;i<10000;i++)
{
    count++;
}
printf(1,"%d \n", count); 
  printf(1,"%s: ends\n",(char *)t);
 lock_release(&lock);
 exit ();
}

int
main(int argc, char *argv[])
{
lock_init(&lock);
thread_create(&child,"A"); 
thread_create(&child,"B");
thread_join(); 
printf(1, "joined \n");
thread_join();
printf(1, "joined\n");
exit();
}
