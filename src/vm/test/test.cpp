#include <catch.hpp>

#include <vm/vm.hpp>


class WhileAsmProg : public AsmProg {
	
	public:
		WhileAsmProg() {
		}
		
		void create_prog() {
			AsmProg::add(MOV,"001","001");
			AsmProg::add(INC,"001","");
			AsmProg::add(CMP,"001","101");
			AsmProg::add(JLE,"001","");
			AsmProg::add(PNT,"001","");
			AsmProg::add(NOP,"","");
		}
};




void test(AsmProg* prg) {
		LeviVirtualMachine lvm;
		lvm.load_internal_asm(prg);
		lvm.start();
		lvm.stop();	
}




int main() 
{
	test(new WhileAsmProg);
	//test(new FibonaciAsmProg);
	//test(new FactorialAsmProg);
	

	return 0;	
}

