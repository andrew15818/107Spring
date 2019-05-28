#include<iostream>
#include"HashTable.h"
#include<vector>
using namespace std;
int main(){
HashTable hashTable;

    // for evaluation
    vector<string> testCases;

    // read data line by line
    std::ifstream infile("data.txt");
    string key, gender;
    int height, weight;

    while (infile >> key >> gender >> height >> weight)
    {
        hashTable.addItem(key, gender, height, weight);

        // collect evaluated test cases
        testCases.push_back(key);
    }


	return 0;
}
