#ifndef GRAPH_H
#define GRAPH_H
#include "cstddef"
#include <vector>
struct Vertex{
	size_t  value;
	//not sure if doing it with
	//vector or linked-list style
	//is better?
//	Vertex *next = NULL;;
	std::vector<Vertex> adjacency;
		Vertex(size_t value ){
			this->value = value;
		}
};
class graph{
	private:
		size_t len;
		Vertex **vertices;
	public:
	graph(size_t nodes);
	void addNode(const size_t& key,const Vertex&);	
};
#endif
