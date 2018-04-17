#include <catch.hpp>

#include <vm/vm.hpp>


class WhileAsmProg : public AsmProg {
	
	public:
		WhileAsmProg() {
		}
		
		void create_prog() {
			AsmProg::add(MOV,"000","011");  // set 0 in reg[3]
			AsmProg::add(INC,"011","");     // reg[3]++
			AsmProg::add(CMP,"011","111");  // compare "7" with reg[3]  
			AsmProg::add(JLE,"001","");     // goto :1 if true 
			AsmProg::add(PNT,"011","");     // print reg[3]
			AsmProg::add(NOP,"","");        // stop
		}
		
		void create_prog2() {
			/*
			AsmProg::add(011,001,011); 
			AsmProg::add(011,001,011); 
			AsmProg::add(011,001,011); 
			AsmProg::add(011,001,011); 
			AsmProg::add(011,001,011); 
			AsmProg::add(011,001,011); 
			*/
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
	//test(new WhileAsmProg);
	//test(new FibonaciAsmProg);
	//test(new FactorialAsmProg);
	

	return 0;	
}

