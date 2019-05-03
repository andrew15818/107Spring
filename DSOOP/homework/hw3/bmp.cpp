#include<iostream>
#include"exception.h"
#include"bmp.h"
/*open specified file and assign header values*/
BMPFile::BMPFile(std::string filename){
	 is.open(filename, std::ios::binary);
	 if(!is.is_open()){throw fileOpen{};}
	 is.read((char*)buffer, 54);
	 bmpheader.signature = *(unsigned short int* )(buffer);
	 bmpheader.fileSize = *(unsigned int*)(buffer+2);
	 bmpheader.size = *(unsigned int*)(buffer+14);
	 bmpheader.xPixels = *(unsigned int*)(buffer+18);
	 bmpheader.yPixels = *(unsigned int*)(buffer+22);
	 bmpheader.planes= *(unsigned short int* )(buffer+26);
	 bmpheader.bitCount = *(unsigned short int*)(buffer+28);
	 bmpheader.compression =*(unsigned int *)(buffer+30);	
	 bmpheader.imageSize =*(unsigned int*)(buffer+34);
	 bmpheader.colorsUsed =*(unsigned int *)(buffer+46);
	 //std::cout<<bmpheader.colorsUsed<<std::endl;
	 //std::cout<<bmpheader.xPixels<<"x"<<bmpheader.yPixels<<"xl"<<bmpheader.planes<<std::endl;
}
