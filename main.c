#include <stdio.h>
#include <ctype.h>
//#include "test_service.h"
#include "VoidList.h"
#include "service.h"
#include "repository.h"
#include <stdlib.h>

#define _CRTDBG_MAP_ALLOC 
#include <stdlib.h>
#include <crtdbg.h>

/// noua
void AfisareNoua(vectorDinamic* pharma)
{
    for (int i = 0; i < pharma->n; i++)
        printf("%f %s %d\n", pharma->e[i].med.concentr, pharma->e[i].med.name, pharma->e[i].quantity);
}

void adaugareProdus(vectorDinamic* pharma,Lista* l) {

    printf("ADAUGARE PRODUS\n");
    printf("Introduceti numele medicamentului: ");
    char nume[100];
    scanf_s("%s", nume , 20);
    float concentr;
    if (searchElem(pharma, nume) == -1) {
        printf("Introduceti concentratia medicamentului: ");
        scanf_s("%f", &concentr);
    }
    else {
        printf("Medicamentul exista deja...adaugare in stoc.");
        concentr = 0;
    }

    int res = addElem(pharma, nume, concentr, l);

    if (res == 0) {
        printf("Produs nou adaugat.");
    }
    else {
        printf("Stoc %s actualizat.", nume);
    }
}

void modifProdus(vectorDinamic* pharma,Lista* l) {
    char nume[100];
    char nume_modif[100];
    float concentr;
    printf("MODIFICARE PRODUS\n");
    int value = -1;
    do {
        printf("Introduceti numele medicamentului de modificat: ");
        scanf_s("%s[^\n]", nume, 20);
        value = searchElem(pharma, nume);
        if (value == -1) {
            printf("Medicamentul nu exista...\n");
            printf("Incerci din nou? (da/nu): \n");
            char ans[10];
            scanf_s("%s", ans, 20);
            if (ans[0] == 'n' || ans[0] == 'N')return;
        }
    } while (value == -1);

    printf("Introduceti numele nou al medicamentului (sau \"none\" daca nu este cazul): ");
    scanf_s("%s", nume_modif, 20);
    char* p = nume_modif;
    for (; *p; ++p) {
        if (*p >= 'A' && *p <= 'Z') {
            *p = 'a' + (*p - 'A');
        }
    }

    if (strcmp(nume_modif, "none") == 0) {
        nume_modif[0] = 0;
    }
    printf("Introduceti concentratia noua a medicamentului (sau 0 daca nu este cazul): ");
    scanf_s("%f", &concentr);

    if (modifElem(pharma, nume, nume_modif, concentr, l) == 1)
        printf("Medicament actualizat!");
    else printf("A aparut o eroare.");
}

void afisSimpla(vectorDinamic* aux,Lista* l) {
    Iterator* i = creaazaIterator(aux);

    for (prim(i); valid(i); urmator(i)) {
        printf("*****************************************\n");
        printf("MEDICAMENTUL %d\n", elementIT(i)->uniqueCode);
        printf("--------------------\n");
        printf("Nume: %s\n", elementIT(i)->med.name);
        printf("Concentratie: %f \n", elementIT(i)->med.concentr);
        printf("Cantitate: %d\n", elementIT(i)->quantity);
    }

    distrugeIT(i);


}

void afisProduse(vectorDinamic* pharma) {
    char cond[100];
    printf("Introdu conditia de afisare (nume/concentratie/stoc): \n");
    scanf_s("%s", cond , 20);
    vectorDinamic* aux = ordonareProduse(pharma, cond);
    //afisSimpla(aux);
    AfisareNoua(aux);
    distruge(aux);
}


void stergeStoc(vectorDinamic* pharma,Lista* l) {
    char nume[100];
    int value = -1;
    do {
        printf("Introduceti numele stocului de sters: ");
        scanf_s("%s[^\n]", nume , 20);
        value = searchElem(pharma, nume);
        if (value == -1) {
            printf("Stocul nu exista...\n");
            printf("Incerci din nou? (da/nu): \n");
            char ans[10];
            scanf_s("%s", ans , 20);
            if (ans[0] == 'n' || ans[0] == 'N')return;
        }
    } while (value == -1);
    stergeStoc_s(pharma, nume, l);
}

void filtrareMedic(vectorDinamic* pharma) {
    int cond;
    printf("FILTRARE\n\n");
    printf("1.Filtrare după stoc.\n");
    printf("2.Filtrare după prima literă din nume.\n");
    printf("3.Filtrare după concentratie.\n");
    printf("Introdu numărul condiției de filtrare: \n");

    scanf_s("%d", &cond);

    vectorDinamic* aux = NULL;
    int condStoc;
    char condNume[50];
    float concentratie;
    switch (cond)
    {
    case 1:
        printf("Introdu marimea minima a stocului: \n");
        scanf_s("%d", &condStoc);
        aux = filtrareStoc(pharma, condStoc);
        break;

    case 2:
        printf("Introdu litera cautata :");
        scanf_s("%s", condNume , 20);
        aux = filtrareNume(pharma, condNume);
        break;
    case 3:
        printf("Introdu concentratia cautata :");
        scanf_s("%f", &concentratie);
        aux = filtrareConcentratie(pharma, concentratie);
        break;
    }
    //afisSimpla(&aux);
    AfisareNoua(aux);
    distruge(aux);
}

int main(int argv, char** argc) {

    run_tests();
    vectorDinamic* farmacia_nelu = creeazaVectDin(100);
    vectorDinamic* v = NULL;
    vectorDinamic* aux = creeazaVectDin(100);
    /// ajutor
    Lista* l = init_Lista();
    char comenzi[9][50] = { "ADAUGARE\n", "MODIFICARE\n","AFISARE\n", "STERGERE\n",
        "FILTRARE\n", "OPRIRE\n", "SORTARE\n" , "AFISARE TOATE\n","UNDO\n" };
    while (1) {
        for (int i = 0; i < 9; ++i) {
            printf("%d.%s", i + 1, comenzi[i]);
        }
        printf("Alege comanda: ");
        int com;
        char mod[100];
        scanf_s("%d", &com);
        switch (--com) {

        case(0):
            adaugareProdus(farmacia_nelu, l);
            break;

        case(1):
            modifProdus(farmacia_nelu, l);
            break;

        case(2):
            afisProduse(farmacia_nelu);
            break;

        case(3):
            stergeStoc(farmacia_nelu, l);
            break;

        case(4):
            filtrareMedic(farmacia_nelu);
            break;

        case(5):
            distruge(farmacia_nelu);
            distruge_Lista(l);
            _CrtDumpMemoryLeaks();
            return 0;
        case(6):
            printf("Alegeti dupa ce vreti sa sortati : ");
            scanf_s("%s" , mod , 20);
            ordonareProduse(farmacia_nelu , mod);
            break;
        case(7):
            AfisareNoua(farmacia_nelu);
            break;
        case(8):
             v = Sterge_Lista_Last(l, farmacia_nelu);
             for (int i = 0; i < v->n; i++)
             {
                 aux->e[i].uniqueCode = v->e[i].uniqueCode;
                 aux->e[i].quantity = v->e[i].quantity;
                 aux->e[i].med.concentr = v->e[i].med.concentr;
                 strcpy_s(aux->e[i].med.name, 20, v->e[i].med.name);
             }
             aux->n = v->n;
             aux->cp = v->cp;
             farmacia_nelu = aux;
            break;
        }
        
        printf("\n");
    }
    
    return 0;
}
