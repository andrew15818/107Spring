#include<iostream>
#include<fstream>
//#include<vector>
#include "graph.h"
using namespace std;
int main(){
	size_t nodes;
	ofstream output;
	ifstream input_file;
	input_file.open("sample data.txt");
	output.open("TP_Sort_Result.txt");

	while(input_file>>nodes){

		graph Graph(nodes);
		size_t input,layers;
		
		
		
		
		/*first receving the values of the vertices*/
		for(int i=0;i<nodes;i++){
			input_file>>input;	
			Graph.newNode(input);
		}
		input_file>>layers;
		size_t primary, secondary;
		string order;

		for(int j=0;j<layers;j++){
			input_file>>primary>>order>>secondary;		
			Graph.addOrder(secondary, primary);

		}
		Graph.search();
		//Graph.print();
		//Graph.printNodeInfo();
		Graph.printTopologicalOrder(output);
	}
	return 0;
}
