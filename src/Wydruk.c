#include "Wydruk.h"


void cpuPrint(const float CPUsPer[], unsigned int count){

    for(unsigned int i=0; i<count; i++){
        if(i==0)
            printf("CPU all: ");
        else
            printf("  CPU %d: ", i-1);
        printf("%.2f%%\n", CPUsPer[i]);
    }

}
