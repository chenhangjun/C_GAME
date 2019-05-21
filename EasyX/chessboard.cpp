#include<graphics.h>
#include<conio.h>

int main()
{
	int step = 50;
	initgraph(500, 500);
	setbkcolor(YELLOW);
	cleardevice();

	setlinestyle(PS_SOLID, 2);
	setcolor(RGB(0, 0, 0));

	int i, j;
	for(i = 1; i <= 8; i++) {
		for(j = 1; j <= 8; j++) {
			if((i + j) % 2 == 1) {
				setfillcolor(BLACK);
				solidrectangle(i * step, j* step, (i + 1) * step, (j + 1) * step);
			} else {
				setfillcolor(WHITE);
				solidrectangle(i * step, j* step, (i + 1) * step, (j + 1) * step);
			}
		}
	}
	getch();
	closegraph();
	return 0;
}