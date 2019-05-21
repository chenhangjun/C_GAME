#include<graphics.h>
#include<conio.h>

#define height 480
#define width 640
#define brickNum 10

int ball_x, ball_y;
int ball_vx, ball_vy;
int radius;
int bar_x, bar_y, bar_height, bar_width;
int bar_left, bar_right, bar_top, bar_bottom;
int isBrickExisted[brickNum];
int brick_height, brick_width;

void startup()
{
	ball_x = width / 2;
	ball_y = height / 2;
	ball_vx = 1;
	ball_vy = 1;
	radius = 20;

	bar_height = height / 20;
	bar_width = width / 2;
	bar_x = width / 2;
	bar_y = height - bar_height / 2;
	bar_left = bar_x - bar_width / 2;
	bar_right = bar_x + bar_width / 2;
	bar_top = bar_y - bar_height / 2;
	bar_bottom = bar_y + bar_height / 2;
	brick_height = height / brickNum;
	brick_width = width / brickNum;

	for(int i = 0; i < brickNum; i++)
	{
		isBrickExisted[i] = 1;
	}

	initgraph(width, height);
	BeginBatchDraw();
}

void clean()
{
	setcolor(BLACK);
	setfillcolor(BLACK);
	fillcircle(ball_x, ball_y, radius);
	bar(bar_left, bar_top, bar_right, bar_bottom);

	int i, brick_left, brick_right, brick_top, brick_bottom;
	for(i = 0; i < brickNum; i++)
	{
		brick_left = i * brick_width;
		brick_right = (i + 1) * brick_width;
		brick_top = 0;
		brick_bottom = brick_height;
		if(!isBrickExisted[i])
		{
			fillrectangle(brick_left, brick_top, brick_right, brick_bottom);
		}
	}

}

void show()
{
	setcolor(YELLOW);
	setfillcolor(GREEN);
	fillcircle(ball_x, ball_y, radius);
	bar(bar_left, bar_top, bar_right, bar_bottom);

	int i, brick_left, brick_right, brick_top, brick_bottom;
	for(i = 0; i < brickNum; i++)
	{
		brick_left = i * brick_width;
		brick_right = (i + 1) * brick_width;
		brick_top = 0;
		brick_bottom = brick_height;
		if(isBrickExisted[i])
		{
			setcolor(WHITE);
			setfillcolor(RED);
			fillrectangle(brick_left, brick_top, brick_right, brick_bottom);
		}
	}

	FlushBatchDraw();

	Sleep(3);
}

void updateWithoutInput()
{
	ball_x = ball_x + ball_vx;
	ball_y = ball_y + ball_vy;
  
	//–°«Ú≈ˆ«Ω
	if(ball_x <= radius || ball_x >= width - radius) {
		ball_vx *= -1;
	}
	if(ball_y <= radius || ball_y >= height - radius) {
		ball_vy *= -1;
	}

	//–°«Ú≈ˆµ≤∞Â
	if( (ball_y + radius >= bar_top && ball_y - radius < bar_top) || 
			(ball_y - radius <= bar_bottom && ball_y + radius > bar_bottom) )
	{
		if(ball_x + radius >= bar_left && ball_x - radius <= bar_right)
		{
			ball_vy *= -1;
		}
		else if(ball_x + radius >= bar_left && ball_x - radius <= bar_left)
		{
			ball_vy *= -1;
		}
		else if(ball_x + radius >= bar_right && ball_x - radius <= bar_right)
		{
			ball_vy *= -1;
		}
	}

	//–°«Ú≈ˆ◊©øÈ
	int i, brick_left, brick_right, brick_bottom;
	for(i = 0; i < brickNum; i++)
	{
		if(isBrickExisted[i])
		{
			brick_left = i * brick_width;
			brick_right = (i + 1) * brick_width;
			brick_bottom = brick_height;
			if(ball_y - radius <= brick_bottom)
			{ 
				if(ball_x >= brick_left && ball_x <= brick_right) 
				{
					isBrickExisted[i] = 0;
					ball_vy *= -1;
				}
				else if(ball_x - radius <= brick_right && ball_x + radius >= brick_right)
				{
					isBrickExisted[i] = 0;
					ball_vy *= -1;
				}
				else if(ball_x - radius <= brick_left && ball_x + radius >= brick_left)
				{
					isBrickExisted[i] = 0;
					ball_vy *= -1;
				}
			}
		}
	}

}

void updateWithInput()
{
	MOUSEMSG m;
	if(MouseHit())
	{
		m = GetMouseMsg();
		if(m.uMsg == WM_MOUSEMOVE)
		{
			bar_x = m.x;
			bar_y = m.y;
			bar_left = bar_x - bar_width / 2;
			bar_right = bar_x + bar_width / 2;
			bar_top = bar_y  - bar_height / 2;
			bar_bottom = bar_y + bar_height / 2;
		} 
		else if(m.uMsg == WM_RBUTTONDOWN)  //≥ı ºªØ–°«ÚŒª÷√
		{
			ball_x = bar_x;
			ball_y = bar_top - radius - 3;
		}
	}

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