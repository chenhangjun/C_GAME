#include<graphics.h>
#include<conio.h>
#include<math.h>
#include<stdio.h>

#pragma comment(lib, "Winmm.lib")

#define Height 680
#define Width 590

IMAGE img_bk, img_planeNormal1, img_planeNormal2, img_bullet1, img_bullet2;
IMAGE img_enemy1, img_enemy2, img_planeExplode1, img_planeExplode2;
float position_x, position_y, bullet_x, bullet_y, enemy_x, enemy_y;
int isExplode;
int score;
int gameStatus = 0;

void startMenu();
void pauseMenu();
void startup();
void show();
void updateWithoutInput();
void updateWithInput();
void gameover();
void readRecordFile();
void writeRecordFile();

void startMenu()
{
	putimage(0, 0, &img_bk);
	setbkmode(TRANSPARENT);
	settextcolor(BLACK);
	settextstyle(50, 0, _T("黑体"));
	outtextxy(Width * 0.3, Height * 0.2, "1 新游戏");
	outtextxy(Width * 0.3, Height * 0.3, "2 读取游戏存档");
	outtextxy(Width * 0.3, Height * 0.4, "3 退出");

	settextcolor(BLUE);
	settextstyle(30, 0, _T("黑体"));
	outtextxy(Width * 0.25, Height * 0.6, "鼠标移动控制飞机移动");
	outtextxy(Width * 0.25, Height * 0.65, "鼠标左键发射子弹");
	outtextxy(Width * 0.25, Height * 0.7, "Esc键暂停游戏");
	outtextxy(Width * 0.25, Height * 0.75, "失败后按回车键重新开始");

	FlushBatchDraw();
	Sleep(2);

	char input;
	if(kbhit())
	{
		input = getch();
		if(input == '1')
		{
			gameStatus = 1;
		}
		else if(input == '2')
		{
			readRecordFile();
			gameStatus = 1;
		}
		else if(input == '3')
		{
			gameStatus = 2;
			exit(0);
		}
	}

}

void pauseMenu()
{
	putimage(0, 0, &img_bk);
	setbkmode(TRANSPARENT);
	settextcolor(BLACK);
	settextstyle(50, 0, _T("黑体"));
	outtextxy(Width * 0.3, Height * 0.2, "1 继续游戏");
	outtextxy(Width * 0.3, Height * 0.3, "2 游戏存档");
	outtextxy(Width * 0.3, Height * 0.4, "3 退出");

	settextcolor(BLUE);
	settextstyle(30, 0, _T("黑体"));
	outtextxy(Width * 0.25, Height * 0.6, "鼠标移动控制飞机移动");
	outtextxy(Width * 0.25, Height * 0.65, "鼠标左键发射子弹");
	outtextxy(Width * 0.25, Height * 0.7, "Esc键暂停游戏");
	outtextxy(Width * 0.25, Height * 0.75, "失败后按回车键重新开始");

	FlushBatchDraw();
	Sleep(2);

	char input;
	if(kbhit())
	{
		input = getch();
		if(input == '1')
		{
			gameStatus = 1;
		}
		else if(input == '2')
		{
			writeRecordFile();
			gameStatus = 1;
		}
		else if(input == '3')
		{
			gameStatus = 2;
			exit(0);
		}
	}

}

void readRecordFile()
{
	FILE *fp;
	fp = fopen("./src1/gameRecord.dat", "r");
	fscanf(fp, "%f %f %f %f %f %f %d %d", &position_x, &position_y, &bullet_x, &bullet_y, 
		&enemy_x, &enemy_y, &isExplode, &score);
	fclose(fp);
}

void writeRecordFile()
{
	FILE *fp;
	fp = fopen("./src1/gameRecord.dat", "w");
	fprintf(fp, "%f %f %f %f %f %f %d %d", position_x, position_y, bullet_x, bullet_y, 
		enemy_x, enemy_y, isExplode, score);
	fclose(fp);
}

void startup()
{
	mciSendString("open ./src1/grame_music.mp3 alias bkmusic", NULL, 0, NULL);
	mciSendString("play bkmusic repeat", NULL, 0, NULL);
	initgraph(Width, Height);

	HWND hwnd = GetHWnd();
	SetWindowText(hwnd, "飞机大战 v1.0");

	loadimage(&img_bk, "./src1/background.jpg");
	loadimage(&img_planeNormal1, "./src1/planeNormal_1.jpg");
	loadimage(&img_planeNormal2, "./src1/planeNormal_2.jpg");
	loadimage(&img_bullet1, "./src1/bullet1.jpg");
	loadimage(&img_bullet2, "./src1/bullet2.jpg");
	loadimage(&img_enemy1, "./src1/enemyPlane1.jpg");
	loadimage(&img_enemy2, "./src1/enemyPlane2.jpg");
	loadimage(&img_planeExplode1, "./src1/planeExplode_1.jpg");
	loadimage(&img_planeExplode2, "./src1/planeExplode_2.jpg");

	position_x = Height * 0.7;
	position_y = Width * 0.5;
	bullet_x = position_x;
	bullet_y = -85;
	enemy_x = Width * 0.5;
	enemy_y = 10;

	isExplode = 0;
	score = 0;
	
	BeginBatchDraw();

	while(gameStatus == 0)
	{
		startMenu();
	}

}

