#include<graphics.h>
#include<stdio.h>
#include<conio.h>
#include<iostream>
#include<dos.h>
#include<fstream>
#include<stdlib.h>
#include<math.h>
using namespace std;
struct data {
    char name[20];
    int score;
};
class graph
{
	data currentplayer;
	int x,y,time,change;
	int arrx[2],arry[2];
	int mx, my1, my2, my3, my4; // coordinates of menu positions
	int currentj;
	int maxx, maxy;
	int x_cord,y_cord;
	static int count,level,level_count,car_count;
	int last_choice,choice,total_score,level_score;

public:
 	
graph()
{
	// Varibles Initialization
	int i;
	x=0;y=0;
	count=0;
	level_count=0;
	car_count=0;
	level_score=0;
	total_score=0;
	level=0;
	choice=0;
	last_choice=0;
	change=20;
	time=200;
	x_cord=320,y_cord=480-60;
	
	// Menu Cordinates
	maxx = getmaxx();
	maxy = getmaxy();
	
	mx = 200;
	my1 = 190;
	my2 = 240;
	my3 = 290;
	my4 = 340;
	
	currentj = my1;
	
	for(i=0;i<2;i++)
	{
		arrx[i]=0;
		arry[i]=0;
	}
}
void leaderboard();
void checkscore();
void checkCurrentPlayer();
void storeScore();

// Menu Function --Display Menu
void menu()
{
    int ret = 2;
    
    // If It Returns 3 means user press Esc... exit.
    do 
	{
        if (ret == 2) {
        	
            cleardevice();
            setcolor(WHITE);
            settextstyle(3, 0, 5);
            outtextxy(150, 50, "Road Race Game");
            
            setcolor(RED);
            setlinestyle(0, 0, 3);
            line(100,120,550,120);
            
            setcolor(WHITE);
            settextstyle(8, 0, 1);
            outtextxy(100, 130, "Press Up/Down Arrow to chnage menu option.");
            
            rectangle(0, 0, maxx, maxy);

            settextstyle(3, 0, 4);
            setcolor(YELLOW);
            outtextxy(mx, my1, "1. New Game");
            outtextxy(mx, my2, "2. Help");
            outtextxy(mx, my3, "3. High Scores");
            outtextxy(mx, my4, "4. Exit");
            setcolor(RED);
            
            switch (currentj) 
			{
	            case 190:
	                outtextxy(mx, my1, "1. New Game");
	                break;
	                
	            case 240:
	                outtextxy(mx, my2, "2. Help");
	                break;
	                
	            case 290:
	                outtextxy(mx, my3, "3. High Scores");
	                break;
	                
	            case 340:
	                outtextxy(mx, my4, "4. Exit");
	                break;
            }
        }
        ret = moveselection();
        
    } while (ret != 3);
}

// Function moveSelection -- Handle Move Selecation, which option is selected, which key is pressed up,down
int moveselection()
{
    int ch = 0;
    ch = getch();
    switch (ch) 
	{
	    case 80: // down arrow key
	        if (currentj == my1) 
			{
	            currentj = my2;
	            setcolor(RED);
	            outtextxy(mx, my2, "2. Help");
	            setcolor(YELLOW);
	            outtextxy(mx, my1, "1. New Game");
	        } 
			else if (currentj == my2) 
			{
	            currentj = my3;
	            setcolor(RED);
	            outtextxy(mx, my3, "3. High Scores");
	            setcolor(YELLOW);
	            outtextxy(mx, my2, "2. Help");
	        } 
			else if (currentj == my3) 
			{
	            currentj = my4;
	            setcolor(RED);
	            outtextxy(mx, my4, "4. Exit");
	            setcolor(YELLOW);
	            outtextxy(mx, my3, "3. High Scores");
	        } 
			else if (currentj == my4) {
	            currentj = my1;
	            setcolor(RED);
	            outtextxy(mx, my1, "1. New Game");
	            setcolor(YELLOW);
	            outtextxy(mx, my4, "4. Exit");
	        }
	        break;
	
	    case 72: // up arrow key
	        if (currentj == my1) 
			{
	            currentj = my4;
	            setcolor(RED);
	            outtextxy(mx, my4, "4. Exit");
	            setcolor(YELLOW);
	            outtextxy(mx, my1, "1. New Game");
	        } 
			else if (currentj == my2) 
			{
	            currentj = my1;
	            setcolor(RED);
	            outtextxy(mx, my1, "1. New Game");
	            setcolor(YELLOW);
	            outtextxy(mx, my2, "2. Help");
	        } 
			else if (currentj == my3) 
			{
	            currentj = my2;
	            setcolor(RED);
	            outtextxy(mx, my2, "2. Help");
	            setcolor(YELLOW);
	            outtextxy(mx, my3, "3. High Scores");
	        } 
			else if (currentj == my4) 
			{
	            currentj = my3;
	            setcolor(RED);
	            outtextxy(mx, my3, "3. High Scores");
	            setcolor(YELLOW);
	            outtextxy(mx, my4, "4. Exit");
	        }
	        break;
	
	    case 13: // enter key
	        if (currentj == my1) 
			{
				ch = 27;
	        }
			else if (currentj == my2) 
			{
	            help();
	        }
			else if (currentj == my3) 
			{
	            leaderboard();
	        }
			else if (currentj == my4)
	            exit(0);
	            
	        break;
	
	    case 27: // escape key
	    	exit(0);
	        break;
	        
	    default:
	        break;
    }

    if (ch == 72 || ch == 80)
        return 1;
    else if (ch == 13 || ch == 49 || ch == 50 || ch == 51)
        return 2;
    else if (ch == 27 || ch == 52)
        return 3;
    else
        return 0;
}

// Function car -- Genrate My Car
void car(int x_cord,int y_cord)
{
	x=x_cord;
	y=y_cord;
	
	setfillstyle(1,1); // Body Color (Blue-1)
	bar(x_cord-20,y_cord-60,x_cord+20,y_cord-30);
	
	setfillstyle(1,0); // Tire Coloe (Black-0)
	bar(x_cord-50,y_cord-30,x_cord-20,y_cord);
	bar(x_cord+20,y_cord-30,x_cord+50,y_cord);
	
	setfillstyle(1,1); // Body Color (Blue-1)
	bar(x_cord-20,y_cord,x_cord+20,y_cord+30);
	
	setfillstyle(1,0); // Tire Coloe (Black-0)
	bar(x_cord-55,y_cord+30,x_cord-20,y_cord+60);
	bar(x_cord+20,y_cord+30,x_cord+55,y_cord+60);
	
	setfillstyle(1,15); //White
}

// Function r_car -- Genrate Enimies Car
void r_car(int rc_x,int rc_y)
{
	setfillstyle((level+2)%12,level+1); // Color based on level
	
	bar(rc_x-20,rc_y-60,rc_x+20,rc_y-30);
	bar(rc_x-50,rc_y-30,rc_x-20,rc_y);
	bar(rc_x+20,rc_y-30,rc_x+50,rc_y);
	
	bar(rc_x-20,rc_y,rc_x+20,rc_y+30);
	bar(rc_x-55,rc_y+30,rc_x-20,rc_y+60);
	bar(rc_x+20,rc_y+30,rc_x+55,rc_y+60);
	
	setfillstyle(1,15); //White
}
 
// Random Car Function -- Handle Random Car on Road
// Contains Logic For Placing Random Car on Road -- Number of car, where, which color
void random_car()
{
	int f=0,rc_x,rc_y,i;
	if(count<2)
	{
		do
		{
			// Select Number of car at given time -- 1 or 2....
			choice=rand()%10;
		}while(choice==last_choice);
		
		last_choice=choice;
		
		// Where To Place Car on Road.
		switch(choice)
		{
			// On First Lan
			case 0:
				rc_x=200;
				rc_y=change;
				break;
				
			// On Second Lan
			case 1:
				rc_x=320;
				rc_y=change;
				break;
				
			// On Third Lan
			case 2:
				rc_x=440;
				rc_y=change;
				break;
		}
		
		for(i=0;i<2;i++)
		{
			if(arrx[i]==0 && arry[i]==0)
			{
				arrx[i]=rc_x;
				arry[i]=rc_y;
				break;
			}
		}
		count++;
	}
	
	for(i=0;i<2;i++)
	{
		if(!(arrx[i]==0 && arry[i]==0))
			r_car(arrx[i],arry[i]);  // Function Call To r_car to genrate car.
	}
}
 
// Car Crash Function -- Hnadle When car Crash
void cord_match()
{
	int i,j;
	
	for(i=0;i<2;i++)
	{
		// Condition For Car Crash
		if(arry[i]>=y-60&&arry[i]<=700&&arrx[i]>=x-60&&arrx[i]<=x+60)
		{
			// If Car Crashed --Display Msg and Exit.
			// Display Message
			setcolor(4);
			settextstyle(8,0,5);
			outtextxy(220,220,"Game Over");
			
			setcolor(15);
			settextstyle(8,0,2);
			outtextxy(220,270,"Press any key to continue!");
			getch();
    		currentplayer.score = total_score;
    		strcpy(currentplayer.name,"");
    		storeScore();
    		exit(0);
		}
	}
}
 
// System Function
void gotoxy(int x,int y)
{
	COORD coord;
	coord.X=x;
	coord.Y=y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}

// Road Function Declaration
void road(int x_cord,int y_cord);

// Help Function -- Display Game Info
void help()
{
    cleardevice();
    
    settextstyle(3, 0, 4);
    setcolor(RED);
    outtextxy(100, 20, "HELP");
    
    setcolor(WHITE);
    rectangle(100, 70, 590, 450);
    
    setcolor(WHITE);
    settextstyle(8, 0, 1);
    
    outtextxy(120, 100, "Hello From Raod Racing");
    outtextxy(120, 130, "IN THIS GAME YOU HAVE TO SAVE YOUR CAR ");
    outtextxy(120, 160, "FROM THE DESCENDING CARS.");
    
    outtextxy(120, 200, "Created By: ");
    
    setcolor(YELLOW);
	outtextxy(120, 230, "Group - 04");
	outtextxy(120, 260, "Karan Raj - 20CP306");
	outtextxy(120, 290, "Dhaval Rana - 20CP315");
	outtextxy(120, 320, "Daxesh Patel - 20CP305");
    
    settextstyle(3, 0, 4);
    setcolor(RED);
    outtextxy(200, 400, " ***BEST OF LUCK*** ");
    
    getch();
}
};

