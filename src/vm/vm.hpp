#ifndef vm_hpp
#define vm_hpp

#include "bytecode.hpp"

#include <queue>
#include <vector>
#include <cassert>

//FIXME move...!
typedef char dsize;
	




class AsmProg {
	public:
			AsmProg() { }
			
			void set(std::vector<LBytecode>* data) {
				m_con = data;
			}
			
			virtual 
			void add(OpCode code,const std::string& str1,const std::string& str2) {
				m_con->push_back(h.create_bytecode(code,str1,str2));
			}
		
			virtual void create_prog() {
				assert(0&&"default prog");
			}
		
			std::vector<LBytecode>* get() {
				return m_con;
			}

	private:
			std::vector<LBytecode>* m_con;
			LBytecodeIntHelper h;
};


class LeviVirtualMachine
{
	
	//FIXME move to utilt/types.h
	
	
	public:
		LeviVirtualMachine() {
			m_ip = 0;
			m_num_data_regs = 3;
			m_data_regs_size = 4;
			m_data_regs.resize(m_num_data_regs);
			m_last_comp = false;
			
			m_finished = false;
		}
		
		bool is_finished() {
			return m_finished;
			//= true;
		}
		
		void execute_next_instruction() {
			//m_code.front().print_debug();
			//FIXME check size;
			//execute_bytecode(m_code.front());
			//m_code.erase(m_code.begin());
			execute_single_bytecode(m_code[m_ip]);
			m_ip++;
				
		}
		
		void execute_single_bytecode(LBytecode& b ) {
			//b.print_debug();
			OpCode code = b.get_opcode();
			dsize* data = b.get_operands();
			execute_opcode_on_data(code,data);
		}
		
		
		
		void load_internal_asm(AsmProg* prg) {
			prg->set(&m_code);
			prg->create_prog();
			m_code = *(prg->get());
			std::cout << "Loaded ok" << std::endl;
				
		}
		
			
		void start() {
			execute();
		}
		

		void stop() {
			//unlaod();
		}
		
		void load_file(const std::string& fname) {
			//TODO
			//util::read_binary_file(fname)
			//
			
	
			//FIXME throw error if error during load.
			//execute();
		}
		
		
		void execute() {
			std::cout << "\n\nexecuting..." << std::endl;
			
			//while ( ! m_code.empty() ) {
			while ( ! is_finished() ) {
				//std::cout << "que size: " << m_code.size()  << std::endl;
				execute_next_instruction();
				//m_ip++;
			}
		}


		void execute_opcode_on_data(OpCode code, dsize* data ) {
			//assert( code!=NOP && data &&"execute on null???");
			std::cout << LBytecode::opcode_2_string(code) << ": " << util::boolarray_2_string(&data[0],3) << " - "<< util::boolarray_2_string(&data[3],3)  << std::endl;
			switch( code ) {

					case NOP:;
						m_finished = true;
						break;			

					
					case PNT:
						//std::cout << "PRINT" << std::endl;
						std::cout << "****VMPRINT:<" << m_data_regs[util::bin_2_dec(util::boolarray_2_string(&data[0],3))] << ">" << std::endl;
						break;
				
					
					case JLE:
						(m_last_comp)?m_ip=util::bin_2_dec(util::boolarray_2_string(&data[0],3)):m_ip;;
						break;
						
					
					//FIXME rewrite
					case MOV:
						//bin_2_dec1
						//std::cout << "IMPLEMENT MOV: ---> data* " <<  util::boolarray_2_string(data,5) << std::endl;
						//std::cout << "VALUE: " << util::bin_2_dec(util::boolarray_2_string(&data[0],3)) << " TO REGN: " <<  util::bin_2_dec(util::boolarray_2_string(&data[3],3)) << std::endl;
						//std::cout << "" << util::boolarray_2_string(&data[0],3) << " TO REGN: " <<  util::boolarray_2_string(&data[3],3) << "."<< std::endl;
						m_data_regs[util::bin_2_dec(util::boolarray_2_string(&data[3],3))]=util::bin_2_dec(util::boolarray_2_string(&data[0],3));
						break;


					case INC:
						//std::cout << "IMPLEMENT INC: ---> " << std::endl;
						m_data_regs[util::bin_2_dec(util::boolarray_2_string(&data[0],3))]++;
						//std::cout << "---" << m_data_regs[util::bin_2_dec(util::boolarray_2_string(&data[0],3))] << std::endl;
						break;
						

				
					case CMP:
						//int f = util::bin_2_dec(util::boolarray_2_string(&data[0],3));
						//int s = util::bin_2_dec(util::boolarray_2_string(&data[3],3));						
						//
						 util::bin_2_dec(util::boolarray_2_string(&data[0],3))>m_data_regs[util::bin_2_dec(util::boolarray_2_string(&data[3],3))]?m_last_comp=true:m_last_comp=false; 
						//m_last_comp=true:m_last_comp=false; 
						break;

						
					case ADD:
						//std::cout << ""
						break;
					
					
					case JMP:
						//assert(!data&&"JMP TO NULL")
						m_ip = reinterpret_cast<dsize>(*data);
						break;
						
						
						
					default:
						assert(0&&"ILLEGAL INSTRUCTION");
						//throw IllegalInstruction
						break;
					
				}
		}

		
	
	private:
			//FIXME THIS MESS
			typedef unsigned int uint;
			typedef uint m_type;
		
			//HOW MANY REGISTERS
			uint m_num_data_regs;
			
			//EACH REG. SIZE
			uint m_data_regs_size;
			//std::vector<std::vector<m_type>> m_data_regs;
			std::vector<m_type> m_data_regs;
			
			//CODE GOES HERE
			//EACH REG. SIZE
			uint m_code_segment_size;
			std::vector<LBytecode> m_code;
			
			
			uint m_data_segment_size;
			std::vector<uint> m_text_data;
			
			//std::queue<LBytecode> m_code;	
			//
			uint m_ip;

			//FIXME
			bool m_last_comp;
			bool m_finished;

};


#endif