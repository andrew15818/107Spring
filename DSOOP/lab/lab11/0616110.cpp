//didn't actually write file in lab, had to use
//lab's computers
//close, but no cigar
#include<iostream>
#include<cstdio>
using namespace std;
void winner(int *num, int size, int count);
void print(int *num, int size);
int main(){
	int cases, i=0, count=1;
	cin>>cases;
	while(i<cases){
		string hola;
		int num[1000]={0};
		cin>>hola;
			for(int j=0; j<hola.size(); j++){
				num[j] = (int)hola[j]-48;

			}
			winner(num, hola.size(), count);
		count++;
		i++;
	}
}
void winner(int *num, int size, int count){
		int left = size, turn=0;
		for(int j=0; j< size; j++){
				//if(left ==1){break;}
				if(num[j]!=0){}{
					int sum=0;
					for(int i=0; i<size;i++){
						if(num[i]!=0 && i!=j){
							sum+=num[i];
						}	
						else{continue;}
					}
					if(sum%3==0){
						num[j]=0;
						if(left==1){break;}	
						left--;
						turn++;
					}
				}
				//print(num, size);
			}
		if(turn%2==0){
			cout<<"Case "<<count<<": T"<<endl;	
		}
		else if (turn%2!=0){
			cout<<"Case "<<count<<": S"<<endl;	
		}
}
void print(int *num, int size){
	cout<<"current matrix value: ";
	for(int a=0; a<size;a++){
		cout<<num[a]<<" ";
	}
	cout<<endl;
}
