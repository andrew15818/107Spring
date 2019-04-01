//insertion sort
#include<iostream>
using namespace std;
int main(){
	int arr[6]={1,3,34,54,2,4};
	for(int j=0;j<6;j++){
		int key = arr[j], i=j-1;
		while(i>0 && arr[i]>key){
			arr[i+1]= arr[i];
			arr[i]=key;
			i--;
		}
	}	
	for(int a=0; a<6;a++){
		cout<<arr[a]<<" ";
	}
	cout<<endl;
	return 0;
}
/*
What this algorithm does is it goes backwards from the current 
arr element and stops at the place where it is no longer smaller
than the corresponding array element.

It takes the key value, or the current value we are testing and 
goes back through the array until the previous element is no 
longer bigger than the key or we have reached the end of the arr.
*/
