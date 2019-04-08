#pragma once
#include <ostream>
#include <string>
#include <stack>
#include <memory>
#include <vector>
#include <array>
#include <cstdint>
#include <map>
#include "DataActor.h"
#include "BKDRHash.h"

#undef GetModuleHandle

namespace Dmsl{

	const size_t MAX_MEM = 16;

	using DmslVarying = std::array<double, 16>;

    namespace Compiler{
		struct Compiled final{
			struct Unit {
				uint32_t memSize;
				std::vector < std::pair<uint32_t, std::vector<uint8_t>>> eventProgram;
				std::vector<uint8_t> initProgram, mainProgram;
				std::map<uint32_t,std::vector<uint8_t>> custumProgram;
				uint32_t outVaryingSize;
			};
			std::map<uintptr_t, uint32_t> linkTable;
			std::map<uintptr_t, uint32_t> custumProgramHandles;
			std::map<uint32_t, Unit> units;
			uint32_t linkMetSize,linkFuncSize;
		};
    };
    class DmslUnit;

    class DmslVirtualMachine final{ //Dmsl�����
    friend class DmslUnit;
    private:
        Compiler::Compiled m_program;
        std::vector<void(*)(double*,void*)> m_cMetLinks;
        std::vector<double(*)(double*,void*)> m_cFuncLinks;
        //std::vector<double> m_uniform;

        bool m_good = false;
        int m_dmovfs_sel = 0;

		void readyCode(std::vector<uint8_t>&);
        void runCode(const uint8_t*& pausePoint, DmslUnit*,const std::vector<uint8_t>& code,std::array<double, MAX_MEM>& attrMem,DmslVarying& varying,const DmslVarying& varyingIn,void* userdata) const;
    public:
        DmslVirtualMachine(const std::string& programCode,std::ostream& log);    //�������������־������Ա�����뵽�����
		DmslVirtualMachine(const char* program);	//�����ֽ���

		DmslVirtualMachine(const DmslVirtualMachine&) = delete;
		DmslVirtualMachine(DmslVirtualMachine&&) = delete;
		const DmslVirtualMachine& operator = (DmslVirtualMachine&&) = delete;
		const DmslVirtualMachine& operator = (const DmslVirtualMachine&) = delete;

        inline bool Good() const {return m_good;}; //�Ƿ�״̬����
        inline bool HaveUnit(uint32_t u) const {return m_program.units.count(u)==1;}
        //void SetUniform(const std::string& uniform,double);  //����Uniform����
		/*inline void SetUniform(int uniLoc, double f) {	//����Uniform����
			m_uniform[uniLoc] = f;
		}*/

		void LinkCFuncImpl(uintptr_t hash, double(*f)(double*, void*));  //����C����
#define LinkCFunc(x,y) LinkCFuncImpl(Basic::BKDRHash(x),y)
		
		void LinkCMetImpl(uintptr_t hash, void(*f)(double*, void*));    //����C����
#define LinkCMet(x,y) LinkCMetImpl(Basic::BKDRHash(x),y)

		void Ready();	//������ɺ�׼������
        inline void SetDMOVFSSelect(int select){m_dmovfs_sel = select;} //���ظ�ֵʱʹ���ĸ�ֵ����0��ʼ}
		
		inline int GetLocImpl(uintptr_t hash) {
			return m_program.linkTable.at(hash);
		}
#define GetLoc(x) GetLocImpl(Basic::BKDRHash(x))

		inline uint32_t GetModuleHandleImpl(uintptr_t hash) const 
		{
			return m_program.custumProgramHandles.at(hash);
		}	//��ȡ�Զ������ľ��
#define GetModuleHandle(x) GetModuleHandleImpl(Basic::BKDRHash(x))

		inline Compiler::Compiled& GetProgram() {
			return m_program;
		}
    };

	

