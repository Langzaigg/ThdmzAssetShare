#pragma once
#include <string>
#include <vector>

namespace Dmsl {

	namespace Utils {
		//��ȡ���ҵ���
		std::string ReadLeftWord(const std::string&);

		//��ȡ�����ҵ�������ĵ���
		std::string ReadRightLine(const std::string&);

		//ȥ���ҿո�
		std::string TrimRight(const std::string&);

		//ȥ��ȫ���ո�
		std::string TrimAll(const std::string&);

		//ȥ��ע��
		std::string DeleteComments(const std::string&);

		//ת����double
		double ToDouble(const std::string&);

		//ת����int
		int ToInt(const std::string&);

		//�з��ַ���
		void Split(std::string str, std::vector<std::string>& out,char ch);

		//������/�������Ϸ���
		void CheckName(const std::string& s);

		//��ȡ���ұߵ�һ������������������и�
		std::string ReadToken(std::string& s);
	}
}
