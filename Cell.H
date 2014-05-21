class Cell
{
	private:
	int x,y;
	int r;
	int fillStyle,fillColor,borderColor;

	public:
	int mode;
	Cell();
	Cell(int newX,int newY,int newR,int newMode=NN,int newBorderColor=15);
	void move(int newX,int newY);
	void hide();
	void changeMode(int newMode);
	void show();
	void show(int newX,int newY,int newR,int newMode=NN,int newBorderColor=15);
};

void Cell::hide()
{
	// Draw a circle which it's color is different with fill color
	setcolor(fillColor+2);
	circle(x,y,r);

	// fill circle with background color --> hide circle fill
	setfillstyle(fillStyle,getbkcolor());
	floodfill(x,y,fillColor+2);

	// Draw circle border with background color --> hide border
	setcolor(getbkcolor());
	circle(x,y,r);
}

Cell::Cell()
{
	x=y=mode=0;
	r=10;
	borderColor=15;
}

Cell::Cell(int newX,int newY,int newR,int newMode, int newBorderColor)
{
	x=newX;
	y=newY;
	r=newR;
	mode=newMode;
	borderColor=newBorderColor;
}

void Cell::changeMode(int newMode)
{
	hide();
	mode=newMode;
	show();
}

void Cell::move(int newX,int newY)
{
	hide();
	x=newX;
	y=newY;
	show();
}

void Cell::show(int newX,int newY,int newR,int newMode,int newBorderColor)
{
	x=newX;
	y=newY;
	r=newR;
	mode=newMode;
	borderColor=newBorderColor;
	show();
}

void Cell::show()
{
	switch(mode)
	{
		case NN:
			fillStyle=1;
			fillColor=0;
		break;
		case HH:
			fillStyle=10;
			fillColor=15;
		break;
		case XX:
			fillStyle=1;
			fillColor=4;
		break;
		case OO:
			fillStyle=1;
			fillColor=2;
		break;
		case XH:
			fillStyle=9;
			fillColor=4;
		break;
		case OH:
			fillStyle=9;
			fillColor=2;
		break;
		case MOVING:
			fillStyle=1;
			fillColor=1;
		break;
		case MOVINGH:
			fillStyle=9;
			fillColor=1;
		break;
		case Null:
			return;
	}
	setcolor(borderColor);  // border color
	circle(x,y,r);
	setfillstyle(fillStyle,fillColor); // style,color
	floodfill(x,y,borderColor);
}
