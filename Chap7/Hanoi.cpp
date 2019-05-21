#include<stdio.h>
#include<stdlib.h>
#include<ctime>
#include<windows.h>

void move(char x, char y, int n, int **p);
void hanoi(int n, char one, char two, char three, int **p);
void changeArray(char x, char y, int n, int **p);
void changeHeight(char x, char y);
void print(int **p);
void printstar(int **p);
void gotoxy(int x, int y);

static int heightA, heightB, heightC, r, c;

int main()
{
	int i, **p;
	printf("Input a number: ");
	scanf("%d", &r);
	c = r * 10;
	p = new int *[r];
	p[0] = new int[r * c];
	for(i = 1; i < r; i++)
	{
		p[i] = p[i - 1] + c;
	}
	heightA = r;
	heightB = 0;
	heightC = 0;

	printf("the step to move %d diskes:\n\n", r);
	printstar(p);
	gotoxy(0, 1);
	getchar();
	hanoi(r, 'A', 'B', 'C', p);

	return 0;
}

void move(char x, char y, int n, int **p)
{
	getchar();
	printf(" %c -> %c\n", x, y);
	changeArray(x, y, n, p);
	print(p);
	changeHeight(x, y);
	gotoxy(0, 1);
}

void hanoi(int n, char one, char two, char three, int **p)
{
	if(n == 1)
	{
		move(one, three, n, p);
	}
	else
	{
		hanoi(n - 1, one, three, two, p);
		move(one, three, n, p);
		hanoi(n - 1, two, one, three, p);
	}
}

void print(int **p)
{
	int i, j;
	for(i = 0; i < r; i++)
	{
		for(j = 0; j < c; j++)
		{
			if(p[i][j] == 1)
			{
				printf("*");
			}
			else
			{
				printf(" ");
			}
		}
	}
}

void changeHeight(char x, char y)
{
	switch(x)
	{
		case 'A': heightA--;
							break;
		case 'B': heightB--;
							break;
		case 'C': heightC--;
							break;
	}
	switch(y)
	{
		case 'A': heightA++;
							break;
		case 'B': heightB++;
							break;
		case 'C': heightC++;
	}
}

void changeArray(char x, char y, int n, int **p)
{
	int i, j;
	if(x == 'A')
	{
		for(i = 0; i < r; i++)
		{
			for(j = 0; j < c; j++)
			{
				if(i == r - heightA && j >= r - n && j <= r + n - 2)
				{
					p[i][j] = 0;
				}
			}
		}
	}
	else if(x == 'B')
	{
		for(i = 0; i < r; i++)
		{
			for(j = 0; j < c; j++)
			{
				if(i == r - heightB && j >= 3 * r - n && j <= 3 * r + n - 2)
				{
					p[i][j] = 0;
				}
			}
		}
	}
	else if(x == 'C')
	{
		for(i = 0; i < r; i++)
		{
			for(j = 0; j < c; j++)
			{
				if(i == r - heightC && j >= 5 * r - n && j <= 5 * r + n - 2)
				{
					p[i][j] = 1;
				}
			}
		}
	}

	if(y == 'A')
	{
		for(i = 0; i < r; i++)
		{
			for(j = 0; j < c; j++)
			{
				if(i == r - heightA - 1 && j >= r - n && j <= r + n - 2)
				{
					p[i][j] = 1;
				}
			}
		}
	}
	else if(y == 'B')
	{
		for(i = 0; i < r; i++)
		{
			for(j = 0; j < c; j++)
			{
				if(i == r - heightB - 1 && j >= 3 * r - n && j <= 3 * r + n - 2)
				{
					p[i][j] = 1;
				}
			}
		}
	}
	else if(y == 'C')
	{
		for(i = 0; i < r; i++)
		{
			for(j = 0; j < c; j++)
			{
				if(i == r - heightC - 1 && j >= 5 * r - n && j <= 5 * r + n - 2)
				{
					p[i][j] = 1;
				}
			}
		}
	}

}

void printstar(int **p)
{
	int i, j;
	for(i = 0; i < r; i++)
	{
		for(j = 0; j < c; j++)
		{
			if(j >= r - i - 1 && j <= r + i - 1)
			{
				p[i][j] = 1;
			}
		}
	}
	for(i = 0; i < r; i++)
	{
		for(j = 0; j < c; j++)
		{
			if(p[i][j] == 1)
			{
				printf("*");
			}
			else
			{
				printf(" ");
			}
		}
		printf("\n");
	}

}

void gotoxy( int x, int y )
{
	CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
	HANDLE hConsoleOut;
	hConsoleOut = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(hConsoleOut, &csbiInfo);
	csbiInfo.dwCursorPosition.X = x;
	csbiInfo.dwCursorPosition.Y = y;
	SetConsoleCursorPosition(hConsoleOut, csbiInfo.dwCursorPosition);
}