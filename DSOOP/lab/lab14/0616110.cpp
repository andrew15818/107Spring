#include<iostream>
#include<vector>
#include<math.h>
#include<algorithm>
#define MAX_SIZE 2703664
using namespace std;
void sieve(bool *arr,int hola){
	int count=0;
	for(int i=2;i<=hola;i++){
			
		if(arr[i]==true){
			count++;
			//cout<<i<<" is prime"<<endl;
			for(int j=i*2; j<=hola;j+=i){
				arr[j]=false;	
				//if(j==(i*i)){cout<<"setting "<<j<<" to false"<<endl;}
			}	
			
		}		
	}	
	//return count;
}

void set_primes(bool *arr, vector<int> &primes/*int*primes*/,int hola){
	int count=0;
	for(int i=2;i<=hola;i++){
		if(arr[i]==true){
			//cout<<"adding "<<i<<" to prime array"<<endl;	
			//primes[count]=i;
			primes.push_back(i);
			count++;
		}
	}
}
/*
int prime_factorization(int *factorials, int input, vector<int >&primes){
	if(find(primes.begin(), begin.end(), input) != primes.end()){
		return 2;	
	}
	count=0;
//add array lookup and set values

	if(factorials[input]!=0){return factorials[input];}
	for(int i=2;i<input;i++ ){
		if(input%i==0){
			count+=prime_factorization(factorials,i,primes);	
			count+=prime_factorization(factorials,input/i,primes);
		}	
	}	
	factorials[input]=count;
	return count;
}
*/
void prime_factorization(int *factorials){

	
	int k;	
	//factorials[0]=factorials[1]=1;
	for(int i=2;i<MAX_SIZE;i++){
			if(factorials[i]==0){factorials[i]=1;}
		for(int j=2;(k=i*j)<MAX_SIZE &&j<=i;j++){
			factorials[k] = factorials[i]+factorials[j];	
		}	

	}
	for(int add=1; add <MAX_SIZE; add++){
		factorials[add]+=factorials[ add -1];	
	}
}
int search_value(int *factorials, int value){
	if(value==0){return 0;}
	for(int a=2;a<MAX_SIZE;a++){
		if(factorials[a]==value){
			return a;	
		}	
	}
	return -1;
}
int factorials[MAX_SIZE];
int main(){
	int input,count=1;
	prime_factorization(factorials);
	while(cin>>input){
		if(input<0){break;}	
		int result = search_value(factorials,input);
		if(result==-1){
			cout<<"Case "<<count<<": Not possible."<<endl;	
		}
		else{
			cout<<"Case "<<count<<": "<<result<<"!"<<endl;	
		}
				
		count++;	
	}
	return 0;
}