// Road Function --Handle Everything on Road..
void graph::road(int x_cord,int y_cord)
{
	// Parameter x_cord, y_cord is used for my car.
	
	int x1,y1,x2,y2,i=0;
	static int flag=0;
	
	cleardevice();
	
	// Road Coordinates
	x1=320-180;
	x2=320+180;
	y1=0;
	y2=800;
	
	// Road Bar
	setfillstyle(1,7);
	bar(x1,y1,x2,y2);
	
	setfillstyle(1,15);
	
	//Text Style For Level,Score Text
	settextstyle(8, 0, 2);
	// Displaying Result-- Level, LevelScore, TotalScore
	
	//Total Score
	char msg[50];
	sprintf(msg, "Total Score =%d", total_score);
	setcolor(RED);
	outtextxy(550,100,msg);
	
	//Level
	char msg1[50];
	sprintf(msg1, "Level =%d", level+1);
	setcolor(WHITE);
	outtextxy(550,130,msg1);
	
	//Level Score
	char msg2[50];
	sprintf(msg2, "Level Score =%d", level_score);
	outtextxy(550,160,msg2);
		
	
	if(flag==0)
	{
		i=0;
		flag=1;
	}
	else
	{
		flag=0;
		i=50;
	}
	
	// Road's center Bars (Moving White bar on road)
	for(;i<=800-50;i=i+120) 
	{
		bar(315,i,325,i+50);
	}
	
	// My car
	// Function Call To place My car on given X,y Coordinates
	car(x_cord,y_cord);
	
	// Enimies Car
	// Function Call To place Enimies Car Randomly
	random_car();
	
	for(i=0;i<2;i++)
	{
		if(arry[i]!=0)
			arry[i]+=change;
			
		if(arry[i]>700)
		{
			arrx[i]=arry[i]=0;
			count--;
			car_count++;
			level_score=car_count*((level+1)*10);
		}
	}
	
	// On Car Crash
	// Function Call To Perform Action on Car Crash
	cord_match();
	
	if(car_count==10)
	{
		total_score=total_score+level_score;
		
		car_count=0;
		level++;
		if(change<60)
			change+=5;
		if(time-50>0)
			time-=5;
	}
	
	// To Speed Up Road Moving Difficulties based on Level
	// Delay Function Handle Road Movement speed. (Low Level: slow Speed...)
	delay(time);
}

