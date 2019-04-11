#include<iostream>
#include<cstdio>
using namespace std;
//int hartals(party*, int, int);
int main(){
	unsigned int cases, i=0;
	cin>>cases;
	//printf("\n");
	while(i<cases){
		int days, parties;			/*total numbers of days counted*/
		cin>>days>>parties;
		//printf("tracking over %d days\n", days);
	//	party num[parties];
		bool strike[days]= {false};
		int hola=0;
		for(int a=0;a<parties;a++){
			cin>>hola;	
			for(int j= hola;j<=days;j+=hola){
					strike[j]=true;
				/*if(j%7!=6 && j%7!=0){
					strike[j]=true;	
					continue;
				}	
				else if(j<7 && j%6!=0 && j%7==0){
					strike[j]=true;	
				}*/
			}
		}

		int result =0;
		for(int h=0; h<days;h++){
			if(strike[h] && h%7!=0 and h%7!=6){
				result++;	
			}
		}

		printf("%d\n", result);
		/*
		for(int a=0;a<parties;a++){
			printf("%d\n", num[a].hartals);	
		}*/
		i++;	
	}
	return 0;
}
/*
int hartals(party* num,int days, int parties ){
		bool hartalitos[days]=false};
		for(int i =0; i < parties; i++){
				num[i].curr_day = num[i].hartals;	
				for(num[i].curr_day = num[i].hartals; num[i].curr_day<=days; num[i].curr_day+=num[i].hartals){
					if(  num[i].curr_day%7!=6 && num[i].curr_day%7 != 0){
							hartalitos[num[i].curr_day] =true;	
					}	
					//num[i].curr_day+=num[i].hartals;
				}
				
		}	
		
		int result=0;
		for(int j=0;j<days;j++){
			if(hartalitos[j] == true){
				//printf("There is a cartal on day %d\n", j);
				result++;		
			}	
		}
		return result;
}*/
