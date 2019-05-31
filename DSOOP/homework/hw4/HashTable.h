#ifndef HASH_TABLE_H
#define HASH_TABLE_H
#include<string>
#include<iostream>
/*Maybe use a linked list for colliding
 * elements?*/
struct patient{
	public:
	patient *prev = NULL,*next=NULL;
	std::string key;
	std::string gender;
	int height, weight;
	//public:	
		 std::string getGender()const{
			//std::cout<<"when calling gender function, returning "<<this->gender<<std::endl;
			return this->gender;
		}int getHeight()const{
			//std::cout<<"when calling the height function, returning "<<this->height<<std::endl;
			return this->height;
		}int getWeight()const{
			return  this->weight;
		}
		 void print_object()const{
			std::cout<<this->key<<" "<<this->gender<<" "<<this->height<<" "<<this->weight<<std::endl; 
		 }
};
class HashTable{
	private:
		patient **patients;
		std::string key, gender;
		int height, weight;
		int Hash(std::string);
	public:
		HashTable();				
		~HashTable();
		void addItem(std::string,std::string , int , int );
   		std::string getGender();
		//int 		getHeight();
		//int 		getWeight();
		const patient& operator[](std::string);		//return const ref b/c don't want change

		void print();

};
#endif
