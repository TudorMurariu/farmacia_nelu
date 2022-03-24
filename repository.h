#pragma once
#include "entities.h"

typedef struct {
    int cp;//capacitate

    int n;//dimensiune

    stoc* e;

}vectorDinamic;

typedef struct {

    vectorDinamic* v;

    int curent;//pozitia curenta

}Iterator;


//VECTORUL DINAMIC

vectorDinamic* creeazaVectDin(int cp);

void redim(vectorDinamic* v);

void distruge(vectorDinamic* v);

int dim(vectorDinamic* v);

stoc* element(vectorDinamic* v, int pos);

void pushBack(vectorDinamic* v, stoc e);

void removeElem(vectorDinamic* v, int pos);

//ITERATORUL
Iterator* creaazaIterator(vectorDinamic* v);

void prim(Iterator* i);

void urmator(Iterator* i);

stoc* elementIT(Iterator* i);

int valid(Iterator* i);

void distrugeIT(Iterator* i);
