#include "login.h"
#include<graphics.h>
using namespace std;

const string adr="account\\";
const int mod1 = 247;
const int mod2 = 233;

login::login(char*a):person(a){}

login::login(char* a,char* b):person(a,b){}

login::login(char* a,char* b,char* c,char* d):person(a,b,c,d){} 

bool login::verify1(){
	string sadr=adr+geta()+".txt";
	string spassword="";
	ifstream in(sadr.data(),ios::in|ios::binary);
	if(!in){
		in.close();
		return false;
	}
	in>>spassword;
	in.close();
	string s1 = getpa();
	for (int i = 1; i < s1.length(); i++) {
		s1[i] = (s1[i - 1] * mod1 + s1[i]) % mod2;
	}
	if(s1==spassword){
		return true;
	}
	else return false;	
}

bool login::verify2() {
	string sadr = adr + geta() + ".txt";
	ifstream ins(sadr.data(), ios::in);
	if (ins) {
		return 1;
	}
	return 0;
}

void login::regist(){
	string sadr=adr+geta()+".txt";
	ofstream out(sadr.data(),ios::out|ios::trunc|ios::binary);
	string s1 = getpa();
	for (int i = 1; i < s1.length(); i++) {
		s1[i] = (s1[i - 1] * mod1 + s1[i]) % mod2;
	}
	out<<s1 <<endl
	   <<getn()  <<endl
	   <<getph() <<endl;
	out.close();
}

void login::in() {
	string sadr = adr + geta() + ".txt";
	ifstream ins(sadr.data(), ios::in);
	string temp1, temp2, temp3;
	ins >> temp1 >> temp2 >> temp3;
	ins.close();
	changen(temp2);
	changeph(temp3);
}

void login::init() {
	for (int i = 0; i < 4; i++) {
		eve[i].indata(i);
	}
}

void login::ending() {
	for (int i = 0; i < 4; i++) {
		eve[i].outdata(i);
	}
}

string login::operation(int diversity, int oper, string title, string content,int i,int j) {//i表示第几个需求，j表示需要第几个数据
		if (oper == 1) {//发布需求
			eve[diversity].add(getn(), getph(), title, content);
			return "";
		}
		else if (oper == 2) {//接受需求
			eve[diversity].del(title);
			return "";
		}
		else if (oper == 3) {//展示需求
			return eve[diversity].display(i, j);
		}
		else if (oper == 4) {//搜索需求
			if (eve[diversity].search(title)) return "a";
			else return"b";
		}
}

int login::tasknumber(int i) {
	return eve[i].getcnt();
}

string login::detail(int diversity, string title,int cho) {
	return eve[diversity].detail(title, cho);
}