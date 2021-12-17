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
		login(char*,char*);//登录初始化 
		login(char*,char*,char*,char*);//注册初始化 
		bool verify1();//登录验证密码是否匹配
		bool verify2();//注册验证账号是否存在
		void regist();//注册
		void in();//将账号文件中的姓名和电话赋给对象
		void init();//读取file中所有需求
		void ending();//将链表中所有数据更新到文件夹中
		int tasknumber(int);//获得链表中现有的需求数量
		string detail(int, string, int);//获得需求的具体信息
		string operation(int, int, string, string, int, int);//对需求进行各种操作
	private:
		events eve[4];
};


#endif
