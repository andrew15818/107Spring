#include<iostream>
#include"HashTable.h"
#include<vector>
using namespace std;
int main(){
HashTable hashTable;

    // for evaluation
    vector<string> testCases;

    // read data line by line
    //std::ifstream infile("data.txt");
	//cout<<"hash table\"puta\" "<<endl;
    string key, gender;
    int height, weight;
	while(cin>>key>>gender>>height>>weight){
		if(key=="0")break;
		hashTable.addItem(key,gender,height,weight);


	}
	cout<<"calling print object function "<<endl;
	//hashTable["puta"].print_object();
	std::cout<<hashTable["puta"].getGender()<<std::endl;
	std::cout<<hashTable["puta"].getHeight()<<std::endl;
	std::cout<<hashTable["puta"].getWeight()<<std::endl;

/*
    while (infile >> key >> gender >> height >> weight)
    {
        hashTable.addItem(key, gender, height, weight);

        // collect evaluated test cases
        testCases.push_back(key);
    }
*/

	return 0;
}
