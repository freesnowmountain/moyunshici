#include<stdio.h>
#include<graphics.h>
#include<conio.h>
#include<stdlib.h>
#include<mmsystem.h>//ý������
#pragma comment(lib,"Winmm.lib")
const int rows = 16, cols = 16;//��ʼ����Ϸ�����С
int i = 0, j = 0;
int panduan = 0;
IMAGE box, dbox, character, blank, ball, wall, background,box2,box3,box4,box5,box6,box7,box8,box9,box10;
//0���յأ�1��ǽ��3��Ŀ�ĵأ�4�����ӣ�5����
//��ʼ����Ϸ��ʼ����
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
���Խ���ӡѭ��������ɾ�������Դ�ӡһ������
ʤ���жϳ��˷�Χ�ĳ�16����������

��ӡһ�����֣����¿�ʼ�����Ͻǣ�
�˳������Ͻǣ�
*/
void InitGame()
{
	mciSendString("open ./dizhi.mp3", 0, 0, 0);//���
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
//��Ϸ����
void PlayGmae()
{
	char cUser;
	while (1)
	{
		//��ȡ��ɫλ��
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
		//��Ϸͨ����ʾ
		if (map[i][j + 1] == 7 && map[i - 1][j + 1] == 7 && map[i - 2][j + 1] == 7)
		{
			//����һ��ʫ�ʱ���
			loadimage(&background, "background.jpg", rows * 64, cols * 64);
			cleardevice();
			putimage(0, 0, &background);
			settextcolor(RGB(0, 128, 255));
			setbkmode(TRANSPARENT);
			settextstyle(50, 0, "��������");
			outtextxy(120, 200, "��ϲ�㣡�����ˣ�");
			outtextxy(220, 260, "�������");
			//sleep(100);Ȼ�����ʫ�ʽ��ܺ���
			break;
		}
		//������Ϸ��ʼ����
		//������Ϸ��ʼ����
		InitGame();
		//¼���û�����
		cUser = _getch();
		//�жϰ���
		switch (cUser)
		{
			//�ϼ�
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
			//�¼�
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
			//���
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
			//�Ҽ�
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
//������
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
	loadimage(&image, "./QQͼƬ20220408204502.jpg", 500, 750);
	putimage(0, 0, &image);
	setbkmode(TRANSPARENT);
	settextcolor(RGB(111, 222, 147));//����������ɫ
	settextstyle(40, 0, _T("������κ"));//�����ֺš�����
	outtextxy(150, 175, "��ʼ��Ϸ");
	outtextxy(150, 250, "��Ϸ����");
	outtextxy(150, 325, "�˳���Ϸ");
	MOUSEMSG m;
	while (1) {
		m = GetMouseMsg();
		if (m.x >= 150 && m.x <= 150 + textwidth("��ʼ��Ϸ") && m.y > 175 && m.y <= 175 + textheight("��ʼ��Ϸ")) {

			if (m.uMsg == WM_LBUTTONDOWN) {		//�������������ʵ����Ӧ����.
				moshi();
			}
		}
		if (m.x >= 150 && m.x <= 150 + textwidth("��Ϸ����") && m.y > 250 && m.y <= 250 + textheight("��Ϸ����")) {
			if (m.uMsg == WM_LBUTTONDOWN) {		//�������������ʵ����Ӧ����.
				outtextxy(120, 175, "��ʼ��Ϸ");
			}
		}
		if (m.x >= 150 && m.x <= 150 + textwidth("�˳���Ϸ") && m.y > 325 && m.y <= 325 + textheight("�˳���Ϸ")) {
			if (m.uMsg == WM_LBUTTONDOWN) {		//�������������ʵ����Ӧ����.
				outtextxy(410, 175, "��ʼ��Ϸ");
			}
		}
	}
	// ��������˳�
	getchar();
}
void moshi() {
	closegraph();
	cleardevice();
	initgraph(500, 750, 0);
	IMAGE image2;
	loadimage(&image2, "./QQͼƬ20220408204521.jpg", 500, 750);//ͼƬ����
	putimage(0, 0, &image2);
	setbkmode(TRANSPARENT);
	settextcolor(RGB(111, 222, 147));//����������ɫ
	settextstyle(40, 0, _T("������κ"));//�����ֺš�����
	outtextxy(150, 175, "������ʫ");
	outtextxy(150, 250, "���Ծ���");
	outtextxy(150, 325, "�δ�");
	outtextxy(150, 400, "����������");
	MOUSEMSG msg;
	while (1) {
		msg = GetMouseMsg();
		if (msg.x >= 150 && msg.x <= 150 + textwidth("������ʫ") && msg.y > 175 && msg.y <= 175 + textheight("��ʼ��Ϸ")) {
			if (msg.uMsg == WM_LBUTTONDOWN) {		//�������������ʵ����Ӧ����.
				game();//��Ϸ����
			}
		}
		if (msg.x >= 150 && msg.x <= 150 + textwidth("���Ծ���") && msg.y > 250 && msg.y <= 250 + textheight("���Ծ���")) {
			if (msg.uMsg == WM_LBUTTONDOWN) {		//�������������ʵ����Ӧ����.
				songci();//��Ϸ����
			}
		}
		if (msg.x >= 150 && msg.x <= 150 + textwidth("�δ�") && msg.y > 325 && msg.y <= 325 + textheight("�δ�")) {
			if (msg.uMsg == WM_LBUTTONDOWN) {		//�������������ʵ����Ӧ����.
				songci();//��Ϸ����
			}
		}
		if (msg.x >= 150 && msg.x <= 150 + textwidth("������ҳ��") && msg.y > 400 && msg.y <= 400 + textheight("������ҳ��")) {
			if (msg.uMsg == WM_LBUTTONDOWN) {		//�������������ʵ����Ӧ����.
				chushi();
			}
		}
	}


}
void songci() {
	//������δʺ���������
	HWND hn = GetHWnd();
	MessageBox(hn, "��ģʽ���ڿ�����", "��ʾ", MB_OKCANCEL);
}
void music() {
	mciSendString("open ./dizhi", 0, 0, 0);
	mciSendString("play ./dizhi", 0, 0, 0);

}
//�ر��������֣�����һ������
void close() {
	mciSendString("close ./background.mp3", 0, 0, 0);
}
//���е����ֶ������¼

void game() {
	initgraph(rows * 64, cols * 64);//��ʼ������С
	loadimage(&background, "background.jpg", rows * 64, cols * 64);//������Ϸ����
	putimage(0, 0, &background);
}