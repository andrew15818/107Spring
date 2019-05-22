#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
int main(){
	long int cases;
	while(cin>>cases){
		if(cases==0){break;}	
		long int arr[cases], largest=0;
		long long int sum=0;
		for(int i =0; i<cases; i++){
			cin>>arr[i];	
		}
		bool found=false;
		/*We first calculate all the sums and then if it is larger than our
		 * current largest, we check to see if it is in the array.*/
		sort(arr,arr+cases);
	//for(long int h = cases-1;h>=0;h--){
		for(long int a=0;a<cases; a++){
			for(long int b =a+1; b<cases; b++){
				for(long int c =b+1; c<cases; c++){				
					sum = arr[a] +arr[b]+arr[c];
					if(sum > largest){ 
						for(long int d =0; d< cases;d++){
								if(arr[d]==sum){
								largest = arr[d];	
								found = true;
								break;
							}	
						}
					}	
					
				}
			}
		//}
		
		}
		if(found == true ){printf("%ld\n",largest);}
		else if(found == false){printf("no solution\n");}
	}
	return 0;
}
