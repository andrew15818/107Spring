#include<iostream>
#include<cstdio>
using namespace std;
long long int happy(long long int num){
	long long int square =0;		
	while(num>0){
		square+=((num%10)*(num%10));	
		num/=10;	
	}
	//printf("Currently sum is: %lld\n",square );
	if(square<10){				
		//printf("returnning %lld\n", square);
		return square;	
	}	
	happy(square);	
}
int main(){
	long long int num, count =1, i=0;

	cin>>num;
	while(i<num){
		long long int current, result;
		cin>>current;	
		result = happy(current);	
		if(result==1){
			printf("Case #%lld: %lld is a Happy number.\n",count, current);	
		}
		else{
			printf("Case #%lld: %lld is an Unhappy number.\n", count, current);	
		}
		count++;
		i++;
	}
	return 0;
}
