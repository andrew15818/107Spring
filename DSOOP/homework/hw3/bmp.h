#ifndef BMP_H
#define BMP_H
//define structures for headers
struct BMPHeader{
	unsigned short int signature; //should be 'BM'
	unsigned int fileSize; 		  //file size in bytes
	unsigned int reserved;		  //unused (for padding to multiple of 4 bytes?)
	unsigned int dataOffset;	  //offset to actual raster data (how far to pixel data begins)
};
struct HeaderInfo{
	unsigned int size;			  //size of the header info (should be 40 bytes)
	unsigned int width;			  //width of the bitmap
	unsigned int height;		  //height of the bitmap
	unsigned short int planes;	  //number of planes
	unsigned short int bitCount;  //number of color bits per pixel
	unsigned int compression;	  //type of compression used
	unsigned int imageSize; 	  //size of the image in bytes after compression
	unsigned int xPixels;		  //horizontal resolution
	unsigned int yPixels;		  //vertical resolution
	unsigned int colorsUsed; 	  //number of colors used
	unsigned int importantColors; //number of important colors (?)
};
#endif
