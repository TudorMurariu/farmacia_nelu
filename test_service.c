#include "service.c"
#include <assert.h>
#include <stdio.h>
#include <math.h>
#include <stdio.h>

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

	assert(searchElem(&pharmacy,medic.name) == 2);

}

void test_modifElem(){
	farm pharmacy;
	pharmacy.nrMeds = 0;
	addElem(&pharmacy, "Bixtonim",20.01);
	addElem(&pharmacy, "Paracetamol",18.2);
	addElem(&pharmacy, "Aspacartim",50);

	modifElem(&pharmacy, "Aspacartim", "Theraflu", 0);

	assert(strcmp(pharmacy.cont[2].med.name, "Theraflu")==0);

	modifElem(&pharmacy, "Paracetamol", "", 25.07);

	assert(floor(pharmacy.cont[1].med.concentr*100) == 2507);
}

void test_stergeStoc(){
	farm pharma;
	pharma.nrMeds = 0;
	addElem(&pharma, "Theraflu", 21.5);
	addElem(&pharma, "Theraflu", 21.5);
	addElem(&pharma, "Theraflu", 21.5);
	addElem(&pharma, "Theraflu", 21.5);

	stergeStoc_s(&pharma, "Theraflu");
	assert(pharma.nrMeds == 0);
}

void test_ordonareProduse(){
	farm pharma;
	pharma.nrMeds = 0;
	addElem(&pharma, "Theraflu", 19.5);
	addElem(&pharma, "Paracetamol", 44);
	addElem(&pharma, "Paracetamol", 44);
	addElem(&pharma, "Paracetamol", 44);
	
	addElem(&pharma, "Gripovit", 65);
	addElem(&pharma, "Gripovit", 65);

	addElem(&pharma, "Abrolen", 21.5);
	addElem(&pharma, "Abrolen", 21.5);
	addElem(&pharma, "Abrolen", 21.5);


	farm aux = ordonareProduse(&pharma, "nume");
	assert(strcmp(aux.cont[0].med.name, "Abrolen") == 0);

	aux = ordonareProduse(&pharma, "concentratie");
	assert(strcmp(aux.cont[0].med.name, "Theraflu") == 0);

	aux = ordonareProduse(&pharma, "stoc");
	assert(strcmp(aux.cont[0].med.name, "Theraflu") == 0);



}

void test_filtrareStoc(){
	farm pharma;
	pharma.nrMeds = 0;
	addElem(&pharma, "Theraflu", 19.5);
	addElem(&pharma, "Paracetamol", 44);
	addElem(&pharma, "Paracetamol", 44);
	addElem(&pharma, "Paracetamol", 44);
	
	addElem(&pharma, "Gripovit", 65);
	addElem(&pharma, "Gripovit", 65);

	addElem(&pharma, "Abrolen", 21.5);
	addElem(&pharma, "Abrolen", 21.5);
	addElem(&pharma, "Abrolen", 21.5);

	farm aux = filtrareStoc(&pharma, 2);
	assert(aux.nrMeds == 3);

	aux = filtrareNume(&pharma, 'A');
	assert(aux.nrMeds == 1);

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
