#include "VoidList.h"

Lista* init_Lista()
{
	/// initiem lista
	Lista* l = (Lista*)malloc(sizeof(Lista));
	l->capacity = 2;
	l->len = 0;
	l->p = (ElemType*)malloc(l->capacity * sizeof(ElemType));
	return l;
}

void distruge_Lista(Lista* l)
{
	/// distrugem lista
	for (int i = 0; i < l->len; i++)
		distruge(l->p[i]);
	free(l->p);
	free(l);
}

void Adauga_Lista(Lista* l, vectorDinamic* v)
{
	/// Dupa efectuarea unei operatii pentru vectorul v trebuie 
	/// sa adaugam un nou vector in lista
	vectorDinamic* v1 = creeazaVectDin(v->cp);
	v1->n = v->n;
	for (int i = 0; i < v->n; i++)
	{
		v1->e[i].uniqueCode = v->e[i].uniqueCode;
		v1->e[i].quantity = v->e[i].quantity;
		v1->e[i].med.concentr = v->e[i].med.concentr;
		strcpy_s(v1->e[i].med.name,20,v->e[i].med.name);
	}
	
	if (l->len + 1 >= l->capacity)
	{
		int newCapacity = l->capacity * 2;
		ElemType* aux = malloc(newCapacity * sizeof(ElemType));
		for (int i = 0; i < l->len; i++)
			aux[i] = l->p[i];
		free(l->p);
		l->p = aux;
		l->capacity = newCapacity;
	}

	l->p[l->len++] = v1;
}

ElemType Sterge_Lista_Last(Lista* l,vectorDinamic* v)
{
	/// Operatia de undo , intoarcem vectorul precedent
	if (l->len > 0)
	{
		distruge(l->p[l->len - 1]);
		l->len--;
		return l->p[l->len - 1];
	}
	return NULL;
}

