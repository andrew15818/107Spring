#include "graph.h"
#include <vector>
//#include "cstddef"
graph::graph(size_t nodes){
	this->len = nodes;
	vertices = new Vertex*[this->len];
	vertices=NULL;
}
void graph::addNode(const size_t& key, const Vertex& v){
	for(size_t i=0;i<len;i++){
		if(vertices[i]->value == key){
			vertices[i]->adjacency.push_back(v);
		}
	}
}


