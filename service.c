#include <stdlib.h>
#include <string.h>
#include "repository.h"
#include <math.h>


int cmpNume(const void *a, const void *b){
    stoc* x = (stoc*)a;
    stoc* y = (stoc*)b;
    return strcmp(x->med.name,y->med.name);
}

int cmpConcentr(const void* a, const void* b){
    stoc* x = (stoc*)a;
    stoc* y = (stoc*)b;
    return floor((x->med.concentr - y->med.concentr)*100);
}

int cmpMarimeStoc(const void* a, const void* b){
    stoc* x = (stoc*)a;
    stoc* y = (stoc*)b;
    return (x->quantity - y->quantity);
}

void bubble_sort(vectorDinamic* v, int (*comparator)(const void* a, const void* b))
{
    int compared = 1;

    while(compared == 1){

        Iterator *i = creaazaIterator(v);
        Iterator *j = creaazaIterator(v);
        compared = 0;

        for(prim(i);valid(i);urmator(i)){
            for(j->curent = i->curent+1;valid(j);urmator(j)){
                if(comparator(elementIT(i), elementIT(j)) > 0){
                    stoc aux = *elementIT(i);
                    *elementIT(i) = *elementIT(j);
                    *elementIT(j) = aux;
                    compared = 1; 
                }
            }
        }
        distrugeIT(i);
        distrugeIT(j);
        
    }
}
stoc createElem(char *name, float conc){
    /*
        Creaza un element de tipul stoc nou

        Args:
            char* name - adresa catre adresa numelui
            float conc - concentratia produsului

        Returns:
            type stoc - Elementul creat cu datele primite

    */
    stoc nMed;
    strcpy(nMed.med.name, name);
    nMed.med.concentr = conc;

    nMed.quantity = 1;
    nMed.uniqueCode = rand() % 1000;

    return nMed;
}

int searchElem(vectorDinamic* pharma, char* name){
    /*
        Cauta elementul transmis in lista.

        Args:
            char* name - numele produsului cautat
            farm* pharma - lista in care sa cauta

        Returns:
            -1 - daca elementul nu se afla in lista

            Pozitia elementului din lista
    */    

    

    Iterator* i = creaazaIterator(pharma);

    for(prim(i); valid(i); urmator(i)){
        if(strcmp(elementIT(i)->med.name, name) == 0){
            int returner = i->curent;
            distrugeIT(i);
            return returner;
        }
    }

    distrugeIT(i);
    return -1;
}

int addElem(vectorDinamic* pharma, char* name, float conc){
    /*
        Adauga un medicament nou sau incrementeaza cantitatea existenta deja
        pe stoc.

        Args:
            vectorDinamic* pharma - farmacia in care se adauga
            char* name - pointer catre numele medicamentului
            float conc - concetratia medicamentului

        Returns:
            0 - daca produsul exista deja
            1 - daca produsul nu exista in lista
    */
    stoc to_add = createElem(name,conc);
    int pos = searchElem(pharma, to_add.med.name);
    
    if(pos == -1){
        pushBack(pharma, to_add);
        return 0;
    }
    else{
        ++element(pharma, pos)->quantity;
        return 1;
    }


}

void actualizare_NumeMedicament(vectorDinamic* pharma, char* name, int pos ){
/* Actualizeaza numele medicamentului de pozitia pos. 
     Args:
      - vectorDinamic* pharma : adresa farmaciei in care se efectueaza modificare
      - char* name   : numele nou al medicamentului
      - int pos      : pozitia elementului care trebuie modificat

    Returns:
        None
*/
    strcpy(element(pharma, pos)->med.name, name);

}

void actualizare_ConcMedicament(vectorDinamic* pharma, float conc,int pos ){
    /* Actualizeaza concentratia medicamentului de pozitia pos. 
     Args:
      - vectorDinamic* pharma : adresa farmaciei in care se efectueaza modificare
      - float conc   : concentratia noua a medicamentului
      - int pos      : pozitia elementului care trebuie modificat

    Returns:
        None
*/
    element(pharma, pos)->med.concentr = conc;

}


