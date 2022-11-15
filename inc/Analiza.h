#ifndef ANALIZA_H
#define ANALIZA_H

#include <stdbool.h>

#include "CPUstat.h"

float cpuCalc(cpustat_t, cpustat_t);
void cpuCalcAll(const cpustat_t[], const cpustat_t[], float[], unsigned int);

#endif
