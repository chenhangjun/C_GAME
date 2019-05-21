#include<graphics.h>
#include<conio.h>
#include<windows.h>

#define height 480
#define width 640

int ball_x, ball_y, ball_vx, ball_vy, radius;
int bar1_left, bar1_right, bar1_top, bar1_bottom;
int bar2_left, bar2_right, bar2_top, bar2_bottom;
int bar_height, bar_width;

void startup()
{
	ball_x = width / 2;
	ball_y = height / 2;
	ball_vx = 1;
	ball_vy = 1;
	radius = 20;

	bar_width = width / 30;
	bar_height = height / 2;

	bar1_left = width / 20;
	bar1_top = height / 4;
	bar1_right = bar1_left + bar_width;
	bar1_bottom = bar1_top + bar_height;

	bar2_left =  width * 18.5 / 20;
	bar2_top = height / 4;
	bar2_right = bar2_left + bar_width;
	bar2_bottom = bar2_top + bar_height;

	initgraph(width, height);
	BeginBatchDraw();
}

void clean()
{
	setcolor(BLACK);
	setfillcolor(BLACK);
	fillcircle(ball_x, ball_y, radius);
	bar(bar1_left, bar1_top, bar1_right, bar1_bottom);
	bar(bar2_left, bar2_top, bar2_right, bar2_bottom);
}

void show()
{
	setcolor(GREEN);
	setfillcolor(GREEN);
	fillcircle(ball_x, ball_y, radius);

	setcolor(YELLOW);
	setfillcolor(YELLOW);
	bar(bar1_left, bar1_top, bar1_right, bar1_bottom);
	bar(bar2_left, bar2_top, bar2_right, bar2_bottom);

	FlushBatchDraw();

	Sleep(3);
}

void updateWithoutInput()
{
	if(ball_x + radius >= bar2_left && ball_y + radius >= bar2_top && ball_y - radius <= bar2_bottom)
	{
		ball_vx *= -1;
	}
	else if(ball_x - radius <= bar1_right && ball_y + radius >= bar1_top && ball_y - radius <= bar1_bottom)
	{
		ball_vx *= -1;
	}

	ball_x += ball_vx;
	ball_y += ball_vy;

	if(ball_x <= radius || ball_x >= width - radius)
	{
		ball_vx *= -1;
	}
	if(ball_y <= radius || ball_y >= height - radius)
	{
		ball_vy *= -1;
	}

}

void updateWithInput()
{

		int step = 1;
		
		if(GetAsyncKeyState(0x57) & 0x8000)   //a
		{
			bar1_top -= step;
		}
		if(GetAsyncKeyState(0x53) & 0x8000)   //d
		{
			bar1_top += step;
		}
		
		if(GetAsyncKeyState(VK_UP) & 0x8000)   //ио
		{
			bar2_top -= step;
		}
		if(GetAsyncKeyState(VK_DOWN) & 0x8000)   //об
		{
			bar2_top += step;
		}
		
		bar1_bottom = bar1_top + bar_height;
		bar2_bottom = bar2_top + bar_height;

	
}

void gameover()
{
	EndBatchDraw();
	closegraph();
}

int main()
{
	startup();
	while(1)
	{
		clean();
		updateWithoutInput();
		updateWithInput();
		show();
	}
	gameover();

	return 0;
}


