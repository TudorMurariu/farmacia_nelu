#include "service.c"
#include <stdio.h>

void adaugareProdus(farm* pharma){

    printf("ADAUGARE PRODUS\n");
    printf("Introduceti numele medicamentului: ");
    char nume[100];
    scanf("%s", nume);
    float concentr;
    printf("Introduceti concentratia medicamentului: ");
    scanf("%f", &concentr);

    int res = addElem(pharma, nume, concentr);

    if(res == 0){
        printf("Produs nou adaugat.");
    }
    else{
        printf("Stoc %s actualizat.", nume);
    }
}


int main(int argv, char** argc){

    farm farmacia_nelu;
    farmacia_nelu.nrMeds = 0;
    char comenzi[5][50]={"ADAUGARE\n", "", "", "", ""};
    while(1){
        for(int i=0;i<1;++i){
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
                break;
            
            case(2):
                break;
            
            case(3):
                break;
            
            case(4):
                break;

        }
        printf("\n");
    }

    return 0;
}