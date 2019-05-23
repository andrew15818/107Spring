#include"HashTable.h"
#include<iostream>
#define MAX_SIZE 10000
HashTable::HashTable(){
	patients = new patient[MAX_SIZE];
}
HashTable::~HashTable(){
	delete[] patients;
}
/*simple hash based on golden ratio*/
int HashTable::Hash(std::string key){
	std::cout<<"key received is "<<key<<std::endl;
	double random_prime = .6180339; //golden ratio
	int primo = 131;
	unsigned int sum=0;
	for(int i=0; i<key.length();i++){
		sum+=((int)key[i]*primo)%MAX_SIZE;	
	}
	sum%=MAX_SIZE;
	std::cout<<"the final hash value of this is "<<sum<<std::endl;
	return 0;
}
void HashTable::addItem(std::string key, std::string gender, int height, int weight){
	int index = Hash(key);
}
std::string HashTable::getGender(){
	return "hola";
}
int HashTable::getHeight(){
	return 0;
}
int HashTable::getWeight(){
	return 0;
}
/*search for the given item in the list and return const ref*/
/*
patient& HashTable::operator[](std::string key){
		
}*/
