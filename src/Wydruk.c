#include "Wydruk.h"


void cpuPrint(float CPUsPer[], unsigned int count){

    for(unsigned int i=0; i<count; i++){
        i == 0 ? printf("CPU all: ") : printf("  CPU %d: ", i-1);
        printf("%.2f%%\n", CPUsPer[i]);
    }
}
