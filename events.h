#ifndef events_H
#define events_H
 
#include<iostream>
#include<cstring>
#include<algorithm>
#include<fstream>
#include "demand.h"
using namespace std;

class events{
	public:
		events();
		~events();
		void set(demand);//�������������
		void add(string,string,string,string);//��װ������
		void del(string);//��������������ɾ��
		bool search(string);//Ѱ������
		void indata(int);//��ĳ���������ݴ����ļ���
		void outdata(int);//��ĳ���ļ������ݶ�������
		int getcnt();//�õ������е���������
		string display(int, int);//������չʾ������
		string detail(string,int);//���ĳ�������������Ϣ
	private:
		int cnt;
		demand *head,*tail;
}; 

#endif

