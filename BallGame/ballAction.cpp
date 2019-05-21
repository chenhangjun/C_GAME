#include<stdio.h>
#include<stdlib.h>
#include<windows.h>

int main()
{
	int i, j;
	int x = 0, y = 5;

	int top = 0, bottom = 10;
	int left = 0, right = 20;
	int velocity_x = 1, velocity_y = 1;

	while( 1 ) {

		CONSOLE_CURSOR_INFO  cci;
		cci.dwSize = 1; //这个设置光标的大小,值为1-100
		cci.bVisible = FALSE; //这个设置光标是否显示

		HANDLE hOutputHandle = GetStdHandle( STD_OUTPUT_HANDLE );
		BOOL bResult = SetConsoleCursorInfo(hOutputHandle, &cci); //设置光标信息

		x += velocity_x;
		y += velocity_y;

		system( "cls" );

		
		for( i = 0; i < 10; i++ ) {
			for( j = 0; j < 21; j++ ) {
				printf( " " );
			}
			printf( "|" );
			
			printf( "\n" );
		}
		for( j = 0; j < 22; j++ ) {
			printf( "_" );
		}
		printf( "\b|" );

		COORD pos;   //光标位置
		pos.X =0;  
		pos.Y = 0;  
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),pos);  

		for( i = 0; i < x; i++ ) {
			printf( "\n" );
		}
		for( j =0; j < y; j++ ) {
			printf( " ");
		}

		printf( "o\n" );
		
		/* 利用循环减速
		for( int m = 1; m < 900000; m++ ) {
			m+=2;
			m-=2;
			printf( "" );
		}   */

		//Sleep( 200 );

		if( x == top || x == bottom ) {
			velocity_x *= -1;
			//printf( "\a" );
		}

		if( y == left || y == right ) {
			velocity_y *= -1;
			//printf( "\a" );
		}

	}

	return 0;
}
