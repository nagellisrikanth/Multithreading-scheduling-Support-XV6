struct stat;
struct rtcdate;
struct stat;
typedef struct __lock_t {
   volatile uint flag;
} lock_t;
// system calls
int fork(void);
int exit(void) __attribute__((noreturn));
int wait(void);
int pipe(int*);
int write(int, void*, int);
int read(int, void*, int);
int close(int);
int kill(int);
int exec(char*, char**);
int open(char*, int);
int mknod(char*, short, short);
int unlink(char*);
int fstat(int fd, struct stat*);
int link(char*, char*);
int mkdir(char*);
int chdir(char*);
int dup(int);
int getpid(void);
char* sbrk(int);
int sleep(int);
int uptime(void);
int sched_type(int);
void setpriority(int,int);
void schedgraph(int);
int clone(void(*fcn)(void*), void * arg, void * stack);
int join(void ** stack);

// ulib.c
int stat(char*, struct stat*);
char* strcpy(char*, char*);
void *memmove(void*, void*, int);
char* strchr(const char*, char c);
int strcmp(const char*, const char*);
void printf(int, char*, ...);
char* gets(char*, int max);
uint strlen(char*);
void* memset(void*, int, uint);
void* malloc(uint);
void free(void*);
int atoi(const char*);
void lock_acquire(struct __lock_t*);
void lock_release(struct __lock_t*);
void lock_init(struct __lock_t*);
//thread lib
int thread_create(void (*start_routine)(void*), void *arg);
int thread_join(void);
