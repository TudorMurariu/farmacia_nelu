#include <stdlib.h>
#include <string.h>
#include "entities.c"

stoc createElem(char *name, float conc){
    /*
        Creaza un element de tipul stoc nou

        Args:
            char* name - adresa catre adresa numelui
            float conc - concentratia produsului

        Returns:

    */
    stoc nMed;
    strcpy(nMed.med.name, name);
    nMed.med.concentr = conc;

    nMed.quantity = 1;
    nMed.uniqueCode = rand() % 1000;

    return nMed;
}

int searchElem(farm* pharma, produs med){
    

    int n = pharma->nrMeds;

    for(int i=0;i<n;++i){
        if(strcmp(pharma->cont[i].med.name, med.name) == 0 &&
           pharma->cont[i].med.concentr == med.concentr)
            return i;
    }

    return -1;
}

int addElem(farm* pharma, char* name, float conc){

    stoc to_add = createElem(name,conc);
    int pos = searchElem(pharma, to_add.med);
    
    if(pos == -1){
        pharma->cont[pharma->nrMeds++] = to_add;
        return 0;
    }
    else{
        ++pharma->cont[pos].quantity;
        return 1;
    }


}


