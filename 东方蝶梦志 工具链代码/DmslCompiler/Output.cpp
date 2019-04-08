#include "Output.h"
#include <map>
#include <queue>
std::vector<uint8_t> DmslOptimizer::Output::Output(const std::vector<DmslOptimizer::Input::OprInput>& in)
{
	std::vector<uint8_t> ret;

	std::map<uintptr_t, uintptr_t> linkTable;	//ÿ��ָ�Ԫָ��Ĵ����ַ

	struct LinkPoint {
		uintptr_t resetValueOffset;
		uintptr_t jumpTo;	//ָ�Ԫ�е���תλ��
	};
	std::queue<LinkPoint> linkPoints;

	/*for (uint16_t i = 0; i < in.size();++i) {
		linkTable[i] = ret.size();
		ret.push_back(uint8_t(in[i].opr));

		if (in[i].opr == Dmsl::VirtualMachine::ElfCode::JMP || in[i].opr == Dmsl::VirtualMachine::ElfCode::IF) {
			LinkPoint p = {
					(uint32_t)ret.size(),in[i].args[0].address
				};
			linkPoints.push(p);
		}

		for (auto arg : in[i].args) {
			if (arg.type == DmslOptimizer::Input::OprInput::Arg::T_ADDRESS) {
				for (uint16_t e = 0; e < sizeof(uint32_t); ++e) {
					uint8_t* p = (uint8_t*)&arg.address;
					ret.push_back(p[i]);
				}
			}
			else if (arg.type == DmslOptimizer::Input::OprInput::Arg::T_VAL) {
				for (uint16_t e = 0; e < sizeof(double); ++e) {
					uint8_t* c = (uint8_t*)&arg.val;
					ret.push_back(c[i]);
				}
			}
		}
	}

	while (!linkPoints.empty()) {
		*((uint32_t*)&ret[linkPoints.front().resetValueOffset]) = linkTable.at(linkPoints.front().jumpTo);
		linkPoints.pop();
	}*/

	for (uint32_t i = 0; i < in.size(); ++i) {
		linkTable[i] = ret.size();
		ret.push_back((uint8_t)in[i].opr);

		if (in[i].opr == Dmsl::VirtualMachine::ElfCode::JMP || in[i].opr == Dmsl::VirtualMachine::ElfCode::IF) {
			LinkPoint p = {
				(uintptr_t)ret.size(),in[i].args[0].address
			};
			linkPoints.push(p);
		}

		for (auto p = in[i].args.begin(); p != in[i].args.end(); ++p) {
			if (p->type == DmslOptimizer::Input::OprInput::Arg::T_ADDRESS) {
				for (uint16_t e = 0; e < sizeof(uintptr_t); ++e) {
					ret.push_back(0);
				}
				*(uintptr_t*)&(ret[ret.size() - sizeof(uintptr_t)]) = p->address;
			}
			else if (p->type == DmslOptimizer::Input::OprInput::Arg::T_VAL) {
				for (uint16_t e = 0; e < sizeof(double); ++e) {
					ret.push_back(0);
				}
				*(double*)&(ret[ret.size() - sizeof(double)]) = p->val;
			}
			else {
				abort();
			}
		}
	}

	while (!linkPoints.empty()) {
		*((uintptr_t*)&ret[linkPoints.front().resetValueOffset]) = linkTable.at(linkPoints.front().jumpTo);
		linkPoints.pop();
	}

	return ret;
}
