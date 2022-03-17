#include <stdlib.h>
#include "repository.h"
vectorDinamic* creeazaVectDin(int cp){
    /*
        Creeaza un vector dinamic de dimensiune cp.

        Args:
            int cp - capacitatea vectorului

        Returns:
            vectorDinamic* p - pointer catre vectorulDinamic
    
    */
    vectorDinamic *v = (vectorDinamic*)malloc(sizeof(vectorDinamic));

    v->cp = cp;
    v->n = 0;
    v->e = (stoc*)malloc(cp * sizeof(stoc));

    return v;
}

void removeElem(vectorDinamic* v, int pos){
    /*
        Sterge elementul de pe pozitia pos din vectorul v.

        Args:
            vectorDinamic* v - pointer catre vectorul dinamic
            int pos - pozitia din vector

        Returns:
            None
    */
    if(pos>=0 && pos<v->n){
        for(int i=pos;i<v->n-1;++i){
            v->e[i] = v->e[i+1];
        }
        v->n--;

    }else return;
}

void distruge(vectorDinamic* v){
    /*
        Distruge vectorul dinamic *v.

        Args:
            vectorDinamic* v - pointer catre vectorul dinamic

        Returns:
            None
    */

    free(v->e);
    free(v);
}

void redim(vectorDinamic* v){
    /*
    Dubleaza capacitatea vectorului dinamic.
        Args:
            vectorDinamic* v - pointer catre vectorul dinamic.
    */


    stoc* new_list = (stoc*)malloc(v->cp * 2 * sizeof(stoc));
    
    for(int i=0;i<v->n;++i){
        new_list[i] = v->e[i];
    }
    
    v->cp = 2 * v->cp;
    
    stoc* old_list = v->e;
    
    v->e = new_list;
    
    free(old_list);
}

int dim(vectorDinamic* v){
    /*
        Returneaza numarul de elemente din vectorul dinamic.

        Returns:
            int dim 
    
    */


    return v->n;
}

stoc* element(vectorDinamic* v, int pos){
    /*
        Returneaza pointer catre elementul de pe pozitia pos.

        Args:
            vectorDinamic* v - vectorul dinamic
            int pos - pozitia elementului cautat

        Returns:
            stoc* - pointer catre element
    */


    if(pos>=0 && pos < v->n)
        return &v->e[pos];
    else return NULL;

}

void pushBack(vectorDinamic* v, stoc e){
    if(v->n == v->cp)redim(v);

    v->e[v->n++] = e;
}

//ITERATOR CODE
Iterator* creaazaIterator(vectorDinamic* v){

    Iterator* i = (Iterator*)malloc(sizeof(Iterator));

    i->curent = 0;
    i->v = v;

    return i;
}

void prim(Iterator* i){
    i->curent = 0;
}

void urmator(Iterator* i){
    ++i->curent;
}

stoc* elementIT(Iterator* i){
    if(valid(i) == 0)
        return NULL;
    else
        return &i->v->e[i->curent];

}

int valid(Iterator* i){
    if(i->curent>=0 && i->curent<i->v->n)
        return 1;
    else return 0;
}

void distrugeIT(Iterator *i){
    free(i);
}


