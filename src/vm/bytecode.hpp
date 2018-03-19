#ifndef bytecode_hpp
#define bytecode_hpp


#include <iostream>
#include <vector>



enum OpCode {
		RET,
		ADD,
		MOV,
		JMP,
		NOP,
		CMP,
		INC,
};		

class LBytecode
{


	public:		
		
		LBytecode(bool* bytecode) {
			m_opcode = bytecode[0]|bytecode[1]|bytecode[2]|bytecode[3];
			
			int i = 4;
			m_operands = m_opcode;
			
			
		}
		
		OpCode get_opcode(){
			return m_opcode;
		}
		
		bool* get_operands() {
			return m_operands;
		}

		void print_debug() {
			//std::cout << opcode2string(m_opcode) << ": " << << std::endl;
		}
		
	
	private:	
		std::string opcode2string() {
			
		}
	
	private:	
		//std::vector<bool> m_impl;
		bool* m_operands;
		OpCode m_opcode;

		
};


#endif