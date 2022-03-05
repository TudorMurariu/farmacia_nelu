#include "service.c"
#include <assert.h>

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
	farm pharmacy;
	pharmacy.nrMeds = 0;
	addElem(&pharmacy, "Bixtonim",20.01);

	assert(pharmacy.nrMeds == 1);
	stoc test =  createElem("Bixtonim",20.01);
	assert(compareStocs(&pharmacy.cont[0],&test)==1);

	addElem(&pharmacy, "Bixtonim", 20.01);
	assert(pharmacy.cont[0].quantity==2);

}

void test_searchElem(){
	farm pharmacy;
	pharmacy.nrMeds = 0;
	addElem(&pharmacy, "Bixtonim",20.01);
	addElem(&pharmacy, "Paracetamol",18.2);
	addElem(&pharmacy, "Aspacartim",50);
	produs medic;
	medic.concentr = 50;
	strcpy(medic.name , "Aspacartim");

	assert(searchElem(&pharmacy,medic) == 2);

}

int main(){
	test_createElem();
	test_addElem();
	test_searchElem();
	return 0;
}