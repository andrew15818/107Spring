#include<iostream>
#include<cstdio>
using namespace std;
void swap(int *m , int * n){
	int temp= *m;
	*m = *n;
	*n = temp;	
}
long int max(long int n1, long int n2){
	if(n1>=n2){
		return n1;	
	}
	return n2;
}
void burgers(int m, int n, int t){
	int times[t+1];//each element is how many burgers in i minutes
	for(int puta=0; puta<=t;puta++){times[puta]=0;} //school system doesn't allow this type of initialization :(
	if(m>t && n>t){
		printf("%d %d\n",0,t);	
		return;
	}
	if(m<=t){times[m] = 1;}
	if(n<=t){times[n] = 1;} /*minimum number of burgers they can eat before we start (by eating just one burger)*/
	for(int i=m;i<=t;i++){
		if(times[i]){
			if(i+m<=t){times[i+m] = max(times[i+m], times[i]+1);}
			if(i+n<=t){times[i+n] = max(times[i+n], times[i]+1);}
		}
	}

	/*print the maximum burgers and beer time*/
	if(times[t]!=0){
		printf("%d\n", times[t]);	
	}
	else if(times[t]==0){
		int diff=t;
		while(1){
			if(times[diff]!=0 && diff!=0){
				printf("%d %d\n", times[diff], t-diff);	
				break;
			}
			diff--;	
		}	
		//printf("%d %d\n", times[diff], t-diff);
	}
	/*else{
		for(int diff = t; diff>=0; diff--){
			if(diff%m==0){
				printf("%d %d\n",times[diff], t-diff);	
				break;
			}	
			if(diff%n==0){
				printf("%d %d\n", times[diff], t-diff);	
				break;
			}
		}
	}
	*/
}

int main(){
	int m,n,t; //time to eat 1 krusty burger, 1 apu burga, t is total time
	
	while(cin>>m>>n>>t){
		
		if(m>n){swap(&m, &n);}		
		burgers(m,n,t);
		
	}
	return 0;
}