int graph::count=0,graph::level=0,graph::level_count=0,graph::car_count=0;

// Leaderboard Function -- Display Game Scores
void graph::leaderboard()
{
	cleardevice();
	
	setcolor(RED);
	settextstyle(3, 0, 4);
    outtextxy(100, 20, "Leaderboard");
    
    setcolor(RED);
    settextstyle(8, 0, 3);
	
	outtextxy(100, 130, "Name");
	outtextxy(100, 160, "-----");
	outtextxy(400, 130, "Score");
	outtextxy(400, 160, "-----");
	setcolor(WHITE);
	settextstyle(8, 0, 2);
	
	int i=1;
	fstream file;
	file.open("RoadRaceScore",ios::in);
	data x;
	
	if(file)
	{
		while(!file.eof())
	    {
	    	file.read((char*)&x, sizeof(x));
	        if (file) 
			{
					outtextxy(100, 185+i , x.name);
		        
			        char scr[50];
			        sprintf(scr,"%d",x.score);
			        outtextxy(400, 185+i ,scr);
			        
			        i+=30;	
			}
	    }
	}    
	file.close();
	
	setcolor(YELLOW);
	outtextxy(50, maxy - 25, "Press <Esc.> to exit...");
	int ch;
	do {
	    ch = getch();
	} while (ch != 27);
}

