#include"HashTable.h"
#include<iostream>
#define MAX_SIZE 3000
HashTable::HashTable(){
	patients = new patient*[MAX_SIZE];
	for(int i =0;i<MAX_SIZE;i++){
		patients[i]=NULL;	
	}
}
HashTable::~HashTable(){
	for(int i = 0; i<MAX_SIZE; i++){
		if(patients[i] != NULL){

			patient *previous=NULL;	
			patient *tmp = patients[i];
			while(tmp != NULL){

				previous = tmp;
				tmp = tmp->next;
				delete previous;
			}	
		}	
	}
	delete[] patients;

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
void HashTable::addItem(std::string key, std::string gender, int height, int weight){
	int index = Hash(key);
	patient *tmp = new patient;
	tmp->key = key;
	tmp->gender = gender;	
	tmp->height = height;
	tmp->weight = weight;
	if(patients[index] == NULL){	
		patients[index] = tmp;	
	}
	/*Incrementing the pointer b4 setting the address :(*/
	else if(patients[index] != NULL){
		patient *insert  = new patient;
		insert = patients[index];
		
		while(1){
			if(insert->next == NULL){
				insert->next = tmp;
				tmp->prev = insert;
				break;
			}	
			else{
				insert = insert->next;	
			}
		}
		//delete insert;
	}	
}
std::string HashTable::getGender(){
	return this->gender;
}
int HashTable::getHeight(){
	return this->height;
}
int HashTable::getWeight(){
	return this->weight;;
}
/*search for the given item in the list and return const ref*/
/*
const patient& HashTable::operator[](std::string key){
	int index = Hash(key); 
	return patients[index];		
}*/
/*
void HashTable::print(const patient& paciente){
	std::cout<<"Patient's records: "<<std::endl;
	std::cout<<"key: "<<paciente->key<<std::endl;
	std::cout<<"height: "<<paciente->height<<std::endl;
	std::cout<<"weight: "<<paciente->weight<<std::endl;
}*/
