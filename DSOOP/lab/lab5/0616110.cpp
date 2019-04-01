#include<iostream>
#include<cstdio>
#include<cmath>
#define MAX_SIZE 10000
using namespace std;
void print( int arr[], int size){
	for(int test = 0; test<size;test++){
		cout<<arr[test]<<" ";	
	}
	cout<<endl;
}
int main(){
	unsigned int currvalue, testo =3;
	int arr[MAX_SIZE], size=0; 
	while(cin>>currvalue){
		arr[size]=currvalue;
		size++;		
		for(int i=0;i<size;i++){
			int key  = arr[i];
			int j=i-1;
			while(j>=0 && arr[j]>key){
				arr[j+1]=arr[j];		
				j-=1;
			}	
			arr[j+1]=key;
		}
		//print(arr,size);
		//cout<<"above array has "<<size<< " elements"<<endl;
		if(size%2==0){
			unsigned int final = (arr[size/2-1]+arr[size/2])/2;
			printf("%d\n", final);
		}	
		else if(size%2!=0){
			printf("%d\n", arr[size/2]);		
		}
		
	}

return 0;
}
