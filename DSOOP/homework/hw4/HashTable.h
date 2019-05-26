#ifndef HASH_TABLE_H
#define HASH_TABLE_H
#include<string>
/*Maybe use a linked list for colliding
 * elements?*/
struct patient{
	patient *prev = NULL,*next=NULL;
	std::string key="";
	std::string gender;
	int height, weight;
};
class HashTable{
	private:
		patient *patients;
		std::string key, gender;
		int height, weight;
		int Hash(std::string);
	public:
		HashTable();				
		~HashTable();
		void addItem(std::string,std::string , int , int );
   		std::string getGender();
		int 		getHeight();
		int 		getWeight();
		const patient& 	operator[](std::string);		//return a reference bc we would
									//wish to modify returned object
};
#endif
