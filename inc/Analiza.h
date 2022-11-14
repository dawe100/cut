#ifndef ANALIZA_H
#define ANALIZA_H

#include <stdbool.h>

#include "CPUstat.h"

float cpuCalc(cpustat_t, cpustat_t);
bool cpuCalcAll(cpustat_t[], cpustat_t[], float[], unsigned int);

#endif
