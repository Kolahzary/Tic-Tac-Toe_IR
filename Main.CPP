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
		{      // arrow keys + Space and Enter for control
			case 72: xo.move(UP);	break;
			case 77: xo.move(RIGHT);break;
			case 80: xo.move(DOWN);	break;
			case 75: xo.move(LEFT);	break;
			case ' ': case  13: xo.select();		break;

		       // numpad keys for position
			case '1': xo.board.move(getmaxx()/4*1,getmaxy()/4*3);   break;
			case '2': xo.board.move(getmaxx()/4*2,getmaxy()/4*3);   break;
			case '3': xo.board.move(getmaxx()/4*3,getmaxy()/4*3);   break;
			case '4': xo.board.move(getmaxx()/4*1,getmaxy()/4*2);   break;
			case '5': xo.board.move(getmaxx()/4*2,getmaxy()/4*2);   break;
			case '6': xo.board.move(getmaxx()/4*3,getmaxy()/4*2);   break;
			case '7': xo.board.move(getmaxx()/4*1,getmaxy()/4*1);   break;
			case '8': xo.board.move(getmaxx()/4*2,getmaxy()/4*1);   break;
			case '9': xo.board.move(getmaxx()/4*3,getmaxy()/4*1);   break;

		       // function keys for size
			case 59: xo.board.resize(getmaxx()/1,getmaxy()/1); break;
			case 60: xo.board.resize(getmaxx()/2,getmaxy()/2); break;
			case 61: xo.board.resize(getmaxx()/3,getmaxy()/3); break;
			case 62: xo.board.resize(getmaxx()/4,getmaxy()/4); break;
			case 63: xo.board.resize(getmaxx()/5,getmaxy()/5); break;
			case 64: xo.board.resize(getmaxx()/6,getmaxy()/6); break;
			case 65: xo.board.resize(getmaxx()/7,getmaxy()/7); break;
			case 66: xo.board.resize(getmaxx()/8,getmaxy()/8); break;
			case 67: xo.board.resize(getmaxx()/9,getmaxy()/9); break;
		}
	}while(ch!=27); // 27: Escape

	getch();
}
