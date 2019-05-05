#include<iostream>
#include"exception.h"
#include"bmp.h"
/*open specified file and assign header values*/
BMPFile::BMPFile(std::string filename){
	//buffer = new unsigned char[54];//allocating memory for the header
	 is.open(filename, std::ios_base::binary);
	 if(!is.is_open()){throw fileOpen{};}
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
	 
	std::cout<<bmpheader.signature<<std::endl
			<<bmpheader.fileSize<<std::endl
			<<bmpheader.size<<std::endl
			<<bmpheader.dataOffset<<std::endl
			<<bmpheader.xPixels<<std::endl
			<<bmpheader.yPixels<<std::endl
			<<bmpheader.planes<<std::endl
			<<bmpheader.bitCount<<std::endl
			<<bmpheader.compression<<std::endl
			<<bmpheader.imageSize<<"is the imatge size"<<std::endl
			<<bmpheader.colorsUsed<<std::endl;
	
}
/*create an out file with same header values and bit values multiplied by mult_factor*/
//TODO: figure out why the image is slanted when trying to copy for debug
//maybe some sort of index error
//colors are now ok ,was reading from wrong offset
void BMPFile::writeToOutFile(std::string out_file, double mult_factor){
	std::ofstream os(out_file, std::ios::binary);
	/*copy header to our new file*/
	long unsigned int length = bmpheader.xPixels * bmpheader.yPixels*3;	
	unsigned char bitmap[length+1];

	is.seekg(bmpheader.dataOffset,is.beg);
	is.read((char*)bitmap,bmpheader.imageSize);
	os.write((char*)buffer, sizeof(buffer));	
	os.write((char*)bitmap,length); 
}
