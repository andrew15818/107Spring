#include"HashTable.h"
#include<iostream>
#define MAX_SIZE 3000
HashTable::HashTable(){
	patients = new patient*[MAX_SIZE];
	//patient patients[MAX_SIZE];
	for(int i =0;i<MAX_SIZE;i++){
		patients[i] =NULL;
	}
}

HashTable::~HashTable(){
	for(int i = 0; i<MAX_SIZE; i++){
		if(patients[i] != NULL){
		//	std::cout<<sizeof(patient)<<" is the size of patient object"<<std::endl;
			patient *previous = new patient;
			previous=NULL;			
			patient *tmp ;//= new patient;
			tmp = patients[i];
			while(tmp != NULL){
				previous = tmp;
				tmp = tmp->next;	
				delete previous;
			}	
			delete tmp;
		}	
		
	}

}

/*simple hash*/ 
int HashTable::Hash(std::string key){
	int primo = 131;
	unsigned int sum=0;
	for(int i=0; i<key.length();i++){
		sum+=((int)key[i]*primo)%MAX_SIZE;	
	}
	sum%=MAX_SIZE;
	return sum;
}
/*create a linked list(chaining) if patients[index] is taken*/
void HashTable::addItem(std::string key, std::string gender, int height, int weight){
	int index = Hash(key);
	patient *tmp = new patient;
	tmp->key = key;
	tmp->gender = gender;	
	tmp->height = height;
	tmp->weight = weight;
	if(patients[index]== NULL){	
		//std::cout<<"adding elements at index "<<index<<std::endl;
		patients[index] = tmp;	
	}
	/*Incrementing the pointer b4 setting the address :(*/
	else if(patients[index]!= NULL){
		
		patient *insert = new patient;
		insert  = patients[index];
		
		while(insert->next!=NULL){
			insert = insert->next;
			//std::cout<<"all good now with temporary index node"<<std::endl;
		}
		tmp->prev = insert;
		insert->next = tmp;
	}
}
/*search for the given item in the list and return const ref*/
const patient& HashTable::operator[](std::string key){
	int index = Hash(key); 
	patient *prueba = new patient;
	if(patients[index]->key ==key){
		return (patient&)*patients[index];
	//	prueba = patients[index];
	}
	else{
		prueba = patients[index];
		while(prueba->key!=key ){
			prueba=prueba->next;
		}
		//return (patient&)*prueba;
	}

		return (patient&)*prueba;
}

void HashTable::print(){
/*
	std::cout<<"Patient's records: "<<std::endl;
	hashTable["puta"].getGender();
	std::cout<<"key: "<<paciente->key<<std::endl;
	std::cout<<"height: "<<paciente->height<<std::endl;
	std::cout<<"weight: "<<paciente->weight<<std::endl;
*/
	for(int i=0;i<MAX_SIZE;i++){
		if(patients[i]!=NULL){
			patient *tmp = patients[i];
			while(tmp != NULL){
					//std::cout<<tmp->key<<" is at index ,"<<i;
					std::cout<<tmp->gender<<" ";
					std::cout<<tmp->height<<" "<<tmp->weight<<std::endl;
					tmp = tmp->next;
			}
		}
	}
}
