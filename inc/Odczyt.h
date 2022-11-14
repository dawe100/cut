#ifndef ODCZYT_H
#define ODCZYT_H

#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "CPUstat.h"

bool cpuRead(FILE*, cpustat_t*, int);
bool cpuReadAll(const char* , cpustat_t[]);
unsigned int cpuCount(const char*);

#endif
