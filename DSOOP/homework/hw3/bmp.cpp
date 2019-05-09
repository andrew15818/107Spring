#include<iostream>
#include"exception.h"
#include"bmp.h"
/*open specified file and assign header values*/
BMPFile::BMPFile(std::string filename){
	//buffer = new unsigned char[54];//allocating memory for the header
	 is.open(filename, std::ios_base::binary);
	 if(!is.is_open()){throw fileOpen{};}
	 std::cout<<"buffer size: "<<sizeof(buffer)<<std::endl;
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
	std::cout<<sizeof(bmpheader)<<" is the size of header. "<<std::endl; 
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
	
}
/*TODO: Still have to implement overflow detection, presumably with try/catch?
 * As far as I can tell, the colors are being modified by the mult_factor haha*/
void BMPFile::writeToOutFile(std::string out_file, double mult_factor){
	std::ofstream os(out_file, std::ios::binary);
	/*copy header to our new file*/
	long unsigned int length = bmpheader.xPixels * bmpheader.yPixels*3;	
	unsigned char bitmap[length];
		
	//is.seekg(bmpheader.dataOffset,is.beg); apparently this method doesn't work
	is.read((char*)bitmap,bmpheader.imageSize);
	for(int i =0; i<(bmpheader.xPixels*bmpheader.yPixels*3);i+=3){
			std::cout<<"pixel count :"<< i/3<<std:: endl;
			bitmap[i]*=mult_factor;
			bitmap[i+1]*=mult_factor;
			bitmap[i+2]*=mult_factor;
			//std::cout<<(int)bitmap[i]<<" "<<(int)bitmap[i+1]<<" "<<(int)bitmap[i+2]<<std::endl;
			if(bitmap[i]>=255){std::cout<<"ypee"<<std::endl; bitmap[i] =255; }
			else if (bitmap[i+1]>=255){std::cout<<"hola"<<std::endl; bitmap[i+1]=255;}
			else if(bitmap[i+2]>=255){std::cout<<"hurray"<<std::endl;bitmap[i+2]=255;}
	}
	os.write((char*)buffer, sizeof(buffer));	
	os.write((char*)bitmap,bmpheader.imageSize); 
}
