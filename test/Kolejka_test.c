#include <assert.h>
#include <stdio.h>
#include "Kolejka.h"

void testEnque(void);
void testDeque(void);

void testEnque(){
    int a[5] = {3,-2, 1, 4, 5};
    char b[5] = "test";

    struct c_st {
        int ca;
        char cb;
        int cc[4];
    };

    struct c_st c[5];

    int ca[5] = {6, 3, 9, 111, -2};
    char cb[5] = {'a', 'x', 'l', 'd', 'q'};
    int cc[5][4] = {{1,5,8,2}, {2,4,8,2}, {34,5,844,22}, {16,5,844,2}, {11,51,18,12}};


    queue_t* qa = qCreate(sizeof(int));
    queue_t* qb = qCreate(sizeof(char));
    queue_t* qc = qCreate(sizeof(struct c_st));

    for (int i=0; i<5; ++i){
        qEnque(qa, &a[i]);
        qEnque(qb, &b[i]);

        c[i].ca = ca[i];
        c[i].cb = cb[i];
        memcpy(c[i].cc, cc[i], 4*sizeof(int));
        qEnque(qc, &c[i]);
    }

    element_t* ptr;

    ptr = qa->head;
    for (int i=0; i<5; ++i){
        assert(*((int*)ptr->data) == a[i]);
        ptr = ptr->next;
    }
    assert(*((int*)qa->tail->data) == a[4]);


    ptr = qb->head;
    for (int i=0; i<5; ++i){
        assert(*((char*)ptr->data) == b[i]);
        ptr = ptr->next;
    }
    assert(*((char*)qb->tail->data) == b[4]);


    ptr = qc->head;
    for (int i=0; i<5; ++i){
        assert((*((struct c_st*)ptr->data)).ca == ca[i]);
        assert((*((struct c_st*)ptr->data)).cb == cb[i]);
        assert(!memcmp((*((struct c_st*)ptr->data)).cc, cc[i], 4*sizeof(int)));
        ptr = ptr->next;
    }
    assert((*((struct c_st*)qc->tail->data)).ca == ca[4]);

}




void testDeque(){
    int a[5] = {3,-2, 1, 4, 5};
    char b[5] = "test";

    struct c_st {
        int ca;
        char cb;
        int cc[4];
    };

    struct c_st c[5];

    int ca[5] = {6, 3, 9, 111, -2};
    char cb[5] = {'a', 'x', 'l', 'd', 'q'};
    int cc[5][4] = {{1,5,8,2}, {2,4,8,2}, {34,5,844,22}, {16,5,844,2}, {11,51,18,12}};


    queue_t* qa = qCreate(sizeof(int));
    queue_t* qb = qCreate(sizeof(char));
    queue_t* qc = qCreate(sizeof(struct c_st));

    for (int i=0; i<5; ++i){
        qEnque(qa, &a[i]);
        qEnque(qb, &b[i]);

        c[i].ca = ca[i];
        c[i].cb = cb[i];
        memcpy(c[i].cc, cc[i], 4*sizeof(int));
        qEnque(qc, &c[i]);
    }


/*-----------------------------------------------------------------*/
    int a_rec;
    char b_rec;
    struct c_st c_rec;

    for (int i=0; i<5; ++i){
        qDeque(qa, &a_rec);
        assert(a_rec == a[i]);

        qDeque(qb, &b_rec);
        assert(b_rec == b[i]);

        qDeque(qc, &c_rec);
        assert(c_rec.ca == ca[i]);
        assert(c_rec.cb == cb[i]);
        assert(!memcmp(c_rec.cc, cc[i], 4*sizeof(int)));
    }

    assert(!qDeque(qa, &a_rec));  //proba odczytu z pustej kolejki (zwraca NULL);
    assert(!qDeque(qb, &b_rec));
    assert(!qDeque(qc, &c_rec));

}



int main(){
    testEnque();
    testDeque();
    return 0;
}
