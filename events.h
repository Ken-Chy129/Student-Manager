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
		void set(demand);//将需求放至链表
		void add(string,string,string,string);//封装新需求
		void del(string);//接受需求后从链表删除
		bool search(string);//寻找需求
		void indata(int);//将某条链表数据存入文件夹
		void outdata(int);//将某个文件夹数据读入链表
		int getcnt();//得到链表中的需求数量
		string display(int, int);//将需求展示到界面
		string detail(string,int);//获得某个需求的其他信息
	private:
		int cnt;
		demand *head,*tail;
}; 

#endif

