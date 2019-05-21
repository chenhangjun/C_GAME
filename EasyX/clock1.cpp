#include<graphics.h>
#include<conio.h>
#include<math.h>

#define height 480
#define width 640
#define PI 3.14159

int main()
{
	initgraph( width, height );
	int center_x, center_y;
	int secondLength, minuteLength, hourLength;
	int secondEnd_x, secondEnd_y, minuteEnd_x, minuteEnd_y, hourEnd_x, hourEnd_y;
	float secondAngle, minuteAngle, hourAngle;
	SYSTEMTIME ti;
	
	center_x = width / 2;
	center_y = height / 2;
	secondLength = width / 5;   
	minuteLength = width / 6;
	hourLength = width / 7;
	
	BeginBatchDraw();

	while(1) {
		//绘制表盘
		setlinestyle(PS_SOLID, 1);
		setcolor(WHITE);
		circle(center_x, center_y, width / 4);

		int x, y, i;
		for(i = 0; i < 60; i++)
		{
			x = center_x + int(width / 4.3 * sin(PI * 2 * i / 60));
			y = center_y - int(width / 4.3 * cos(PI * 2 * i / 60));

			if( i % 15 == 0)
			{
				bar(x - 5, y - 5, x + 5, y + 5);
			} else if( i % 5 == 0)
			{
				circle(x, y, 3);
			} else {
				putpixel(x, y, WHITE);
			}
		}

		outtextxy(center_x - 25, center_y + width / 6, "我的时钟");
		
		GetLocalTime(&ti);
		secondAngle = ti.wSecond * 2 * PI / 60;
		minuteAngle = ti.wMinute * 2 * PI / 60 + secondAngle / 60;
		hourAngle = ti.wHour * 2 * PI / 12 + minuteAngle / 12;

		secondEnd_x = center_x + secondLength * sin(secondAngle);
		secondEnd_y = center_y - secondLength * cos(secondAngle);
		minuteEnd_x = center_x + minuteLength * sin(minuteAngle);
		minuteEnd_y = center_y - minuteLength * cos(minuteAngle);
		hourEnd_x = center_x + hourLength * sin(hourAngle);
		hourEnd_y = center_y - hourLength * cos(hourAngle);

 		setlinestyle(PS_SOLID, 2);   //实线，两个像素宽度
		setcolor(YELLOW);
		line(center_x, center_y, secondEnd_x, secondEnd_y);
		setlinestyle(PS_SOLID, 4);   
		setcolor(BLUE);
		line(center_x, center_y, minuteEnd_x, minuteEnd_y);
		setlinestyle(PS_SOLID, 6);   
		setcolor(RED);
		line(center_x, center_y, hourEnd_x, hourEnd_y);

		FlushBatchDraw();
		Sleep(10);

		setcolor(BLACK);
		setlinestyle(PS_SOLID, 2);   
		line(center_x, center_y, secondEnd_x, secondEnd_y);
		setlinestyle(PS_SOLID, 4);   
		line(center_x, center_y, minuteEnd_x, minuteEnd_y);
		setlinestyle(PS_SOLID, 6);   
		line(center_x, center_y, hourEnd_x, hourEnd_y);

		//secondAngle += 2 * PI / 60;
	}

	EndBatchDraw();
	getch();
	closegraph();

	return 0;
}