#include "NuzPrecompiled.h"
#include "SnowRVReader.h"
#include "Asset.h"

using namespace std;
using namespace Basic;

//#define _USE_BIN_CODE

std::string SnowRVReader::Trim(const std::string& s)
{
    string t;
    for(auto p = s.begin();p != s.end();++p)
        if(*p != ' ' && *p != '\t' && *p != '\0')
            t+=*p;
    return t;
}

void SnowRVReader::loadFromBin(const std::shared_ptr<std::vector<uint8_t> >& buf)
{
    //TODO:需要重写
	throw std::exception("未能实现");
}

void SnowRVReader::loadFromText(const std::shared_ptr<std::vector<uint8_t> >& buf)
{
    uint32_t num = 0;
    uint32_t lineNum = 1;
    bool bRun = true;
    while(bRun){
        //GetLine
        string line;
        bool bGetLine_Run = true;
        while(bGetLine_Run){
            if(num >= buf -> size()){
                bRun = false;
                bGetLine_Run = false;
            }
            char c = (*buf)[num++];
            if(num >= buf -> size()){
                bRun = false;
                bGetLine_Run = false;
            }
            if(c == '\n') break;
            else if(c == '\r') break;
            else line += c;
        }

        //If it is a # or empty line
        if(Trim(line).empty()) continue;
        if(line[0] == '#') continue;

        //Get Type
        auto p = line.find(' ');
        if(p == string::npos) throw SnowRVCompileFailed("Can not get value type in line " + std::to_string(lineNum) + ".");
        string type = line.substr(0,p);

        //Get Name
        auto p2 = line.find('=');
        if(p == string::npos) throw SnowRVCompileFailed("Can not find \'+\' in line" + std::to_string(lineNum) + ".");
        string name = Trim(line.substr(p,p2-p));
        if(name.empty()) throw SnowRVCompileFailed("Invaild name in line" + std::to_string(lineNum) + ".");

        //Get Value
        string value = line.substr(p2+1,line.length()-p2-1);

        if(type == "INT"){
			const auto s = Trim(value);
            if(s.empty()) throw SnowRVCompileFailed("Invaild int value in line " + std::to_string(lineNum) + ".");
			const auto hash = BKDRHash(name);
			if (m_ints.count(hash))
				throw SnowRVCompileFailed("Int title hash collisition:" + name);
            m_ints[hash] = atoi(s.c_str());
        }else if(type == "FLOAT"){
			const auto s = Trim(value);
            if(s.empty()) throw SnowRVCompileFailed("Invaild double value in line " + std::to_string(lineNum) + ".");
			const auto hash = BKDRHash(name);
			if (m_flts.count(hash))
				throw SnowRVCompileFailed("Float title hash collisition:" + name);
            m_flts[hash] = atof(s.c_str());
        }else if(type == "STR"){
			const auto ps1 = value.find('\"');
            value = value.substr(ps1+1,value.length()-ps1-1);
			const auto ps2 = value.find('\"',ps1);
            if(ps1 == string::npos || ps2 == string::npos) throw SnowRVCompileFailed("Invaild string value in line " + std::to_string(lineNum) + ".");
			const auto hash = BKDRHash(name);
			if (m_strs.count(hash))
				throw SnowRVCompileFailed("Float title hash collisition:" + name);
            m_strs[hash] = value.substr(0,ps2);
        }else{
            throw SnowRVCompileFailed("Unknow type \"" + type +"\" in line " + std::to_string(lineNum) + ".");
        }
        ++lineNum;
    }
}


SnowRVReader::SnowRVReader(const std::string& path)
{
#ifdef _USE_BIN_CODE
	Asset ast("Elf/" + path + "o");
#else
	Asset ast(path);
#endif

	auto buf = ast.Ptr();

    //If it is an empty file.
    if(buf -> size() == 0) throw SnowRVCompileFailed("It is an empty file.");
    //Read As Binary File
    if((*buf)[0] == 0xFF)
        loadFromBin(buf);
    else
        loadFromText(buf);
}

std::string SnowRVReader::GetStringImpl(uintptr_t s) const
{
    if(m_strs.count(s)) return m_strs.at(s);
    else throw ValueNotFound("string title " + to_string(s) +" not found.");
}

int SnowRVReader::GetIntImpl(uintptr_t s) const
{
    if(m_ints.count(s)) return m_ints.at(s);
    else throw ValueNotFound("Int title " + to_string(s) +" not found.");
}

double SnowRVReader::GetDoubleImpl(uintptr_t s) const
{
    if(m_flts.count(s)) return m_flts.at(s);
    else throw ValueNotFound("Double title" + to_string(s) +" not found.");
}

void SnowRVReader::SaveToBinaryFile(const std::string& file) const{
    //TODO:需要重写
	throw std::exception("未能实现");
}

