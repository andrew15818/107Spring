#include<iostream>
#include<cmath>
#include<cstdio>
#define max(a,b) ((a>b)? a : b)
#define min(a,b)((a<b)? a : b)
using namespace std;
struct rectangle{
	int x1, y1,x2,y2;
	int area;
};

int main(){
	int tests, count=1, i=0;
	cin>>tests;
	while(i<tests){

		int rectangles, j=0;
		cin>>rectangles;
		rectangle inputs[rectangles];
		while(j<rectangles){
			cin>>inputs[j].x1>>inputs[j].y1>>inputs[j].x2>>inputs[j].y2;
			j++;	
		}
		int flag = 0;
		int leastx=inputs[0].x1, leasty=inputs[0].y1, greatx =inputs[0].x2, greaty=inputs[0].y2;
		for(int a=0; a<rectangles;a++){
			/*if(inputs[a].x1>leastx && inputs[a].x1<greatx){leastx = inputs[a].x1;}	
			if(inputs[a].x2<greatx && inputs[a].x2>leastx){greatx=inputs[a].x2;}
			if(inputs[a].y1>leasty && inputs[a].y1<greaty){greaty= inputs[a].y1;}
			if(inputs[a].y2<greaty && inputs[a].y2>leasty){greaty = inputs[a].y2;}
			*/
			leastx = max(leastx, inputs[a].x1), greatx = min(greatx, inputs[a].x2);
			leasty = max(leasty, inputs[a].y1), greaty = min(greaty, inputs[a].y2);
			if(greatx <= leastx || greaty<= leasty){flag = -1;}
			//else{inputs[a].x1=leastx, inputs[a].y1=leasty, inputs[a].y2 = greaty, inputs[a].x2 = greatx;}
		}
		if(leastx>=greatx || leasty>=greaty){flag = -1;}
		//cout<<"min point ("<<leastx<<","<<leasty<<")"<<endl;
		//cout<<"max point ("<<greatx<<","<<greaty<<")"<<endl;
		printf("Case %d:", count);
		if(flag==0){
			printf(" %d\n", (greatx-leastx)*(greaty-leasty));	
		}
		else if(flag == -1){
			printf(" 0\n");
		}
		i++;	
		count++;
	}
	return 0;
}
