#include<iostream>
using namespace std;
int main(){
	int rows, columns, entrance;
	while(cin>>rows>>columns>>entrance){
		if(rows==0 && columns==0){return 0;}	
		int  grid[rows][columns];;
		char input[rows][columns];
		for(int i=0;i<rows;i++){
			for(int j=0;j<columns;j++){	
				cin>>input[i][j];
				grid[i][j]=0;
			}
		}

		/*for(int a=0;a<rows;a++){
			for(int b=0;b<columns;b++){
				cout<<input[a][b];
				if(b==columns-1){cout<<endl;}
			}	
		}*/
		int loopcounter=0, steps=0;		
		int posR=0,posC=entrance-1; 
		bool exit=false, loopexit=false;
		while(!exit && !loopexit){
			char location =input[posR][posC];
			//cout<<"curently at point ("<<posR<<","<<posC<<")";
			//cout<<"\t current locaton value: "<<location;
			//cout<<"\t visited this location "<<grid[posR][posC]<<" times"<<endl;
			/*if(grid[posR][posC]==2){
					loopexit=true;		
					break;
			}*/
			switch(location){
				case 'N':
					posR-=1;
					break;
				case 'S':
					posR+=1;
					break;
				case 'E':
					posC+=1;
					break;
				case 'W':
					posC-=1;
					break;
			}
			grid[0][entrance]=1;
			if(posR<0||posR>rows ||posC<0||posC>columns ||!input[posR][posC]){
				//cout<<"exiting the arrays bounds"<<endl;
				exit=true;	
				break;
			}
			//cout<<"moving to "<<input[posR][posC]<<endl;
			if(grid[posR][posC]==1){
				loopcounter++;	
			}
			if(grid[posR][posC]==2){
				//cout<<"we have found a loop"<<endl;
				loopexit=true;
				break;
			}
			grid[posR][posC]++;
			steps++;
		}
		if(exit){
			printf("%d step(s) to exit\n", steps);	
		}
		else if(loopexit){
			printf("%d step(s) before a loop of %d step(s)\n",steps-2*loopcounter, loopcounter);	
		}
	}
	return 0;
}
