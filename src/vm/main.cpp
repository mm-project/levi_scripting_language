#include "vm.hpp"

#include <util/fileio.hpp>

int main(int c, char** argv ) 
{
	//FIXME check input arguments and count.
	
	LeviVirtualMachine lvm;
	
	//try  {
		lvm.load(argv[0]);
		//lvm.start();
		//lvm.stop();

	//} catch (VMexception d) {
	//	
	//
	//} catch (...) {
	//	
	//		
	//}
	//lvm.execute("")
	
}