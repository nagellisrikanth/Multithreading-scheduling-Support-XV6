//----**project2**----//

//-----[PRIORITY BASED SCHEDULER]------//

#include "types.h"
#include "user.h"
#define NCHILDS  8  //Number of childs to be generated
#define LOOPCOUNT 0x01000000 

int
main(int argc, char *argv[])
{
    int scheduler_selected= 0; //default scheduler to be selected
    int i = 0; 
	int j = 0;
    int k = 0;
    if (argc < 2)
    {
        printf(2, "Usage: testc [0:RoundRobin or 1:priority based scheduler] \n"); //if the the application is used wrongly
        exit();
    }
    
    struct {
        int pid;
        int priority;
    } process[NCHILDS]; // to create n childs with priority
    
	int fd[NCHILDS][2]; //file descriptor of each childs created
    int buf = 0;

    printf(1, "\n");

 
 	//----Scheduler Selection---//
    if (argv[1][0] == '0')
    {
        scheduler_selected= 0;
        printf(1, "Using round robin(default) scheduler");
    }
    else
    {
        scheduler_selected= 1;
        printf(1, "Using the priority based scheduler");
    }

    printf(1, "\n");
    
    sched_type(scheduler_selected);
    
    //---Creating NChilds---//
    
    for (i = 0; i < NCHILDS; i++)
    {
        if (pipe(fd[i]) < 0)
        {
            printf(2, "pipe failed!\n");
            exit();
        }

        process[i].pid = fork();
        if (process[i].pid < 0)
        {
            printf(2, "fork failed!\n");
            exit();
        }
        else if (process[i].pid == 0) 
        {  
            close(fd[i][1]); 
            //---child reads---//
            read(fd[i][0], &buf, 1);
            while(j < LOOPCOUNT)
            {
                k += j;
                j++;
            }
            
            exit();
        }
        else 
        {
            close(fd[i][0]); 

            if (scheduler_selected == 0) // Round-robin-scheduler
            {
                printf(1,"Process[pid=%d]\n", process[i].pid);
            }
            else // priority-based scheduler
            {
                if (i == 0 || i == 1)
                {
                    process[i].priority = 1;
                    setpriority(process[i].pid, process[i].priority);
                }
                else if (i == 4 || i == 5)
                {
                    process[i].priority = 3;
                    setpriority(process[i].pid, process[i].priority);
                }
                else if(i==6|| i==7)
                {
                	process[i].priority = 4;
                    setpriority(process[i].pid, process[i].priority);
				}
                else 
                {
                    process[i].priority = 2; //default 2
                }
                printf(1, "Process[pid=%d priority=%d]\n", process[i].pid, process[i].priority);
            }
        }
    }
    
    printf(1, "\n");
    schedgraph(1);
    
    //---Parent writes---//
    
    for (i = 0; i < NCHILDS; i++)
    {   
       write(fd[i][1], "hi", 1); 
    }

    for (i = 0; i <NCHILDS; i++)
    {   
        if (wait() < 0)
        {
            printf(2,"wait() on child%d failed!\n", i);
        }
    }
    schedgraph(0);
    printf(1, "\n");
    exit();
}
