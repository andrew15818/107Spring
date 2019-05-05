#ifndef BMP_H
#define BMP_H
#include<iostream>
#include<fstream>
/*So, we could only the output file until we directly write to it to simplify befinnign code*/
//TODO:figure out how to properly take in and assign the header fields from input file.
//Maybe we could parse the relevant header values in the constructor for the file.
struct BMPHeader{
	unsigned short int  signature; //should be 'BM'
	unsigned int fileSize; 		  //file size in bytes
	unsigned int  reserved;		  //unused (for padding to multiple of 4 bytes?)
	unsigned int  dataOffset;	  //offset to actual raster data (how far to pixel data begins)
	unsigned int size;			  //size of the header info (should be 40 bytes)
	unsigned int width;			  //width of the bitmap
	unsigned int height;		  //height of the bitmap
	unsigned short int planes;	  	  //number of planes
	unsigned short int bitCount;  	  //number of color bits per pixel
	unsigned int compression;	  //type of compression used
	unsigned int imageSize; 	  //size of the image in bytes after compression
	unsigned int xPixels;		  //horizontal resolution
	unsigned int yPixels;		  //vertical resolution
	unsigned int colorsUsed; 	  //number of colors used
	unsigned int importantColors; //number of important colors (?)
};
/*declare file and read it in its own class*/
class BMPFile{
	//handle file opening directly in class functions
	private:	
		BMPHeader bmpheader;	
		std::string file_name, type; //specify if we are to read or write to file
		std::ifstream is;
		unsigned char buffer[54]; 	//going to receive our header values, then we will read from it
		//unsigned char bitmap[];
	public:
		BMPFile(std::string file_name);
		//~BMPFile();
		void open(); 			  //open the input file for reading/writing, assign values to header
		void writeToOutFile(std::string out_file , double mult_factor); // pass each byte* mult_factor into out file	
};
#endif
