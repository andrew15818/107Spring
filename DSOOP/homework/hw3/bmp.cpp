#include"bmp.h"
#include<iostream>

/*open specified file and assign header values*/
BMPFile::BMPFile(std::string filename){
	int length =54; 
	 unsigned char buffer[54];
	 is.open(filename, std::ios::binary);
	 if(is.is_open()){
		is.seekg(0, is.end);	 
		int length = is.tellg();
		is.seekg(0, is.beg);
	 }
	 std::cout<<length<<" characters"<<std::endl;


	 //is.read( buffer, length); 
	//if(!is.is_open()){throw fileOpen{};}
}
