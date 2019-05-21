#include <graphics.h>
#include <conio.h>

void sanjiaoxing(int x, int y, int color)
{
     // 设置画线颜色
     setlinecolor(color);

     // 画三角形的三条边
     line(x, y, x+10, y);
     line(x, y, x, y+10);
     line(x+10, y, x, y+10);
}

void main()
{
    initgraph(640, 480);	// 初始化图形窗口

    for(int x=0; x<640; x+=10)
        for(int y=0; y<480; y+= 10)
            sanjiaoxing(x, y, RGB(x*255/640, y*255/480, 0));

    getch();				// 按任意键继续
    closegraph();			// 关闭图形窗口
}