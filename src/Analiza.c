#include "Analiza.h"

float cpuCalc(cpustat_t prev, cpustat_t curr){

	unsigned long long prev_idle, curr_idle, prev_total,  \
					   curr_total, total_d, idle_d;

    prev_idle = prev.idle + prev.iowait;
    curr_idle = curr.idle + curr.iowait;

    prev_total = prev.user + prev.nice + prev.system \
                                  + prev.irq + prev.softirq + prev.steal + prev_idle;

    curr_total = curr.user + curr.nice + curr.system \
                                  + curr.irq + curr.softirq + curr.steal + curr_idle;

    total_d = curr_total - prev_total;
    idle_d  = curr_idle - prev_idle;

	return (total_d - idle_d)*100/(float)total_d;
}


void cpuCalcAll(const cpustat_t CPUsprev[], const cpustat_t CPUscurr[], float CPUsPerc[], unsigned int count){

    for(unsigned int i=0; i<count; ++i){
        CPUsPerc[i] = cpuCalc(CPUsprev[i], CPUscurr[i]);

    }

}


 
