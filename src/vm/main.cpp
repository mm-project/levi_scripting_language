#include "vm.hpp"


#include <util/conversion.hpp>

#include <iostream>

class test {

public:
		void load() {
			util::string_2_boolarray("0001","0000000000000001");
			util::string_2_boolarray("0001","0000000000000001");
			util::string_2_boolarray("0001","0000000000000001");
			util::string_2_boolarray("0001","0000000000000001");
		}
	
};

int main(int c, char** argv ) 
{
	//FIXME check input arguments and count.
	//test t;
	//t.load();
		
	LeviVirtualMachine lvm;
	
	//try  {
		lvm.load(argv[0]);
		//lvm.start();
		//lvm.stop();
	std::cout << "end" << std::endl;
	//} catch (VMexception d) {
	//	
	//
	//} catch (...) {
	//	
	//		
	//}
	//lvm.execute("")
	
}
