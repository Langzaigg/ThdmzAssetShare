#pragma once
#include <vector>
#include <string>
#include <map>
#include <cstdint>
#include <string>
#include <set>


namespace Dmsl {
	namespace Compiler {

		//Ԥ����ɹ�
		struct Precompiled final{
			struct Unit {
				struct Code {
					std::string code;
					int line;
				};
				std::vector<Code> initProgram, mainProgram;	//��ʼ���������������
				std::map<uint32_t, std::vector<Code>> custumProgram;	//�Զ������
				//std::set<uint32_t> customProgramLinkToC;	//Ҫ���ӵ�C���Զ������
				std::vector<std::pair<int, std::vector<Code>>> eventProgram;
				std::map<std::string, uint32_t> varTable;	//˽�б������ӱ�
				std::map<std::string, uint32_t> inVarying,outVarying;	//varying���ű�
				uint32_t memSize;	//�ڴ�ռ�ô�С
				uint32_t num;	//����Ԫ���
			};
			std::map<std::string, uint32_t> attributeVars,cFuncs,cMet;	//���Ա��������ױ�������ӱ�C���Ժ������ӱ�C���Է���
			std::map<std::string, double> constants;	//����
			std::map<uint32_t, uint32_t> metParamNum, funcParmNum;	//�������������ͺ�����������
			std::vector<Unit> units;	//����Ԫ
			std::map<std::string, uint32_t> custumProgramTable;	//�Զ�������
			std::set<uint32_t> interfaceTable;	//���������еľ�Ϊinterface��������Ҫ���ֽ������޳�
		};

		//Ԥ������룬����trueΪ�ɹ�
		bool Precompile(const std::string& codeStr,Precompiled&,std::ostream& log);

	}
}