// CheckStore Function -- Comapre Score and add to file (MIMP)
void graph::checkscore()
{
	fstream file;
    file.open("RoadRaceScore",ios::in);
    data x;
    int pos;
    int flag=0;
    
    // Chechk if file exist or not
    if(file)
    {
    	// create temp file to write data
    	ofstream fo("RoadRaceScore1", ios::out | ios::binary);
    	
    	// check user alredy exist in file or not
    	while(!file.eof())
	    {
	    	// get Position
	    	pos = file.tellp();
	    	
	    	file.read((char*)&x, sizeof(x));
	        if (file) 
			{
				// If user found
		    	if((strcmp(x.name,currentplayer.name)==0))
		    	{
		    		// set flag --No Append at end
		    		flag=1;
		    		
		    		// overwrite alredy existing user score
		    		fo.seekp(pos);
		    		
		    		if(x.score < currentplayer.score)
		    		{
		    			fo.write((char*)&currentplayer, sizeof(currentplayer));
					}
					else
					{
						fo.write((char*)&x, sizeof(x));
					}
    				
				}
				// if not found write other user as it is...
				else
				{
					fo.write((char*)&x, sizeof(x));
				}
			}
	    }
	    // If user alredy not found then append this user
	    // flag=0-- append
	    if(flag==0)
	    {
	    	fo.write((char*)&currentplayer, sizeof(currentplayer));
		}
	    fo.close();
	}
	// If file not exist create new and append/ write first user
	else
	{
		ofstream fo("RoadRaceScore1", ios::app | ios::binary);
		fo.write((char*)&currentplayer, sizeof(currentplayer));
		fo.close();
	}
    file.close();
    remove("RoadRaceScore");
    rename("RoadRaceScore1", "RoadRaceScore");
    
    /*
    Working:
    	1. open file, if file exist then step 3, if file not exist step 2
    	2. if file not exist, create temp file and write user data
    	
    	3. if file exist, check is given user alredy exist, if exist step 4, if not stpe 5
    	4. if given user exist, get its position and overwrite it's score.
    	
    	NOTE: in loop wether user exist or not write other user data as it is...
    	
    	5. if given user not exist, at end append user data in temp
    	
    	6. copy temp to orignal file, delete temp.
    */
}

