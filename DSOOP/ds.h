#ifndef DS_H
#define DS_H
#include<iostream>
template<typename T>
class stack{
	private:
		int tail, size;
		T* arr;
	public:
		stack(int size);
		~stack(){delete [];}
		bool push(T);
		bool pop();
		void print();
};
template<typename T>
stack<T>::stack(int size){
	arr = new T[size];
	this->size=size;
	tail =0;
}
template<typename T>
bool stack<T>::push(T value){
	if(tail!=size){
		tail++;
		arr[tail] = value;	
		return true;
	}
	return false;
}
template<typename T>
bool stack<T>::pop(){
	if(tail>0){
		tail--;
		return true;
	}	
	return false;
}
template<typename T>
void stack<T>::print(){
	for(int i=0;i<=tail;i++){
			std::cout<<arr[i]<<" ";
	}
}
#endif
