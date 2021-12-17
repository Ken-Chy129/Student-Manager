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
		person(char*,char*);//登录初始化 
		person(char*,char*,char*,char*);//注册初始化 
		string geta();//返回账号 
		string getpa();//返回密码 
		string getn();//返回姓名 
		string getph();//返回电话号 
		void changea(string);//初始化写入账号 
		void changepa(string);//初始化写入密码 
		void changen(string);//初始化写入姓名 
		void changeph(string);//初始化写入电话号 
	private:
		string account, password, name, phone;
};

#endif
