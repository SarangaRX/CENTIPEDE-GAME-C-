//Header Files
#include <iostream>
#include <conio.h>
#include <windows.h>
#include <string>

using namespace std;
//Declaring Global Variables
bool Defeat, shoot, MoveFWD ,MoveBCW ,CNTPD;
const int width = 20;
const int height = 20;
int x, y,  Bul1, Bul2, score ,X ,Y;
int ScoreVal ,limit , length;
int Tail1[20], tailY[20];
int TailVal;
enum Dir { STOP = 0, LEFT, RIGHT,F};
Dir dir;
void Start();
void gotoxy(short , short );
void UserManual();
void Lost();

//Functional declaration to do the changes with the hardness or the playing mode
void Hardness(char level)
{
    if( level == 'a')
    {
        ScoreVal = 10;
        limit = 15;
        length = 10;
    }
    else if ( level == 'b' )
    {
        ScoreVal = 20;
        limit = 10;
        length = 15;
    }
    else if ( level == 'c')
    {
        ScoreVal = 30;
        limit = 5;
        length = 20;
    }
}
//Setup function for set the initial values at the start
void Setup(char hardness)
{
    Hardness(hardness);
	Defeat = false ;
	dir = STOP ;
	x = width / 2 ;
	y = height - 1 ;
	X = 0 ;
	Y = 0 ;
	TailVal = length ;
	Bul1 = y - 1 ;
	Bul2 = x ;
	score = 0 ;
}
//Functional Declaration to draw the map and objects
void Draw()
{
	system("cls"); //system("clear");-+
	for (int i = 0 ; i < width + 2 ; i++)
	
		cout << "*";
	cout << endl;

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (j == 0)
				cout << "*";
			if (i == y && j == x)
				cout << "i";
			else if( i == Bul1 && j == Bul2 )
			{
				cout << "^";
			}
			else if(i == Y && j == X)
            {
                cout<<"O";
            }
			else
            {
                bool print = false;
				for (int k = 0; k < TailVal; k++)
				{
					if (Tail1[k] == j && tailY[k] == i)
					{
						cout << "o";
						print = true;
					}
				}
				if (!print)
					cout << " ";

            }

			if (j == width - 1)
				cout << "*";
		}
		cout << endl;
	}

	for (int i = 0; i < width+2; i++)
		cout << "*";
	cout << endl;
	cout << "Score:" << score << endl;
}

//functional declaration for checking inputs and progress
void Input()
{
	if (_kbhit())
	{
		switch (_getch())
		{
		case 'a':
			dir = LEFT;
			break;
		case 'd':
			dir = RIGHT;
			break;
        case 's':
            dir = F;
            shoot = true;
            break;
		case 'x':
			Defeat = true;
			Lost();
			
			break;
		}
	}
}


//functional declaration to do logical analasis
void Logic()
{
    if( Y==0 && X < 10 )
    {
        CNTPD=false;
    }
    else
    {
        CNTPD=true;
    }
    if( X == 0 )
    {
        MoveFWD = true;
        MoveBCW = false;
        if(Y!=0)
        {
            Y++;
        }
        else
        Y=0;
    }
    if(X==width-1)
    {
        MoveBCW = true;
        MoveFWD = false;
        Y++;
    }
    if(MoveFWD)
    {
      //  if(X!=1)
        X++;
//        else
//        X=0;
    }
    if(MoveBCW)
    {
  //      if(X!=width-1)
        X--;
//        else
//        X=width-1;
    }

	int prevX = Tail1[0];
	int prevY = tailY[0];
	int prev2X, prev2Y;
	Tail1[0] = X;
	tailY[0] = Y;
	for (int i = 1; i < TailVal; i++)
	{
		prev2X = Tail1[i];
		prev2Y = tailY[i];
		Tail1[i] = prevX;
		tailY[i] = prevY;
		prevX = prev2X;
		prevY = prev2Y;
	}
	switch (dir)
	{
	case LEFT:
		x--;
		dir = STOP;
		break;
	case RIGHT:
		x++;
		dir = STOP;
		break;
    case F:
        break;
	default:
		break;
	}
	//if (x > width || x < 0 || y > height || y < 0)
	//	Defeat = true;
	if (x >= width) x = width-1; //else if (x < 0) x = width - 1;
    if (x <= 0) x = 0;

	if(shoot)
    {
        Bul1--;
    }
    else  
    {
        Bul1=y-1;
        Bul2=x;
    }
    if(Bul1 == 0)
    {
        shoot=false;
    }
    if( Y > limit )
    {
        Defeat = true;
        Lost();
    }

    for( int i = 0 ; i < TailVal ; i++ )
    {
            if( Bul2 == Tail1[i] && Bul1 == tailY[i] )
            {
                Bul1 = y - 1 ;
                Bul2 = x ;
                shoot = false ;
                score += ScoreVal;
                TailVal--;
            }
    }


	for (int i = 0; i < TailVal; i++)
		if (Tail1[i] == x && tailY[i] == y)
		{
		
			Defeat = true;
Lost();
}
			
						
			
			

}
//Main function
int main()

