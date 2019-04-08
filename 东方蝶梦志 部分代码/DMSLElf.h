#pragma once
namespace Dmsl {
	namespace VirtualMachine {
		enum  class ElfCode {
			//����ָ��
			DMOVFS = 0x00,	//���ظ�ֵ�����������uint16_t ��ַ,n;double datas[n];�������ָ����һ��double��ֵ����ַΪk�ı�����*
			MOV = 0x01,	//��ջ��ȡֵ����ֵ��������ָ�룩ָ��ı���*
			CFUNC = 0x02,	//���ú���������Ϊ������ַ��ע���з���ֵ��ջ���ֲ�ͬ*
			CMET = 0x03,	//���÷���������Ϊ������ַ��û�з���ֵ��ջ���ֲ�ͬ*
			PUSH = 0x04,	//ѹջ��double*
			IF = 0x05,	//���ջ��Ϊbool = true�������Ӵ�ָ�������ת��ָ�����ָ���Ĵ���λ��*
			JMP = 0x06,	//��������ת���뵽����λ��*
			END = 0x07,	//����ִ��*

			DUNPA = 0x08,   //ֱ�ӽ����ó�Attr��Var��ѹջ*
			//DUNPU = 0x09,   //ֱ�ӽ����ó�Uniform��ѹջ*

			//����ָ��
			NEGA = 0x0A,	//ջ��ȡ��ѹջ*

			//Ҫ��ջ��������Ϊdouble����ѹ��double
			ADD = 0x0B,	//�ӷ�*
			SUB = 0x0C,	//����*
			MUL = 0x0D,	//�˷�*
			DIV = 0x0E,	//����*
			MOD = 0x0F,	//ȡ��������*

			//Ҫ��ջ��������Ϊdouble����ѹ��BOOL
			BIG = 0x10,	//����*
			BIGE = 0x11,	//���ڵ���*
			SML = 0x12,	//С��*
			SMLE = 0x13,	//С�ڵ���*
			EQ = 0x14,	//����*
			NE = 0x15,	//������*

			//Ҫ��ջ��������ΪBOOL����ѹ��BOOL
			AND = 0x16,	//��*
			OR = 0x17,	//��*
			NOT = 0x18,	//��*

			//VARYING��ָ��
			VARYING_MOV = 0x19,	//��ջ��д��ֵ��Varying Out���򣬲���Ϊһ��Address
			VARYING_READ_IN = 0x1A,	//��Varying Inȡ��һ��ֵѹջ������Ϊһ��Address
			VARYING_UNP = 0x1B,	//��Varying Out����ȡ��һ��ֵ��ѹջ������Ϊһ��Address

			//����ʱ�������ͣ
			PAUSE = 0x1C,	//�޲���

			//DataActor����
			//������ADDRESS var
			//ջ����(top)FLOAT end,FLOAT time,FLOAT function
			DATAACTOR_ADD_ATTR = 0x1D,	//���Attribute��DataActor
			DATAACTOR_ADD_VARYING = 0x1E	//���Varying��DataActor
		};
	}
}
