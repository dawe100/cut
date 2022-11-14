#include "Analiza.h"

float cpuCalc(cpustat_t prev, cpustat_t curr){

    unsigned long long prev_idle = prev.idle + prev.iowait;
    unsigned long long curr_idle = curr.idle + curr.iowait;

    unsigned long long prev_total = prev.user + prev.nice + prev.system \
                                  + prev.irq + prev.softirq + prev.steal + prev_idle;

    unsigned long long curr_total = curr.user + curr.nice + curr.system \
                                  + curr.irq + curr.softirq + curr.steal + curr_idle;

    unsigned long long total_d = curr_total - prev_total;
    unsigned long long idle_d  = curr_idle - prev_idle;

    float CPU_Perc = (float)(total_d - idle_d)*100.0/(float)total_d;

    return CPU_Perc;
}


bool cpuCalcAll(cpustat_t CPUsprev[], cpustat_t CPUscurr[], float CPUsPerc[], unsigned int count){

    if (count <= 0)
        return false;

    for(unsigned int i=0; i<count; ++i){
        CPUsPerc[i] = cpuCalc(CPUsprev[i], CPUscurr[i]);

    }
    return true;
}



