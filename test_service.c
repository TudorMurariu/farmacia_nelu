#include "service.h"
#include <assert.h>
#include <stdio.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

void test_createElem(){
	stoc medicament;
	strcpy(medicament.med.name, "Bixtonim");
	medicament.med.concentr = 20.01;
	medicament.quantity = 1;

	char name[] = "Bixtonim"; 
	stoc compare = createElem(name, 20.01); 
	medicament.uniqueCode = compare.uniqueCode;

	assert(compareStocs(&medicament,&compare)==1);

}

void test_addElem(){
	vectorDinamic* pharmacy = creeazaVectDin(100);

	addElem(pharmacy, "Bixtonim",20.01);

	assert(dim(pharmacy)== 1);
	stoc test =  createElem("Bixtonim",20.01);
	assert(compareStocs(element(pharmacy, 0),&test)==1);

	addElem(pharmacy, "Bixtonim", 20.01);
	assert(element(pharmacy, 0)->quantity == 2 );

	distruge(pharmacy);
}

void test_searchElem(){
	vectorDinamic* pharmacy = creeazaVectDin(100);
	addElem(pharmacy, "Bixtonim",20.01);
	addElem(pharmacy, "Paracetamol",18.2);
	addElem(pharmacy, "Aspacartim",50);

	char name[] = "Aspacartim";

	assert(searchElem(pharmacy,name) == 2);

	distruge(pharmacy);

}

void test_modifElem(){
	vectorDinamic* pharmacy = creeazaVectDin(100);
	
	addElem(pharmacy, "Bixtonim",20.01);
	addElem(pharmacy, "Paracetamol",18.2);
	addElem(pharmacy, "Aspacartim",50);

	modifElem(pharmacy, "Aspacartim", "Theraflu", 0);

	assert(strcmp(element(pharmacy, 2)->med.name, "Theraflu")==0);

	modifElem(pharmacy, "Paracetamol", "", 25.07);

	assert(floor(element(pharmacy, 1)->med.concentr*100) == 2507);

	distruge(pharmacy);
}

void test_stergeStoc(){
	vectorDinamic* pharma = creeazaVectDin(100);

	addElem(pharma, "Theraflu", 21.5);
	addElem(pharma, "Theraflu", 21.5);
	addElem(pharma, "Theraflu", 21.5);
	addElem(pharma, "Theraflu", 21.5);

	stergeStoc_s(pharma, "Theraflu");
	assert(dim(pharma) == 0);

	distruge(pharma);
}

void test_ordonareProduse(){
	vectorDinamic* pharma = creeazaVectDin(100);

	addElem(pharma, "Theraflu", 19.5);
	addElem(pharma, "Paracetamol", 44);
	addElem(pharma, "Paracetamol", 44);
	addElem(pharma, "Paracetamol", 44);

	addElem(pharma, "Gripovit", 65);
	addElem(pharma, "Gripovit", 65);
	addElem(pharma, "Abrolen", 21.5);
	addElem(pharma, "Abrolen", 21.5);
	addElem(pharma, "Abrolen", 21.5);


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
}

void test_filtrareStoc(){
	vectorDinamic* pharma = creeazaVectDin(100);

	addElem(pharma, "Theraflu", 19.5);
	addElem(pharma, "Paracetamol", 44);
	addElem(pharma, "Paracetamol", 44);
	addElem(pharma, "Paracetamol", 44);

	addElem(pharma, "Gripovit", 65);
	addElem(pharma, "Gripovit", 65);
	addElem(pharma, "Abrolen", 21.5);
	addElem(pharma, "Abrolen", 21.5);
	addElem(pharma, "Abrolen", 21.5);

	vectorDinamic* aux = filtrareStoc(pharma, 2);
	assert(dim(aux) == 3);
	distruge(aux);

	aux = filtrareNume(pharma, 'A');
	assert(dim(aux) == 1);
	
	distruge(aux);
	distruge(pharma);
}

void run_tests(){
	test_createElem();
	test_addElem();
	test_searchElem();
	test_modifElem();
	test_stergeStoc();
	test_ordonareProduse();
	test_filtrareStoc();
}

int main(){
	run_tests();

	return 0;
}