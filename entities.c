#include <string.h>
#include <stdlib.h>
#include <stdio.h>
typedef struct produse {

    //struct pentru definirea entitatii de medicament 
    //pentru farmacie   
    char name[100];
    float concentr;
}produs;

typedef struct stocuri{
    produs med;
    int uniqueCode;
    int quantity;
    struct stocuri *next;

}stoc;

typedef struct farmacii{
    stoc *cont;

    int nrMeds;
}farm;

stoc* getPos(farm* pharma, int pos){

    stoc* auxil = pharma->cont;

    int i=0;
    while(i<pos)
    {
        auxil = auxil->next;
        ++i;
    }
    return auxil;
}

void addStoc(farm* pharma, stoc *to_add){
    stoc* auxil = pharma->cont;

    if(auxil!=NULL){
        while(auxil->next != NULL){
            auxil = auxil->next;
        }
        auxil->next = (stoc*)malloc(sizeof(stoc));
        *(auxil->next) = *to_add;
        auxil->next->next = NULL;

        pharma->nrMeds++;
    }
    else{
        pharma->cont = (stoc*)malloc(sizeof(stoc));
        *(pharma->cont) = *to_add;
        pharma->cont->next = NULL;
        pharma->nrMeds++;
    }
}

void removeStoc(farm* pharma, int pos){
    stoc *auxil = pharma->cont;
    if(pos>0){
        auxil = getPos(pharma, pos-1);
        stoc *nxt = auxil->next->next;
        free(auxil->next);
        auxil->next = nxt;

    }else{
        stoc* helper = pharma->cont;
        pharma->cont = pharma->cont->next;
        free(helper);
    }
    --pharma->nrMeds;
    
}

void destroyFarm(farm* pharma){
    //stoc* aux = pharma->cont;

    while(pharma->nrMeds>0){
        removeStoc(pharma, 0);
    }
    free(pharma->cont);
    
}

farm new_farm(){
    farm pharma;
    pharma.nrMeds = 0;
    pharma.cont = NULL;

    return pharma;
}

int compareStocs(stoc* prod1, stoc* prod2){
    
    if(prod1->med.concentr != prod2->med.concentr)
        return 0;
    if(strcmp(prod1->med.name, prod2->med.name) != 0)
        return 0;
    if(prod1->quantity != prod2->quantity)
        return 0;
    
    
    return 1;


}

