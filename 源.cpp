#include <stdlib.h>
#include <graphics.h>
#include <conio.h>
#include <windows.h>
#include <mmsystem.h>
#pragma comment (lib, "winmm.lib")
#include"login.h"
#include"demand.h"

const int LEN=15;//��������
const int HEIGHT = 990;//���泤��
const int WIDTH = 556.5;//������
TCHAR account[LEN], password[LEN], phone[LEN], name[LEN];//�˺š����롢�ֻ�������
TCHAR diversity[2], title[LEN], content[50];//diversity[0]�����������ࡢ������⡢��������
TCHAR ss[] = _T("w");//charתΪTCHAR��ý�����飬���ú�����ssΪ������TCHAR��ʽ
string number[1000];//������
string element[10] = { "0","1","2","3","4","5","6","7","8","9" };//��������ŵ�Ԫ��
login usernow;//��ǰ�˵�����ĵ�¼�˺�

char* TCHARTOCHAR(LPWSTR);//��TCHAR���͵�����ת��Ϊchar��������
void CHARTOTCHAR(const char*);//��char���͵�����ת��ΪTCHAR��������
void Begin();//��ʼ����
void Register();//ע������
void Login();//��¼����
void Login_Word();//��¼����������ʾ
void Login_Change();//��¼�����¼ȡ����ť��ɫ
void Login_Inputbox();//��¼������������
void Login_Cursor1();//��¼�����˺��������˸
void Login_Cursor2();//��¼���������������˸
void Login_Input1();//��¼�����˺�����
void Login_Input2();//��¼������������
void Menu_Initial();//����˵�����
void Menu_Need(int,int);//�˵���������չʾ
void Menu_Publish(int);//�˵����淢������

