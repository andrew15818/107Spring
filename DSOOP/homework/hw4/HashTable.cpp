#include"HashTable.h"
#include<iostream>
#define MAX_SIZE 3000
HashTable::HashTable(){
	patients = new patient*[MAX_SIZE];
	patients = {NULL};
}
HashTable::~HashTable(){
	for(int i =0;i<MAX_SIZE;i++){
		patient* tmp = patients[i];
		/*
		while(tmp!=NULL){
			patient *scrap = tmp;
			tmp = tmp->next;
			delete scrap;
		}*/
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
