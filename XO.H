
#include "C:\XO\SETTINGS.H"
class XO
{
	private:
		int game[4][4][4];  //Main game data containe
		int turn;	    // turn of XX or OO ?
		int status;		// 1: Level1, 2: Level2, 3: Dooz in level 2, 4: Moving...
		int X,O;		// Count of remaining X and O's
		void end(int);
		int oldXdooz,oldOdooz;	// contains last dooz counts
		int getDoozCount(int);
		void H(int,int,int);	// highlight
		void uH(int,int,int);	// undo highlight
		void findH(int*,int*,int*);// find and returns highlighted cell's position
	public:
		Board board;
		XO();
		~XO();
		void show();
		void move(int);  // 1: up, 2: right, 3: down, 4: left
		void select();
		void check();
};
void XO::end(int who)
{
	char winner;
	int i;
	clrscr();
	switch(who)
	{
		case XX: winner='X'; break;
		case OO: winner='O'; break;
		default: winner='N';
	}

	for(i=1;i<=960;i++) cout<<winner;
	if(who==NN)
		cout<<"\n\n\t\t\t\t.oO0 Game Equal 0Oo.\t\t\t\t\n\n\n";
	else
	{
		cout<<"\n\n\t\t\tHey "<<winner<<"(";
		if     (winner=='X') cout<<"Red";
		else if(winner=='O') cout<<"Green";
		cout<<")"<<", This game is yours!...\t\t\t\n\n\n";
	}
	for(i=1;i<=960;i++) cout<<winner;

	getch();
	exit(0);
}

int XO::getDoozCount(int who)
{
	int i, j, count=0;
	switch (who)
	{
	case XX:
		for (i = 1; i <= 3; i++)
			for (j = 1; j <= 3; j++)
			{
				if ((game[i][j][1] == XX || game[i][j][1] == XH) && (game[i][j][2] == XX || game[i][j][2] == XH) && (game[i][j][3] == XX || game[i][j][3] == XH))
					count++;
				if ((game[i][1][j] == XX || game[i][1][j] == XH) && (game[i][2][j] == XX || game[i][2][j] == XH) && (game[i][3][j] == XX || game[i][3][j] == XH))
					count++;
				if ((game[1][i][j] == XX || game[1][i][j] == XH) && (game[2][i][j] == XX || game[2][i][j] == XH) && (game[3][i][j] == XX || game[3][i][j] == XH))
					count++;
			}
			break;
	case OO:
		for (i = 1; i <= 3; i++)
			for (j = 1; j <= 3; j++)
			{
				if ((game[i][j][1] == OO || game[i][j][1] == OH) && (game[i][j][2] == OO || game[i][j][2] == OH) && (game[i][j][3] == OO || game[i][j][3] == OH))
					count++;
				if ((game[i][1][j] == OO || game[i][1][j] == OH) && (game[i][2][j] == OO || game[i][2][j] == OH) && (game[i][3][j] == OO || game[i][3][j] == OH))
					count++;
				if ((game[1][i][j] == OO || game[1][i][j] == OH) && (game[2][i][j] == OO || game[2][i][j] == OH) && (game[3][i][j] == OO || game[3][i][j] == OH))
					count++;
			}
		break;
	}
	return count;
}

void XO::check()
{
	int newXdooz=0,newOdooz=0,i,j,k;
	newXdooz = getDoozCount(XX);
	newOdooz = getDoozCount(OO);
	if (newXdooz > oldXdooz)
	{
		if (status == 1)
		{
			O--;
		}
		else if (status == 2)
		{
			status = 3;
		}
		turn=XX;
	}
	else if (newOdooz > oldOdooz)
	{
		if (status == 1)
		{
			X--;
		}
		else if (status == 2)
		{
			status = 3;
		}
		turn=OO;
	}
	switch (status)
	{
	case 1:
		if (X <= 0 && O <= 0)
		{
			if(O<0 || X<0) status = 3; else status = 2;   // when pawn count is 0 and new dooz detected it will be less than 0

			for (i = 1; i <= 3; i++) //floor
				for (j = 1; j <= 3; j++) //column
					for (k = 1; k <= 3; k++) //row
					{
						if (game[i][j][k] == XX || game[i][j][k] == XH)      X++;
						else if (game[i][j][k] == OO || game[i][j][k] == OH) O++;
					}
			if( (X==TOTALX) && (O==TOTALO) ) end(NN); // if nothing removed, we don't have any space to move our pawn. so, game ended without winner

		}
		break;
	case 2:
		if (X < 3)
			end(OO);
		else if (O < 3)
			end(XX);
	}

	oldXdooz = newXdooz;
	oldOdooz = newOdooz;
}

