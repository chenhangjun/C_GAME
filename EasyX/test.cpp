#include<graphics.h>
#include<conio.h>

//int main()
{
	initgraph(640, 480);
	setcolor(YELLOW);
	setfillcolor(GREEN);
	fillcircle(100, 100, 20);
	getch();
	closegraph();
	return 0;
}