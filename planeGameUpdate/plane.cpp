#include<stdio.h>
#include<stdlib.h>
#include<conio.h>

int position_x, position_y;
int height, width;

void startup()
{
	height = 20;
	width = 20;
	position_x = height / 2;
	position_y = width / 2;
}

void show()
{
	system("cls");
	int i, j;
	for(i = 0; i < height; i++) {
		for(j = 0; j < width; j++) {
			if( i == position_x && j == position_y) {
				printf("*");
			} else {
				printf(" ");
			}
		}
		printf("\n");
	}
}

void updateWithoutInput()
{
}

void updateWithInput()
{
	char input;
	if(kbhit()) {
		input = getch();
		if(input == 'a') {
			position_y--;
		}
		if(input == 'd') {
			position_y++;
		}
		if(input == 'w') {
			position_x--;
		}
		if(input == 's') {
			position_x++;
		}
	}
}

int main()
{
	startup();
	while(1) {
		show();
		updateWithoutInput();
		updateWithInput();
	}
	return 0;
}
