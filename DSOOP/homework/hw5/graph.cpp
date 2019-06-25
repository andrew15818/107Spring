#include "graph.h"
#include "iostream"
//Maybe need to add more args

graph::graph(size_t nodes){
	this->len = nodes;
	filled=0;
	timestamp=1;
	vertices = new Vertex*[len];
	//vertices ={0};
	for(int i =0;i<len;i++){
		vertices[i]=NULL;
	}
}

void searchAid(const size_t& key, Vertex* v, size_t *timestamp,Vertex** vertices){
	//maybe keep track of the idx in each iteration and pass it, instead of trying to pass the vertex object
	//v->d = *timestamp;	
	//v->color = 1;
	//std::cout<<"Going to compare the values in vertex array with the vertex pointer passed to function"<<std::endl;
	//std::cout<<"value in v: "<<v->value<<" "<<v->color<<std::endl;
	Vertex *puta = vertices[key];
	puta ->color=1;
	*timestamp+=1;
	puta->d = *timestamp;
	
	std::cout<<"value in m'array: "<<puta->value<<""<<puta->color<<std::endl;	
	std::vector<Vertex*>::iterator it;
	for(it = puta->adjacency.begin(); it != puta->adjacency.end();it++){
		if((*it)->color == 0){
			(*timestamp)++;
			searchAid((*it)->value-1, puta,timestamp,vertices);
		}	
	}
	*timestamp+=1;	
	puta->f = *timestamp;
	v->color =2;

	return;
}
//just adding the node to the array
void graph::newNode(const size_t& key){
	Vertex *vertex = new Vertex(key);	
	vertices[filled] = vertex;
	std::cout<<vertices[filled]->value<<" is what we just put in at index  "<<filled<<std::endl; filled++;
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
void graph::printColor(){
	size_t idx =0;
	for(idx;idx<len;idx++){
		std::cout<<vertices[idx]->value<<": "<<vertices[idx]->color<<std::endl;	
	}
}
void graph::printNodeInfo(){
	size_t idx = 0;
	while(idx<filled){
		std::cout<<"value: "<<vertices[idx]->value<<"\tcolor: "<<vertices[idx]->color<<"\tstart: "<<vertices[idx]->d<<"\tfinish: "<<vertices[idx]->f<<std::endl;
		idx++;
	}
}
//Here is where we perform DFS
void graph::search(){
	size_t idx=0;
	for(idx;idx<filled;idx++){
		if(vertices[idx]->color == 0){	
			this->printNodeInfo();
			searchAid(idx,vertices[idx], &timestamp, vertices); 
			//this->printColor();
		}
	
	}
}

