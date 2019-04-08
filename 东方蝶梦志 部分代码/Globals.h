#pragma once
#include "Asset.h"
#include <string>
#include <iostream>
#include "Log.h"
#include <codecvt>
#include <cmath>
#include <memory>
#include "CtxFont.h"

#define LPS 100

//#define OUTPUT_COMPILED_BIN	//����������ļ���asset_runtime_compiledĿ¼

//#define USE_COMPILED_BIN	//ʹ�ñ�����Ķ���������

#define CHECK (x) if(!(x)) Crash(L"Assert!");	//����

#define AT(x,i) x.at(i)		//��������������

//�߼���Ļ��С
const int WIDTH = 1280;
const int HEIGHT = 720;
const int MAX_LINE_IN_SCREEN = 1469;

const unsigned VERSION = 0xFF000000;

/* �汾��ʽ��
 * ��һ�ֽ�ΪFF��Ϊ�����еİ汾
 * �ڶ��ֽ�Ϊ��Ϸ�ı��
 * �����͵����ֽ�Ϊ��Ϸ�����İ汾�š�
 */


//���������˳�
void Crash(const std::wstring&);

inline double Clamp(double smallVar, double bigVar, double x) {
	x = x > smallVar ? x : smallVar;
	x = x < bigVar ? x : bigVar;
	return x;
}

constexpr double Mix(double smallVar, double bigVar, double x) {	//�����ֵ
	return x * (bigVar - smallVar) + smallVar;
}

inline double SlowMotion(double p) {	//��һ��0~1�ĸ��������л�������
	return -p * p + 2 * p;
}

inline double SlowMotion2(double x) {	//Բ�λ���
	return sqrt(1 - (x - 1)*(x - 1));
}

inline double SlowMotion3(double x) {
	return 1 - SlowMotion2(1 - x);	//����Բ�λ���
}

inline double SlowMotion4(double x) {
	return 1 - SlowMotion(1 - x);
}

inline double SlowMotion5(double x) {
	return sin(M_PI / 2 * x);
}

Basic::Video::Renderer2D::CtxFont & GetCtxFont1();

inline double Rand() {
	return double(rand()) / RAND_MAX;
}

std::wstring Str2WStr(const std::string& s);


//�ַ���IO
inline void WriteStringToStream(const std::string& str, std::ostream& out) {
	uint32_t size = (uint32_t)str.size();
	out.write((char*)&size, sizeof(size));

	std::vector<char> c;
	for (auto ch : str) {
		c.push_back(~ch);
	}
	out.write(&c[0], size);
}

inline void LoadStringFromStream(std::string& str, std::istream& in) {
	uint32_t size;
	in.read((char*)&size, sizeof(size));
	str.resize(size);
	in.read(&str[0], size);
	for (auto& c : str)
		c = ~c;
}