#include "vm.hpp"

#include <iostream>



int main(int c, char** argv ) 
{
	//TODO
	//util::check_args(vm,c,argv);
	
	LeviVirtualMachine lvm;
	//lvm.load_file(argv[1]);
	lvm.load_file("");
	
	lvm.start();
	lvm.stop();

	return 0;	
	
}