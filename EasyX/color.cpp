#include <graphics.h>
#include <conio.h>

void sanjiaoxing(int x, int y, int color)
{
     // ���û�����ɫ
     setlinecolor(color);

     // �������ε�������
     line(x, y, x+10, y);
     line(x, y, x, y+10);
     line(x+10, y, x, y+10);
}

void main()
{
    initgraph(640, 480);	// ��ʼ��ͼ�δ���

    for(int x=0; x<640; x+=10)
        for(int y=0; y<480; y+= 10)
            sanjiaoxing(x, y, RGB(x*255/640, y*255/480, 0));

    getch();				// �����������
    closegraph();			// �ر�ͼ�δ���
}