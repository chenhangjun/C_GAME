#include<graphics.h>
#include<conio.h>

#pragma comment(lib, "Winmm.lib")
IMAGE img_bk, img_bd1, img_bd2, img_bar_up1,  img_bar_up2, img_bar_down1, img_bar_down2;
int bird_x, bird_y;

void startup()
{
	initgraph(350, 600);
	loadimage(&img_bk, "./src/background.jpg");
	loadimage(&img_bd1, "./src/bird1.jpg");
	loadimage(&img_bd2, "./src/bird2.jpg");
	loadimage(&img_bar_up1, "./src/bar_up1.gif");
	loadimage(&img_bar_up2, "./src/bar_up2.gif");
	loadimage(&img_bar_down1, "./src/bar_down1.gif");
	loadimage(&img_bar_down2, "./src/bar_down2.gif");

	bird_x = 50;
	bird_y = 200;

	BeginBatchDraw();

	mciSendString("open ./src/background.mp3 alias bkmusic", NULL, 0, NULL);
	mciSendString("play bkmusic repeat", NULL, 0, NULL);
}

void show()
{
	putimage(0, 0, &img_bk);
	putimage(150, -300, &img_bar_up1, NOTSRCERASE);
	putimage(150, -300, &img_bar_up2, SRCINVERT);
	putimage(150, 400, &img_bar_down1, NOTSRCERASE);
	putimage(150, 400, &img_bar_down2, SRCINVERT);
	putimage(bird_x, bird_y, &img_bd1, NOTSRCERASE);
	putimage(bird_x, bird_y, &img_bd2, SRCINVERT);

	FlushBatchDraw();
	Sleep(50);
}

void updateWithoutInput()
{
	if(bird_y < 580)
	{
		bird_y = bird_y + 3;
	}
}

void updateWithInput()
{
	char input;
	if(kbhit())
	{
		input = getch();
		if(input == ' ' && bird_y > 20)
		{
			bird_y -= 60;
			mciSendString("close jpmusic", NULL, 0, NULL);
			mciSendString("open ./src/Jump.mp3 alias jpmusic", NULL, 0, NULL);
			mciSendString("play jpmusic", NULL, 0, NULL);
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