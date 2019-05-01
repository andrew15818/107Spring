#ifndef EXCEPT_H
#define EXCEPT_H
#include<stdexcept>
/*If there are too few command line arguments, throw error*/
class argCountException:public std::runtime_error{
	public:
		argCountException(): 
			std::runtime_error{"Wrong amount of command line args:program_name [input_file][output_file][mult_factor]"}{};
};
#endif