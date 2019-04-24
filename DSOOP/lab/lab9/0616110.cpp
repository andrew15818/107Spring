#include<iostream>
#include<cmath>
#include<vector>
#define MAX_SIZE 32650
using namespace std;
void gen_primes(bool *result){
	for(int i=2;i<=MAX_SIZE;i++){
		if(!result[i]){

			for(int k=i*i;k<=MAX_SIZE;k+=i){
				result[k]=true;	
			}
		}
			
	}
}
long int get_prime(long int index, bool *result){
	long int count=2, seen=0;
	while(seen<index && count<MAX_SIZE){
		if(!result[count]){
			seen++;	
			if(seen == index ){
				return count; 
			}		

		}
		count++;
	}	
}
void kill(int index, bool *people){
	/*
	int curr_alive=0;
	int count=0;
	while(1){
		if(!)
		count++;
	}
	*/
}
int main(){
	bool result[MAX_SIZE] ={false};
	gen_primes(result);
	int n;
	while(cin>>n){
		
		if(n==0){return 0;}	
		vector<int > people;

		for(int a=1;a<=n;a++){
			people.push_back(a);

		}
		
		int curr_prime=1, current=0, size =n;
		while(size>1){
			int dead = ((current+ get_prime(curr_prime,result) -1)%size);
			people.erase(people.begin()+dead);
				/*for(vector<int>::iterator test = people.begin();test!=people.end();++test){
					cout<<*test<<" ";	
				}*/

			size--;
			current=dead;
			if(current ==size){current=0;}
			curr_prime++;
		}
		cout<<people[0]<<endl;
		}
	return 0;
}
