//UVA 10405 jolly jumpers
#include<iostream>
#include<cstdio>
#include<cmath>
using namespace std;
int main(){
	int number;
	while(cin>>number){
		int input[number];
		bool jolly[number];	
		for(int b=0; b<number;b++){
			jolly[b] =false;	
		}
		for(int i=0; i<number;i++){
			cin>>input[i];	

		}
		
		for(int j =1 ; j<number;j++){
			int diff = abs((double)(input[j] - input[j-1]));
			jolly[diff]=true;
		}
		bool stillJolly = true;
		for(int a=1;a<number;a++){
			if(!jolly[a]){
				printf("Not jolly\n");	
				stillJolly = false;
				break;
			}	
		}
		if(stillJolly){
			printf("Jolly\n");	
		}
	}
}