struct btNode {
	int x, y;
	wchar_t text[20];//����
	int status;//Ĭ��Ϊ0�����°�ťʱΪ1
};//��ť
btNode Node[5] = {
	{30,50,L"���Ϸ���",0},{30,50,L"���Ϸ���",0},
	{30,150,L"��ݴ���",0},
	{30,250,L"��Ʒ����",0},
	{30,350,L"����ƽ̨",0},
};//�����水ť��Ϣ
void DrawBtn(int k) {
	btNode t = Node[k];
	settextcolor(BLACK);
	settextstyle(45, 0, _T("��������ع��"));
	setlinecolor(RGB(50,50,75));
	setlinestyle(PS_SOLID, 2, NULL, 0);//�������֡��߿�ĸ�ʽ����ɫ
	if (t.status == 0) {
		roundrect(t.x, t.y - 8, t.x + 193, t.y + 55, 20, 20);//��ʼΪ����䰴ť
	}
	else {
		setfillcolor(RGB(130,127,133));
		fillroundrect(t.x, t.y - 8, t.x + 193, t.y + 55, 20, 20);//���ʱstatus=1��ת��Ϊ��䰴ť
	}
	setbkmode(TRANSPARENT);
	outtextxy(t.x + 13, t.y + 2, t.text);//�����ť����
}//���ư�ť
inline char* TCHARTOCHAR(LPWSTR lpwszStrIn){
	LPSTR pszOut = NULL;
	if (lpwszStrIn != NULL){
		int nInputStrLen = wcslen(lpwszStrIn);
		int nOutputStrLen = WideCharToMultiByte(CP_ACP, 0, lpwszStrIn, nInputStrLen, NULL, 0, 0, 0) + 2;
		pszOut = new char[nOutputStrLen];
		if (pszOut){
			memset(pszOut, 0x00, nOutputStrLen);
			WideCharToMultiByte(CP_ACP, 0, lpwszStrIn, nInputStrLen, pszOut, nOutputStrLen, 0, 0);
		}
	}
	return pszOut;
}
inline void CHARTOTCHAR(const char* s) {
	int iLength;
	iLength = MultiByteToWideChar(CP_ACP, 0, s, -1, NULL, 0);
	MultiByteToWideChar(CP_ACP, 0, s, -1, ss, iLength);
}
void Begin() {
	initgraph(HEIGHT, WIDTH);
	setbkmode(TRANSPARENT);
	loadimage(NULL, _T("0.jpg"), HEIGHT, WIDTH);//��ʼ������
	settextcolor(BLACK);
	settextstyle(30 * 1.5, 0, _T("���Ĳ���"), 0, 0, 750, 0, 0, 0);//�������ָ�ʽ
	TCHAR s2[] = _T("��¼");
	outtextxy(295 * 1.5, 151 * 1.5, s2);//�������
	TCHAR s3[] = _T("ע��");
	outtextxy(295 * 1.5, 225 * 1.5, s3);
	TCHAR s4[] = _T("�˳�");
	outtextxy(295 * 1.5, 299 * 1.5, s4);
	settextcolor(RED);
	settextstyle(40 * 1.5, 0, _T("����"), 0, 0, 1000, 0, 0, 0);//�������ָ�ʽ
	TCHAR s1[] = _T("ѧ���������ϵͳ");
	outtextxy(160 * 1.5, 70 * 1.5, s1);
	settextstyle(15 * 1.5, 0, _T("�����ٶ�����"), 0, 0, 0, 0, 0, 0);
	TCHAR s0[] = _T("By����41С��");
	outtextxy(568 * 1.5, 350 * 1.5, s0);
	FlushMouseMsgBuffer();//���������������
	MOUSEMSG m;
	while (1)
	{
		m = GetMouseMsg();//��ȡ�����Ϣ
		if (m.uMsg == WM_LBUTTONDOWN) {//����������жϸ�����ť��������벻ͬ����
			if (m.x <= 358 * 1.5 && m.x >= 295 * 1.5 && m.y <= 181 * 1.5 && m.y >= 151 * 1.5) {
				Login();
			}
			if (m.x <= 358 * 1.5 && m.x >= 295 * 1.5 && m.y <= 255 * 1.5 && m.y >= 225 * 1.5) {
				Register();
			}
			if (m.x <= 358 * 1.5 && m.x >= 295 * 1.5 && m.y <= 329 * 1.5 && m.y >= 299 * 1.5) {
				exit(0);
			}
		}
	}
	closegraph();//�رմ���
}
void Register() {
	login user;//����һ��δ��ʼ���Ķ������ں�������ע����Ա��Ϣ
	int i = InputBox(account, LEN, L"�������˺�(��֧��������Ż�����)", L"ע��", 0, 0, 0, 0);//�����Ի���
	user.changea(TCHARTOCHAR(account));//�����˺�
	if (i == 0) {//��������Ͻǹرռ���ѡ����ȡ��
		MessageBox(GetForegroundWindow(), L"ע��ʧ��", L"��ʾ", 0);//������Ϣ����ʾע��ʧ��
		Begin();//�ص���ҳ��
	}
	else {
		while (user.verify2()) {//�ж��˺��Ƿ��Ѵ��ڣ�������������ѭ��
			InputBox(account, LEN, L"�˺��ѱ�ע�ᣬ����������", L"��ʾ", 0, 0, 0, 1);
			user.changea(TCHARTOCHAR(account));//�����˺�
		}
		int len1;//�����ж��˺ų���
		len1 = lstrlen(account);
		while (len1 < 6) {//���˺ų��ȴ��ڵ���6ʱ����ѭ��
			InputBox(account, LEN, L"�˺ų�������ڵ�����λ������������", L"��ʾ", 0, 0, 0, 1);
			len1 = lstrlen(account);
		}
		user.changea(TCHARTOCHAR(account));//�����˺�
		int j = InputBox(password, LEN, L"����������(��֧��������Ż�����)", L"ע��", 0, 0, 0, 0);
		int len2 = lstrlen(password);//�ж����볤��
		if (j == 0) {//��������ʱ���ȡ����رմ�������ֹע��
			MessageBox(GetForegroundWindow(), L"ע��ʧ��", L"��ʾ", 0);
			Begin();
		}
		else {//�����볤�ȴ��ڵ���6ʱ����ѭ��
			while (len2 < 6) {
				InputBox(password, LEN, L"���볤������ڵ�����λ������������", L"��ʾ", 0, 0, 0, 1);
				len2 = lstrlen(password);
			}
			user.changepa(TCHARTOCHAR(password));//��������
			MessageBox(GetForegroundWindow(), L"ע��ɹ�", L"��ʾ", 0);//ע��ɹ�
		}
	}
	MessageBox(GetForegroundWindow(), L"�뿪ʼ���Ƹ�����Ϣ", L"��ʾ", 0);
	InputBox(name, LEN, L"����������", L"������Ϣ", 0, 0, 0, 1);
	user.changen(TCHARTOCHAR(name));//���������������
	InputBox(phone, LEN, L"�������ֻ�����", L"������Ϣ", 0, 0, 0, 1);
	int len3 = lstrlen(phone);//�ж��ֻ����볤��
	while (len3 != 11) {//���ֻ�����Ϊ11ʱ����ѭ��
		InputBox(phone, LEN, L"��������ȷ���ֻ�����(11λ)", L"������Ϣ", 0, 0, 0, 1);
		len3 = lstrlen(phone);
	}
	user.changeph(TCHARTOCHAR(phone));//�����ֻ�����
	MessageBox(GetForegroundWindow(), L"������Ϣ��д�ɹ�", L"��ʾ", 0);
	user.regist();//��������Ϣȫ��д���ļ�
	Login();//�ɹ�ע�������¼����
}
void Login() {
	IMAGE LOGIN;
	initgraph(HEIGHT, WIDTH);
	loadimage(&LOGIN, _T("0.jpg"), HEIGHT, WIDTH);
	SetWorkingImage(&LOGIN);////�趨��ǰ�Ļ�ͼ�豸ΪLOGIN����
	login user;//����һ���������ڼ�¼��¼ʱ������˺�����
	Login_Word();//����¼������ı�����
	Login_Inputbox();//����¼������������
	SetWorkingImage(); //�趨��ǰ�Ļ�ͼ�豸ΪĬ�ϻ�ͼ����
	putimage(0, 0, &LOGIN);//�ڵ�ǰ�豸����ָ��ͼ�񣬼���Ĭ�ϻ�ͼ���ڻ���LOGIN����
	settextstyle(18 * 1.5, 0, L"����", 0, 0, 0, 0, 0, 0);
	setbkmode(OPAQUE); //���õ�ǰ�豸ͼ�������������ʱ�ı���ģʽ��OPAQUE��ʾ�����õ�ǰ����ɫ���
	setbkcolor(RGB(255, 255, 255));//����Ĭ�ϱ�����ɫ
	MOUSEMSG m;
	while (1) {
		m = GetMouseMsg();
		if (m.uMsg == WM_LBUTTONDOWN) {
			if (m.x <= 426 * 1.5 && m.x >= 353 * 1.5 && m.y <= 290 * 1.5 && m.y >= 255 * 1.5) {
				Begin();//���ȡ����ص���ʼ����
				break;
			}
			else if (m.x <= 298 * 1.5 && m.x >= 225 * 1.5 && m.y <= 290 * 1.5 && m.y >= 255 * 1.5) {
				MessageBox(GetForegroundWindow(), L"�������˺�", L"��ʾ", 0);//�����¼����ʾ�������˺�
			}
			else if (m.x <= 425 * 1.5 && m.x >= 275 * 1.5 && m.y <= 191 * 1.5 && m.y >= 161 * 1.5) {//��������
				while (_kbhit()) {//��ռ�����Ϣ����������������ǰ�ļ�����Ϣֱ�ӱ����������
					_getch();
				}
				Login_Cursor1();//���ƹ����˸����⵽��������������˸
				break;//������˸���˳�����ж�
			}
		}
	}
	Login_Input1();//���ݼ�����Ϣ���˺��������ʾ�˺ţ�����س����򵽴�ָ������λ�������
	user.changea(TCHARTOCHAR(account));//���˺�����login
	Login_Cursor2();//�����������˸����⵽��������������˸
	Login_Input2();//���ݼ�����Ϣ�������������ʾ���루*����ʾ��������س����򵽴�ָ������λ�������
	user.changepa(TCHARTOCHAR(password));//����������login
	Login_Change();//����¼��ȡ����λ
	FlushMouseMsgBuffer();//��������Ϣ������
	while (_kbhit()) {//��ռ�����Ϣ������
		_getch();
	}
	while (1) {
		m = GetMouseMsg();
		if (m.uMsg == WM_MOUSEMOVE) {
			if (m.x >= 225 * 1.5 && m.x <= 298 * 1.5 && m.y >= 255 * 1.5 && m.y <= 290 * 1.5) {//����ƶ�����¼��ʱ����¼���ֱ�Ϊ��ɫ
				settextcolor(RGB(255, 0, 0));
				outtextxy(236 * 1.5, 260 * 1.5, _T("��¼"));
			}
			else if (m.x >= 353 * 1.5 && m.x <= 426 * 1.5 && m.y >= 255 * 1.5 && m.y <= 290 * 1.5) {//����ƶ���ȡ����ʱ��ȡ�����ֱ�Ϊ��ɫ
				settextcolor(RGB(255, 0, 0));
				outtextxy(364 * 1.5, 260 * 1.5, _T("ȡ��"));
			}
			else {
				settextcolor(BLACK);//������λ����������λ���ֶ�Ϊ��ɫ
				outtextxy(236 * 1.5, 260 * 1.5, _T("��¼"));
				outtextxy(364 * 1.5, 260 * 1.5, _T("ȡ��"));
			}
		}
		else if (m.uMsg == WM_LBUTTONDOWN) {
			if (m.x <= 298 * 1.5 && m.x >= 225 * 1.5 && m.y <= 290 * 1.5 && m.y >= 255 * 1.5) {//���������¼��
				if (user.verify1()) {//�˺�����ƥ��
					usernow = user;//����ǰuser���˺����븳ֵ��ȫ�ֶ���usernow�Ա�����������ʹ��
					usernow.in();//�鵽���˺Ŷ�Ӧ���ֻ�����������ֵ��usernow
					Menu_Initial();//�����������
					break;
				}
				MessageBox(GetForegroundWindow(), L"���������˺Ų����ڣ�", L"��ʾ", 0);//�˺����벻ƥ���������ʾ
				Login();//ˢ�µ�¼�������µ�¼
				break;
			}
			else if (m.x <= 426 * 1.5 && m.x >= 353 * 1.5 && m.y <= 290 * 1.5 && m.y >= 255 * 1.5) {
				Begin();//���ȡ����ص���ʼ����
				break;
			}
		}
	}
}
void Login_Word() {
	setbkmode(TRANSPARENT);//���õ�ǰ�豸ͼ�������������ʱ�ı���ģʽΪ͸��
	settextstyle(40 * 1.5, 0, L"����", 0, 0, 1000, 0, 0, 0);
	settextcolor(RED);
	TCHAR s1[] = _T("�û���¼");
	outtextxy(245 * 1.5, 55 * 1.5, s1);
	setlinecolor(BLACK);
	rectangle(175 * 1.5, 125 * 1.5, 475 * 1.5, 315 * 1.5);//��Χ���ο�
	setfillcolor(RGB(190, 190, 190));
	rectangle(225 * 1.5, 255 * 1.5, 298 * 1.5, 290 * 1.5);//��¼��
	rectangle(353 * 1.5, 255 * 1.5, 426 * 1.5, 290 * 1.5);//ȡ����
	settextstyle(25 * 1.5, 0, L"����", 0, 0, 0, 0, 0, 0);
	settextcolor(BLACK);
	outtextxy(215 * 1.5, 162 * 1.5, _T("�˺�"));
	outtextxy(215 * 1.5, 205 * 1.5, _T("����"));
	settextstyle(25 * 1.5, 0, L"����", 0, 0, 500, 0, 0, 0);
	outtextxy(236 * 1.5, 260 * 1.5, _T("��¼"));
	outtextxy(364 * 1.5, 260 * 1.5, _T("ȡ��"));
}
void Login_Change() {
	setbkmode(TRANSPARENT);
	setlinestyle(PS_SOLID, 1, NULL, 0);//���ñ߿��ʽ
	setlinecolor(BLACK);
	setfillcolor(RGB(190, 190, 190));
	fillrectangle(225 * 1.5, 255 * 1.5, 298 * 1.5, 290 * 1.5);
	fillrectangle(353 * 1.5, 255 * 1.5, 426 * 1.5, 290 * 1.5);
	settextstyle(25 * 1.5, 0, L"����", 0, 0, 800, 0, 0, 0);
	settextcolor(BLACK);
	outtextxy(236 * 1.5, 260 * 1.5, _T("��¼"));
	outtextxy(364 * 1.5, 260 * 1.5, _T("ȡ��"));
}
void Login_Inputbox()
{
	setlinestyle(PS_SOLID, 1, NULL, 0);
	setfillcolor(WHITE);
	int i;
	for (i = 0; i < 2; i++) {
		bar(275 * 1.5, (161 + 41 * i) * 1.5, 425 * 1.5, (191 + 41 * i) * 1.5);
		setcolor(RGB(0, 0, 0));
		rectangle(275 * 1.5, (161 + 41 * i) * 1.5, 425 * 1.5, (191 + 41 * i) * 1.5);
	}
}
void Login_Cursor1()//��˸���
{
	while (1) {//�������û�н���������ѭ����˸
		Login_Inputbox();//���˺������
		if (_kbhit()) {//�������з�Ӧʱ_kbhit()�᷵��һ������ֵ
			break;//�˳���˸
		}
		Sleep(500);
		setlinestyle(PS_SOLID, 2, NULL, 0);//�����ߵ���ʽΪPS_SOLID�����Ϊ2
		line(278 * 1.5, 165 * 1.5, 279 * 1.5, 185 * 1.5);//�������
		Sleep(500);//��ʱ
	}
}
void Login_Cursor2()//��˸���
{
	while (1) {//�������û�н���������ѭ����˸
		setlinestyle(PS_SOLID, 1, NULL, 0);
		bar(275 * 1.5, 202 * 1.5, 425 * 1.5, 232 * 1.5);
		rectangle(275 * 1.5, 202 * 1.5, 425 * 1.5, 232 * 1.5);
		if (_kbhit()) {//�������з�Ӧʱ_kbhit()�᷵��һ������ֵ
			break;//�˳���˸
		}
		Sleep(500);
		setlinestyle(PS_SOLID, 2, NULL, 0);//�����ߵ���ʽΪPS_SOLID�����Ϊ2
		line(278 * 1.5, 206 * 1.5, 279 * 1.5, 226 * 1.5);//�������
		Sleep(500);//��ʱ
	}
}
void Login_Input1() {
	for (int i = 0; i < LEN; i++) {
		account[i] = _getch();
		outtextxy((277 + 8 * i) * 1.5, 167 * 1.5, account[i]);
		if (account[i] == 8) {//ʹ��delete��
			account[i] = 0;
			outtextxy((277 + 8 * i) * 1.5, 167 * 1.5, L"  ");//����հ׵�סdelete��
			if (i > 0) outtextxy((277 + 8 * (i - 1)) * 1.5, 167 * 1.5, L"  ");//����հ׵�סǰһ���ַ���ʾɾ��
			i -= 2;
			if (i < 0) {
				i = -1;
			}
		}
		else if (account[i] == 13) {//ʹ�ûس���
			outtextxy((277 + 8 * i) * 1.5, 167 * 1.5, L"  ");
			account[i] = '\0';
			break;
		}
	}
}
void Login_Input2() {
	int j = 0;
	for (int j = 0; j < LEN; j++) {
		password[j] = _getch();
		outtextxy((277 + 8 * j) * 1.5, 208 * 1.5, L'*');//���*��
		if (password[j] == 8) {//ʹ��delete��
			password[j] = 0;
			outtextxy((277 + 8 * j) * 1.5, 208 * 1.5, L"  ");//����հ׵�סdelete��
			if(j>0) outtextxy((277 + 8 * (j - 1)) * 1.5, 208 * 1.5, L"  ");//����հ׵�סǰһ���ַ���ʾɾ��
			j -= 2;
			if (j < 0) {
				j = -1;
			}
		}
		else if (password[j] == 13) {//ʹ�ûس���
			outtextxy((277 + 8 * j) * 1.5, 208 * 1.5, L"  ");
			password[j] = '\0';
			break;
		}
	}
}
void Menu_Initial() {
	usernow.init();//�������ļ�ȫ����������
	initgraph(HEIGHT, WIDTH);//�����������
	Menu_Need(1, 0);//���õ�һ������ĵ�һҳ
}
void Menu_Need(int op,int n) {//op��ʾ�ڼ�������n��ʾ��n+1ҳ
	cleardevice();//�õ�ǰ����ɫ��ջ�ͼ�豸��������ǰ������ (0, 0)
	setbkmode(TRANSPARENT);
	loadimage(NULL, _T("0.jpg"), HEIGHT, WIDTH, 1);
	setlinestyle(PS_DASH, 2, NULL, 0);
	setlinecolor(BLACK);
	circle(75, 493, 30);//������ť
	circle(173, 493, 30);//�˳���ť
	for (int j = 1; j < 5; j++) {
		if (j == op) Node[j].status = 1;//�Ľ���չʾ��op�������򽫸ð�ť��״̬����
		else Node[j].status = 0;
		DrawBtn(j);//�������а�ť
	}
	settextcolor(BLACK);
	settextstyle(30, 0, _T("�����ٶ�����"), 0, 0, 0, 0, 0, 0);
	outtextxy(50, 480, _T("����"));//��������
	outtextxy(148, 480, _T("�˳�"));//�˳�����
	setlinestyle(PS_DASHDOT, 2, NULL, 0);
	line(253, 0, 253, WIDTH);
	line(250, 0, 250, WIDTH);//���÷ֽ���
	int cnt = 5 * n;//��ĿǰΪֹ������������
	int goucnt = 0;//��ʾ��ҳ��������������-1
	for (int i = 0; i < 5 ; i++, cnt++) {//չʾ����
		if (cnt == usernow.tasknumber(op-1)) break;//��ĿǰΪֹ��������ڸ�����ӵ�е��������������չʾ
		settextcolor(RED);//�����ɫ
		number[cnt + 1] = element[(int)((cnt + 1) / 10)] + element[(int)(cnt + 1) % 10];//���ɵ�ǰҳ��i+1������ı��
		CHARTOTCHAR(number[cnt+1].data());//�����תΪTCHAR��
		outtextxy(307, 57 + 100 * i, ss);//������
		settextcolor(BLACK);
		setlinecolor(BLACK);
		setlinestyle(PS_SOLID, 2, NULL, 0);
		setfillcolor(RGB(130, 127, 133));
		circle(848, 73 + 100 * i, 25);
		outtextxy(834, 60 + 100 * i, _T("��"));//������������İ�ť
		setlinestyle(PS_DASHDOTDOT, 2, NULL, 0);
		rectangle(365, 48 + 100 * i, 800, 98 + 100 * i);//չʾ����ı߿�
		CHARTOTCHAR(usernow.operation(op-1, 3, " ", " ", cnt, 3).data());//������תΪTCHAR��
		outtextxy(374, 59 + 100 * i, ss);//�������ı���
		goucnt = i;//���¸�ҳ��ĿǰΪֹ����������-1
	}
	for (int i = 0; i < 3; i++) {//��������ҳ�������İ�ť�߿�
		setlinecolor(RGB(51,56,75));
		setlinestyle(PS_SOLID, 1, NULL, 0);
		setfillcolor(RGB(130, 127, 133));
		fillrectangle(915, 68 + 160 * i, 955, 158 + 160 * i);
	}
	outtextxy(922, 70, _T("��"));
	outtextxy(922, 98, _T("һ"));
	outtextxy(922, 126, _T("ҳ"));
	outtextxy(922, 240, _T("��"));
	outtextxy(922, 280, _T("��"));
	outtextxy(922, 392, _T("��"));
	outtextxy(922, 420, _T("һ"));
	outtextxy(922, 448, _T("ҳ"));
	MOUSEMSG m;
	while (1) {
		m = GetMouseMsg();//��ȡ�����Ϣ
		if (m.uMsg == WM_LBUTTONDOWN) {
			for (int i = 1; i < 5; i++) {
				if (m.x >= Node[i].x && m.x <= Node[i].x + 193 && m.y >= Node[i].y - 8 && m.y <= Node[i].y + 55) {//�������i������ť
					Menu_Need(i, 0);//ת������i������չʾ
					break;
				}
			}
			for (int i = 0; i <= goucnt; i++) {//�������������ť
				if (m.x >= 823 && m.x <= 873 && m.y >= 48 + 100 * i && m.y <= 98 + 100 * i) {
					string a = "����", b = "��������Ϣ���Ƿ���ܣ�", c = "�����˵ĵ绰Ϊ";
					string d = usernow.operation(op - 1, 3, "", "", n * 5 + i, 1);
					string e = usernow.operation(op - 1, 3, "", "", n * 5 + i, 2);
					string f = usernow.operation(op - 1, 3, "", "", n * 5 + i, 3);
					string g = a + d + b;
					string h = c + e;
					CHARTOTCHAR(g.data());
					int flag = MessageBox(GetForegroundWindow(), ss, L"��ʾ", 1);//��ʾ����ĳ���˷���������
					if (flag==1) {
						MessageBox(GetForegroundWindow(), L"���ܳɹ���", L"��ʾ", 0);
						usernow.operation(op - 1, 2, f, "", n * 5 + i, 2);//ɾ��������
						CHARTOTCHAR(h.data());
						MessageBox(GetForegroundWindow(), ss, L"��ʾ", 0);//չʾ�����󷢲��˵ĵĵ绰
						Menu_Need(op, 0);//ˢ�¸ý���
					}
				}
			}
			for (int i = 0; i <= goucnt; i++) {
				if (m.x >= 365 && m.x <= 800 && m.y >= 48 + 100 * i && m.y <= 98 + 100 * i) {
					CHARTOTCHAR(usernow.operation(op - 1, 3, "", "", n * 5 + i, 4).data());//���ÿ������չʾ��
					MessageBox(GetForegroundWindow(), ss, L"����", 0);//չʾ����ľ�������
				}
			}
			if (m.x >= 45 && m.x <= 105 && m.y >= 463 && m.y <= 523) {//�����������ť
				Menu_Publish(op);//���뷢������
				Menu_Need(op, 0);//ˢ�½���
			}
			else if (m.x >= 143 && m.x <= 203 && m.y >= 463 && m.y <= 523) {//����˳���ť
				usernow.ending();//����ǰ�������ݶ����ļ�
				Begin();//�ص�������
			}
			else if (m.x >= 915 && m.x <= 955 && m.y >= 228 && m.y <= 318) {//���������ť
				TCHAR temp[LEN];
				InputBox(temp, LEN, L"������Ҫ�����ı���", L"����", 0, 0, 0, 1);//��������������ı���
				if (usernow.operation(op - 1, 4, TCHARTOCHAR(temp), "", 0, 0) == "a") {//�ж��Ƿ��и�����
					MessageBox(GetForegroundWindow(), L"�����ɹ�", L"��ʾ", 0);
					string a = usernow.detail(op - 1, TCHARTOCHAR(temp), 1);
					string b = usernow.detail(op - 1, TCHARTOCHAR(temp), 2);
					string c = usernow.detail(op - 1, TCHARTOCHAR(temp), 3);
					string d = usernow.detail(op - 1, TCHARTOCHAR(temp), 4);
					string e = "����������:" + a + "\n" + "�������ֻ�����:" + b + "\n" + "��Ϣ����:" + c + "\n" + "��Ϣ����:" + d + "\n";
					int iLength;//����������ص�������Ϣ
					TCHAR tmp[] = _T("w");
					iLength = MultiByteToWideChar(CP_ACP, 0, e.data(), -1, NULL, 0);
					MultiByteToWideChar(CP_ACP, 0, e.data(), -1, tmp, iLength);//��������Ϣת��ΪTCHAR����
					MessageBox(GetForegroundWindow(), tmp, L"������Ϣ", 0);//չʾ������Ϣ
					int flag = MessageBox(GetForegroundWindow(), L"�Ƿ���ܴ�����Ϣ", L"��ʾ", 1);
					if (flag == 1) {
						usernow.operation(op - 1, 2, TCHARTOCHAR(temp), "", 0, 0);//���������Ϣ��ɾ��������
						Menu_Need(op, 0);//��ˢ�½���
					}
					Menu_Need(op, n);//�������򲻽��в���
				}
				else {
					MessageBox(GetForegroundWindow(), L"��ר��δ�ҵ������Ϣ", L"��ʾ", 0);//���������������ʾ
				}
			}
			else if (m.x >= 915 && m.x <= 955 && m.y >= 68 && m.y <= 158) {//�����һҳ
				if (n == 0) {//n=0������ҳ
					MessageBox(GetForegroundWindow(), L"��ǰ������ҳ", L"��ʾ", 0);//��ʾ����һҳ
				}
				else {
					Menu_Need(op, n - 1);//���������һҳ
				}
			}
			else if (m.x >= 915 && m.x <= 955 && m.y >= 388 && m.y <= 478) {
				if (cnt == usernow.tasknumber(op - 1)) {//�����ý���������Ѿ����ڸ������������������
					MessageBox(GetForegroundWindow(), L"��ǰ����ĩҳ", L"��ʾ", 0);//��˵���Ѿ�����ĩҳ
				}
				else {
					Menu_Need(op, n + 1);//���������һҳ
				}
			}
		}
	}
}
void Menu_Publish(int op) {//������op�����͵�����
	bool flag = InputBox(diversity, 2, L"��ѡ�����뷢��������\n1-���Ϸ���;2-��ݴ���;3-��Ʒ����;4-����ƽ̨", L"����", 0, 0, 0, 0);
	if (!flag) {//���ȡ����رնԻ���
		Menu_Need(op, 0);
		return;
	}
	while (TCHARTOCHAR(diversity)[0] < '1' || TCHARTOCHAR(diversity)[0] > '4') {//����ǹ涨����
		flag = InputBox(diversity, 2, L"������1-4�ڵ�����", L"��ʾ", 0, 0, 0, 1);
		if (!flag) {//���ȡ����رնԻ���
			Menu_Need(op, 0);
			return;
		}
	}
	InputBox(title, LEN, L"�����뷢�����ݵı���", L"����", 0, 0, 0, 1);
	InputBox(content, 50, L"�����뷢��������", L"����", 0, 0, 0, 1);
	usernow.operation((TCHARTOCHAR(diversity)[0] - 49), 1, TCHARTOCHAR(title), TCHARTOCHAR(content), 0, 0);//��������
	MessageBox(GetForegroundWindow(), L"�����ɹ�", L"��ʾ", 0);
}
int main() {
	mciSendString(L"open bgm.mp3 alias start", 0, 0, 0);
	mciSendString(L"play start repeat", NULL, 0, NULL);
	TCHAR fileName[] = L"BGM1.mp3";
	TCHAR shortName[MAX_PATH];
	GetShortPathName(fileName, shortName, sizeof(shortName) / sizeof(TCHAR));
	//printf("shortName = %s\n",shortName);
	TCHAR cmd[MAX_PATH + 10];
	wsprintf(cmd, "play %s", shortName);
	//printf("cmd = %s\n",cmd);
	mciSendString(cmd, NULL, 0, NULL);
	//mciSendString("play SOMEON~1.mp3",NULL, 0, NULL); //һ�仰����mp3
	TCHAR volume[256]; // ����(�ַ���)
	int nVolume; // ����(����)
	wsprintf(cmd, "status %s volume", fileName); // szPath Ϊ���ֵ�·��
	mciSendString(cmd, volume, sizeof(volume), 0); // ��ȡ��ǰ������ volume �ַ�����
	nVolume = atoi(volume); // �ַ���ת��Ϊ����
	wsprintf(cmd, "setaudio %s volume to %i", fileName, nVolume - 200); // ����ý��������������� 200
	mciSendString(cmd, "", 0, NULL); // ִ��ý������
	Begin();
}