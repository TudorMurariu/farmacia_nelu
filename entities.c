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
}stoc;




int compareStocs(stoc* prod1, stoc* prod2){

    if(prod1->med.concentr != prod2->med.concentr)
        return 0;
    if(strcmp(prod1->med.name, prod2->med.name) != 0)
        return 0;
    if(prod1->quantity != prod2->quantity)
        return 0;
    
    
    return 1;


}

stoc NULL_STOC(){
    stoc null_stoc;
    null_stoc.med.concentr = 0;
    null_stoc.med.name[0] = 0;
    null_stoc.quantity = 0;
    null_stoc.uniqueCode = 0;

    return null_stoc;
}