{
int Players;
char Difficulty;
Start();
//multiplayer
cout<<"Choose Single Player or Multiplayer"<<endl<<endl;
cout<<"Enter 1 for single player Enter 2 for multiplayer = ";
cin>>Players;
cout<<endl;

if(Players==1)
{
string name1;
cout<<"Enter player name = ";
cin>>name1;
cout<<"Start to the game "<<name1<<endl<<endl<<endl;
system("pause");
UserManual();
cout<<"Enter the difficulty level 'a' for hard 'b' for medium 'c' for hard =";
cin>>Difficulty;



	Setup(Difficulty);
	while (!Defeat)
	{
		
	  
		Draw();
		Input();
		Logic();
    } 
	return 0;	
	
	
}

else if(Players==2)
{
int x=1;
while(x<=2)
{
	
	

if(x==1)
{

cout<<"Enter player1 name = ";
string name1;
cin>>name1;
cout<<"Start to the game "<<name1<<endl<<endl<<endl;
system("pause");
UserManual();
cout<<"Enter the difficulty level 'a' for hard 'b' for medium 'c' for hard =";
cin>>Difficulty;
	Setup(Difficulty);
	while (!Defeat)
	{
		
	  
		Draw();
		Input();
		Logic();
		cout<<endl<<endl;
    }	
	
	
	
}
else
{


cout<<"Enter player2 name = ";
string name2;
cin>>name2;
cout<<"Start to the game "<<name2<<endl<<endl<<endl;
system("pause");
UserManual();
cout<<"Enter the difficulty level 'a' for hard 'b' for medium 'c' for hard =";
cin>>Difficulty;
	Setup(Difficulty);
	while (!Defeat)
	{
		
	  
		Draw();
		Input();
		Logic();
    }	
	
	
	
}	
	
	
	
	
x++;	
}



	return 0;	
}	
	
	
	
	
	
}


