#ifndef vm_hpp
#define vm_hpp

#include "bytecode.hpp"

#include <queue>
#include <vector>
#include <cassert>

class LeviVirtualMachine
{
	public:
		/*LeviVirtualMachine() {
			m_ip = 0;
			m_num_data_regs = 3;
			m_data_regs_size = 4;
			m_data_regs.resize(m_num_data_regs);
		}
		
		void execute_next_instruction() {
				execute_bytecode(m_queue.front());
				m_queue.pop();
		}
		
		void execute_bytecode(LBytecode& b ) {
				b.print_debug();
				//OpCode code = b.get_opcode();
				//bool* data = b.get_operands();
				//execute_opcode_on_data(code,data);
		}
		*/
		void load(const std::string& fname) {
			//TODO
				
				util::string_2_boolarray("0001","0000000000000001");
				util::string_2_boolarray("0001","0000000000000001");
				util::string_2_boolarray("0001","0000000000000001");
				util::string_2_boolarray("0001","0000000000000001");
				
			/*LBytecodeIntHelper h;
			h.create_bytecode(MOV,"0001","0000000000000001");
			h.create_bytecode(ADD,"0001","0000000000000001");
			h.create_bytecode(MOV,"0001","0000000000000001");
			
			/*
			m_queue.push(h.create_bytecode(MOV,"0001","0000000000000001"));
			m_queue.push(h.create_bytecode(PNT,"0001",""));
			m_queue.push(h.create_bytecode(MOV,"0101","0000000000000101"));
			m_queue.push(h.create_bytecode(PNT,"0101",""));
			m_queue.push(h.create_bytecode(ADD,"0001","0002"));
			m_queue.push(h.create_bytecode(PNT,"1111",""));
			m_queue.push(h.create_bytecode(NOP,"",""));
			*/
			
			//m_queue.push();
			//execute();
		}
		
		/*
		void execute() {
			std::cout << "executing..." << std::endl;
			
			while ( ! m_queue.empty() ) {
				std::cout << "que size: " << m_queue.size()  << std::endl;
				execute_next_instruction();
				m_ip++;
			}
		}


		void execute_opcode_on_data(OpCode code, bool* data ) {
			switch( code ) {
					RET:
						break;
					
					ADD:
						//std::cout << ""
						break;
					
					MOV:
						break;
					
					JMP:
						break;
				
					NOP:;
						break;
					
					CMP:
						break;
					
					INC:
						break;
					
					PNT:
						std::cout << "PRINT" << std::endl;
						//std::cout << *data << std::endl;
						break;
					
					default:
						assert(0&&"ILLEGAL INSTRUCTION");
						//throw IllegalInstruction
						break;
					
				}
		}

		
	
	private:
			typedef unsigned int uint;
			typedef uint m_type;
			uint m_num_data_regs;
			uint m_data_regs_size;
			//std::vector<m_type> m_code_reg
			std::vector<std::vector<m_type>> m_data_regs;
			
			std::queue<LBytecode> m_queue;	
			uint m_ip;

	*/
};


#endif