#include "demand.h"

demand::demand(string a, string b) :name(a), phone(b) {
	last = next = NULL;
}

string demand::getname() {
	return name;
}

string demand::getphone() {
	return phone;
}

string demand::gettitle() {
	return title;
}

string demand::getcontent() {
	return content;
}

void demand::changen(string s) {
	name = s;
}

void demand::changep(string s) {
	phone = s;
}

void demand::changet(string s) {
	title = s;
}

void demand::changec(string s) {
	content = s;
}

istream& operator>>(istream& in, demand& a) {
	in >> a.name >> a.phone >> a.title>> a.content;
	return in;
}

ostream& operator<<(ostream& os, demand& a) {
	os << a.name << endl
		<< a.phone << endl
		<< a.title << endl
		<< a.content << endl;
	return os;
}