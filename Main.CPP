#include "C:\XO\XO.H"

void main()
{
	char ch;
	XO xo;
	do
	{
		ch=getch();
		//cout<<(int)ch;    // for debug
		switch(ch)
		{
			case 'w': case 'W': case 72: xo.move(UP);	break;
			case 'd': case 'D': case 77: xo.move(RIGHT);  	break;
			case 's': case 'S': case 80: xo.move(DOWN);	break;
			case 'a': case 'A': case 75: xo.move(LEFT);	break;
			case ' ': case  13: xo.select();                  break;
		}
	}while(ch!=27);

	getch();
}
