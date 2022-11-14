#include <stdio.h>
#include <stdbool.h>
#include <string.h>

typedef struct cpustat_s{
    int No;
    unsigned long user, nice, system, idle, iowait, \
                  irq, softirq, steal, guest, guest_nice;

}cpustat_t;



bool cpuRead(FILE*, cpustat_t*, int);
bool cpuReadAll(const char* , cpustat_t[]);
unsigned int cpuCount(const char*);
