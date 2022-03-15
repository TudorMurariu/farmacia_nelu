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
	farm pharmacy = new_farm();
	addElem(&pharmacy, "Bixtonim",20.01);

	
	assert(pharmacy.nrMeds == 1);
	stoc test =  createElem("Bixtonim",20.01);
	assert(compareStocs(getPos(&pharmacy,0),&test)==1);

	addElem(&pharmacy, "Bixtonim", 20.01);
	assert(getPos(&pharmacy,0)->quantity == 2);

	destroyFarm(&pharmacy);
}

void test_searchElem(){
	farm pharmacy = new_farm() ;
	pharmacy.nrMeds = 0;
	addElem(&pharmacy, "Bixtonim",20.01);
	addElem(&pharmacy, "Paracetamol",18.2);
	addElem(&pharmacy, "Aspacartim",50);
	produs medic;
	medic.concentr = 50;
	strcpy(medic.name , "Aspacartim");

	assert(searchElem(&pharmacy,medic.name) == 2);
	destroyFarm(&pharmacy);
}

void test_modifElem(){
	farm pharmacy = new_farm();
	pharmacy.nrMeds = 0;
	addElem(&pharmacy, "Bixtonim",20.01);
	addElem(&pharmacy, "Paracetamol",18.2);
	addElem(&pharmacy, "Aspacartim",50);

	modifElem(&pharmacy, "Aspacartim", "Theraflu", 0);

	assert(strcmp(getPos(&pharmacy, 2)->med.name, "Theraflu")==0);

	modifElem(&pharmacy, "Paracetamol", "", 25.07);

	assert(floor(getPos(&pharmacy, 1)->med.concentr*100) == 2507);

	destroyFarm(&pharmacy);
}

void test_stergeStoc(){
	farm pharma = new_farm();
	pharma.nrMeds = 0;
	addElem(&pharma, "Theraflu", 21.5);
	addElem(&pharma, "Theraflu", 21.5);
	addElem(&pharma, "Theraflu", 21.5);
	addElem(&pharma, "Theraflu", 21.5);

	stergeStoc_s(&pharma, "Theraflu");
	assert(pharma.nrMeds == 0);
	destroyFarm(&pharma);

}

void test_ordonareProduse(){
	farm pharma = new_farm();
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

	farm aux = new_farm();
	ordonareProduse(&pharma, "nume", &aux);

	
	assert(strcmp(getPos(&aux, 0)->med.name, "Abrolen") == 0);

	ordonareProduse(&pharma, "concentratie", &aux);
	assert(strcmp(getPos(&aux, 0)->med.name, "Theraflu") == 0);

	ordonareProduse(&pharma, "stoc", &aux);
	assert(strcmp(getPos(&aux, 0)->med.name, "Theraflu") == 0);
	

	destroyFarm(&pharma);
	destroyFarm(&aux);

}

void test_filtrareStoc(){
	farm pharma = new_farm();
	addElem(&pharma, "Theraflu", 19.5);
	addElem(&pharma, "Paracetamol", 44);
	addElem(&pharma, "Paracetamol", 44);
	addElem(&pharma, "Paracetamol", 44);
	
	addElem(&pharma, "Gripovit", 65);
	addElem(&pharma, "Gripovit", 65);

	addElem(&pharma, "Abrolen", 21.5);
	addElem(&pharma, "Abrolen", 21.5);
	addElem(&pharma, "Abrolen", 21.5);

	farm aux = new_farm();
	filtrareStoc(&pharma, 2, &aux);
	assert(aux.nrMeds == 3);
	destroyFarm(&aux);
	
	filtrareNume(&pharma, 'A', &aux);
	assert(aux.nrMeds == 1);
	
	
	destroyFarm(&pharma);
	destroyFarm(&aux);


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

