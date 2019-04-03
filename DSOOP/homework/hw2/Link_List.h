#ifndef LINK_LIST
#define LINK_LIST

#include <iostream>
using namespace std;

template <typename T>
struct Int_Node
{
	T value;
	Int_Node<T> *pre, *next;
};

template <typename T>
class Link_List
{
	template <typename U>
	friend ostream &operator<<(ostream &, const Link_List<U> &);  	// print all integers in the list
	template <typename U>
	friend istream &operator>>(istream &, Link_List<U> &);			// input a value at the back of the list, like insert_node(val);

public:
	Link_List();										// default constructor
	Link_List(const Link_List &);						// copy constructor
	~Link_List();
	int getSize() const;
	
	const Link_List &operator=(const Link_List &);		// assignment operator
	bool operator==(const Link_List &) const;			// equality operator
	bool operator!=(const Link_List &right) const		// inequality operator
	{
		return !(*this == right);
	}

	T &operator[](int index);							// subscript operator for non-const objects
	T operator[](int index) const;						// subscript operator for const objects

	bool insert_node(T value);							// insert an integer at the back of link list
	bool delete_node();									// delete the last node
	bool insert_node(int index, T value);				// insert an integer after the i_th position
	bool delete_node(int index);						// delete the i_th node

private:
	int size;
	Int_Node<T> *head, *tail;								// pointer to the first and the last element of Link_List
};
//set the initial pointers to Null, value is undefinded for
//default constructor
//maybe this is why the << doesn't print correctly ?
template<typename T>
Link_List<T>::Link_List(){
	Int_Node<T> *data = new Int_Node<T>;
	
	//data->value = NULL;
	data->pre=data->next=nullptr;
	head=tail=data;
	size=1;
}
template<typename T >
//termina de corregir despues
//for the first node in the list, the head is that,
//then the tail equals any subsequent members of the list
Link_List<T>::Link_List(const Link_List<T>& ll){
	while(ll.data !=  nullptr){
		Int_Node<T> *data= new Int_Node<T>;
		data->value = ll.data.value;
		data->pre= ll.data->prev;
		data->next = ll.data->next;
	}	
	size =ll.size;
}
template<typename T>
Link_List<T>::~Link_List(){	
}

//insert value at the end of the list
//If so, we add a node at the end  and move the tail back
template<typename U>
istream& operator>>(istream& is, Link_List<U>& ll){
	Int_Node<U> *data= new Int_Node<U>; 
	is>>data->value;
	data->pre = ll.tail;
	data->next = nullptr;
	ll.tail->next = data;
	ll.tail = data;
	
	ll.size++;
	return is;
}
template<typename U>
ostream& operator<<(ostream& os, const Link_List<U>& ll){
	Int_Node<U> *tmp = new Int_Node<U>;
	tmp = ll.head;
	//cout<<"list currently has "<<ll.size<<endl;
	//cout<<"current head and tail are: "<<endl;
	cout<<"tail: "<<tmp->value<<endl; 

	while(tmp!=nullptr){
		os<<tmp->value;
		tmp=tmp->next;	
	}
	return os;
}
#endif // LINK_LIST
