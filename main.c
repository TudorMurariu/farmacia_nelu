#include <stdio.h>
#include <ctype.h>
#include "test_service.c"
void adaugareProdus(farm* pharma){

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

void modifProdus(farm* pharma){
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

    modifElem(pharma, nume,nume_modif,concentr);
    printf("Medicament actualizat!");
    
}

void afisSimpla(farm* aux){
    for(int i=0;i<aux->nrMeds;++i){
        stoc* actual = getPos(aux,i);
        printf("*****************************************\n");
        printf("MEDICAMENTUL %d\n", actual->uniqueCode);
        printf("--------------------\n");
        printf("Nume: %s\n", actual->med.name);
        printf("Concentratie: %f \n",actual->med.concentr);
        printf("Cantitate: %d\n", actual->quantity);
    }


}

void afisProduse(farm* pharma){
    char cond[100];
    printf("Introdu conditia de afisare (nume/concentratie/stoc): \n");
    scanf("%s", cond);
    farm aux = new_farm();
    ordonareProduse(pharma, cond, &aux);
    afisSimpla(&aux);
    destroyFarm(&aux);
}


void stergeStoc(farm* pharma){
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

void filtrareMedic(farm* pharma){
    int cond;
    printf("FILTRARE\n\n");
    printf("1.Filtrare după stoc.\n");
    printf("2.Filtrare după prima literă din nume.\n");
    printf("Introdu numărul condiției de filtrare: \n");

    scanf("%d", &cond);

    farm aux = new_farm();
    int condStoc;
    char condNume;
    switch (cond)
    {
        case 1:
            printf("Introdu marimea minima a stocului: \n");
            scanf("%d", &condStoc);
            filtrareStoc(pharma, condStoc, &aux);
            break;
    
        case 2:
            printf("Introdu litera cautata : \n");
            scanf("%c", &condNume);
            filtrareNume(pharma, condNume, &aux);
            break;
    }
    afisSimpla(&aux);
    destroyFarm(&aux);

}

int main(int argv, char** argc){
    run_tests();
    
    farm farmacia_nelu = new_farm();
    char comenzi[6][50]={"ADAUGARE\n", "MODIFICARE\n","AFISARE\n", "STERGERE\n", "FILTRARE\n", "EXIT\n"};
    while(1){
        for(int i=0;i<6;++i){
            printf("%d.%s",i+1, comenzi[i]);
        }
        printf("Alege comanda: ");
        int com;
        scanf("%d", &com);
        switch(--com){

            case(0):
                adaugareProdus(&farmacia_nelu);
                break;
            
            case(1):
                modifProdus(&farmacia_nelu);
                break;
            
            case(2):
                afisProduse(&farmacia_nelu);
                break;
            
            case(3):
                stergeStoc(&farmacia_nelu);
                break;
            
            case(4):
                filtrareMedic(&farmacia_nelu);
                break;
            case(5):
                destroyFarm(&farmacia_nelu);
                return 0;
                break;

        }
        printf("\n");
    }

    return 0;
}
