#ifndef CPUSTAT_H
#define CPUSTAT_H

typedef struct cpustat_s{
    int No;
    unsigned long user, nice, system, idle, iowait, \
                  irq, softirq, steal, guest, guest_nice;

}cpustat_t;


#endif