    class DmslUnit final{ //ִ�е�Ԫ
    friend class DmslVirtualMachine;
    private:
		Basic::DataActor m_dataActor;
        std::array<double, MAX_MEM> m_attribute;
        const DmslVirtualMachine* m_dvm;
		bool m_notInit = true;
        const Compiler::Compiled::Unit* m_unit;
		uint16_t m_sleepTime = 0;	//˯�ߴ��������Ҫ��˯���ˣ���ᰴ�մ���˯�ߣ�ֻ��main����Ч

		std::shared_ptr<DmslVarying> m_varying;
		std::shared_ptr<const DmslVarying> m_varyingIn;
		unsigned m_eventIter = 0;
		unsigned m_timer = 0;	//ʱ��

		const uint8_t* m_pausePoint;

		static std::stack<DmslUnit*> m_nowRunning;

		void* m_userdata = nullptr;
    public:

		DmslUnit(const DmslUnit&) = delete;
		DmslUnit(DmslUnit&&) = delete;
		const DmslUnit& operator = (DmslUnit&&) = delete;
		const DmslUnit& operator = (const DmslUnit&) = delete;

        DmslUnit(const DmslVirtualMachine& dvm,uint32_t unit, std::shared_ptr<const DmslVarying> varyingIn = nullptr);

		inline auto& GetVM() const {
			return *m_dvm;
		}

		inline auto& GetDataActor() {
			return m_dataActor;
		}
		inline void SetUserData(void* d) {
			m_userdata = d;
		}

        inline void Call(){ //���г���
			m_nowRunning.push(this);
			m_timer++;

			m_dataActor.Update();

			if (m_notInit) {
				m_notInit = false;
				m_dvm->runCode(m_pausePoint,this,m_unit->initProgram, m_attribute,*m_varying, *m_varyingIn,m_userdata);
			}
			if (m_sleepTime)
				--m_sleepTime;
			else {
				m_dvm->runCode(m_pausePoint,this,m_unit->mainProgram, m_attribute, *m_varying, *m_varyingIn,m_userdata);
			}

			
			if(m_eventIter < m_unit->eventProgram.size())
				if (m_timer >= m_unit->eventProgram.at(m_eventIter).first) {
					const uint8_t* p = nullptr;
					auto& code = m_unit->eventProgram.at(m_eventIter++).second;
					m_dvm->runCode(p, this, code, m_attribute, *m_varying, *m_varyingIn, m_userdata);
				}
			
			m_nowRunning.pop();

		}

		inline auto static GetRuningUnit() {
			return m_nowRunning.top();

		}
		inline void Call(uint32_t handle) { //�����Զ������
			m_nowRunning.push(this);
			const uint8_t* p = nullptr;
			m_dvm->runCode(p,this,m_unit->custumProgram.at(handle), m_attribute, *m_varying, *m_varyingIn,m_userdata);
			m_nowRunning.pop();
		}
		inline bool GetInterfaceExist(uint32_t module) const {
			if (m_unit->custumProgram.count(module))
				return true;
			else
				return false;
		}

		inline std::shared_ptr<const DmslVarying> GetVaryingOut() const{
			return m_varying;
		}

		inline void SetVaryingOut(int n, double value) {
			(*m_varying)[n] = value;
		}

		inline void SetVaryingIn(std::shared_ptr<const DmslVarying> ptr) {
			m_varyingIn = ptr;
		}

        void SetAttribute(const std::string& attribute,double);  //����Attribute����
        double GetAttribute(const std::string& attribute) const;   //��ȡAttribute����
		inline void SetAttribute(int loc, double f) {	//����Attribute����
			m_attribute[loc] = f;
		}
		inline double GetAttribute(int loc) const {   //��ȡAttribute����
			return m_attribute.at(loc);
		}
		inline void Sleep(uint16_t s) {
			m_sleepTime = s;
		}

		void* operator new(size_t);
		void operator delete(void* ptr);
    };
}

