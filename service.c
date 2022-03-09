#include <stdlib.h>
#include <string.h>
#include "entities.c"
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

int searchElem(farm* pharma, char* name){
    /*
        Cauta elementul transmis in lista.

        Args:
            char* name - numele produsului cautat
            farm* pharma - lista in care sa cauta

        Returns:
            -1 - daca elementul nu se afla in lista

            Pozitia elementului din lista
    */    

    int n = pharma->nrMeds;

    for(int i=0;i<n;++i){
        if(strcmp(pharma->cont[i].med.name, name) == 0)
            return i;
    }

    return -1;
}

int addElem(farm* pharma, char* name, float conc){
    /*
        Adauga un medicament nou sau incrementeaza cantitatea existenta deja
        pe stoc.

        Args:
            farm* pharma - stocul in care se adauga
            char* name - pointer catre numele medicamentului
            float conc - concetratia medicamentului

        Returns:
            0 - daca produsul exista deja
            1 - daca produsul nu exista in lista
    */
    stoc to_add = createElem(name,conc);
    int pos = searchElem(pharma, to_add.med.name);
    
    if(pos == -1){
        pharma->cont[pharma->nrMeds++] = to_add;
        return 0;
    }
    else{
        ++pharma->cont[pos].quantity;
        return 1;
    }


}

void actualizare_NumeMedicament(farm* pharma, char* name, int pos ){
/* Actualizeaza numele medicamentului de pozitia pos. 
     Args:
      - farm* pharma : adresa farmaciei in care se efectueaza modificare
      - char* name   : numele nou al medicamentului
      - int pos      : pozitia elementului care trebuie modificat

    Returns:
        None
*/
    strcpy(pharma->cont[pos].med.name, name);

}

void actualizare_ConcMedicament(farm* pharma, float conc,int pos ){
    /* Actualizeaza concentratia medicamentului de pozitia pos. 
     Args:
      - farm* pharma : adresa farmaciei in care se efectueaza modificare
      - float conc   : concentratia noua a medicamentului
      - int pos      : pozitia elementului care trebuie modificat

    Returns:
        None
*/
    pharma->cont[pos].med.concentr = conc;

}


int modifElem(farm *pharma, char* name, char* modif_name, float modif_conc){
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

void stergeStoc_s(farm *pharma, char* name){
    /*
        Sterge stocul medicamentului cu numele transmis.

        Args:
            farm* pharma : adresa catre farmacie
            char* name   : numele medicamentului al carui stoc trebuie sters

    */
    int pos = searchElem(pharma, name);

    for(int i = pos;i<pharma->nrMeds-1;++i){
        stoc aux = pharma->cont[i];
        pharma->cont[i] = pharma->cont[i+1];
        pharma->cont[i+1] = aux; 
    }
    pharma->nrMeds--;
}

farm ordonareProduse(farm* pharma, char* cond){
    /*
        Ordoneaza produsele dupa conditia transmisa.

        Args:
            farm* pharma : adresa catre farmacie
            char* cond   : conditia de ordonare (nume/concentratie/stoc)
        
        Returns:
            O farmacie noua, ordonata dupa criteriul dat.

    */

    char* p = cond;
    farm aux;
    aux.nrMeds = pharma->nrMeds;
    for(int i=0;i<aux.nrMeds;++i){
        aux.cont[i] = pharma->cont[i];
    }
    for(;*p;++p){
        if(*p>='A' && *p<='Z'){
            *p='a'+*p-'A';
        }
    }

    if(strcmp(cond, "nume") == 0){
        qsort(aux.cont, aux.nrMeds, sizeof(stoc),cmpNume);
    }else if(strcmp(cond, "concentratie") == 0){
        qsort(aux.cont, aux.nrMeds, sizeof(stoc),cmpConcentr);
    }else if(strcmp(cond, "stoc")==0){
        qsort(aux.cont, aux.nrMeds, sizeof(stoc),cmpMarimeStoc);
    }
    return aux;
}

farm filtrareStoc(farm* pharma, int stocMin){
    /*
        Filtreaza farmacia dupa marimea stocului.

        Args:
            farm* pharma : adresa catre farmacia in care se efectueaza modificarea
            int stocMin  : marimea minima a stocului dupa care se face filtrarea

        Returns:
            farm aux: o farmacie provenita din farmacia initiala cu elementele filtrate

    */
    farm aux;
    aux.nrMeds = 0;
    for(int i=0;i<pharma->nrMeds;++i){
        if(pharma->cont[i].quantity >= stocMin){
            aux.cont[aux.nrMeds++] = pharma->cont[i];
        }
    }
    return aux;
}
farm filtrareNume(farm* pharma, char condNume){
    /*
        Filtreaza farmacia dupa prima litera din nume.

        Args:
            farm* pharma : adresa catre farmacia in care se efectueaza modificarea
            char condNume  : litera dupa care se face filtrarea

        Returns:
            farm aux: o farmacie provenita din farmacia initiala cu elementele filtrate

    */
    
    farm aux;
    aux.nrMeds = 0;
    for(int i=0;i<pharma->nrMeds;++i){
        if(pharma->cont[i].med.name[0] == condNume){
            aux.cont[aux.nrMeds++] = pharma->cont[i];
        }
    }
    return aux;
}

