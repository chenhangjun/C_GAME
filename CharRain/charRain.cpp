#include<graphics.h>
#include<time.h>
#include<conio.h>

#define Height 600
#define Width 1000
#define charSize 20

int main()
{
	int HeightNum = Height / charSize;
	int WidthNum = Width / charSize;

	int charRain[Height / charSize][Width / charSize];
	int colNum[Width / charSize];
	int colorG[Width / charSize];
	int i, j, x, y;
	srand((unsigned)time(NULL));

	for(i = 0; i < WidthNum; i++)
	{
		colNum[i] = (rand() % (HeightNum * 9 / 10)) + HeightNum / 10;
		colorG[i] = 255;
		for(j = 0; j < colNum[i]; j++)
		{
			//charRain[j][i] = (rand() % 26) + 65;     //×Ö·ûÓê
			charRain[j][i] = (rand() % 10) + 48;         //Êý×ÖÁ÷
			//charRain[j][i] = rand() % 2 + 48;          //0 1Âë
		}
	}

	initgraph(Width, Height);
	BeginBatchDraw();
	setfont(25, 10, "Courier");

	while(1)
	{
		for(i = 0; i < WidthNum; i++)
		{
			if(colNum[i] < HeightNum - 1)
			{
				for(j = colNum[i] - 1; j >= 0; j--)
				{
					charRain[j + 1][i] = charRain[j][i];
				}
				//charRain[0][i] = rand() % 26 + 65;
				charRain[0][i] = rand() % 10 + 48;
				//charRain[0][i] = rand() % 2 + 48;
				colNum[i]++;
			}
			else
			{
				if(colorG[i] > 40)
				{
					colorG[i] -= 20;
				}
				else
				{
					colNum[i] = rand() % (HeightNum / 3) + HeightNum / 10;
					colorG[i] = rand() % 75 + 180;
					for(j = 0; j < colNum[i]; j++)
					{
						//charRain[j][i] = rand() % 26 + 65;
						charRain[j][i] = rand() % 10 + 48;
						//charRain[j][i] = rand() % 2 + 48;
					}
				}
			}
		}

		for(i = 0; i < WidthNum; i++)
		{
			x = i * charSize;
			for(j = 0; j < colNum[i]; j++)
			{
				y = j * charSize;
				setcolor(RGB(0, colorG[i], 0));
				outtextxy(x, y, charRain[j][i]);
			}
		}

		FlushBatchDraw();
		Sleep(50);
		clearrectangle(0, 0, Width - 1, Height - 1);
	}

	EndBatchDraw();
	getch();
	closegraph();

	return 0;
}