#include "graph.h"
#include <vector>
#include "iostream"
graph::graph(size_t nodes){
	this->len = nodes;
	filled=0;
	vertices = new Vertex*[len];
	//vertices ={0};
	for(int i =0;i<len;i++){
		vertices[i]=NULL;
	}
}
//just adding the node to the array
void graph::newNode(const size_t& key){
	Vertex *vertex = new Vertex(key);	
	vertices[filled] = vertex;
	std::cout<<vertices[filled]->value<<" is what we just put in at index  "<<filled<<std::endl;
	filled++;
}
//adding the edges of the graph(completion order for the Topological sort)
void graph::addOrder(const size_t& primary, const size_t secondary){
	Vertex *insert = new Vertex(secondary);
	for(size_t idx=0;idx<len;idx++){
		if(vertices[idx]->value == primary){
			vertices[idx]->adjacency.push_back(insert);	
			std::cout<<"added pair "<<vertices[idx]->value<<" > "<<insert->value<<std::endl;
			break;
		}
	}
}
void graph::print(){
	size_t idx=0;
	while(vertices[idx]!=NULL){
		std::cout<<"adjacency list for "<<vertices[idx]->value<<": ";
		std::vector<Vertex*>::iterator it;	
		for(it=vertices[idx]->adjacency.begin();it!=vertices[idx]->adjacency.end();it++){
				std::cout<<(*it)->value<<"-> ";
		}
		std::cout<<std::endl;
		idx++;	
	}
}


