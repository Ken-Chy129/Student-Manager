#ifndef LOGIN_H
#define LOGIN_H

#include<iostream>
#include<algorithm>
#include<cstring>
#include<fstream>
#include "person.h"
#include "events.h"
using namespace std;

class login:virtual public person{
	public:
		login() = default;
		login(char*);
		login(char*,char*);//��¼��ʼ�� 
		login(char*,char*,char*,char*);//ע���ʼ�� 
		bool verify1();//��¼��֤�����Ƿ�ƥ��
		bool verify2();//ע����֤�˺��Ƿ����
		void regist();//ע��
		void in();//���˺��ļ��е������͵绰��������
		void init();//��ȡfile����������
		void ending();//���������������ݸ��µ��ļ�����
		int tasknumber(int);//������������е���������
		string detail(int, string, int);//�������ľ�����Ϣ
		string operation(int, int, string, string, int, int);//��������и��ֲ���
	private:
		events eve[4];
};


#endif
