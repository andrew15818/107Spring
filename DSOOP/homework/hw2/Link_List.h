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
		return !(*this == right); }

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
/* 
 * For a linked list, the heaad pointer is at the left in your drawing, therefore head->pre should be null, same as 
 * tail->next
 */
//set the initial pointers to Null, value is undefinded for
//default constructor
template<typename T>
Link_List<T>::Link_List(){
	//Int_Node<T> *data = new Int_Node<T>;	
	head = tail = nullptr;
	//data->pre=data->next=nullptr;
	//head=tail=data;
	size=0;
}
template<typename T >
//termina de corregir despues
//for the first node in the list, the head is that,
//then the tail equals any subsequent members of the list
Link_List<T>::Link_List(const Link_List<T>& ll){
	Int_Node<T> *tmp  = new Int_Node<T>; 		/*node object we will use for traversing the list*/
	tmp = ll.head;
	head=tail=nullptr;
	size =0;
	while(tmp !=  nullptr){	
		Int_Node<T> *data= new Int_Node<T>;
		data->value  = tmp->value;
		if(size==0){
			data->pre =data->next = nullptr;	/*creating first node, setting equal to head, tail */
			head = tail = data;
		}
		else{
			data->pre   = tail; 				/*adding a new node, shifting accordingly*/
			data->next  = nullptr;
			tail->next = data;
			tail = data;	
		}
		tmp=tmp->next;
		size++;
	}	
	cout<<"size after copying "<<size<<endl;
	delete tmp;
}
template<typename T>
Link_List<T>::~Link_List(){	
}

//insert value at the end of the list
//If so, we add a node at the end  and move the tail back
template<typename U>
istream& operator>>(istream& is, Link_List<U>& ll){
	Int_Node<U> *data= new Int_Node<U>; 
	/*If there are no nodes, create a new one with value*/
	if( ll.head	== nullptr && ll.tail == nullptr && ll.size ==0){
		is>>data->value;
		data->pre=data->next = nullptr;
		ll.head = ll.tail =data;
		ll.size++;
		//cout<<"first element in list is "<<ll.head->value<<endl;
		return is;
	}
		is>>data->value;
		//cout<<"next element is "<<data->value<<endl;
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
	while(tmp!=nullptr){
		os<<tmp->value<<" ";
		tmp=tmp->next;	
	}
	delete tmp;
	return os;
}
#endif // LINK_LIST
