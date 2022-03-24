#include "test_service.h"
#include <assert.h>
#include <stdio.h>
#include <math.h>
#include <stdio.h>
#include <string.h>


void test_createElem() {
	stoc medicament;
	strcpy_s(medicament.med.name, 20 , "Bixtonim");
	medicament.med.concentr = 20.01;
	medicament.quantity = 1;

	char name[] = "Bixtonim";
	stoc compare = createElem(name, 20.01);
	medicament.uniqueCode = compare.uniqueCode;

	assert(compareStocs(&medicament, &compare) == 1);

}

void test_addElem() {
	Lista* l = init_Lista();
	vectorDinamic* pharmacy = creeazaVectDin(2);

	addElem(pharmacy, "Bixtonim", 20.01,l);

	assert(dim(pharmacy) == 1);
	stoc test = createElem("Bixtonim", 20.01);
	assert(compareStocs(element(pharmacy, 0), &test) == 1);

	addElem(pharmacy, "Bixtonim", 20.01,l);
	assert(element(pharmacy, 0)->quantity == 2);

	distruge(pharmacy);
	distruge_Lista(l);
}

void test_searchElem() {
	Lista* l = init_Lista();
	vectorDinamic* pharmacy = creeazaVectDin(2);
	addElem(pharmacy, "Bixtonim", 20.01,l);
	addElem(pharmacy, "Paracetamol", 18.2,l);
	addElem(pharmacy, "Aspacartim", 50,l);

	char name[] = "Aspacartim";

	assert(searchElem(pharmacy, name) == 2);

	distruge(pharmacy);
	distruge_Lista(l);
}

void test_modifElem() {
	Lista* l = init_Lista();
	vectorDinamic* pharmacy = creeazaVectDin(2);

	addElem(pharmacy, "Bixtonim", 20.01,l);
	addElem(pharmacy, "Paracetamol", 18.2,l);
	addElem(pharmacy, "Aspacartim", 50,l);

	modifElem(pharmacy, "Aspacartim", "Theraflu", 0,l);

	assert(strcmp(element(pharmacy, 2)->med.name, "Theraflu") == 0);

	modifElem(pharmacy, "Paracetamol", "", 25.07,l);

	assert(floor(element(pharmacy, 1)->med.concentr * 100) == 2507);

	distruge(pharmacy);
	distruge_Lista(l);
}

void test_stergeStoc() {
	Lista* l = init_Lista();
	vectorDinamic* pharma = creeazaVectDin(2);

	addElem(pharma, "Theraflu", 21.5,l);
	addElem(pharma, "Theraflu", 21.5,l);
	addElem(pharma, "Theraflu", 21.5,l);
	addElem(pharma, "Theraflu", 21.5,l);

	stergeStoc_s(pharma, "Theraflu",l);
	assert(dim(pharma) == 0);

	distruge(pharma);
	distruge_Lista(l);
}

void test_ordonareProduse() {
	Lista* l = init_Lista();
	vectorDinamic* pharma = creeazaVectDin(2);

	addElem(pharma, "Theraflu", 19.5,l);
	addElem(pharma, "Paracetamol", 44,l);
	addElem(pharma, "Paracetamol", 44,l);
	addElem(pharma, "Paracetamol", 44,l);

	addElem(pharma, "Gripovit", 65,l);
	addElem(pharma, "Gripovit", 65,l);
	addElem(pharma, "Abrolen", 21.5,l);
	addElem(pharma, "Abrolen", 21.5,l);
	addElem(pharma, "Abrolen", 21.5,l);


	vectorDinamic* aux = ordonareProduse(pharma, "nume");
	assert(strcmp(element(aux, 0)->med.name, "Abrolen") == 0);
	//printf("%s", element(aux, 0)->med.name);
	distruge(aux);

	aux = ordonareProduse(pharma, "concentratie");
	assert(strcmp(element(aux, 0)->med.name, "Theraflu") == 0);
	distruge(aux);


	aux = ordonareProduse(pharma, "stoc");
	assert(strcmp(element(aux, 0)->med.name, "Theraflu") == 0);
	distruge(aux);


	distruge(pharma);
	distruge_Lista(l);
}

void test_filtrareStoc() {
	vectorDinamic* pharma = creeazaVectDin(2);
	Lista* l = init_Lista();
	addElem(pharma, "Theraflu", 19.5, l);
	addElem(pharma, "Paracetamol", 44, l);
	addElem(pharma, "Paracetamol", 44, l);
	addElem(pharma, "Paracetamol", 44, l);

	addElem(pharma, "Gripovit", 65, l);
	addElem(pharma, "Gripovit", 65, l);
	addElem(pharma, "Abrolen", 21.5, l);
	addElem(pharma, "Abrolen", 21.5, l);
	addElem(pharma, "Abrolen", 21.5, l);

	vectorDinamic* aux = filtrareStoc(pharma, 2);
	assert(dim(aux) == 3);
	distruge(aux);

	aux = filtrareNume(pharma, "A");
	assert(dim(aux) == 1);

	distruge(aux);
	distruge(pharma);
	distruge_Lista(l);
}

void run_tests() {
	test_createElem();
	test_addElem();
	test_searchElem();
	test_modifElem();
	test_stergeStoc();
	test_ordonareProduse();
	test_filtrareStoc();
}
