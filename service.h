#include "repository.h"

int cmpNume(const void *a, const void *b);

int cmpConcentr(const void* a, const void* b);

int cmpMarimeStoc(const void* a, const void* b);

void bubble_sort(vectorDinamic* v, int (*comparator)(const void* a, const void* b));

stoc createElem(char *name, float conc);

int searchElem(vectorDinamic* pharma, char* name);

int addElem(vectorDinamic* pharma, char* name, float conc);

void actualizare_NumeMedicament(vectorDinamic* pharma, char* name, int pos );

void actualizare_ConcMedicament(vectorDinamic* pharma, float conc,int pos );

int modifElem(vectorDinamic *pharma, char* name, char* modif_name, float modif_conc);

void stergeStoc_s(vectorDinamic *pharma, char* name);

vectorDinamic* ordonareProduse(vectorDinamic* pharma, char* cond);

vectorDinamic* filtrareStoc(vectorDinamic* pharma, int stocMin);

vectorDinamic* filtrareNume(vectorDinamic* pharma, char condNume);
