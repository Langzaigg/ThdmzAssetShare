#pragma once
#include "../NThgfm/DMSLElf.h"
#include <vector>

namespace DmslOptimizer {
	namespace Input {
		struct OprInput {
			Dmsl::VirtualMachine::ElfCode opr;	//������

			struct Arg {
				union  { double val; uintptr_t address; };
				enum{T_VAL,T_ADDRESS}type;
			};
			std::vector<Arg> args;	//�����б�
			uintptr_t oprAddress;	//�ֽ����ַ
		};


		std::vector<OprInput> GetInput(const std::vector<uint8_t>& code);

		void RelinkInputCode(std::vector<OprInput>&);	//�������е���ת����ΪOprInput�±����ת���������Ż�
	}
}