#include<iostream>
#include<cstdio>
using namespace std;
void sum(int*  n1 , int *n2, const int digits );
int main(){
	int a=0;
	long int tests;
	cin>>tests;

	while(a<tests){

		string holis;
		long int digits;
		getline(cin, holis);	//getting rid of empty line b/w digits and actual numbers
		cin>>digits;

		int n1[digits], n2[digits];
		for(int i=0;i<digits;i++){
			cin>>n1[i]>>n2[i];	
		}
		if(a>=1){cout<<endl;}
		sum(n1, n2, digits);	//passing function by pointer to first element 
		a++;
	}
	return 0;
}
void sum(int *n1, int *n2, const int digits){ 
	int result[digits], carry_result[digits+1];
	int carry =0;
	bool overflow=false; //if there is overflow in the last digit to be added
	for(int i=digits-1; i>=0;i--){
		int small_sum=0; // if >=10, will hold the ones position, the tens will be the carry;
		//cout<<"carry value "<<carry<<endl;
		//cout<<small_sum<<endl;

		small_sum = n1[i] + n2[i] + carry;
		carry=0;
		if( small_sum>=10){
			if(i==0){		
				for(int a=digits; a>=1; a--){
					carry_result[a] = result[a-1];

				}
				carry_result[0] = small_sum/10;
				overflow = true;
				break;
			}
			carry = small_sum/10;
			small_sum = small_sum%10;	
		}

		result[i]= small_sum;
		//cout<<"currently adding "<<n1[i]<<"+"<<n2[i]<<"+"<<carry<<" getting result "<<result[i]<<endl;
	}

	if(overflow){
		for(int b=0; b<digits+1; b++){
			printf("%d", carry_result[b]);	
		}
		printf("\n");
	}
	else if(!overflow){
		for(int c=0; c<digits;c++){
			printf("%d", result[c]);	
		}	
		printf("\n");
	}

}

