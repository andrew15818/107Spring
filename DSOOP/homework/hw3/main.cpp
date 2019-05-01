#include<iostream>
#include<string>
#include<stdexcept>
#include<fstream>
#include<cstdint>
#include"exception.h"
#include"bmp.h"
//#include<stderror>
using namespace std;
int main(int argc, char *argv[]){
	/* trying to assign values, throws exception if not possible*/
	string in_file, out_file; double mult_factor;
	try{
		if(argc!=4){throw argCountException{};}


		in_file = argv[1];
		out_file= argv[2];
		mult_factor = atof(argv[3]);
		
	}
	catch(const argCountException &argCount){
			cout<<argCount.what()<<endl;
	}
	
	//trying to open the respecitve file
	try{
		BMPFile file1(in_file, "read");
		BMPFile file2(out_file, "write");

	}
	catch(const fileOpen& file_exception){
		cout<<file_exception.what()<<endl;
	}	
	return 0;
}
