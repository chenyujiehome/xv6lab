struct stat;

// system calls
int fork(void);//Create a process, return child’s PID.
int exit(int) __attribute__((noreturn));//Terminate the current process; status reported to wait(). No return，0 is for normal 
int wait(int*);//Wait for a child to exit; exit status in *status; returns child PID.
int pipe(int*);//Create a pipe, put read/write file descriptors in p[0] and p[1].
int write(int, const void*, int);//Write n bytes from buf to file descriptor fd; returns n.
int read(int, void*, int);//Read n bytes into buf; returns number read; or 0 if end of file.
int close(int);//Release open file fd.
int kill(int);//Terminate process PID. Returns 0, or -1 for error.
int exec(const char*, char**);//Load a file and execute it with arguments; only returns if error.
int open(const char*, int);//Open a file; flags indicate read/write; returns an fd (file descriptor).
int mknod(const char*, short, short);//Create a device file.
int unlink(const char*);//Remove a file.
int fstat(int fd, struct stat*);//Place info about an open file into *st.
int link(const char*, const char*);//Create another name (file2) for the file file1.
int mkdir(const char*);//Create a new directory.
int chdir(const char*);//Change the current directory.
int dup(int);//Return a new file descriptor referring to the same file as fd.
int getpid(void);//Return the current process’s PID.
char* sbrk(int);//Grow process’s memory by n bytes. Returns start of new memory.
int sleep(int);//Pause for n clock ticks.
int uptime(void);

// ulib.c
int stat(const char*, struct stat*);
char* strcpy(char*, const char*);
void *memmove(void*, const void*, int);
char* strchr(const char*, char c);
int strcmp(const char*, const char*);
void fprintf(int, const char*, ...);
void printf(const char*, ...);
char* gets(char*, int max);
uint strlen(const char*);
void* memset(void*, int, uint);
void* malloc(uint);
void free(void*);
int atoi(const char*);
int memcmp(const void *, const void *, uint);
void *memcpy(void *, const void *, uint);

