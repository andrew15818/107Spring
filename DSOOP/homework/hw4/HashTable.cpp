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
			std::cout<<"entering loop"<<std::endl;
			patient *previous=NULL;	
			patient *tmp = patients[i];
			while(tmp != NULL){
				std::cout<<"Entering second loop "<<std::endl;
				previous = tmp;
				tmp = tmp->next;
				delete previous;
			}	
		}	
	}
	delete[] patients;
}
/*simple hash based on golden ratio*/
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
	/*Check if there is a better way to do this later*/	
	else if(patients[index] != NULL){
		patient *insert  = patients[index];
		while(1){
			insert = insert->next;	
			if( insert == NULL){
				insert->prev = tmp;	
				tmp->prev->next = NULL;
				break;
			}
		}
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
