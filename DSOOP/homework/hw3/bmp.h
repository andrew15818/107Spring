#ifndef BMP_H
#define BMP_H
//define structures for headers
/*So, we could only the output file until we directly write to it to simplify befinnign code*/
//TODO:figure out how to properly take in and assign the header fields from input file.
struct BMPHeader{
	uint16_t signature; //should be 'BM'
	uint32_t fileSize; 		  //file size in bytes
	uint32_t reserved;		  //unused (for padding to multiple of 4 bytes?)
	uint32_t  dataOffset;	  //offset to actual raster data (how far to pixel data begins)
	uint32_t size;			  //size of the header info (should be 40 bytes)
	uint32_t width;			  //width of the bitmap
	uint32_t height;		  //height of the bitmap
	uint16_t planes;	  	  //number of planes
	uint16_t bitCount;  	  //number of color bits per pixel
	uint32_t compression;	  //type of compression used
	uint32_t imageSize; 	  //size of the image in bytes after compression
	uint32_t xPixels;		  //horizontal resolution
	uint32_t yPixels;		  //vertical resolution
	uint32_t colorsUsed; 	  //number of colors used
	uint32_t importantColors; //number of important colors (?)
};
/*declare file and read it in its own class*/
class BMPFile{
	//handle file opening directly in class functions
	private:	
		BMPHeader bmpheader;	
		std::string file_name, type; //specify if we are to read or write to file
		std::ifstream is;
		std::ofstream os;
		double mult_factor;
		void setHeaders();
	public:
		BMPFile(std::string file_name, std::string type);
		~BMPFile();
		void open(); 			  //open the input file for reading/writing
		void read();			  //assign values to headers and read file contents
		void writeToOutFile(const BMPFile&, double mult_factor); // pass each byte* mult_factor into out file	
};
#endif
