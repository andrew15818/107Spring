#ifndef GRAPH_H
#define GRAPH_H
#include "cstddef"
#include <fstream>
#include <vector>
struct Vertex{
	//REMEMBER: white=0; gray = 1; black =2
	size_t  value,d,f,color;
	//std::string color;
	//not sure if doing it with
	//vector or linked-list style
	//is better?
//	Vertex *next = NULL;;
	std::vector<Vertex*> adjacency;
		Vertex(size_t value ){
			this->value = value;
			color = 0;
		}
};
//The main strategy for topological sort is to perform
//DFS and as a vertex is finished, insert it into a list
class graph{
	private:
		size_t len,filled,timestamp;
		Vertex **vertices;
		std::vector<const Vertex*>topological;
	public:
	//TODO: add destructor for garbage collection w/ dynamic memmory
	/*To help in the DFS main function*/
	friend void searchAid(const size_t& key,  Vertex* v, size_t * timestamp, std::vector<Vertex*>&topological);


	graph(size_t nodes);
	~graph();
	void newNode(const size_t& key);	
	Vertex* getVertex(const size_t& idx);
	void addOrder(const size_t& primary, const size_t secondary);
	
	//just to see if everything is a-okay
	void print();
	void printColor();
	void printNodeInfo();
	void printTopologicalOrder(std::ofstream& output);
	void printTopologicalOrderToStdOut();
	void search();

};
#endif
