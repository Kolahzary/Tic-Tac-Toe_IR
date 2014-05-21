class Board
{
	private:
	int x,y;
	int width,height;
	int lineColor,cellBorderColor;
	void initgraphics();

	public:
	Cell cells[4][4][4];
	Board();
	Board(int newX,int newY,int newWidth,int newHeight,int newLineColor=AQUA, int newCellBorderColor=WHITE);
	void show();
	void hide();
	void move(int newX,int newY);
	void resize(int newWidth,int newHeight);
};

void Board::show()
{
	int i,j,k;
	setcolor(lineColor);
	for(i=1;i<=3;i++)
		rectangle(x-(width/2)*i,y-(height/2)*i,x+(width/2)*i,y+(height/2)*i);
	for(i=-1;i<=1;i+=2)
	{
		line(x-(width/2)*3*i,y-(height/2)*3*i,x-width/2*i,y-height/2*i);	// \ \ 
		line(x+(width/2)*3*i,y-(height/2)*3*i,x+width/2*i,y-height/2*i);	// / / 
		line(x+(width/2)*3*i,y,x+width/2*i,y);   // - -
		line(x,y-(height/2)*3*i,x,y-height/2*i); // | |
	}

	for(i=1;i<=3;i++)
	{
		for(j=-1;j<=1;j++)
		{
			for(k=-1;k<=1;k++)
			{
				cells[i][j+2][k+2].show(x-(width/2*i)*j,y-(height/2*i)*k,width<height?width/6:height/6,NN,cellBorderColor);
			}
		}
	}
	//outtextxy(x+(width/2)*3+(width<height?width/6:height/6),y,"Iranian Tic-Tac-Toe Game");
}

void Board::hide()
{
	int i,j,k;
	setcolor(getbkcolor());
	rectangle(x-width/2,y-height/2,x+width/2,y+height/2);
	rectangle(x-width,y-height,x+width,y+height);
	rectangle(x-(width/2)*3,y-(height/2)*3,x+(width/2)*3,y+(height/2)*3);

	// \ \ 
	line(x-(width/2)*3,y-(height/2)*3,x-width/2,y-height/2);
	line(x+(width/2)*3,y+(height/2)*3,x+width/2,y+height/2);

	// / / 
	line(x+(width/2)*3,y-(height/2)*3,x+width/2,y-height/2);
	line(x-(width/2)*3,y+(height/2)*3,x-width/2,y+height/2);

	// - -
	line(x+(width/2)*3,y,x+width/2,y);
	line(x-(width/2)*3,y,x-width/2,y);

	// | |
	line(x,y-(height/2)*3,x,y-height/2);
	line(x,y+(height/2)*3,x,y+height/2);

	for(i=1;i<=3;i++)
	{
		for(j=1;j<=3;j++)
		{
			for(k=1;k<=3;k++)
			{
				cells[i][j][k].hide();
			}
		}
	}

}

void Board::move(int newX,int newY)
{
	hide();
	x=newX;
	y=newY;
	show();
}

void Board::resize(int newWidth,int newHeight)
{
	hide();
	width=newWidth;
	height=newHeight;
	show();
}

Board::Board()
{
	initgraphics();
	x=getmaxx()/2;
	y=getmaxy()/2;
	width=getmaxx()/4;
	height=getmaxy()/4;
	lineColor=BRIGHT;
	cellBorderColor=WHITE;
}

Board::Board(int newX,int newY,int newWidth,int newHeight,int newLineColor, int newCellBorderColor)
{
	initgraphics();
	x=newX-newWidth/2;
	y=newY;
	width=newWidth/2;
	height=newHeight;
	lineColor=newLineColor;
	cellBorderColor=newCellBorderColor;
}

void Board::initgraphics()
{
	// Graphic Drivier initialization
	int gdriver = DETECT, gmode, errorcode;
	initgraph(&gdriver, &gmode, "c:\\tc\\bgi");
	errorcode = graphresult();
	if (errorcode != grOk)
	{
	   cout<<"Graphics error: "<<grapherrormsg(errorcode)<<"\n";
	   cout<<"Press any key to halt:";
	   getch();
	   exit(1);
	}
}
