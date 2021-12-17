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
	demand* last=NULL, * next=NULL;//链表指针
	string getname();
	string getphone();
	string gettitle();
	string getcontent();
	void changen(string);
	void changep(string);
	void changet(string);
	void changec(string);
	friend istream& operator>>(istream&, demand&);//重载输入运算符
	friend ostream& operator<<(ostream&, demand&);//重载输出运算符
private:
	string name, phone, title, content;
};

#endif