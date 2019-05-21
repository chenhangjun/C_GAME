#include<graphics.h>
#include<conio.h>

int main()
{
	initgraph(640, 480);
	for(int i = 0; i <= 480; i += 48) {
		setcolor(RGB(0, 0, i));
		line(0, i, 640, i);
		}
	getch();
	closegraph();
	return 0;
}