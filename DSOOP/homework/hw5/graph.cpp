#include "graph.h"
#include "iostream"
//Maybe need to add more args

graph::graph(ssize_t nodes){
	this->len = nodes;
	filled=0;
	timestamp=0;
	vertices = new Vertex*[len];
	//vertices ={0};
	for(int i =0;i<len;i++){
		vertices[i]=NULL;
	}
}
graph::~graph(){
	ssize_t idx=0;
	for(idx;idx<len;idx++){
		delete vertices[idx];	
	}
	delete [] vertices;
}
void searchAid(const ssize_t& key, Vertex* v, ssize_t *timestamp, std::vector<const Vertex*> &topological ){
	*timestamp+=1;
	v->d = *timestamp;	
	v->color = 1;
	std::vector<Vertex*>::iterator it;
	for(it = v->adjacency.begin(); it != v->adjacency.end();it++){
		if((*it)->color == 0){
			searchAid((*it)->value, (*it),timestamp, topological);
		}	
	}
	*timestamp+=1;	
	v->f = *timestamp;
	v->color =2;
	topological.push_back(v);
	return;
}
//just adding the node to the array
void graph::newNode(const ssize_t& key){
	Vertex *vertex = new Vertex(key);	
	vertices[filled] = vertex;
	//std::cout<<vertices[filled]->value<<" is what we just put in at index  "<<filled<<std::endl; 
	filled++;
}
Vertex* graph::getVertex(const ssize_t& idx){
	ssize_t index = 0;
	for(index;index<len;index++){
		if(vertices[index]->value == idx){
			return vertices[index];
			break;
		}
	}
	return NULL;
}
//The problem was instead of adding the same node with the same value, 
//I was creating a new node with the secondary value every time, so 
//twice as much nodes. Then the nodes in the vertices[] arr and each 
//individual adjacency list were different.
void graph::addOrder(const ssize_t& primary, const size_t secondary){
	Vertex *insert = getVertex(secondary);
	//std::cout<<"This is the vertex we got: "<<insert->value<<std::endl;	
	for(ssize_t idx=0;idx<len;idx++){
		if(vertices[idx]->value == primary){
			vertices[idx]->adjacency.push_back(insert);	
			break;
		}
	}
		
}
void graph::print(){
	ssize_t idx=0;
	while(idx<filled){
		std::cout<<"adjacency list for "<<vertices[idx]->value<<": ";
		std::vector<Vertex*>::iterator it;	
		for(it=vertices[idx]->adjacency.begin();it!=vertices[idx]->adjacency.end();it++){
				std::cout<<(*it)->value<<"-> ";
		}
		std::cout<<std::endl;
		idx++;	
	}
}
void graph::printColor(){
	ssize_t idx =0;
	for(idx;idx<len;idx++){
		std::cout<<vertices[idx]->value<<": "<<vertices[idx]->color<<std::endl;	
	}
}
void graph::printNodeInfo(){
	ssize_t idx = 0;
	while(idx<filled){
		std::cout<<"value: "<<vertices[idx]->value<<"\tcolor: "<<vertices[idx]->color<<"\tstart: "<<vertices[idx]->d<<"\tfinish: "<<vertices[idx]->f<<std::endl;
		idx++;
	}
}
void graph::printTopologicalOrder(std::ofstream& output){
	std::vector<const Vertex*>::iterator it;
	for(it = topological.end()-1;it!= topological.begin()-1;it--){
		output<<(*it)->value<<" ";
	}
	output<<std::endl;
}
void graph::printTopologicalOrderToStdOut(){
	std::vector<const Vertex*>::iterator it;	
	for(it=topological.end()-1;it!=topological.begin()-1;it--){
		std::cout<<(*it)->value<<" ";	
	}
	std::cout<<std::endl;
}
//Here is where we perform DFS
void graph::search(){
	ssize_t idx=0;
	for(idx;idx<filled;idx++){
		if(vertices[idx]->color == 0){	
			searchAid(idx,vertices[idx], &timestamp, topological); 	
		}	
	}
}

