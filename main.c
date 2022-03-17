#include "service.h"
#include <stdio.h>
#include <ctype.h>
void adaugareProdus(vectorDinamic* pharma){

    printf("ADAUGARE PRODUS\n");
    printf("Introduceti numele medicamentului: ");
    char nume[100];
    scanf("%s", nume);
    float concentr;
    if(searchElem(pharma, nume) == -1){
        printf("Introduceti concentratia medicamentului: ");
        scanf("%f", &concentr);
    }
    else{
        printf("Medicamentul exista deja...adaugare in stoc.");
        concentr = 0;
    }

    int res = addElem(pharma, nume, concentr);

    if(res == 0){
        printf("Produs nou adaugat.");
    }
    else{
        printf("Stoc %s actualizat.", nume);
    }
}

void modifProdus(vectorDinamic* pharma){
    char nume[100];
    char nume_modif[100];
    float concentr;
    printf("MODIFICARE PRODUS\n");
    int value = -1;
    do{
        printf("Introduceti numele medicamentului de modificat: ");
        scanf("%s[^\n]", nume);
        value = searchElem(pharma, nume);
        if(value==-1){
            printf("Medicamentul nu exista...\n");
            printf("Incerci din nou? (da/nu): \n");
            char ans[10];
            scanf("%s",ans);
            if(ans[0]=='n' || ans[0]=='N')return;
        }
    }while(value==-1);
    
    printf("Introduceti numele nou al medicamentului (sau \"none\" daca nu este cazul): ");
    scanf("%s", nume_modif);
    char* p = nume_modif;
    for(; *p;++p){
        if(*p>='A' && *p<='Z'){
            *p = 'a'+(*p-'A');
        }
    }

    if(strcmp(nume_modif, "none")==0){
        nume_modif[0]=0;
    }
    printf("Introduceti concentratia noua a medicamentului (sau 0 daca nu este cazul): ");
    scanf("%f", &concentr);

    if(modifElem(pharma, nume,nume_modif,concentr) == 1)
        printf("Medicament actualizat!");
    else printf("A aparut o eroare.");
}

void afisSimpla(vectorDinamic* aux){
    Iterator* i = creaazaIterator(aux);

    for(prim(i);valid(i);urmator(i)){
        printf("*****************************************\n");
        printf("MEDICAMENTUL %d\n", elementIT(i)->uniqueCode);
        printf("--------------------\n");
        printf("Nume: %s\n", elementIT(i)->med.name);
        printf("Concentratie: %f \n",elementIT(i)->med.concentr);
        printf("Cantitate: %d\n", elementIT(i)->quantity);
    }

    distrugeIT(i);


}

void afisProduse(vectorDinamic* pharma){
    char cond[100];
    printf("Introdu conditia de afisare (nume/concentratie/stoc): \n");
    scanf("%s", cond);
    vectorDinamic* aux = ordonareProduse(pharma, cond);
    afisSimpla(aux);
    distruge(aux);
}


void stergeStoc(vectorDinamic* pharma){
    char nume[100];
    int value = -1;
    do{
        printf("Introduceti numele stocului de sters: ");
        scanf("%s[^\n]", nume);
        value = searchElem(pharma, nume);
        if(value==-1){
            printf("Stocul nu exista...\n");
            printf("Incerci din nou? (da/nu): \n");
            char ans[10];
            scanf("%s",ans);
            if(ans[0]=='n' || ans[0]=='N')return;
        }
    }while(value==-1);
    stergeStoc_s(pharma, nume);
}

void filtrareMedic(vectorDinamic* pharma){
    int cond;
    printf("FILTRARE\n\n");
    printf("1.Filtrare după stoc.\n");
    printf("2.Filtrare după prima literă din nume.\n");
    printf("Introdu numărul condiției de filtrare: \n");

    scanf("%d", &cond);

    vectorDinamic* aux;
    int condStoc;
    char condNume;
    switch (cond)
    {
        case 1:
            printf("Introdu marimea minima a stocului: \n");
            scanf("%d", &condStoc);
            aux = filtrareStoc(pharma, condStoc);
            break;
    
        case 2:
            printf("Introdu litera cautata : \n");
            scanf("%c", &condNume);
            aux = filtrareNume(pharma, condNume);
            break;
    }
    afisSimpla(aux);
    distruge(aux);
}

int main(int argv, char** argc){
    
    vectorDinamic* farmacia_nelu = creeazaVectDin(100);
    char comenzi[6][50]={"ADAUGARE\n", "MODIFICARE\n","AFISARE\n", "STERGERE\n", "FILTRARE\n", "OPRIRE\n"};
    while(1){
        for(int i=0;i<6;++i){
            printf("%d.%s",i+1, comenzi[i]);
        }
        printf("Alege comanda: ");
        int com;
        scanf("%d", &com);
        switch(--com){

            case(0):
                adaugareProdus(farmacia_nelu);
                break;
            
            case(1):
                modifProdus(farmacia_nelu);
                break;
            
            case(2):
                afisProduse(farmacia_nelu);
                break;
            
            case(3):
                stergeStoc(farmacia_nelu);
                break;
            
            case(4):
                filtrareMedic(farmacia_nelu);
                break;

            case(5):
                distruge(farmacia_nelu);
                return 0;

        }
        printf("\n");
    }

    return 0;
}