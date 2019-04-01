//Accepted in UVA but not the school's system for timelimit
#include<iostream>
#include<cstdio>
#include<cstdlib>
using namespace std;
int cycle(const int&,const int&); 
int main(){
	int n1, n2, lowest, highest;
	while(cin>>n1>>n2){
		lowest=n1;
		highest=n2;
		if(n1>n2){
			int temp = n1;
			n1=n2;
			n2=temp;
		}		
		printf("%d %d %d\n", lowest, highest,cycle(n1,n2));	
	}	
	return 0;
}
int cycle(const int& n1, const int& n2){
	long int greatest=1;
	for(int i=n1;i<=n2;i++){
		int scrap=i, length=1;
		while(scrap!=1){
			if(scrap%2==0){
				scrap/=2;	
			}
			else{
				scrap=(scrap*3)+1;	
			}
			length++;
		}
		if(length>greatest){greatest=length;}
	}
	return greatest;
}
