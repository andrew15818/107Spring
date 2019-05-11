#include<iostream>
#include"exception.h"
#include"bmp.h"
/*open specified file and assign header values*/
BMPFile::BMPFile(std::string filename){
	//buffer = new unsigned char[54];//allocating memory for the header
	 is.open(filename, std::ios_base::binary);
	 if(!is.is_open()){throw fileOpen{};}
	// std::cout<<"buffer size: "<<sizeof(buffer)<<std::endl;
	 is.read((char*)buffer, sizeof(BMPHeader));
	 bmpheader.signature = *(unsigned short int* )(buffer);
	 bmpheader.fileSize = *(unsigned int*)(buffer+2);
	 bmpheader.dataOffset = *(unsigned int*)(buffer+10);
	 bmpheader.size = *(unsigned int*)(buffer+14);
	 bmpheader.xPixels = *(unsigned int*)(buffer+18);
	 bmpheader.yPixels = *(unsigned int*)(buffer+22);
	 bmpheader.planes= *(unsigned short int* )(buffer+26);
	 bmpheader.bitCount = *(unsigned short int*)(buffer+28);
	 bmpheader.compression =*(unsigned int *)(buffer+30);	
	 bmpheader.imageSize =*(unsigned int*)(buffer+34);
	 bmpheader.colorsUsed =*(unsigned int *)(buffer+46);
	/*optionally print header info*/
	 /*
	std::cout<<(char)bmpheader.signature<<std::endl
			<<"File Size: "<<bmpheader.fileSize<<std::endl
			<<"Header Size: "<<bmpheader.size<<std::endl
			<<"Data offset: "<<bmpheader.dataOffset<<std::endl
			<<"xPixels: "<<bmpheader.xPixels<<std::endl
			<<"YPixels: "<<bmpheader.yPixels<<std::endl
			<<"planes: "<<bmpheader.planes<<std::endl
			<<"bitCount: "<<bmpheader.bitCount<<std::endl
			<<"compression: "<<bmpheader.compression<<std::endl
			<<"Image Size: "<<bmpheader.imageSize<<std::endl
			<<"Colors used: "<<bmpheader.colorsUsed<<std::endl;
	*/	
}
/*Create new dest file, copy bitmap contents to it*/
void BMPFile::writeToOutFile(std::string out_file, double mult_factor){
	std::ofstream os(out_file, std::ios::binary);
	/*copy header to our new file*/
	long unsigned int length = bmpheader.xPixels * bmpheader.yPixels*3;	
	unsigned char bitmap[length];
	int currx=0, curry=0;	

	is.read((char*)bitmap,bmpheader.imageSize);
	/*for every bit in the bitmap, assign temp values,
	 * check for overflow this way and throw exception*/
	for(int i =0; i<(bmpheader.xPixels*bmpheader.yPixels*3);i+=3){
			currx =i%bmpheader.yPixels;
			curry= i%bmpheader.xPixels;
			try{
				int hola = (int )bitmap[i]*mult_factor;
				int adios = (int)bitmap[i+1]*mult_factor;
				int que = (int)bitmap[i+2]*mult_factor;
				if(hola >255){hola = 255; throw overflow{};}
				if(adios >255){ adios = 255; throw overflow{};}
				if(adios >255){que=255; throw overflow{};}
				bitmap[i] = (unsigned char)hola;
				bitmap[i+1] = (unsigned char)adios;
				bitmap[i+2] = (unsigned char) que;
			}
			catch(const overflow& of){
				std::cout<<of.what()<<currx<<" "<<curry<<std::endl;
			}
	}
	os.write((char*)buffer, sizeof(buffer));	
	os.write((char*)bitmap,bmpheader.imageSize); 
}
