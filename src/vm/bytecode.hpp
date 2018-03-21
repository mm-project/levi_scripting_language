#ifndef bytecode_hpp
#define bytecode_hpp



#include <iostream>
#include <vector>
#include <string>
#include <cassert>

#include <util/conversion.hpp>

enum OpCode {
		PNT = 0,
		RET,
		ADD,
		MOV,
		JMP,
		NOP,
		CMP,
		INC
};		




class LBytecode
{


	public:		
		/*
		LBytecode(bool* bytecode) {
			//m_opcode = static_cast<OpCode>(bytecode[0]|bytecode[1]|bytecode[2]|bytecode[3]);
			
			//int i = 4;
			//m_operands = &bytecode[4];
		}
		/**/
		
		LBytecode(OpCode code, bool* data) {
			m_opcode = code;
			m_operands = data;
			//std::cout << "Adding: "  << static_cast<int>(m_opcode) << std::endl;
			//std::cout << "Adding: " << opcode_2_string(code) << std::endl;
			//opcode_2_string(code);
			}
		
		OpCode get_opcode(){
			return m_opcode;
		}
		
		bool* get_operands() {
			//return 0;
			return m_operands;
		}

		void print_debug() {
			std::cout << "OPCODE(" << opcode_2_string(m_opcode) << "): " << std::endl;
		}
		

	private:	
		std::string opcode_2_string(const OpCode& code) {
			std::string r;
			
		
			switch( code ) {
				case PNT:
					r = "PNT";
					break;
					
				case RET:
					r = "RET";
					break;
					
				case ADD:
					r = "ADD";
					break;

				case MOV:
					r = "MOV";
					break;

				case JMP:
					r = "JMP";
					break;

				case NOP:
					r = "NOP";
					break;


				case CMP:
					r = "CMP";
					break;

				
				case INC:
					r = "INC";
					break;
					
				default:
					r = "UNDEF";
					//std::cout << "DEFAULT:" << static_cast<int>(code) << std::endl;
					assert(0&&"Unknown opcode");
					break;
			}
		
			return r;
		}
	
	private:	
		//std::vector<bool> m_impl;
		bool* m_operands;
		OpCode m_opcode;

		
};

//FOR DEBUGGING ONLY
//FIMXE add debug macro check
class LBytecodeIntHelper
{
	public:
		LBytecode create_bytecode(OpCode code, const std::string& arg1, const std::string& arg2) { //, const std::string& arg3) {
			//std::cout << "create_bytecode -> " << static_cast<int>(code) << std::endl;
			return LBytecode(code,util::string_2_boolarray(arg1,arg2));
		}
	
};

#endif