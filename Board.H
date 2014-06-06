class Board
{
	private:
	int x,y;
	int width,height;
	int lineColor,cellBorderColor;
	void initgraphics();
	int bX,bO,bTurn,bStatus; // backup for text functions

	public:
	Cell cells[4][4][4];
	Board();
	Board(int newX,int newY,int newWidth,int newHeight,int newLineColor=AQUA, int newCellBorderColor=WHITE);
	void updateText(int X,int O,int turn,int status,int force=0);
	void hideText();
	void show();
	void hide();
	void move(int newX,int newY);
	void resize(int newWidth,int newHeight);
};

void Board::hideText()
{
	const char CLEAN=219;
	const int COUNT=54,COUNT1=11,COUNT2=4;
	static char strTmp[COUNT],strTmp1[COUNT1],strTmp2[COUNT2];
	int i;

	settextjustify(CENTER_TEXT,CENTER_TEXT);
	settextstyle(1,0,1);
	setcolor(0);

	for(i=0;i<COUNT;i++)	strTmp[i]=CLEAN;
	strTmp[COUNT-1]='\0';
	for(i=0;i<COUNT1;i++)	strTmp1[i]=CLEAN;
	strTmp1[COUNT1-1]='\0';
	for(i=0;i<COUNT2;i++)	strTmp2[i]=CLEAN;
	strTmp2[COUNT2-1]='\0';

	outtextxy(x,y-10,strTmp1);
	outtextxy(x,y+10,strTmp1);
	outtextxy(x,y-height/3*4-4,strTmp);
	outtextxy(x,y-height/3*4+4,strTmp);
	outtextxy(x,y+height/3*4-4,strTmp);
	outtextxy(x,y+height/3*4+4,strTmp);
}

void Board::updateText(int X,int O,int turn,int status,int force)
{
	bX=X;bO=O;bTurn=turn;bStatus=status;
	const char CLEAN=219;
	const int COUNT=54,COUNT1=11,COUNT2=4;
	static oldX,oldO,oldStatus,oldTurn;
	static char strTmp[COUNT],strTmp1[COUNT1],strTmp2[COUNT2];
	int i;

	settextjustify(CENTER_TEXT,CENTER_TEXT);
	settextstyle(1,0,1);

	for(i=0;i<COUNT;i++)	strTmp[i]=CLEAN;
	strTmp[COUNT-1]='\0';
	for(i=0;i<COUNT1;i++)	strTmp1[i]=CLEAN;
	strTmp1[COUNT1-1]='\0';
	for(i=0;i<COUNT2;i++)	strTmp2[i]=CLEAN;
	strTmp2[COUNT2-1]='\0';

	{// Hide old text --> send "Û" character to output --> ascii code: 219
		setcolor(0);
		if(oldX!=X||force==1)
			outtextxy(x,y-10,strTmp1);
		if(oldO!=O||force==1)
			outtextxy(x,y+10,strTmp1);
		if(oldStatus!=status||force==1)
		{
			outtextxy(x,y+height/3*4-4,strTmp);
			outtextxy(x,y+height/3*4+4,strTmp);
		}
	}

	if(oldTurn!=turn || oldStatus!=status || oldX!=X || oldO!=O||force==1) // if anything changed, update texts
	{
		if(turn==XX) setcolor(4); else setcolor(2);
		outtextxy(x,y-height/3*4,"Iranian Tic-Tac-Toe(Naughts and Crosses) Game");
		switch (status)
		{
			case 1:
				strcpy(strTmp,"Level 1: Insert");
				break;
			case 2:
				strcpy(strTmp,"Level 2: Pick up a pawn to move");
				break;
			case 3:
				strcpy(strTmp,"Level 2: Select a competitors pawn to remove");
				break;
			case 4:
				strcpy(strTmp,"Level 2: Put your pawn in an empty cell");
		}
		outtextxy(x,y+height/3*4,strTmp);

		strcpy(strTmp1,"Red: ");		// Write text to variable
		itoa(X,strTmp2,10);			// convert count from integer to ASCII (Make count appendable to text)
		strcat(strTmp1,strTmp2);		// Append count to text
		outtextxy(x,y-10,strTmp1); // Show result on screen

		strcpy(strTmp1,"Green: ");	// Write text to variable
		itoa(O,strTmp2,10);			// convert count from integer to ASCII (Make count appendable to text)
		strcat(strTmp1,strTmp2);		// Append count to text
		outtextxy(x,y+10,strTmp1); // Show result on screen
	}
	oldStatus=status; oldX=X; oldO=O; oldTurn=turn; // update static variables for next run
}

void Board::show()
{
	int i,j,k,a,b,c;

	setcolor(lineColor);
	for(i=1;i<=3;i++)
		rectangle(x-(width/3)*i,y-(height/3)*i,x+(width/3)*i,y+(height/3)*i);
	for(i=-1;i<=1;i+=2)
	{
		line(x-(width/3)*3*i,y-(height/3)*3*i,x-width/3*i,y-height/3*i);	// \ \
		line(x+(width/3)*3*i,y-(height/3)*3*i,x+width/3*i,y-height/3*i);	// / /
		line(x+(width/3)*3*i,y,x+width/3*i,y);   // - -
		line(x,y-(height/3)*3*i,x,y-height/3*i); // | |
	}

	for(i=1;i<=3;i++)
		for(j=-1;j<=1;j++)
			for(k=-1;k<=1;k++)
			{
				a=i; // floor
				switch(j){ case -1:b=3;break;  case 0:b=2;break;  case 1:b=1;break;} // column
				switch(k){ case -1:c=3;break;  case 0:c=2;break;  case 1:c=1;break;} // row
				if(b==2&&c==2) continue; // if it's center cell, don't show...
				cells[a][b][c].show(x-(width/3*i)*j,y-(height/3*i)*k,width<height?width/8:height/8,NN,cellBorderColor);
			}
	updateText(bX,bO,bTurn,bStatus,1);
}

void Board::hide()
{
	int i,j,k;
	setcolor(getbkcolor());
	for(i=1;i<=3;i++)
		rectangle(x-(width/3)*i,y-(height/3)*i,x+(width/3)*i,y+(height/3)*i);
	for(i=-1;i<=1;i+=2)
	{
		line(x-(width/3)*3*i,y-(height/3)*3*i,x-width/3*i,y-height/3*i);	// \ \
		line(x+(width/3)*3*i,y-(height/3)*3*i,x+width/3*i,y-height/3*i);	// / /
		line(x+(width/3)*3*i,y,x+width/3*i,y);   // - -
		line(x,y-(height/3)*3*i,x,y-height/3*i); // | |
	}

	for(i=1;i<=3;i++)
		for(j=1;j<=3;j++)
			for(k=1;k<=3;k++)
				cells[i][j][k].hide();
	hideText();
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
	width=getmaxx()/3;
	height=getmaxy()/3;
	lineColor=BRIGHT;
	cellBorderColor=WHITE;
}

Board::Board(int newX,int newY,int newWidth,int newHeight,int newLineColor, int newCellBorderColor)
{
	initgraphics();
	x=newX;
	y=newY;
	width=newWidth;
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
