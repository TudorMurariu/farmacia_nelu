#pragma once
#include <stdlib.h>
#include "repository.h"

typedef void* ElemType;
typedef ElemType(*CopyFct)(ElemType);
typedef void (*DestroyFct)(ElemType);

typedef struct {
	ElemType* p;
	int len;
	int capacity;
	DestroyFct dsf;
}Lista;

Lista* init_Lista();
void distruge_Lista(Lista* l);
void Adauga_Lista(Lista* l , vectorDinamic* v);
ElemType Sterge_Lista_Last(Lista* l, vectorDinamic* v);