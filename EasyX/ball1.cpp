#include<graphics.h>
#include<conio.h>
#include<math.h>
#include<time.h>

#define height 480
#define width 640
#define ballNum 15

int main()
{
	float ball_x[ballNum], ball_y[ballNum];
	float ball_vx[ballNum], ball_vy[ballNum];
	int radius;
	int i, j;
	radius = 20;
	int flag = 1;
	srand((unsigned)time(NULL));
	float minDistances[ballNum][2];

	while(flag) {
		flag = 0;
		for(i = 0; i < ballNum; i++) 
		{
			ball_x[i] = rand() % int(width - 4 * radius) + 2 * radius;
			ball_y[i] = rand() % int(height - 4 * radius) + 2 * radius;
			ball_vx[i] = (rand() % 2) * 2 - 1;
			ball_vy[i] = (rand() % 2) * 2 - 1;
		}

		for(i = 0; i < ballNum; i++)
		{
			minDistances[i][0] = 9999999;
			minDistances[i][1] = -1;
		}
		for(i = 0; i < ballNum; i++)
		{
			for(j = 0; j < ballNum; j++)
			{
				if(i != j)
				{
					float dist;
					dist = (ball_x[i] - ball_x[j]) * (ball_x[i] - ball_x[j]) + (ball_y[i] - ball_y[j]) * (ball_y[i] - ball_y[j]);
					if(dist < minDistances[i][0])
					{
						minDistances[i][0] = dist;
						minDistances[i][1] = j;
					}
				}
			}
		}
		
			//粘合：同向速度
		for(i = 0; i < ballNum; i++) 
		{
			if(minDistances[i][0] <= 4 * radius * radius)
			{
				flag = 1;
			}
		}
	}

	initgraph(width, height);
	BeginBatchDraw();
	
	while(1)
	{
		setcolor(BLACK);
		setfillcolor(BLACK);
		for(i = 0; i < ballNum; i++)
		{
			fillcircle(ball_x[i], ball_y[i], radius);
			ball_x[i] += ball_vx[i];
			ball_y[i] += ball_vy[i];
			if(ball_x[i] <= radius || ball_x[i] >= width - radius) {
				ball_vx[i] *= -1;
			}
			if(ball_y[i] <= radius || ball_y[i] >= height - radius) {
				ball_vy[i] *= -1;
			}

		}

		//float minDistances[ballNum][2];
		for(i = 0; i < ballNum; i++)
		{
			minDistances[i][0] = 9999999;
			minDistances[i][1] = -1;
		}
		for(i = 0; i < ballNum; i++)
		{
			for(j = 0; j < ballNum; j++)
			{
				if(i != j)
				{
					float dist;
					dist = (ball_x[i] - ball_x[j]) * (ball_x[i] - ball_x[j]) + (ball_y[i] - ball_y[j]) * (ball_y[i] - ball_y[j]);
					if(dist < minDistances[i][0])
					{
						minDistances[i][0] = dist;
						minDistances[i][1] = j;
					}
				}
			}
		}

		//碰撞
		for(i = 0; i < ballNum; i++)
		{
			if(minDistances[i][0] <= 4 * radius * radius + 2)
			{
				j = minDistances[i][1];
				int temp;
				temp = ball_vx[i];
				ball_vx[i] = ball_vx[j];
				ball_vx[j] = temp;
				temp = ball_vy[i];
				ball_vy[i] = ball_vy[j];
				ball_vy[j] = temp;
				minDistances[j][0] = 9999999;
				minDistances[j][1] = -1;
			}
		}

		setcolor(YELLOW);
		setfillcolor(GREEN);
		for(i = 0; i < ballNum; i++)
		{
			fillcircle(ball_x[i], ball_y[i], radius);
		}

		FlushBatchDraw();

		Sleep(6);
	}

	EndBatchDraw();
	closegraph();

	return 0;
}


