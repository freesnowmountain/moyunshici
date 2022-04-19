#include<stdio.h>
#include<graphics.h>
#include<conio.h>
#include<stdlib.h>
#include<mmsystem.h>//媒体音乐
#pragma comment(lib,"Winmm.lib")
const int rows = 16, cols = 16;//初始化游戏界面大小
int i = 0, j = 0;
int panduan = 0;
IMAGE box, dbox, character, blank, ball, wall, background,box2,box3,box4,box5,box6,box7,box8,box9,box10;
//0：空地，1：墙，3：目的地，4：箱子，5：人
//初始化游戏初始界面
int map[rows][cols] =
{
   {1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0},
   {1,1,1,0,0,0,0,0,0,1,1,1,1,1,1,1},
   {1,1,1,0,0,0,0,0,0,1,1,1,1,1,1,1},
   {1,3,0,0,0,0,0,4,0,0,0,0,1,1,0,0},
   {1,3,0,4,0,0,0,0,0,0,4,0,1,1,0,0},
   {1,3,0,0,0,0,0,5,0,0,0,0,1,1,0,0},
   {1,3,0,0,4,0,0,0,0,0,0,0,1,1,0,0},
   {1,3,1,1,0,0,0,0,4,0,0,0,1,1,0,0},
   {1,3,0,0,0,0,0,0,0,0,0,0,1,1,1,1},
   {1,3,0,0,0,4,0,0,0,0,0,0,1,1,1,1},
   {1,3,0,0,0,0,0,0,0,4,0,0,0,0,1,1},
   {1,3,0,0,0,0,0,1,1,0,0,0,0,0,1,1},
   {1,3,0,0,0,4,0,0,0,0,0,0,0,0,1,1},
   {1,0,4,0,0,0,0,0,0,0,0,0,0,1,1,1},
   {1,0,0,0,0,0,0,0,0,4,0,0,0,1,1,1},
   {1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0}
};
/*
可以将打印循环把箱子删掉，独自打印一遍箱子
胜利判断除了范围改成16，其它不变

打印一个文字，重新开始（右上角）
退出（左上角）
*/
void InitGame()
{
	mciSendString("open ./dizhi.mp3", 0, 0, 0);//填歌
	mciSendString("play ./dizhi.mp3", 0, 0, 0);
	int x, y;
	for (int i = 0; i < 16; i++)
	{
		for (int j = 0; j < 16; j++)
		{
			x = j * 64;
			y = i * 64;
			switch (map[i][j])
			{
			case 0:
				putimage(x, y, &blank);
				break;
			case 1:
				putimage(x, y, &wall);
				break;
			case 3:
				putimage(x, y, &ball);
				break;
			case 4:
				putimage(x, y, &box);
				break;
			case 5:
				putimage(x, y, &character);
				break;
			case 7:
				putimage(x, y, &dbox);
				break;
			case 8:
				putimage(x, y, &character);
				break;
			}
		}
	}
}
//游戏操作
void PlayGmae()
{
	char cUser;
	while (1)
	{
		//读取角色位置
		for (i = 0; i < 16; i++)
		{
			for (j = 0; j < 16; j++)
			{
				if (map[i][j] == 5 || map[i][j] == 8)
					break;
			}
			if (map[i][j] == 5 || map[i][j] == 8)
				break;
		}
		//游戏通关提示
		if (map[i][j + 1] == 7 && map[i - 1][j + 1] == 7 && map[i - 2][j + 1] == 7)
		{
			//插入一张诗词背景
			loadimage(&background, "background.jpg", rows * 64, cols * 64);
			cleardevice();
			putimage(0, 0, &background);
			settextcolor(RGB(0, 128, 255));
			setbkmode(TRANSPARENT);
			settextstyle(50, 0, "华文琥珀");
			outtextxy(120, 200, "恭喜你！过关了！");
			outtextxy(220, 260, "你真棒！");
			//sleep(100);然后进入诗词介绍函数
			break;
		}
		//调用游戏初始函数
		//调用游戏初始函数
		InitGame();
		//录入用户按键
		cUser = _getch();
		//判断按键
		switch (cUser)
		{
			//上键
		case 72:
		case 'w':
		case 'W':
			if (map[i - 1][j] == 0 || map[i - 1][j] == 3)
			{
				map[i - 1][j] += 5;
				map[i][j] -= 5;
			}
			else if (map[i - 1][j] == 4 || map[i - 1][j] == 7)
			{
				if (map[i - 2][j] == 0 || map[i - 2][j] == 3)
				{
					map[i - 2][j] += 4;
					map[i - 1][j] += 1;
					map[i][j] -= 5;
				}
			}
			break;
			//下键
		case 80:
		case 's':
		case 'S':
			if (map[i + 1][j] == 0 || map[i + 1][j] == 3)
			{
				map[i + 1][j] += 5;
				map[i][j] -= 5;
			}
			else if (map[i + 1][j] == 4 || map[i + 1][j] == 7)
			{
				if (map[i + 2][j] == 0 || map[i + 2][j] == 3)
				{
					map[i + 2][j] += 4;
					map[i + 1][j] += 1;
					map[i][j] -= 5;
				}
			}
			break;
			//左键
		case 75:
		case 'a':
		case 'A':
			if (map[i][j - 1] == 0 || map[i][j - 1] == 3)
			{
				map[i][j - 1] += 5;
				map[i][j] -= 5;
			}
			else if (map[i][j - 1] == 4 || map[i][j - 1] == 7)
			{
				if (map[i][j - 2] == 0 || map[i][j - 2] == 3)
				{
					map[i][j - 2] += 4;
					map[i][j - 1] += 1;
					map[i][j] -= 5;
				}
			}
			break;
			//右键
		case 77:
		case 'd':
		case 'D':
			if (map[i][j + 1] == 0 || map[i][j + 1] == 3)
			{
				map[i][j + 1] += 5;
				map[i][j] -= 5;
			}
			else if (map[i][j + 1] == 4 || map[i][j + 1] == 7)
			{
				if (map[i][j + 2] == 0 || map[i][j + 2] == 3)
				{
					map[i][j + 2] += 4;
					map[i][j + 1] += 1;
					map[i][j] -= 5;
				}
			}
			break;
		}
	}
}
//主函数
void chushi();
void moshi();
void songci();
void music();
void close();
void game();
int main()
{
	chushi();//
	return 0;
}
void chushi() {
	initgraph(500, 750, 0);
	mciSendString("open ./dizhi.mp3", NULL, 0, NULL);
	mciSendString("play ./dizhi.mp3", NULL, 0, NULL);
	IMAGE image;
	loadimage(&image, "./QQ图片20220408204502.jpg", 500, 750);
	putimage(0, 0, &image);
	setbkmode(TRANSPARENT);
	settextcolor(RGB(111, 222, 147));//设置字体颜色
	settextstyle(40, 0, _T("华文新魏"));//设置字号、字体
	outtextxy(150, 175, "开始游戏");
	outtextxy(150, 250, "游戏介绍");
	outtextxy(150, 325, "退出游戏");
	MOUSEMSG m;
	while (1) {
		m = GetMouseMsg();
		if (m.x >= 150 && m.x <= 150 + textwidth("开始游戏") && m.y > 175 && m.y <= 175 + textheight("开始游戏")) {

			if (m.uMsg == WM_LBUTTONDOWN) {		//如果按下鼠标左键实现相应功能.
				moshi();
			}
		}
		if (m.x >= 150 && m.x <= 150 + textwidth("游戏介绍") && m.y > 250 && m.y <= 250 + textheight("游戏介绍")) {
			if (m.uMsg == WM_LBUTTONDOWN) {		//如果按下鼠标左键实现相应功能.
				outtextxy(120, 175, "开始游戏");
			}
		}
		if (m.x >= 150 && m.x <= 150 + textwidth("退出游戏") && m.y > 325 && m.y <= 325 + textheight("退出游戏")) {
			if (m.uMsg == WM_LBUTTONDOWN) {		//如果按下鼠标左键实现相应功能.
				outtextxy(410, 175, "开始游戏");
			}
		}
	}
	// 按任意键退出
	getchar();
}
void moshi() {
	closegraph();
	cleardevice();
	initgraph(500, 750, 0);
	IMAGE image2;
	loadimage(&image2, "./QQ图片20220408204521.jpg", 500, 750);//图片待定
	putimage(0, 0, &image2);
	setbkmode(TRANSPARENT);
	settextcolor(RGB(111, 222, 147));//设置字体颜色
	settextstyle(40, 0, _T("华文新魏"));//设置字号、字体
	outtextxy(150, 175, "五言律诗");
	outtextxy(150, 250, "七言绝句");
	outtextxy(150, 325, "宋词");
	outtextxy(150, 400, "返回主界面");
	MOUSEMSG msg;
	while (1) {
		msg = GetMouseMsg();
		if (msg.x >= 150 && msg.x <= 150 + textwidth("五言律诗") && msg.y > 175 && msg.y <= 175 + textheight("开始游戏")) {
			if (msg.uMsg == WM_LBUTTONDOWN) {		//如果按下鼠标左键实现相应功能.
				game();//游戏函数
			}
		}
		if (msg.x >= 150 && msg.x <= 150 + textwidth("七言绝句") && msg.y > 250 && msg.y <= 250 + textheight("七言绝句")) {
			if (msg.uMsg == WM_LBUTTONDOWN) {		//如果按下鼠标左键实现相应功能.
				songci();//游戏函数
			}
		}
		if (msg.x >= 150 && msg.x <= 150 + textwidth("宋词") && msg.y > 325 && msg.y <= 325 + textheight("宋词")) {
			if (msg.uMsg == WM_LBUTTONDOWN) {		//如果按下鼠标左键实现相应功能.
				songci();//游戏函数
			}
		}
		if (msg.x >= 150 && msg.x <= 150 + textwidth("返回主页面") && msg.y > 400 && msg.y <= 400 + textheight("返回主页面")) {
			if (msg.uMsg == WM_LBUTTONDOWN) {		//如果按下鼠标左键实现相应功能.
				chushi();
			}
		}
	}


}
void songci() {
	//鼠标点击宋词后会出来弹窗
	HWND hn = GetHWnd();
	MessageBox(hn, "该模式正在开发中", "提示", MB_OKCANCEL);
}
void music() {
	mciSendString("open ./dizhi", 0, 0, 0);
	mciSendString("play ./dizhi", 0, 0, 0);

}
//关闭所有音乐，打开另一个音乐
void close() {
	mciSendString("close ./background.mp3", 0, 0, 0);
}
//所有的音乐都在这记录

void game() {
	initgraph(rows * 64, cols * 64);//初始画布大小
	loadimage(&background, "background.jpg", rows * 64, cols * 64);//设置游戏背景
	putimage(0, 0, &background);
}