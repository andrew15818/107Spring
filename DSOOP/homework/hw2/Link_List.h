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
/*Initial constructor only creates head,tail ptrs, sets size to zero, values
 * and other nodes are created elsewhere as needed.*/
template<typename T>
Link_List<T>::Link_List(){
	head = tail = nullptr;
	size=0;
}
/*set a tmp node equal to the header and set the corresponding node in the list
 * with the same value*/
template<typename T>
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
	//cout<<"size after copying "<<size<<endl;
	delete tmp;
}
/*destructor deletes every node*/
template<typename T>
Link_List<T>::~Link_List(){	
	Int_Node<T> *tmp = new Int_Node<T>;
	tmp = head;
	while(tmp!= NULL){
		delete tmp;
		tmp = tmp->next;	
		size--;
	}
}
template<typename T>
int Link_List<T>::getSize() const {
	return size;
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
		return is;
	}
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
	Int_Node<U> *tmp = ll.head;
	while(tmp!=nullptr){
		os<<tmp->value<<" ";
		tmp=tmp->next;	
	}
	return os;
}
/*I imagine this is similar to the copy constructor?*/
template<typename T>
const Link_List<T>& Link_List<T>::operator=(const Link_List& ll){
	Int_Node<T> *tmp=ll.head;			
	while(tmp!=NULL){
		Int_Node<T> *data;
		if(size==0){
			data->value = tmp->value;
			data->next=data->prev = nullptr;	
			head = tail =data;
			continue;
		}
		data->value = tmp->value;	
		data->prev = tail;
		data->next = nullptr;
		tail = data;
		tmp= tmp->next;	
	}
	delete tmp;
	return *this;
}
/*If the values in a list don't appear in the same order, return  false*/
template<typename T>
bool Link_List<T>::operator==(const Link_List<T>& ll)const{
	Int_Node<T> *tmp =ll.head;
	Int_Node<T> *current =  this->head;
	while(tmp=NULL){
		if(tmp->value != current->value){
			return false;	
		}	
		tmp = tmp->next;
		current = current->next;
	}

	return true;
}
/*To return the value at the index, we have to traverse the entire list up
 * to that point*/
template<typename T>
T& Link_List<T>::operator[](int index){
	Int_Node<T> *tmp = head;;
	int i=0;
	while(tmp!=NULL){
		if(i==index){
			return tmp->value;
		}
		tmp=tmp->next;
		i++;
	}
	return head->value;/*return the first value if loop fails*/
}
template<typename T>
T Link_List<T>::operator[](int index)const{
	Int_Node<T> *tmp = head; 
	int i=0;
	while(tmp!=NULL){
		if(i==index){
			return tmp->value;	
		}	
		i++;
		tmp=tmp->next;
	}
	return tmp->value;
}
template<typename T>
bool Link_List<T>::insert_node(T value){
	Int_Node<T> *data = new Int_Node<T>;

	data->value  = value;

	if(size ==0){
		head = data;			/*If the list is empty, create a new first node with value*/
		data->pre=nullptr;	

	}
	else{	
		data->pre = tail;
		tail->next= data;
	}
	tail=data;
	data->next=nullptr;
	size++;
	return true;
}

/*delete the last node of the list*/
template<typename T>
bool Link_List<T>::delete_node(){
	if(size==0){
		return false;	
	}	
	Int_Node<T> *tmp = tail;
	tail->pre->next = nullptr;
	tail = tail->pre;

	delete tmp;
	return true;
}
template<typename T>
bool Link_List<T>::insert_node(int index, T value){
	Int_Node<T> *data=new Int_Node<T>;
	Int_Node<T> *current = head;
	data->value = value;
	int i=0;
	if(index>=size || size==0){ 						/*We account for these two cases in the one-argument insert_node*/
			bool result = this->insert_node(value); 	/*return status of insertion operation */
			return result;
	} 	
	while(i<=index){
		if(i==index){
			data->pre = current;
			data->next = current->next;
			current->next = data;		
			size++;
		}
		current=current->next;
		i++;	
	}			
	return true;
}
template<typename T>
bool Link_List<T>::delete_node(int index){
 	if(index >= size){
		bool result = this->delete_node();				/*Already accounted for this case*/
		return result;
	};	
	Int_Node<T> *current = head;							/*Node used for traversing the list */
	int i=0;
	while(i<=index){
		if(i==index){
		
			current->pre->next = current->next;	
			current ->next->pre= current->pre;
			delete current;
			return true;
		}
		i++;
		current= current->next;	
	}
	return true;
}

#endif // LINK_LIST