void show()
{
	while(gameStatus == 3)
	{
		pauseMenu();
	}

	putimage(0, 0, &img_bk);
	if(isExplode == 0)
	{
		putimage(position_x - 50, position_y - 60, &img_planeNormal1, NOTSRCERASE);
		putimage(position_x - 50, position_y - 60, &img_planeNormal2, SRCINVERT);
		putimage(bullet_x - 7, bullet_y, &img_bullet1, NOTSRCERASE);
		putimage(bullet_x - 7, bullet_y, &img_bullet2, SRCINVERT);
		putimage(enemy_x, enemy_y, &img_enemy1, NOTSRCERASE);
		putimage(enemy_x, enemy_y, &img_enemy2, SRCINVERT);
	}
	else
	{
		putimage(position_x - 50, position_y - 60, &img_planeExplode1, NOTSRCERASE);
		putimage(position_x - 50, position_y - 60, &img_planeExplode2, SRCINVERT);
	}

	settextcolor(RED);
	settextstyle(20, 0, _T("黑体"));
	outtextxy(Width * 0.48, Height * 0.95, "得分：");
	char s[5];
	sprintf(s, "%d", score);
	outtextxy(Width * 0.55, Height *0.95, s);
		
	FlushBatchDraw();
	Sleep(2);
}

void updateWithoutInput()
{

	if(isExplode != 0)
	{
		//按回车键重新开始游戏 
	  getchar();
	  startup();
	}

	if(isExplode == 0)
	{
		if(bullet_y > -25) 
		{
			bullet_y -= 2;
		}
		if(enemy_y < Height - 25)
		{
			enemy_y += 0.5;
		} 
		else 
		{
			enemy_y = 10;
		}

		//子弹击中敌机
		if(abs(bullet_y - enemy_y) <= 128 && bullet_x - enemy_x >= 10 && bullet_x - enemy_x <= 84 )
		{
			enemy_x = rand() % Width;
			enemy_y = -40;
			bullet_y = -85;

			mciSendString("stop gemusic", NULL, 0, NULL);
			mciSendString("close gemusic", NULL, 0, NULL);
			mciSendString("open ./src1/gotEnemy.mp3 alias gemusic", NULL, 0, NULL);
			mciSendString("play gemusic", NULL, 0, NULL);
			
			score++;
			if(score > 0 && score % 5 == 0 && score % 2 != 0)
			{
				mciSendString("close 5music", NULL, 0, NULL);
				mciSendString("close 5music", NULL, 0, NULL);
				mciSendString("open ./src1/5.mp3 alias 5music", NULL, 0, NULL);
				mciSendString("play 5music", NULL, 0, NULL);
			}
			if(score % 10 == 0)
			{
				mciSendString("close 10music", NULL, 0, NULL);
				mciSendString("close 10music", NULL, 0, NULL);
				mciSendString("open ./src1/10.mp3 alias 10music", NULL, 0, NULL);
				mciSendString("play 10music", NULL, 0, NULL);
			}
		}

		//敌机撞击我机
		if(abs(position_y - enemy_y) <= 183 && position_x - enemy_x <= 134 && enemy_x - position_x <= 47)
		{
			isExplode = 1;
			mciSendString("close exmusic", NULL, 0, NULL);
			mciSendString("close exmusic", NULL, 0, NULL);
			mciSendString("open ./src1/explode.mp3 alias exmusic", NULL, 0, NULL);
			mciSendString("play exmusic", NULL, 0, NULL);
		}
	}


}

void updateWithInput()
{
	if(isExplode == 0)
	{
		MOUSEMSG m;
		while(MouseHit())
		{
			m = GetMouseMsg();
			if(m.uMsg == WM_MOUSEMOVE)
			{
				position_x = m.x;
				position_y = m.y;
			}
			else if(m.uMsg == WM_LBUTTONDOWN)
			{
				bullet_x = position_x;
				bullet_y = position_y - 85;
				mciSendString("stop fgmusic", NULL, 0, NULL);
				mciSendString("close fgmusic", NULL, 0, NULL);
				mciSendString("open ./src1/f_gun.mp3 alias fgmusic", NULL, 0, NULL);
				mciSendString("play fgmusic", NULL, 0, NULL);
			}
		}
	}

	char input;
	if(kbhit())
	{
		input = getch();
		if(input == 27)                   //Esc
		{
			gameStatus = 3;
		}
	}

}

void gameover()
{
	EndBatchDraw();
	getch();
	closegraph();
}

int main()
{
	startup();
	while(1)
	{
		show();
		updateWithoutInput();
		updateWithInput();
	}
	gameover();

	return 0;
}
