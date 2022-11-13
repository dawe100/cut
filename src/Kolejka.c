#include "Kolejka.h"

queue_t* qCreate(const size_t elemsize){

    queue_t* queue = (queue_t*)malloc(sizeof(queue_t));

    if(queue == NULL)
        return NULL;

    queue->element_size = elemsize;
    queue->head = NULL;
    queue->tail = NULL;

    return queue;
}

bool qEnque(queue_t* queue, const void* data_in){

    element_t* element = (element_t*)malloc(sizeof(element_t));

    if(element == NULL)
        return false;

    element->data = malloc(queue->element_size);

    if(element->data == NULL)
        return false;

    element->next = NULL;

    memcpy(element->data, data_in, queue->element_size);

    if(queue->head == NULL)
        queue->head = element;

    if(queue->tail != NULL)
        queue->tail->next = element;

    queue->tail = element;

    return true;
}


bool qDeque(queue_t* queue, void* data_out){

    if(queue->head != NULL){
        element_t* element = queue->head;
        memcpy(data_out, element->data, queue->element_size);

        if (queue->head->next == NULL)   //gdy zdejmujemy ostatni element
            queue->tail = NULL;

        queue->head = queue->head->next;

        free(element->data);
        free(element);
        return true;
    }
    return false;
}


bool qFront(const queue_t* queue, void* data){
    if(queue->head != NULL){
        memcpy(data, queue->head->data, queue->element_size);
        return true;
    }

	return false;
}


void qClear(queue_t* queue){

    element_t* element;

    while(queue->head != NULL){
        element = queue->head;
        queue->head = element->next;
        free(element->data);
        free(element);
    }
    queue->tail = NULL;
}











