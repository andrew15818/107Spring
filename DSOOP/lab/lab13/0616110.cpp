#include<iostream>
#include<cstdio>
using namespace std;
int main(){
	string s1,s2;
	while(cin>>s1>>s2){
	int starting=0, count=0;
	for(int i=0; i<s1.length();i++){
		for(int j=starting;j<s2.length(); j++){
			if(s1[i]==s2[j]){
				//cout<<s1[i]<<" and "<<s2[j]<<" are equal\t"<<"and i is "<<i <<"and j is "<<j<<endl;;
				starting=j+1;
				count++;		
				break;
			}	

		}	
	}	
		if(count == s1.length()){
			printf("Yes\n");	
		}
		else{
			printf("No\n");	
		}
	}
	return 0;
}
