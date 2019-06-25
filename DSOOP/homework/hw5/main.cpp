#include<iostream>
#include<vector>
#include "graph.h"
using namespace std;
int main(){
	size_t nodes;

	while(cin>>nodes){
		//cout<<"Working with "<<nodes<< " nodes"<<endl;	
		graph Graph(nodes);
		size_t input,layers;
		/*first receving the values of the vertices*/
		for(int i=0;i<nodes;i++){
			cin>>input;	
			Graph.newNode(input);
		}
		cin>>layers;
		size_t primary, secondary;
		string order;
		cout<<layers<<" layers to look through"<<endl;
		for(int j=0;j<layers;j++){
			cin>>primary>>order>>secondary;		
			Graph.addOrder(secondary, primary);
			//cout<<primary<<" "<<order<<" "<<secondary;	
		}
		Graph.search();
		//Graph.print();
		//Graph.printNodeInfo();
		Graph.printTopologicalOrder();
	}
	return 0;
}
