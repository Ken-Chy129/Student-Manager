#include "person.h"

person::person(char* a) {
	account = a;
}

person::person(char* a,char* b){
	account = a;
	password = b;
} 

person::person(char* a,char* b,char* c,char* d){
	account = a;
	password = b;
	name = c;
	phone = d;
}

string person::geta(){
	return account;
}

string person::getpa(){
	return password;
}

string person::getn(){
	return name;
}

string person::getph(){
	return phone;
}

void person::changea(string a){
	account = a;
} 

void person::changepa(string a){
	password = a;
}

void person::changen(string a){
	name = a;
}

void person::changeph(string a){
	phone = a;
}
