#include <stdlib.h>
#include <graphics.h>
#include <conio.h>
#include <windows.h>
#include <mmsystem.h>
#pragma comment (lib, "winmm.lib")
#include"login.h"
#include"demand.h"

const int LEN=15;//长度限制
const int HEIGHT = 990;//界面长度
const int WIDTH = 556.5;//界面宽度
TCHAR account[LEN], password[LEN], phone[LEN], name[LEN];//账号、密码、手机、姓名
TCHAR diversity[2], title[LEN], content[50];//diversity[0]储存需求种类、需求标题、需求内容
TCHAR ss[] = _T("w");//char转为TCHAR的媒介数组，调用函数后ss为参数的TCHAR形式
string number[1000];//需求编号
string element[10] = { "0","1","2","3","4","5","6","7","8","9" };//组成需求编号的元素
login usernow;//当前菜单界面的登录账号

char* TCHARTOCHAR(LPWSTR);//将TCHAR类型的数组转换为char类型数组
void CHARTOTCHAR(const char*);//将char类型的数组转换为TCHAR类型数组
void Begin();//起始界面
void Register();//注册流程
void Login();//登录界面
void Login_Word();//登录界面文字显示
void Login_Change();//登录界面登录取消按钮变色
void Login_Inputbox();//登录界面绘制输入框
void Login_Cursor1();//登录界面账号栏光标闪烁
void Login_Cursor2();//登录界面密码栏光标闪烁
void Login_Input1();//登录界面账号输入
void Login_Input2();//登录界面密码输入
void Menu_Initial();//进入菜单界面
void Menu_Need(int,int);//菜单界面需求展示
void Menu_Publish(int);//菜单界面发布需求

