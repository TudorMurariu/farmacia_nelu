#include "produs.c"

typedef struct stocuri{
    produs med;
    int uniqueCode;
    int quantity;
}stoc;

typedef struct farmacii{
    stoc cont[100];
    int nrMeds;
}farm;


int compareStocs(stoc* prod1, stoc* prod2){

    if(prod1->med.concentr != prod2->med.concentr)
        return 0;
    if(strcmp(prod1->med.name, prod2->med.name) != 0)
        return 0;
    if(prod1->quantity != prod2->quantity)
        return 0;
    
    
    return 1;


}
