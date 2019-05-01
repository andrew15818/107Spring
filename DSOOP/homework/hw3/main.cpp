#include<iostream>
#include<string>
#include<stdexcept>
#include<fstream>
#include"exception.h"
#include"bmp.h"
//#include<stderror>
using namespace std;
int main(int argc, char *argv[]){
	/* trying to assign values, throws exception if not possible*/
	cout<<sizeof(HeaderInfo)<<endl;
	try{
		if(argc!=4){throw argCountException{};}

		string in_file, out_file;
		double mult_factor;
		in_file = argv[1];
		out_file= argv[2];
		mult_factor = atoi(argv[3]);

	}

	catch(const argCountException &argCount){
			cout<<argCount.what()<<endl;
	}
	return 0;
}
