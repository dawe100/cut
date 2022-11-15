#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

#include "Kolejka.h"
#include "CPUstat.h"
#include "Odczyt.h"
#include "Analiza.h"
#include "Wydruk.h"

#define L_SEK 1

void* thReaderFunc(void* arg);
void* thAnalyzerFunc(void* arg);
void* thPrinterFunc(void* arg);


typedef struct QueueTh_s{
    queue_t* queue;
    pthread_mutex_t mutex;
    pthread_cond_t  cond;
}queueTh_t;


static queueTh_t q_CPUs, q_CPUsPerc;

static unsigned int cpu_count = 0;



int main(){

    cpu_count = cpuCount("/proc/stat");

    q_CPUs.queue = qCreate(cpu_count*sizeof(cpustat_t));
    q_CPUsPerc.queue = qCreate(cpu_count*sizeof(float));

    pthread_mutex_init(&q_CPUs.mutex, NULL);
    pthread_mutex_init(&q_CPUsPerc.mutex, NULL);
    pthread_cond_init(&q_CPUs.cond, NULL);
    pthread_cond_init(&q_CPUsPerc.cond, NULL);

    pthread_t th_reader, th_analyzer, th_printer;

    pthread_create(&th_reader, NULL, thReaderFunc, NULL);
    pthread_create(&th_analyzer, NULL, thAnalyzerFunc, NULL);
    pthread_create(&th_printer, NULL, thPrinterFunc, NULL);


    pthread_join(th_reader, NULL);
    pthread_join(th_analyzer, NULL);
    pthread_join(th_printer, NULL);

    pthread_mutex_destroy(&q_CPUsPerc.mutex);
    pthread_mutex_destroy(&q_CPUs.mutex);
    pthread_cond_destroy(&q_CPUsPerc.cond);
    pthread_cond_destroy(&q_CPUs.cond);

    qClear(q_CPUsPerc.queue);
    qClear(q_CPUs.queue);
    free(q_CPUs.queue);
    free(q_CPUsPerc.queue);


    return 0;
}




void* thReaderFunc(void* arg){
    (void)arg;

    cpustat_t CPUs[cpu_count];

    while(1){
        if(cpuReadAll("/proc/stat", CPUs)){
            pthread_mutex_lock(&q_CPUs.mutex);
            if(qEnque(q_CPUs.queue, CPUs))
                pthread_cond_signal(&q_CPUs.cond);
            pthread_mutex_unlock(&q_CPUs.mutex);
        }

       sleep(L_SEK);
    }

}


void* thAnalyzerFunc(void* arg){
    (void)arg;

    cpustat_t CPUsprev[cpu_count], CPUscurr[cpu_count];
    float CPUsPerc[cpu_count];

    memset(CPUsprev, 0, sizeof(CPUsprev)); //inicjalizacja zerami
    memset(CPUscurr, 0, sizeof(CPUscurr));

    while(1){

        pthread_mutex_lock(&q_CPUs.mutex);
        while(!qDeque(q_CPUs.queue, CPUscurr))
            pthread_cond_wait(&q_CPUs.cond, &q_CPUs.mutex);
        pthread_mutex_unlock(&q_CPUs.mutex);

        cpuCalcAll(CPUsprev, CPUscurr, CPUsPerc, cpu_count);
        memcpy(CPUsprev, CPUscurr, sizeof(CPUsprev));


        pthread_mutex_lock(&q_CPUsPerc.mutex);
        if(qEnque(q_CPUsPerc.queue, CPUsPerc))
            pthread_cond_signal(&q_CPUsPerc.cond);

        pthread_mutex_unlock(&q_CPUsPerc.mutex);

    }
}


void* thPrinterFunc(void* arg){
    (void)arg;

    float CPUsPerc[cpu_count];

    while(1){
        pthread_mutex_lock(&q_CPUsPerc.mutex);
        while(!qDeque(q_CPUsPerc.queue, CPUsPerc))
            pthread_cond_wait(&q_CPUsPerc.cond, &q_CPUsPerc.mutex);
        pthread_mutex_unlock(&q_CPUsPerc.mutex);


        cpuPrint(CPUsPerc, cpu_count);
        printf("\n");

        sleep(L_SEK);
    }
}