// Function storeScore -- on Game over display user score, take user name and perform file operation
void graph::storeScore()
{
	cleardevice();
    settextstyle(3, 0, 4);
    setcolor(RED);
    outtextxy(100, 20, "Your Score");
    setcolor(WHITE);
    rectangle(100, 70, 590, 450);
    setcolor(WHITE);
    settextstyle(8, 0, 1);
    
    char msg[50];
	sprintf(msg, "Your Score = %d", currentplayer.score);
	outtextxy(120,100,msg);	
	
    outtextxy(120, 130, "Enter Your Name: ");

	// Take user input in graphics mode LOGIC
	int input_pos = 0;
    int the_end = 0;
	do
	{
	   outtextxy (120,160, currentplayer.name);
	   char c = getch();
	   switch (c)
	   {
	        case 8: /* backspace */
	          if (input_pos)
	          {
	             input_pos--;
	             currentplayer.name[input_pos] = 0;
	          }
	          break;
	          
	        case 13: /* return */
	          the_end = 1;
	          break;
	          
	        case 27: /* Escape = Abort */
	          currentplayer.name[0] = 0;
	          the_end = 1;
	          break;
	          
	        default:
	          if (input_pos < 20-1 && c >= ' ' && c <= '~')
	          {
	             currentplayer.name[input_pos] = c;
	             input_pos++;
	             currentplayer.name[input_pos] = 0;
	          }
	   }
	} while (!the_end);
	
	if((strcmp(currentplayer.name,"")==0))
	{
		strcpy(currentplayer.name,"user");
	}
	
	checkscore();
	outtextxy (120,190, "Your data has been saved");
	setcolor(RED);
	outtextxy (120,220, "Press any key to go to main menu");
	delay(1000);
	getch();
	menu();	
}

// Main Function
int main()
{
	initwindow(1500,1000,"Game");
	int errorcode;
	int i,x_cord=320,y_cord=650;
	
	char ch;
	errorcode = graphresult();
	if (errorcode != grOk)
	{
		printf("Graphics error: %s\n", grapherrormsg(errorcode));
		printf("Press any key to halt:");
		getch();
		exit(1);
	}
	
//	int directvideo=0;
//	int randomize();
	
	graph g;
	
	// dISPLAY MENU
	g.menu();
	
	do
	{
		do
		{
			do
			{
				// Call To Road Function -- Which Will Start Game
				g.road(x_cord,y_cord);
				
			}while(!kbhit());
			
			ch=getch();
			
		}while(!(ch=='a'||ch=='A'||ch=='d'||ch=='D'||ch==77||ch==75));
		
		// Handling My Car Movements
		
		// LEFT
		if(ch=='a'||ch=='A'|| ch==75)
		{
			if(x_cord>=320-60)
			x_cord-=120;
		}
		// RIGHT
		else if(ch=='d'||ch=='D'|| ch==77)
		{
			if(x_cord<=320+60)
			x_cord+=120;
		}
		
	}while(!(ch==13||ch==27));	
	
	getch();
	return 0;
}
