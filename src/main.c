#include <stdio.h>
#include "Kolejka.h"

int main(){
    char znaki[10] = "abcdefghi";
    char c;

	queue_t* Queue = qCreate(sizeof(int));
	for(int i=0; i<10; ++i){
        qEnque(Queue, &znaki[i]);
    }

    qClear(Queue);
    qDeque(Queue, &c);
    qEnque(Queue, &znaki[4]);
  //  qDeque(Queue, &c);

    for(int i=0; i<30; ++i){
        if(qDeque(Queue, &c))
            printf("%c", c);
    }


    return 0;
}
