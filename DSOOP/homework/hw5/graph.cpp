#include "graph.h"
#include "iostream"
//Maybe need to add more args

graph::graph(size_t nodes){
	this->len = nodes;
	filled=0;
	timestamp=0;
	vertices = new Vertex*[len];
	//vertices ={0};
	for(int i =0;i<len;i++){
		vertices[i]=NULL;
	}
}

void searchAid(const size_t& key, Vertex* v, size_t *timestamp){
	std::cout<<"current timestamp : "<<*timestamp<<std::endl;
	v->d=(*timestamp)+1;
	v->color = 1;
	std::cout<<"now searching node with value "<<v->value<<std::endl;
	std::vector<Vertex*>::iterator it;
	for(it = v->adjacency.begin();it!=v->adjacency.end();it++){
		if((*it)->color==0){
			searchAid((*it)->value, (*it), timestamp);
		}	
	}
	v->color = 2;
	*timestamp+=1;
	v->f = *timestamp;
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
void graph::printNodeInfo(){
	size_t idx = 0;
	while(idx<filled){
		std::cout<<"value: "<<vertices[idx]->value<<"\tstart: "<<vertices[idx]->d<<"\tfinish: "<<vertices[idx]->f<<std::endl;
		idx++;
	}
}
//Here is where we perform DFS
void graph::search(){
	size_t idx=0;
	for(idx;idx<filled;idx++){
		if(vertices[idx]->color ==0){
			searchAid(idx,vertices[idx], &timestamp);
		}
	}
}