void XO::select()
{
	int i,j,k;
	switch (status)
	{
	case 1:	// Level 1
		for (i = 1; i <= 3; i++) //floor
			for (j = 1; j <= 3; j++) //column
				for (k = 1; k <= 3; k++) //row
					if (game[i][j][k] == HH)
					{
						if (turn == XX)
						{
							game[i][j][k] = XH;
							X--;
							turn = OO;
						}
						else if (turn == OO)
						{
							game[i][j][k] = OH;
							O--;
							turn = XX;
						}
					}
		break;
	case 2: // Level 2
		for (i = 1; i <= 3; i++) //floor
			for (j = 1; j <= 3; j++) //column
				for (k = 1; k <= 3; k++) //row
					if ( (game[i][j][k] == XH && turn==XX)||(game[i][j][k] == OH && turn==OO) )
					{
						if((turn==XX && X==3)||(turn==OO && O==3))
						{
							game[i][j][k] = MOVINGH;
							status = 4;
						}
						else
						{
							if( (i+1<4 && game[i+1][j][k]==NN) || (i-1>0 && game[i-1][j][k]==NN)
							 || (j+1<4 && game[i][j+1][k]==NN) || (j-1>0 && game[i][j-1][k]==NN)
							 || (k+1<4 && game[i][j][k+1]==NN) || (k-1>0 && game[i][j][k-1]==NN) )
							 {
								game[i][j][k] = MOVINGH;
								status = 4;
							 }
						}
					}
		break;
	case 3: // Level 2 --> Dooz
		for (i = 1; i <= 3; i++) //floor
			for (j = 1; j <= 3; j++) //column
				for (k = 1; k <= 3; k++) //row
					if(game[i][j][k] == XH&&turn == OO)
					{
						game[i][j][k] = HH;
						X--;
						status=2;
						turn=XX;
					}
					else if(game[i][j][k] == OH&&turn == XX)
					{
						game[i][j][k] = HH;
						O--;
						status=2;
						turn=OO;
					}
		break;
	case 4: // Level 2 --> Moving...
		for (i = 1; i <= 3; i++) //floor
			for (j = 1; j <= 3; j++) //column
				for (k = 1; k <= 3; k++) //row
					if (game[i][j][k] == MOVINGH)
					{
						if (turn == XX)
							game[i][j][k] = XH;
						else if (turn == OO)
							game[i][j][k] = OH;
						oldXdooz++;
						status=2;
					}
					else if (game[i][j][k] == HH)
					{
						if(turn==XX && X==3)
						{
							game[i][j][k] = XH;
							turn = OO;
							status = 2;
						}
						else if(turn==OO && O==3)
						{
							game[i][j][k] = OH;
							turn = XX;
							status = 2;
						}
						else
						{
							if( game[i+1][j][k]==MOVING || game[i-1][j][k]==MOVING
							 || game[i][j+1][k]==MOVING || game[i][j-1][k]==MOVING
							 || game[i][j][k+1]==MOVING || game[i][j][k-1]==MOVING )
							{
								if (turn == XX)
								{
									game[i][j][k] = XH;
									turn = OO;
								}
								else if (turn == OO)
								{
									game[i][j][k] = OH;
									turn = XX;
								}
								status = 2;
							}

						}
					}
		if (status == 2)
			for (i = 1; i <= 3; i++) //floor
				for (j = 1; j <= 3; j++) //column
					for (k = 1; k <= 3; k++) //row
						if (game[i][j][k] == MOVING)
						{
							game[i][j][k] = NN;
						}
	}
				
	check();show();
}

void XO::H(int i,int j,int k)
{
	if(game[i][j][k]==NN)
		game[i][j][k]=HH;
	else if(game[i][j][k]==XX)
		game[i][j][k]=XH;
	else if(game[i][j][k]==OO)
		game[i][j][k]=OH;
	else if(game[i][j][k]==MOVING)
		game[i][j][k]=MOVINGH;
}

void XO::uH(int i,int j,int k)
{
	if(game[i][j][k]==HH)
		game[i][j][k]=NN;
	else if(game[i][j][k]==XH)
		game[i][j][k]=XX;
	else if(game[i][j][k]==OH)
		game[i][j][k]=OO;
	else if(game[i][j][k]==MOVINGH)
		game[i][j][k]=MOVING;
}

void XO::findH(int *a, int *b, int *c)
{
	int i,j,k;
	for(i=1;i<=3;i++) //floor
		for(j=1;j<=3;j++) //column
			for(k=1;k<=3;k++) //row
				if(game[i][j][k]==HH||game[i][j][k]==XH||game[i][j][k]==OH||game[i][j][k]==MOVINGH)
				{
					 *a=i;
					 *b=j;
					 *c=k;
					 return;
				}

}

