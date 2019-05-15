#include<iostream>
#include"ds.h"
using namespace std;
int main(){
	stack<int> hola(7);
	for(int i=0;i<5;i++){
		hola.push(i);
	}

	hola.print();
}
