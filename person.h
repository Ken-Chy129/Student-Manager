#ifndef PERSON_H
#define PERSON_H

#include<iostream>
#include<algorithm>
#include<cstring>
#include<fstream>
using namespace std;

class person{
	public:
		person() = default;
		person(char*);
		person(char*,char*);//��¼��ʼ�� 
		person(char*,char*,char*,char*);//ע���ʼ�� 
		string geta();//�����˺� 
		string getpa();//�������� 
		string getn();//�������� 
		string getph();//���ص绰�� 
		void changea(string);//��ʼ��д���˺� 
		void changepa(string);//��ʼ��д������ 
		void changen(string);//��ʼ��д������ 
		void changeph(string);//��ʼ��д��绰�� 
	private:
		string account, password, name, phone;
};

#endif
