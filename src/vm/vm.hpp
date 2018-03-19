#ifndef vm_hpp
#define vm_hpp

#include "bytecode.hpp"

#include <queue>
#include <vector>
#include <cassert>

class LeviVirtualMachine
{
	public:
		LeviVirtualMachine() {
			m_ip = 0;
			m_num_data_regs = 3;
			m_data_regs_size = 4;
			m_data_regs.resize(m_num_data_regs);
		}
		
		void execute_next_instruction() {
				execute_bytecode(m_queue.pop());
		}
		
		void execute_bytecode(LBytecode& b ) {
				OpCode code = b.get_opcode();
				void* data = b.get_operands();
				execute_opcode_on_data(code,data);
		}
		
		void load(const std::string& fname) {
			//TODO
			bool* b = new bool(5);
			b(0000,0000,0001)
			b(0000,0000,0002)
			b(0000,0000,0002)
						
			
			m_queue.push();
			
		}
		
		void execute() {
			while ( ! m_queue.empty() ) {
				execute_next_instruction();
				m_ip++;
			}
		}


		void execute_opcode_on_data(OpCode code, void* data ) {
			switch( code ) {
					RET:;
						break;
					
					ADD:;
					
					MOV:;
						break;
					
					JMP:;
						break;
				
					NOP:;
						break;
					
					CMP:;
						break;
					
					INC:;
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

	
};


#endif