int modifElem(vectorDinamic *pharma, char* name, char* modif_name, float modif_conc){
    /*
        Cauta si modifica medicamentul cu numele transmis in functie parametrii transmisi.

        Args:
            farm* pharma : adresa catre farmacia in care se efectueaza modificarea
            char* name : numele medicamentului de modificat
            char* modif_name: numele nou al medicamentului (pls default to "" pentru a il pastra la fel)
            float modif_conc: concentratia noua a medicamentului (pls default to 0 pentru a o pastra la fel)

        Returns:
            -1 daca elementul cu numele dat nu exista in farmacie
             1 daca modificarea a fost realizata cu succes 
    */
    int pos = searchElem(pharma, name);
    if(pos == -1)
        return -1;
    else{
        if(strlen(modif_name)>0){
            actualizare_NumeMedicament(pharma, modif_name, pos);
        }
        if(modif_conc != 0){
            actualizare_ConcMedicament(pharma, modif_conc, pos);
        }
        return 1;
    }

}

void stergeStoc_s(vectorDinamic *pharma, char* name){
    /*
        Sterge stocul medicamentului cu numele transmis.

        Args:
            vectorDinamic* pharma : adresa catre farmacie
            char* name   : numele medicamentului al carui stoc trebuie sters

    */
    int pos = searchElem(pharma, name);
    
    removeElem(pharma, pos);
}

vectorDinamic* ordonareProduse(vectorDinamic* pharma, char* cond){
    /*
        Ordoneaza produsele dupa conditia transmisa.

        Args:
            vectorDinamic* pharma : adresa catre farmacie
            char* cond   : conditia de ordonare (nume/concentratie/stoc)
        
        Returns:
            O farmacie noua, ordonata dupa criteriul dat.

    */

    char* p = cond;
    vectorDinamic* aux = creeazaVectDin(100);
    Iterator* i = creaazaIterator(pharma);

    for(prim(i);valid(i);urmator(i)){
        pushBack(aux, *elementIT(i));
    }

    for(;*p;++p){
        if(*p>='A' && *p<='Z'){
            *p='a'+*p-'A';
        }
    }

    if(strcmp(cond, "nume") == 0){
        bubble_sort(aux,cmpNume);
    }else if(strcmp(cond, "concentratie") == 0){
        bubble_sort(aux,cmpConcentr);
    }else if(strcmp(cond, "stoc")==0){
        bubble_sort(aux,cmpMarimeStoc);
    }
    distrugeIT(i);
    return aux;
}

vectorDinamic* filtrareStoc(vectorDinamic* pharma, int stocMin){
    /*
        Filtreaza farmacia dupa marimea stocului.

        Args:
            farm* pharma : adresa catre farmacia in care se efectueaza modificarea
            int stocMin  : marimea minima a stocului dupa care se face filtrarea

        Returns:
            farm aux: o farmacie provenita din farmacia initiala cu elementele filtrate

    */
    vectorDinamic* aux = creeazaVectDin(100);
    Iterator* i = creaazaIterator(pharma);
    for(prim(i);valid(i);urmator(i)){
        if(elementIT(i)->quantity >= stocMin){
            pushBack(aux, *elementIT(i));
        }
    }
    distrugeIT(i);
    return aux;
}
vectorDinamic* filtrareNume(vectorDinamic* pharma, char* condNume){
    /*
        Filtreaza farmacia dupa prima litera din nume.

        Args:
            farm* pharma : adresa catre farmacia in care se efectueaza modificarea
            char condNume  : litera dupa care se face filtrarea

        Returns:
            farm aux: o farmacie provenita din farmacia initiala cu elementele filtrate

    */
    
    vectorDinamic* aux = creeazaVectDin(100);
    Iterator* i = creaazaIterator(pharma);
    for(prim(i);valid(i);urmator(i)){
        if(elementIT(i)->med.name[0] == condNume[0]){
            pushBack(aux, *elementIT(i));
        }
    }
    distrugeIT(i);
    return aux;
}

