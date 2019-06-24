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
	std::vector<Vertex*> adjacency;
		Vertex(size_t value ){
			this->value = value;
		}
};
class graph{
	private:
		size_t len,filled;
		Vertex **vertices;
	public:
	//TODO: add destructor for garbage collection w/ dynamic memmory
	graph(size_t nodes);
	void newNode(const size_t& key);	
	void addOrder(const size_t& primary, const size_t secondary);
	//just to see if everything is a-okay
	void print();
};
#endif
