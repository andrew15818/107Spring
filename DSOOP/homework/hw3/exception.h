#ifndef EXCEPT_H
#define EXCEPT_H
#include<stdexcept>
/*If there are too few command line arguments, throw error*/
class argCountException:public std::runtime_error{
	public:
		argCountException(): 
			std::runtime_error{"Wrong amount of command line args:program_name [input_file][output_file][mult_factor]"}{};
};
class fileOpen:public std::runtime_error{
		public:
		fileOpen():
		std::runtime_error{"Error opening file."}{};
};
class overflow:public std::runtime_error{
	public:
		overflow():std::runtime_error{"Overflow at bit "}{};
};
#endif