//Startup interface
void Start()
{ // The main title, I tried to centipedeer it as best as I could
int x = 13;
int y = 0;

system("color A");              


gotoxy(x, y  );    cout<<" _________  ";  
gotoxy(x, y+1);    cout<<" | _______| "; 
gotoxy(x, y+2);    cout<<" | |        "; 
gotoxy(x, y+3);    cout<<" | |        ";
gotoxy(x, y+3);    cout<<" | |______ "; 
gotoxy(x, y+4);    cout<<" |________|";
Sleep(300);
gotoxy(x+8, y+3 );cout<<"  _______  ";
gotoxy(x+8, y+4); cout<<" |  _____| ";
gotoxy(x+8, y+5); cout<<" | |_____  "; 
gotoxy(x+8, y+6); cout<<" | ______| ";
gotoxy(x+8, y+7); cout<<" | |_____  ";
gotoxy(x+8, y+8); cout<<" |_______| ";
Sleep(300);
gotoxy(x+15,y+7); cout<<"  ___       ___  "; 
gotoxy(x+15,y+8); cout<<"  | |\\      | |  "; 
gotoxy(x+15,y+9); cout<<"  | |  \\    | |  ";
gotoxy(x+15,y+10);cout<<"  | |    \\  | |  "; 
gotoxy(x+15,y+11);cout<<"  |_|      \\|_|  ";
Sleep(300);
gotoxy(x+20,y+12);cout<<" ______________ ";
gotoxy(x+20,y+13);cout<<" |____________|";
gotoxy(x+20,y+14);cout<<"       | |  ";
gotoxy(x+20,y+15);cout<<"       | |  "; 
gotoxy(x+20,y+16);cout<<"       |_|  ";
Sleep(300);
gotoxy(x+30,y+13);cout<<"           ";
gotoxy(x+30, y+14);cout<<"  ()   ";
gotoxy(x+30, y+15);cout<<"______ ";
gotoxy(x+30, y+16);cout<<"|    | ";
gotoxy(x+30, y+17);cout<<"|    | ";
gotoxy(x+30, y+18);cout<<"|    | ";
gotoxy(x+30, y+19);cout<<"|    | ";
gotoxy(x+30, y+20);cout<<"|____| ";
Sleep(300);
gotoxy(x+35, y+19);cout<<" __________";
gotoxy(x+35, y+20);cout<<" |    __  |";
gotoxy(x+35, y+21);cout<<" |   |__| |";
gotoxy(x+35, y+22);cout<<" | _______|";
gotoxy(x+35, y+23);cout<<" | | ";
gotoxy(x+35, y+24);cout<<" |_| ";
Sleep(300);
gotoxy(x+40, y+23);cout<<"  _______  ";
gotoxy(x+40, y+24);cout<<" |  _____| ";
gotoxy(x+40, y+25);cout<<" | |_____  "; 
gotoxy(x+40, y+26);cout<<" | ______| ";
gotoxy(x+40, y+27);cout<<" | |_____  ";
gotoxy(x+40, y+28);cout<<" |_______| ";
Sleep(300);
gotoxy(x+45, y+27);cout<<"   __________  ";
gotoxy(x+45, y+28);cout<<"  |__   ___  | ";
gotoxy(x+45, y+29);cout<<"     | |   | | "; 
gotoxy(x+45, y+30);cout<<"     | |   | | ";
gotoxy(x+45, y+31);cout<<"   __| |___| | ";
gotoxy(x+45, y+32);cout<<"  |__________| ";
Sleep(300);
gotoxy(x+50, y+31);cout<<"  _______  ";
gotoxy(x+50, y+32);cout<<" |  _____| ";
gotoxy(x+50, y+33);cout<<" | |_____  "; 
gotoxy(x+50, y+34);cout<<" | ______| ";
gotoxy(x+50, y+35);cout<<" | |_____  ";
gotoxy(x+50, y+36);cout<<" |_______| ";

system("pause");
system("cls");


	
}
	


//go to function
void gotoxy(short x, short y)
{
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD position = { x, y };
	SetConsoleCursorPosition(hStdout, position);
}

//function to display the user manual
void UserManual()
{
system("cls");

cout<<"User Manual"<<endl<<endl<<endl;
cout<<"A) You can move the gun by using the key 'A' for left and 'D' for right"<<endl<<endl;
cout<<"B) You can shoot by using the S key"<<endl<<endl;
cout<<"C) You can select the hardness level at the begining"<<endl<<endl;
cout<<"D) The length of the centipede will increase with the hardness and the distance it has to come near you to kill you will be decreased.You will get more marks for hard level successful targets.Easy level 10,Medium level 20,Hard level 30.";
cout<<"E) Pree 'x' to exit the game at anytime"<<endl<<endl;
cout<<"D) Please follows these instructions while playing this game"<<endl<<endl;

system("pause");

system("cls");
	
	
}

void Lost()
{
	
//function to display the game over messege
	
cout<<"  ____   ____  ___ ___    ___       ___   __ __    ___  ____  "<<endl;
cout<<" /    | /    ||   |   |  /  _]     /   \\ |  |  |  /  _]|    \\ "<<endl;
cout<<"|   __||  o  || _   _ | /  [_     |     ||  |  | /  [_ |  D  )"<<endl;
cout<<"|  |  ||     ||  \\_/  ||    _]    |  O  ||  |  ||    _]|    / "<<endl;
cout<<"|  |_ ||  _  ||   |   ||   [_     |     ||  :  ||   [_ |    \\ "<<endl;
cout<<"|     ||  |  ||   |   ||     |    |     ||   / |      ||  .  \\"<<endl;
cout<<"|_____||__|__||___|___||_____|     \\___/   \_/   |_____||__|\\_|"<<endl;	
		
	
	
	
	
}
