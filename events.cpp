#include "events.h"

const string adr[4]={"file\\knowledge.txt",
					 "file\\delivery.txt" ,
					 "file\\trade.txt"    ,
					 "file\\friend.txt"   };
 
events::events(){
	cnt=0;
	head=NULL;
	tail=NULL;
}

events::~events(){ 
	demand *p=head;
	if (!p)return;
	demand *p1=p->next;
	do{
		delete p;
		p=p1;
		if(p1!=NULL)p1=p1->next;
	}while(p1!=NULL);
	if(p)delete p;
}  

void events::set(demand ap){
	cnt++;
	demand *p=new demand(ap);
	if(tail)tail->next=p;
	p->last=tail;
	tail=p;
	tail->next=NULL;
	if(cnt==1)head=tail;
}

void events::add(string name,string phone,string title,string content){
	demand p;
	p.changen(name);
	p.changep(phone);
	p.changet(title); 
	p.changec(content);
	set(p);
}

bool events::search(string title){
	if(!cnt){
		return 0; 
	}
	demand *p=head;
	do{
		if(p->gettitle()==title){
			return 1;
		}
		p=p->next;

	}while(p!=NULL);
	return 0;
}

void events::del(string title){
	demand* p = head;
	if (!p) return;
	do {
		if (p->gettitle() == title) {
			cnt--;
			demand* p1 = p->last;
			demand* p2 = p->next;
			if (p1) {
				p1->next = p2;
				if (p2)p2->last = p1;
				else tail = p1;
			}
			else {
				head = p->next;
				if (p2)p2->last = NULL;
			}
			if (p)delete p;
			return;
		}
		p = p->next;
	} while (p != NULL);
	return;
}

void events::indata(int k){
	ifstream ins(adr[k].data(),ios::in|ios::binary);
	while(!ins.eof()&&ins){	
		demand a;
		ins>>a;
		if (a.getname() != "") {
			set(a);
		}
	}
	ins.close();
}

string events::display(int cnt, int j) {
	demand *p=head;
	for (int i = 1; i <= cnt; i++) {
			p = p->next;
	}
	if (j == 1) return p->getname();
	if (j == 2) return p->getphone();
	if (j == 3) return p->gettitle();
	if (j == 4) return p->getcontent();
}

void events::outdata(int k){
	ofstream out(adr[k].data(),ios::out|ios::trunc|ios::binary);
	demand *p=head;
	while(p){
		out<<*p;
		p=p->next; 
	}
	out.close();
}

int events::getcnt() {
	return cnt;
}

string events::detail(string title, int cho) {
	demand* p = head;
	do {
		if (p->gettitle() == title) {
			if (cho == 1) return p->getname();
			else if (cho == 2) return p->getphone();
			else if (cho == 3) return p->gettitle();
			else if (cho == 4) return p->getcontent();
		}
		p = p->next;
	} while (p != NULL);
	return NULL;
}