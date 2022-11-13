//#ifndef KOLEJKA_H_INCLUDED
//#define KOLEJKA_H_INCLUDED

#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct Element_s{
    void*  data;
    struct Element_s* next;
}element_t;


typedef struct Queue_s{
    size_t element_size;
    element_t* head;
    element_t* tail;
}queue_t;



queue_t* qCreate(const size_t elemsize);
bool qEnque(queue_t* , const void*);
bool qDeque(queue_t* , void*);
bool qFront(const queue_t*, void*);
void qClear(queue_t*);



//#endif // KOLEJKA_H_INCLUDED
