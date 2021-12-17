#ifndef DEMAND_H
#define DEMAND_H

#include<iostream>
#include<algorithm>
#include<cstring>
#include<fstream>
using namespace std;

class demand {
public:
	demand() {}
	demand(string, string);
	demand* last=NULL, * next=NULL;//����ָ��
	string getname();
	string getphone();
	string gettitle();
	string getcontent();
	void changen(string);
	void changep(string);
	void changet(string);
	void changec(string);
	friend istream& operator>>(istream&, demand&);//�������������
	friend ostream& operator<<(ostream&, demand&);//������������
private:
	string name, phone, title, content;
};

#endif