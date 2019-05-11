/*Should be run using c++11*/
#include<iostream>
#include<string>
#include<stdexcept>
#include<fstream>
#include<cstdint>
#include<cctype>
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
		BMPFile hola(in_file);
	try{
	
	}
	catch(const fileOpen& file_exception){
		cout<<file_exception.what()<<endl;
	}	
	hola.writeToOutFile(out_file, mult_factor);
	return 0;
}