struct btNode {
	int x, y;
	wchar_t text[20];//内容
	int status;//默认为0，按下按钮时为1
};//按钮
btNode Node[5] = {
	{30,50,L"资料分享",0},{30,50,L"资料分享",0},
	{30,150,L"快递代拿",0},
	{30,250,L"商品交易",0},
	{30,350,L"交友平台",0},
};//主界面按钮信息
void DrawBtn(int k) {
	btNode t = Node[k];
	settextcolor(BLACK);
	settextstyle(45, 0, _T("迷你简中特广告"));
	setlinecolor(RGB(50,50,75));
	setlinestyle(PS_SOLID, 2, NULL, 0);//设置文字、边框的格式及颜色
	if (t.status == 0) {
		roundrect(t.x, t.y - 8, t.x + 193, t.y + 55, 20, 20);//起始为无填充按钮
	}
	else {
		setfillcolor(RGB(130,127,133));
		fillroundrect(t.x, t.y - 8, t.x + 193, t.y + 55, 20, 20);//点击时status=1，转换为填充按钮
	}
	setbkmode(TRANSPARENT);
	outtextxy(t.x + 13, t.y + 2, t.text);//输出按钮文字
}//绘制按钮
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
	loadimage(NULL, _T("0.jpg"), HEIGHT, WIDTH);//初始化界面
	settextcolor(BLACK);
	settextstyle(30 * 1.5, 0, _T("华文彩云"), 0, 0, 750, 0, 0, 0);//设置文字格式
	TCHAR s2[] = _T("登录");
	outtextxy(295 * 1.5, 151 * 1.5, s2);//输出文字
	TCHAR s3[] = _T("注册");
	outtextxy(295 * 1.5, 225 * 1.5, s3);
	TCHAR s4[] = _T("退出");
	outtextxy(295 * 1.5, 299 * 1.5, s4);
	settextcolor(RED);
	settextstyle(40 * 1.5, 0, _T("楷体"), 0, 0, 1000, 0, 0, 0);//设置文字格式
	TCHAR s1[] = _T("学生需求服务系统");
	outtextxy(160 * 1.5, 70 * 1.5, s1);
	settextstyle(15 * 1.5, 0, _T("方正少儿简体"), 0, 0, 0, 0, 0, 0);
	TCHAR s0[] = _T("By：第41小组");
	outtextxy(568 * 1.5, 350 * 1.5, s0);
	FlushMouseMsgBuffer();//清空鼠标操作缓存区
	MOUSEMSG m;
	while (1)
	{
		m = GetMouseMsg();//获取鼠标信息
		if (m.uMsg == WM_LBUTTONDOWN) {//单击左键后判断各个按钮的坐标进入不同界面
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
	closegraph();//关闭窗口
}
void Register() {
	login user;//声明一个未初始化的对象，用于后续储存注册人员信息
	int i = InputBox(account, LEN, L"请输入账号(不支持特殊符号或中文)", L"注册", 0, 0, 0, 0);//弹出对话框
	user.changea(TCHARTOCHAR(account));//储存账号
	if (i == 0) {//点击了右上角关闭键或选择了取消
		MessageBox(GetForegroundWindow(), L"注册失败", L"提示", 0);//弹出消息，提示注册失败
		Begin();//回到主页面
	}
	else {
		while (user.verify2()) {//判断账号是否已存在，不存在则跳出循环
			InputBox(account, LEN, L"账号已被注册，请重新输入", L"提示", 0, 0, 0, 1);
			user.changea(TCHARTOCHAR(account));//存入账号
		}
		int len1;//用于判断账号长度
		len1 = lstrlen(account);
		while (len1 < 6) {//当账号长度大于等于6时跳出循环
			InputBox(account, LEN, L"账号长度需大于等于六位，请重新输入", L"提示", 0, 0, 0, 1);
			len1 = lstrlen(account);
		}
		user.changea(TCHARTOCHAR(account));//更新账号
		int j = InputBox(password, LEN, L"请输入密码(不支持特殊符号或中文)", L"注册", 0, 0, 0, 0);
		int len2 = lstrlen(password);//判断密码长度
		if (j == 0) {//输入密码时点击取消或关闭窗口则终止注册
			MessageBox(GetForegroundWindow(), L"注册失败", L"提示", 0);
			Begin();
		}
		else {//当密码长度大于等于6时跳出循环
			while (len2 < 6) {
				InputBox(password, LEN, L"密码长度需大于等于六位，请重新输入", L"提示", 0, 0, 0, 1);
				len2 = lstrlen(password);
			}
			user.changepa(TCHARTOCHAR(password));//更新密码
			MessageBox(GetForegroundWindow(), L"注册成功", L"提示", 0);//注册成功
		}
	}
	MessageBox(GetForegroundWindow(), L"请开始完善个人信息", L"提示", 0);
	InputBox(name, LEN, L"请输入姓名", L"个人信息", 0, 0, 0, 1);
	user.changen(TCHARTOCHAR(name));//将输入的姓名储存
	InputBox(phone, LEN, L"请输入手机号码", L"个人信息", 0, 0, 0, 1);
	int len3 = lstrlen(phone);//判断手机号码长度
	while (len3 != 11) {//当手机长度为11时跳出循环
		InputBox(phone, LEN, L"请输入正确的手机号码(11位)", L"个人信息", 0, 0, 0, 1);
		len3 = lstrlen(phone);
	}
	user.changeph(TCHARTOCHAR(phone));//更新手机号码
	MessageBox(GetForegroundWindow(), L"个人信息填写成功", L"提示", 0);
	user.regist();//将个人信息全部写入文件
	Login();//成功注册后进入登录界面
}
void Login() {
	IMAGE LOGIN;
	initgraph(HEIGHT, WIDTH);
	loadimage(&LOGIN, _T("0.jpg"), HEIGHT, WIDTH);
	SetWorkingImage(&LOGIN);////设定当前的绘图设备为LOGIN对象
	login user;//声明一个对象用于记录登录时输入的账号密码
	Login_Word();//将登录界面的文本导入
	Login_Inputbox();//将登录界面的输入框导入
	SetWorkingImage(); //设定当前的绘图设备为默认绘图窗口
	putimage(0, 0, &LOGIN);//在当前设备绘制指定图像，即在默认绘图窗口绘制LOGIN对象
	settextstyle(18 * 1.5, 0, L"宋体", 0, 0, 0, 0, 0, 0);
	setbkmode(OPAQUE); //设置当前设备图案填充和文字输出时的背景模式，OPAQUE表示背景用当前背景色填充
	setbkcolor(RGB(255, 255, 255));//设置默认背景颜色
	MOUSEMSG m;
	while (1) {
		m = GetMouseMsg();
		if (m.uMsg == WM_LBUTTONDOWN) {
			if (m.x <= 426 * 1.5 && m.x >= 353 * 1.5 && m.y <= 290 * 1.5 && m.y >= 255 * 1.5) {
				Begin();//点击取消则回到初始界面
				break;
			}
			else if (m.x <= 298 * 1.5 && m.x >= 225 * 1.5 && m.y <= 290 * 1.5 && m.y >= 255 * 1.5) {
				MessageBox(GetForegroundWindow(), L"请输入账号", L"提示", 0);//点击登录则提示先输入账号
			}
			else if (m.x <= 425 * 1.5 && m.x >= 275 * 1.5 && m.y <= 191 * 1.5 && m.y >= 161 * 1.5) {//点击输入框
				while (_kbhit()) {//清空键盘消息缓冲区，避免输入前的键盘消息直接被导入输入框
					_getch();
				}
				Login_Cursor1();//控制光标闪烁，检测到键盘输入后结束闪烁
				break;//结束闪烁后退出鼠标判断
			}
		}
	}
	Login_Input1();//根据键盘消息在账号输入框显示账号，点击回车键或到达指定输入位数后结束
	user.changea(TCHARTOCHAR(account));//将账号输入login
	Login_Cursor2();//密码输入框闪烁，检测到键盘输入后结束闪烁
	Login_Input2();//根据键盘消息在密码输入框显示密码（*号显示），点击回车键或到达指定输入位数后结束
	user.changepa(TCHARTOCHAR(password));//将密码输入login
	Login_Change();//填充登录、取消键位
	FlushMouseMsgBuffer();//清空鼠标消息缓冲区
	while (_kbhit()) {//清空键盘消息缓冲区
		_getch();
	}
	while (1) {
		m = GetMouseMsg();
		if (m.uMsg == WM_MOUSEMOVE) {
			if (m.x >= 225 * 1.5 && m.x <= 298 * 1.5 && m.y >= 255 * 1.5 && m.y <= 290 * 1.5) {//鼠标移动到登录键时，登录二字变为红色
				settextcolor(RGB(255, 0, 0));
				outtextxy(236 * 1.5, 260 * 1.5, _T("登录"));
			}
			else if (m.x >= 353 * 1.5 && m.x <= 426 * 1.5 && m.y >= 255 * 1.5 && m.y <= 290 * 1.5) {//鼠标移动到取消键时，取消二字变为红色
				settextcolor(RGB(255, 0, 0));
				outtextxy(364 * 1.5, 260 * 1.5, _T("取消"));
			}
			else {
				settextcolor(BLACK);//在其他位置则两个键位文字都为黑色
				outtextxy(236 * 1.5, 260 * 1.5, _T("登录"));
				outtextxy(364 * 1.5, 260 * 1.5, _T("取消"));
			}
		}
		else if (m.uMsg == WM_LBUTTONDOWN) {
			if (m.x <= 298 * 1.5 && m.x >= 225 * 1.5 && m.y <= 290 * 1.5 && m.y >= 255 * 1.5) {//左键单击登录键
				if (user.verify1()) {//账号密码匹配
					usernow = user;//将当前user的账号密码赋值给全局对象usernow以便在需求界面的使用
					usernow.in();//查到该账号对应的手机和姓名并赋值给usernow
					Menu_Initial();//进入需求界面
					break;
				}
				MessageBox(GetForegroundWindow(), L"密码错误或账号不存在！", L"提示", 0);//账号密码不匹配则进行提示
				Login();//刷新登录界面重新登录
				break;
			}
			else if (m.x <= 426 * 1.5 && m.x >= 353 * 1.5 && m.y <= 290 * 1.5 && m.y >= 255 * 1.5) {
				Begin();//点击取消则回到初始界面
				break;
			}
		}
	}
}
void Login_Word() {
	setbkmode(TRANSPARENT);//设置当前设备图案填充和文字输出时的背景模式为透明
	settextstyle(40 * 1.5, 0, L"楷体", 0, 0, 1000, 0, 0, 0);
	settextcolor(RED);
	TCHAR s1[] = _T("用户登录");
	outtextxy(245 * 1.5, 55 * 1.5, s1);
	setlinecolor(BLACK);
	rectangle(175 * 1.5, 125 * 1.5, 475 * 1.5, 315 * 1.5);//外围矩形框
	setfillcolor(RGB(190, 190, 190));
	rectangle(225 * 1.5, 255 * 1.5, 298 * 1.5, 290 * 1.5);//登录框
	rectangle(353 * 1.5, 255 * 1.5, 426 * 1.5, 290 * 1.5);//取消框
	settextstyle(25 * 1.5, 0, L"宋体", 0, 0, 0, 0, 0, 0);
	settextcolor(BLACK);
	outtextxy(215 * 1.5, 162 * 1.5, _T("账号"));
	outtextxy(215 * 1.5, 205 * 1.5, _T("密码"));
	settextstyle(25 * 1.5, 0, L"宋体", 0, 0, 500, 0, 0, 0);
	outtextxy(236 * 1.5, 260 * 1.5, _T("登录"));
	outtextxy(364 * 1.5, 260 * 1.5, _T("取消"));
}
void Login_Change() {
	setbkmode(TRANSPARENT);
	setlinestyle(PS_SOLID, 1, NULL, 0);//设置边框格式
	setlinecolor(BLACK);
	setfillcolor(RGB(190, 190, 190));
	fillrectangle(225 * 1.5, 255 * 1.5, 298 * 1.5, 290 * 1.5);
	fillrectangle(353 * 1.5, 255 * 1.5, 426 * 1.5, 290 * 1.5);
	settextstyle(25 * 1.5, 0, L"宋体", 0, 0, 800, 0, 0, 0);
	settextcolor(BLACK);
	outtextxy(236 * 1.5, 260 * 1.5, _T("登录"));
	outtextxy(364 * 1.5, 260 * 1.5, _T("取消"));
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
void Login_Cursor1()//闪烁光标
{
	while (1) {//如果键盘没有进行输入这循环闪烁
		Login_Inputbox();//画账号密码框
		if (_kbhit()) {//当键盘有反应时_kbhit()会返回一个非零值
			break;//退出闪烁
		}
		Sleep(500);
		setlinestyle(PS_SOLID, 2, NULL, 0);//设置线的样式为PS_SOLID，宽度为2
		line(278 * 1.5, 165 * 1.5, 279 * 1.5, 185 * 1.5);//光标的描绘
		Sleep(500);//延时
	}
}
void Login_Cursor2()//闪烁光标
{
	while (1) {//如果键盘没有进行输入这循环闪烁
		setlinestyle(PS_SOLID, 1, NULL, 0);
		bar(275 * 1.5, 202 * 1.5, 425 * 1.5, 232 * 1.5);
		rectangle(275 * 1.5, 202 * 1.5, 425 * 1.5, 232 * 1.5);
		if (_kbhit()) {//当键盘有反应时_kbhit()会返回一个非零值
			break;//退出闪烁
		}
		Sleep(500);
		setlinestyle(PS_SOLID, 2, NULL, 0);//设置线的样式为PS_SOLID，宽度为2
		line(278 * 1.5, 206 * 1.5, 279 * 1.5, 226 * 1.5);//光标的描绘
		Sleep(500);//延时
	}
}
void Login_Input1() {
	for (int i = 0; i < LEN; i++) {
		account[i] = _getch();
		outtextxy((277 + 8 * i) * 1.5, 167 * 1.5, account[i]);
		if (account[i] == 8) {//使用delete键
			account[i] = 0;
			outtextxy((277 + 8 * i) * 1.5, 167 * 1.5, L"  ");//输出空白挡住delete键
			if (i > 0) outtextxy((277 + 8 * (i - 1)) * 1.5, 167 * 1.5, L"  ");//输出空白挡住前一个字符以示删除
			i -= 2;
			if (i < 0) {
				i = -1;
			}
		}
		else if (account[i] == 13) {//使用回车键
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
		outtextxy((277 + 8 * j) * 1.5, 208 * 1.5, L'*');//输出*号
		if (password[j] == 8) {//使用delete键
			password[j] = 0;
			outtextxy((277 + 8 * j) * 1.5, 208 * 1.5, L"  ");//输出空白挡住delete键
			if(j>0) outtextxy((277 + 8 * (j - 1)) * 1.5, 208 * 1.5, L"  ");//输出空白挡住前一个字符以示删除
			j -= 2;
			if (j < 0) {
				j = -1;
			}
		}
		else if (password[j] == 13) {//使用回车键
			outtextxy((277 + 8 * j) * 1.5, 208 * 1.5, L"  ");
			password[j] = '\0';
			break;
		}
	}
}
void Menu_Initial() {
	usernow.init();//将需求文件全部导入链表
	initgraph(HEIGHT, WIDTH);//绘制需求界面
	Menu_Need(1, 0);//调用第一个需求的第一页
}
void Menu_Need(int op,int n) {//op表示第几个需求，n表示第n+1页
	cleardevice();//用当前背景色清空绘图设备，并将当前点移至 (0, 0)
	setbkmode(TRANSPARENT);
	loadimage(NULL, _T("0.jpg"), HEIGHT, WIDTH, 1);
	setlinestyle(PS_DASH, 2, NULL, 0);
	setlinecolor(BLACK);
	circle(75, 493, 30);//发布按钮
	circle(173, 493, 30);//退出按钮
	for (int j = 1; j < 5; j++) {
		if (j == op) Node[j].status = 1;//改界面展示第op个需求，则将该按钮的状态更改
		else Node[j].status = 0;
		DrawBtn(j);//画出所有按钮
	}
	settextcolor(BLACK);
	settextstyle(30, 0, _T("方正少儿简体"), 0, 0, 0, 0, 0, 0);
	outtextxy(50, 480, _T("发布"));//发布文字
	outtextxy(148, 480, _T("退出"));//退出文字
	setlinestyle(PS_DASHDOT, 2, NULL, 0);
	line(253, 0, 253, WIDTH);
	line(250, 0, 250, WIDTH);//设置分界线
	int cnt = 5 * n;//到目前为止共有需求数量
	int goucnt = 0;//表示该页的需求需求数量-1
	for (int i = 0; i < 5 ; i++, cnt++) {//展示需求
		if (cnt == usernow.tasknumber(op-1)) break;//到目前为止的需求等于该链表拥有的所有需求则结束展示
		settextcolor(RED);//编号颜色
		number[cnt + 1] = element[(int)((cnt + 1) / 10)] + element[(int)(cnt + 1) % 10];//生成当前页第i+1个需求的编号
		CHARTOTCHAR(number[cnt+1].data());//将编号转为TCHAR型
		outtextxy(307, 57 + 100 * i, ss);//输出编号
		settextcolor(BLACK);
		setlinecolor(BLACK);
		setlinestyle(PS_SOLID, 2, NULL, 0);
		setfillcolor(RGB(130, 127, 133));
		circle(848, 73 + 100 * i, 25);
		outtextxy(834, 60 + 100 * i, _T("√"));//画出接受需求的按钮
		setlinestyle(PS_DASHDOTDOT, 2, NULL, 0);
		rectangle(365, 48 + 100 * i, 800, 98 + 100 * i);//展示需求的边框
		CHARTOTCHAR(usernow.operation(op-1, 3, " ", " ", cnt, 3).data());//将标题转为TCHAR型
		outtextxy(374, 59 + 100 * i, ss);//输出需求的标题
		goucnt = i;//更新该页到目前为止的需求数量-1
	}
	for (int i = 0; i < 3; i++) {//画出上下页和搜索的按钮边框
		setlinecolor(RGB(51,56,75));
		setlinestyle(PS_SOLID, 1, NULL, 0);
		setfillcolor(RGB(130, 127, 133));
		fillrectangle(915, 68 + 160 * i, 955, 158 + 160 * i);
	}
	outtextxy(922, 70, _T("上"));
	outtextxy(922, 98, _T("一"));
	outtextxy(922, 126, _T("页"));
	outtextxy(922, 240, _T("搜"));
	outtextxy(922, 280, _T("索"));
	outtextxy(922, 392, _T("下"));
	outtextxy(922, 420, _T("一"));
	outtextxy(922, 448, _T("页"));
	MOUSEMSG m;
	while (1) {
		m = GetMouseMsg();//获取鼠标信息
		if (m.uMsg == WM_LBUTTONDOWN) {
			for (int i = 1; i < 5; i++) {
				if (m.x >= Node[i].x && m.x <= Node[i].x + 193 && m.y >= Node[i].y - 8 && m.y <= Node[i].y + 55) {//点击到第i个需求按钮
					Menu_Need(i, 0);//转跳至第i个需求展示
					break;
				}
			}
			for (int i = 0; i <= goucnt; i++) {//点击到接受需求按钮
				if (m.x >= 823 && m.x <= 873 && m.y >= 48 + 100 * i && m.y <= 98 + 100 * i) {
					string a = "这是", b = "发布的消息，是否接受？", c = "发布人的电话为";
					string d = usernow.operation(op - 1, 3, "", "", n * 5 + i, 1);
					string e = usernow.operation(op - 1, 3, "", "", n * 5 + i, 2);
					string f = usernow.operation(op - 1, 3, "", "", n * 5 + i, 3);
					string g = a + d + b;
					string h = c + e;
					CHARTOTCHAR(g.data());
					int flag = MessageBox(GetForegroundWindow(), ss, L"提示", 1);//提示这是某个人发布的需求
					if (flag==1) {
						MessageBox(GetForegroundWindow(), L"接受成功！", L"提示", 0);
						usernow.operation(op - 1, 2, f, "", n * 5 + i, 2);//删除该需求
						CHARTOTCHAR(h.data());
						MessageBox(GetForegroundWindow(), ss, L"提示", 0);//展示改需求发布人的的电话
						Menu_Need(op, 0);//刷新该界面
					}
				}
			}
			for (int i = 0; i <= goucnt; i++) {
				if (m.x >= 365 && m.x <= 800 && m.y >= 48 + 100 * i && m.y <= 98 + 100 * i) {
					CHARTOTCHAR(usernow.operation(op - 1, 3, "", "", n * 5 + i, 4).data());//点击每个需求展示框
					MessageBox(GetForegroundWindow(), ss, L"详情", 0);//展示需求的具体内容
				}
			}
			if (m.x >= 45 && m.x <= 105 && m.y >= 463 && m.y <= 523) {//点击发布需求按钮
				Menu_Publish(op);//进入发布函数
				Menu_Need(op, 0);//刷新界面
			}
			else if (m.x >= 143 && m.x <= 203 && m.y >= 463 && m.y <= 523) {//点击退出按钮
				usernow.ending();//将当前链表数据读入文件
				Begin();//回到主界面
			}
			else if (m.x >= 915 && m.x <= 955 && m.y >= 228 && m.y <= 318) {//点击搜索按钮
				TCHAR temp[LEN];
				InputBox(temp, LEN, L"请输入要搜索的标题", L"搜索", 0, 0, 0, 1);//输入所搜索需求的标题
				if (usernow.operation(op - 1, 4, TCHARTOCHAR(temp), "", 0, 0) == "a") {//判断是否有该需求
					MessageBox(GetForegroundWindow(), L"搜索成功", L"提示", 0);
					string a = usernow.detail(op - 1, TCHARTOCHAR(temp), 1);
					string b = usernow.detail(op - 1, TCHARTOCHAR(temp), 2);
					string c = usernow.detail(op - 1, TCHARTOCHAR(temp), 3);
					string d = usernow.detail(op - 1, TCHARTOCHAR(temp), 4);
					string e = "发布人姓名:" + a + "\n" + "发布人手机号码:" + b + "\n" + "消息标题:" + c + "\n" + "消息内容:" + d + "\n";
					int iLength;//读入需求相关的所有信息
					TCHAR tmp[] = _T("w");
					iLength = MultiByteToWideChar(CP_ACP, 0, e.data(), -1, NULL, 0);
					MultiByteToWideChar(CP_ACP, 0, e.data(), -1, tmp, iLength);//将所有信息转化为TCHAR类型
					MessageBox(GetForegroundWindow(), tmp, L"具体信息", 0);//展示所有信息
					int flag = MessageBox(GetForegroundWindow(), L"是否接受此条消息", L"提示", 1);
					if (flag == 1) {
						usernow.operation(op - 1, 2, TCHARTOCHAR(temp), "", 0, 0);//如果接受信息则删除该需求
						Menu_Need(op, 0);//并刷新界面
					}
					Menu_Need(op, n);//不接受则不进行操作
				}
				else {
					MessageBox(GetForegroundWindow(), L"该专栏未找到相关消息", L"提示", 0);//搜索不到则进行提示
				}
			}
			else if (m.x >= 915 && m.x <= 955 && m.y >= 68 && m.y <= 158) {//点击上一页
				if (n == 0) {//n=0代表首页
					MessageBox(GetForegroundWindow(), L"当前已是首页", L"提示", 0);//提示无上一页
				}
				else {
					Menu_Need(op, n - 1);//否则进入上一页
				}
			}
			else if (m.x >= 915 && m.x <= 955 && m.y >= 388 && m.y <= 478) {
				if (cnt == usernow.tasknumber(op - 1)) {//若到该界面的需求已经等于该需求链表的所有需求
					MessageBox(GetForegroundWindow(), L"当前已是末页", L"提示", 0);//则说明已经到达末页
				}
				else {
					Menu_Need(op, n + 1);//否则进入下一页
				}
			}
		}
	}
}
void Menu_Publish(int op) {//发布第op个类型的需求
	bool flag = InputBox(diversity, 2, L"请选择你想发布的内容\n1-资料分享;2-快递代拿;3-商品交易;4-交友平台", L"发布", 0, 0, 0, 0);
	if (!flag) {//点击取消或关闭对话框
		Menu_Need(op, 0);
		return;
	}
	while (TCHARTOCHAR(diversity)[0] < '1' || TCHARTOCHAR(diversity)[0] > '4') {//输入非规定数字
		flag = InputBox(diversity, 2, L"请输入1-4内的数字", L"提示", 0, 0, 0, 1);
		if (!flag) {//点击取消或关闭对话框
			Menu_Need(op, 0);
			return;
		}
	}
	InputBox(title, LEN, L"请输入发布内容的标题", L"发布", 0, 0, 0, 1);
	InputBox(content, 50, L"输入想发布的内容", L"发布", 0, 0, 0, 1);
	usernow.operation((TCHARTOCHAR(diversity)[0] - 49), 1, TCHARTOCHAR(title), TCHARTOCHAR(content), 0, 0);//发布需求
	MessageBox(GetForegroundWindow(), L"发布成功", L"提示", 0);
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
	//mciSendString("play SOMEON~1.mp3",NULL, 0, NULL); //一句话播放mp3
	TCHAR volume[256]; // 音量(字符串)
	int nVolume; // 音量(整型)
	wsprintf(cmd, "status %s volume", fileName); // szPath 为音乐的路径
	mciSendString(cmd, volume, sizeof(volume), 0); // 获取当前音量至 volume 字符串中
	nVolume = atoi(volume); // 字符串转化为整型
	wsprintf(cmd, "setaudio %s volume to %i", fileName, nVolume - 200); // 生成媒体命令，设置音量减 200
	mciSendString(cmd, "", 0, NULL); // 执行媒体命令
	Begin();
}