#include<graphics.h>
#include<math.h>
#include<time.h>

#define WIDTH 1024
#define HEIGHT 600
#define NUM_MOVERS 800
#define FRICTION 0.96f

struct Mover
{
	COLORREF color;
	float x, y;
	float vx, vy;
	float radius;
};

Mover movers[NUM_MOVERS];
int mouseX, mouseY;
int prevMouseX, prevMouseY;
int mouseVX, mouseVY;
int isMouseDown;

void delay(DWORD ms);

void startup()
{
	srand((unsigned)time(NULL));
	for(int i = 0; i < NUM_MOVERS; i++)
	{
		movers[i].color = RGB(rand() % 256, rand() % 256, rand() % 256);
		movers[i].x = rand() % WIDTH;
		movers[i].y = rand() % HEIGHT;
		movers[i].vx = float(cos(float(i))) * (rand() % 34);   //?????
		movers[i].vy = float(sin(float(i))) * (rand() % 34);
		movers[i].radius = (rand() % 34) / 15.0;
	}

	mouseX = prevMouseX = WIDTH / 2;
	mouseY = prevMouseY = HEIGHT / 2;

	isMouseDown = 0;
	
	initgraph(WIDTH, HEIGHT);
	BeginBatchDraw();
}

void show()
{
	clearrectangle(0, 0, WIDTH - 1, HEIGHT - 1);
	for(int i = 0; i < NUM_MOVERS; i++)
	{
		setcolor(movers[i].color);
		setfillstyle(movers[i].color);
		fillcircle(int(movers[i].x + 0.5), int(movers[i].y + 0.5), int(movers[i].radius + 0.5));
	}

	FlushBatchDraw();
	delay(5);
}

void updateWithoutInput()
{
	float toDist = WIDTH * 0.86;
	float blowDist = WIDTH * 0.5;
	float stirDist = WIDTH * 0.125;

	mouseVX = mouseX - prevMouseX;
	mouseVY = mouseY - prevMouseY;
	prevMouseX = mouseX;
	prevMouseY = mouseY;

	for(int i = 0; i < NUM_MOVERS; i++)
	{
		float x = movers[i].x;
		float y = movers[i].y;
		float vx = movers[i].vx;
		float vy = movers[i].vy;
		
		float dX = x - mouseX;
		float dY = y - mouseY;
		float d = sqrt(dX * dX + dY * dY);

		if(d != 0)
		{
			dX = dX / d;
			dY = dY / d;
		}
		else
		{
			dX = 0;
			dY = 0;
		}

		if(d < toDist)
		{
			float toAcc = (1 - (d / toDist)) * WIDTH * 0.0014f;
			vx -= dX * toAcc;
			vy -= dY * toAcc;
		}

		if(isMouseDown && d < blowDist)
		{
			float blowAcc = (1 - (d / blowAcc)) * 10;
			vx += dX * blowAcc + 0.5f - float(rand()) / RAND_MAX;
			vy += dY * blowAcc + 0.5f - float(rand()) / RAND_MAX;
		}

		if(d < stirDist)
		{
			float mAcc = (1 - (d / stirDist)) * WIDTH * 0.00026f;
			vx += mouseVX * mAcc;
			vy += mouseVY * mAcc;
		}

		vx *= FRICTION;
		vy *= FRICTION;


		float avgVX = fabs(vx);
		float avgVY = fabs(vy);
		float avgV = (avgVX + avgVY) * 0.5f;

		if(avgVX < 0.1)
		{
			vx = vx * float(rand()) / RAND_MAX * 3;
		}
		if(avgVY < 0.1)
		{
			vy = vy * float(rand()) / RAND_MAX * 3;
		}

		float sc = avgV * 0.45f;
		sc = max(min(sc, 3.5f), 0.4f);
		movers[i].radius = 3.5f - sc + 0.4f;      //半径越大速度越小
		//movers[i].radius = 3.5f - sc + 0.4f;        //半径越大速度越大

		float nextX = x + vx;
		float nextY = y + vy;

		if(nextX > WIDTH)
		{
			nextX = WIDTH;
			vx *= -1;
		}
		if(nextX < 0)
		{
			nextX = 0;
			vx *= -1;
		}
		if(nextY > HEIGHT)
		{
			nextY = HEIGHT;
			vy *= -1;
		}
		if(nextY < 0)
		{
			nextY = 0;
			vy *= -1;
		}

		movers[i].vx = vx;
		movers[i].vy = vy;
		movers[i].x = nextX;
		movers[i].y = nextY;
	}
}

void updateWithInput()
{
	MOUSEMSG m;
	while(MouseHit())
	{
		m = GetMouseMsg();
		if(m.uMsg == WM_MOUSEMOVE)
		{
			mouseX = m.x;
			mouseY = m.y;
		}
		else if(m.uMsg == WM_LBUTTONDOWN)
		{
			isMouseDown = 1;
		}
		else if(m.uMsg == WM_LBUTTONUP)
		{
			isMouseDown = 0;
		}
	}

}

void delay(DWORD ms)
{
	static DWORD oldtime = GetTickCount();
	while(GetTickCount() - oldtime < ms)
	{
		Sleep(1);
	}
	oldtime = GetTickCount();
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
		show();
		updateWithoutInput();
		updateWithInput();
	}
	gameover();

	return 0;
}
