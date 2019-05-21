
#include <graphics.h>
#include <conio.h>

void main()
{
    initgraph(1000, 600);
	
    // ∂¡»°Õº∆¨
    loadimage(NULL, "c:\\fire.jpg");
	
    int c;
    for(int x=500; x<1000; x++)
        for(int y=0; y<600; y++)
        {
            c = getpixel(x, y);
						//c &= 0xffff00;
            c = (0xff0000 - (c & 0xff0000)) | (0x00ff00 - (c & 0x00ff00)) | (0x0000ff - (c & 0x0000ff));
            putpixel(x, y, c);
        }
		
		getch();
		closegraph();
}