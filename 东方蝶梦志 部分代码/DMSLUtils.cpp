#include "NuzPrecompiled.h"
#include "DMSLUtils.h"
#include <iostream>
#include <stdexcept>
#include <set>
#include <cctype>
#include <string>

using namespace std;

namespace Dmsl {
	namespace Utils {

		//��ȡ���ҵ���
		std::string ReadLeftWord(const std::string& s) {
			std::string str;
			for (auto c : s) {
				if (isalnum(c))
					str += c;
				else break;
			}
			return str;
		}

		//��ȡ�����ҵ�������ĵ���
		std::string ReadRightLine(const std::string& s) {
			std::string str;
			bool start = false;
			for (auto c : s) {
				if (!isalnum(c))
					start = true;
				if (start) str += c;
			}
			return str;
		}

		//ȥ���ҿո�
		std::string TrimRight(const std::string& s) {
			std::string t;
			bool killSpace = true;
			for (auto p = s.begin(); p != s.end(); ++p) {
				if ((!isblank(*p) || !killSpace) && *p != '\r') {
					t += *p;
					killSpace = false;
				}
			}
			return t;
		}

		//ȥ��ȫ���ո�
		std::string TrimAll(const std::string& s) {
			std::string t;
			for (auto p = s.begin(); p != s.end(); ++p) {
				if (!isblank(*p) && *p != '\r') {
					t += *p;
				}
			}
			return t;
		}

		//ȥ��ע��
		std::string DeleteComments(const std::string& a) {
			auto str = a + '#';
			return str.substr(0, str.find('#'));
		}


		//ת����double
		double ToDouble(const std::string& f) {
			for (char ch : f)
				if (!isdigit(ch) && ch != '.') throw std::invalid_argument(string("�������ֵ ") + f);
			return (double)atof(f.c_str());
		}
		int ToInt(const std::string & i)
		{
			for (auto ch : i)
				if (!isdigit(ch)) throw invalid_argument("�������ֵ " + i);
			return atoi(i.c_str());
		}
		void Split(std::string str, std::vector<std::string>& out,char ch)
		{
			while (1) {
				auto pos = str.find(ch);
				if (pos == string::npos) {
					out.push_back(str);
					break;
				}
				else {
					out.push_back(str.substr(0, pos));
					str = str.substr(pos + 1, str.length() - pos - 1);
				}
			}
		}
		void CheckName(const std::string & s)
		{
			if (s.empty()) throw invalid_argument("�յı���/����/����/��������");
			if (isdigit(s[0])) throw invalid_argument("����/����/����/��������һλ���������֣�" + s + "��");
			for (char c : s) if (!isalnum(c) && c != '_') throw invalid_argument("�Ƿ��ı���/����/����/��������" + s + "��");

		}
		std::string ReadToken(std::string & s)
		{
		    static set<string> symbols;
		    static bool inited = false;
		    if(!inited){
                inited = true;
                symbols.insert("+");
                symbols.insert("-");
                symbols.insert("*");
                symbols.insert("/");
                symbols.insert("(");
                symbols.insert(")");
                symbols.insert("%");
                symbols.insert("&&");
                symbols.insert("||");
                symbols.insert("!");
                symbols.insert(">=");
                symbols.insert("<=");
                symbols.insert("==");
                symbols.insert("!=");
                symbols.insert(">");
                symbols.insert("<");
                symbols.insert(",");
                symbols.insert("@");
		    }
			if(s.empty()) return s;

			string r;
			if (isalnum(s[0])) {
				while (isalnum(s[0]) || s[0] == '.') {
					r += s[0];
					s = s.substr(1, s.length() - 1);
				}
			}
			else {
				while (!(isalnum(s[0]) || s[0] == '_')) {
					r += s[0];
					s = s.substr(1, s.length() - 1);
					if(s.empty()) break;
				}
                while(!symbols.count(r)){
                    s = r[r.length()-1] + s;
                    r = r.substr(0,r.length()-1);
					if (r.empty()) {
						throw invalid_argument("������������");
					}
                }
			}
			return r;
		}
	}
}