void XO::move(int direction)
{
	int i,j,k;
	findH(&i,&j,&k);
	switch(direction)
	{
		case UP:
			if(j==2)
			{
				if(k==1)
				{
					if(i+1<=3)
					{
						H(i+1,j,k);
						uH(i,j,k);break;
					}
					else
					{
						H(i,j,3);
						uH(i,j,k);break;
					}
				}
				if(k==3)
				{
					if(i-1>=1)
					{
						H(i-1,j,k);
						uH(i,j,k);break;
					}
					else
					{
						H(i,j,k-2);
						uH(i,j,k);break;
					}
				}
			}
			else
			{
				if(k-1>=1)
				{
					H(i,j,k-1);
					uH(i,j,k);break;
				}
				else if(i+1<=3)
				{
					H(i+1,j,k);
					uH(i,j,k);break;
				}
				else
				{
					H(i,j,3);
					uH(i,j,k);break;
				}
			}
		break;
		//////////////////////////////////////////////////////////////////////////////
		case RIGHT:
			if(k==2)
			{
				if(j==1)
				{
					if(i-1>=1)
					{
						H(i-1,j,k);
						uH(i,j,k);break;
					}
					else
					{
						H(i,j+2,k);
						uH(i,j,k);break;
					}
				}
				if(j==3)
				{
					if(i+1<=3)
					{
						H(i+1,j,k);
						uH(i,j,k);break;
					}
					else
					{
						H(i,1,k);
						uH(i,j,k);break;
					}
				}
			}
			else
			{
				if(j+1<=3)
				{
					H(i,j+1,k);
					uH(i,j,k);break;
				}
				else if(i+1<=3)
				{
					H(i+1,j,k);
					uH(i,j,k);break;
				}
				else
				{
					H(i,1,k);
					uH(i,j,k);break;
				}
			}
		break;
		//////////////////////////////////////////////////////////////////////////////
		case DOWN:
			if(j==2)
			{
				if(k==1)
				{
					if(i-1>=1)
					{
						H(i-1,j,k);
						uH(i,j,k);break;
					}
					else
					{
						H(i,j,k+2);
						uH(i,j,k);break;
					}
				}
				if(k==3)
				{
					if(i+1<=3)
					{
						H(i+1,j,k);
						uH(i,j,k);break;
					}
					else
					{
						H(i,j,1);
						uH(i,j,k);break;
					}
				}
			}
			else
			{
				if(k+1<=3)
				{
					H(i,j,k+1);
					uH(i,j,k);break;
				}
				else if(i+1<=3)
				{
					H(i+1,j,k);
					uH(i,j,k);break;
				}
				else
				{
					H(i,j,1);
					uH(i,j,k);break;
				}
			}
		break;
		//////////////////////////////////////////////////////////////////////////////
		case LEFT:
			if(k==2)
			{
				if(j==1)
				{
					if(i+1<=3)
					{
						H(i+1,j,k);
						uH(i,j,k);break;
					}
					else
					{
						H(i,3,k);
						uH(i,j,k);break;
					}
				}
				if(j==3)
				{
					if(i-1>=1)
					{
						H(i-1,j,k);
						uH(i,j,k);break;
					}
					else
					{
						H(i,j-2,k);
						uH(i,j,k);break;
					}
				}
			}
			else
			{
				if(j-1>=1)
				{
					H(i,j-1,k);
					uH(i,j,k);break;
				}
				else if(i+1<=3)
				{
					H(i+1,j,k);
					uH(i,j,k);break;
				}
				else
				{
					H(i,3,k);
					uH(i,j,k);break;
				}
			}
	}
	show();

}

void XO::show() // Show variables with graphics
{
	int i,j,k;
	
	board.updateText(X,O,turn,status);
	
	/* Update Cells */
	for(i=1;i<=3;i++)
		for(j=1;j<=3;j++)
			for(k=1;k<=3;k++)
				if(board.cells[i][j][k].mode!=game[i][j][k])
					board.cells[i][j][k].changeMode(game[i][j][k]);
}

XO::XO()
{

	// Preset Variables
	int i,j,k;
	for(i=1;i<=3;i++) //floor
		for(j=1;j<=3;j++) //column
			for(k=1;k<=3;k++) //row
			{
				if(j==2&&k==2)
					game[i][j][k]=Null;
				else
					game[i][j][k]=NN;
			}
	game[3][1][1]=HH;
	turn=FIRSTGAMER;
	status=1;

	X=TOTALX;
	O=TOTALO;
	oldXdooz=0;
	oldOdooz=0;

	// Convert Variables to Graphics
	board.show();
	show();
}

XO::~XO()
{
	closegraph();
	clrscr();
}
