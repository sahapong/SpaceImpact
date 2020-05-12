////////////////////// Sahapong Pathiwongpaisan 5688098 year 1 //////////////////////

#include<stdio.h>
#include<conio.h>
#include<windows.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>
#include "color.h"

////////////////////// define //////////////////////

#define R 15		//map hight
#define C 70		//map width
#define B 4			//blank
#define HP 10		//health point
#define BTIME 70	//boss come out time
#define DELAYBUL 8	//bullet delay time
#define HEARTD 30	//delay release heart
#define ITEMD 50	//delay relase item

////////////////////// struct //////////////////////

struct health
{
	int ship,shipc; 	//ship mean ship health//shipc help to know health have change
	int boss,bossc;	//ship mean boss health//shipc help to know boss health have change
};
struct clock
{
	int game,pause,ptotal;	//game is game time//pause how much time you use in pause//ptotal how much time you use in pause total
	int g1,g2,p1,p2;	//use in function time
};
////////////////////// global variable //////////////////////

char map[R][C];			//array map
char mon1[3][3];		//array monster
char boss[8][15];		//array boss
char logo[10][100];		//array logo
char logosml[10][100];	//array logo small
char hslogo[10][100];	//array high score logo
char hwlogo[10][100];	//array how to play logo
char hw[12][100];		//array how to play text
char win[10][100];		//array how to win logo
char lose[10][100];		//array how to lose logo
char warn[10][100];		//array how to warnning logo
char scorelogo[10][100];//array score logo
char name[5][15];		//array name of higchscore list
int score[5];			//array name of higchscore score
int bo=0; 					//bo mean boos status =0 boss wait,=1 boss come out
int m=6,n=2;				//coordinates of spaceship
int point=0,totalscore=0;	//point mean how many kills//totalscore mean the overall score
int p=0,monsterdelay=5;		//p mean monster delay couting //monsterdelay mean how much time for each monster come out
int item1=30,item2=60;		//time1 and time2 is time to release item
int gunstatus=1,gunc=1,bul=0; //gunstatus mean howmany bullet //gunc help to know gunstatus have change//bul help to delay bullet
int barc=1,quit=0,sq=0;		//barc help to know status game bar have to change(win lose warnning)//quit check quit//sq help random mons
struct health hp;	//struct hp of user and boss
struct clock t;		//struct time and pause time


 

////////////////////// import txt function //////////////////////

//import highscore
void geths()
{
    int i;
    char temp[105][200];
    FILE *fone;
    fone=fopen("hs.txt","r"); //fone=fopen(flevel,"r");
    if(ferror(fone)!=0)
    {
     printf("Sorry! could not open highscore file.");
    }
    else
    {
        i=0;
        while(!feof(fone))
        {
            fscanf(fone,"%s %d",&name[i],&score[i]);
            i++;
        }
        fclose(fone);
	}
}

//export highscore
void whs()
{
    int i;
    char temp[105][200];
    FILE *fone;
    fone=fopen("hs.txt","w"); //fone=fopen(flevel,"r");
    if(ferror(fone)!=0)
    {
     printf("Sorry! could not save highscore file.");
    }
    else
    {
    	for(i=0;i<5;i++)
    	{
 	  	 	fprintf(fone,"%s %d\n",&name[i],score[i]);
    	}
    	fclose(fone);
	}
}

//import monster
void getmon()
{
	char temp[5];
	int i=0;
	FILE*fp;
	fp=fopen("mon.txt","r");
	if(ferror(fp)!=0) printf("error");
	else
	{
		i=0;
        while (!feof(fp))
        {
            fgets(temp,5,fp);
            strcpy(mon1[i],temp);
            i++;
        }
        fclose(fp);
	}
}

//import boss
void getboss()
{
	char temp2[15];
	int i=0;
	FILE*fp;
	fp=fopen("boss.txt","r");
	if(ferror(fp)!=0) printf("error");
	else
	{
		i=0;
        while (!feof(fp))
        {
            fgets(temp2,15,fp);
            strcpy(boss[i],temp2);
            i++;
        }
        fclose(fp);
	}
}

//import how to play text
void gethw()
{
	char temp[200];
	int i=0;
	FILE*fp;
	fp=fopen("howto.txt","r");
	if(ferror(fp)!=0) printf("error");
	else
	{
		i=0;
        while (!feof(fp))
        {
            fgets(temp,200,fp);
            strcpy(hw[i],temp);
            i++;
        }
        fclose(fp);
	}
	hw[5][38]=26;
}

//import how to play logo
void gethwlogo()
{
	char temp[200];
	int i=0;
	FILE*fp;
	fp=fopen("hwlogo.txt","r");
	if(ferror(fp)!=0) printf("error");
	else
	{
		i=0;
        while (!feof(fp))
        {
            fgets(temp,200,fp);
            strcpy(hwlogo[i],temp);
            i++;
        }
        fclose(fp);
	}
}

//import score logo
void getscorelogo()
{
	char temp[200];
	int i=0;
	FILE*fp;
	fp=fopen("score.txt","r");
	if(ferror(fp)!=0) printf("error");
	else
	{
		i=0;
        while (!feof(fp))
        {
            fgets(temp,200,fp);
            strcpy(scorelogo[i],temp);
            i++;
        }
        fclose(fp);
	}
}

//import highscore logo
void gethslogo()
{
	char temp[200];
	int i=0;
	FILE*fp;
	fp=fopen("hslogo.txt","r");
	if(ferror(fp)!=0) printf("error");
	else
	{
		i=0;
        while (!feof(fp))
        {
            fgets(temp,200,fp);
            strcpy(hslogo[i],temp);
            i++;
        }
        fclose(fp);
	}
}

//import logosmall
void getlogosml()
{
	char temp[200];
	int i=0;
	FILE*fp;
	fp=fopen("logosml.txt","r");
	if(ferror(fp)!=0) printf("error");
	else
	{
		i=0;
        while (!feof(fp))
        {
            fgets(temp,200,fp);
            strcpy(logosml[i],temp);
            i++;
        }
        fclose(fp);
	}
}

//import lose text
void getlose()
{
	char temp[200];
	int i=0;
	FILE*fp;
	fp=fopen("lose.txt","r");
	if(ferror(fp)!=0) printf("error");
	else
	{
		i=0;
        while (!feof(fp))
        {
            fgets(temp,200,fp);
            strcpy(lose[i],temp);
            i++;
        }
        fclose(fp);
	}
}

//import win text
void getwin()
{
	char temp6[200];
	int i=0;
	FILE*fp;
	fp=fopen("win.txt","r");
	if(ferror(fp)!=0) printf("error");
	else
	{
		i=0;
        while (!feof(fp))
        {
            fgets(temp6,200,fp);
            strcpy(win[i],temp6);
            i++;
        }
        fclose(fp);
	}
}

//import warn text
void getwarn()
{
	char temp[200];
	int i=0;
	FILE*fp;
	fp=fopen("warn.txt","r");
	if(ferror(fp)!=0) printf("error");
	else
	{
		i=0;
        while (!feof(fp))
        {
            fgets(temp,200,fp);
            strcpy(warn[i],temp);
            i++;
        }
        fclose(fp);
	}
}

//import score logo
void getlogo()
{
	char temp[200];
	int i=0;
	FILE*fp;
	fp=fopen("logo.txt","r");
	if(ferror(fp)!=0) printf("error");
	else
	{
		i=0;
        while (!feof(fp))
        {
            fgets(temp,200,fp);
            strcpy(logo[i],temp);
            i++;
        }
        fclose(fp);
	}
}

////////////////////// hit the ship function //////////////////////

//hit to center
void hitme_center(int j,int i) //delete monster
{
	map[j][i]=0;
	map[j][i+1]=0;
	map[j][i+2]=0;
	map[j][i+3]=0;
	map[j+1][i+2]=0;
	map[j+1][i+3]=0;
	map[j-1][i+2]=0;
	map[j-1][i+3]=0;
}

//hit to center
void hitme_center2(int j,int i) //delete monster
{
	map[j][i]=0;
	map[j][i+1]=0;
	map[j][i+2]=0;
	map[j+1][i+1]=0;
	map[j+1][i+2]=0;
	map[j-1][i+1]=0;
	map[j-1][i+2]=0;
}

//hit to top
void hitme_top(int j,int i) //delete monster
{
	map[j][i]=0;
	map[j][i+1]=0;
	map[j][i+2]=0;
	map[j+1][i]=0;
	map[j+1][i+1]=0;
	map[j+1][i+2]=0;
	map[j+2][i+1]=0;
	map[j+2][i+2]=0;
}

//hit to bottom
void hitme_bottom(int j,int i) //delete monster
{
	map[j][i]=0;
	map[j][i+1]=0;
	map[j][i+2]=0;
	map[j-1][i]=0;
	map[j-1][i+1]=0;
	map[j-1][i+2]=0;
	map[j-2][i+1]=0;
	map[j-2][i+2]=0;
}

//check was the ship attacked
void hitme(int j,int i)
{
	//hit to center
	if((map[j][i]==16||map[j][i]==60)&&map[j][i+1]=='#'&&map[j][i+2]=='#'&&map[j][i+3]=='#') hitme_center(j,i); 
	else if((map[j][i]==16||map[j][i]==60)&&map[j][i+1]=='#'&&map[j][i+2]=='#'
										  &&map[j+1][i+1]=='#'&&map[j+1][i+2]=='#'
									  	  &&map[j-1][i+1]=='#'&&map[j-1][i+2]=='#') hitme_center2(j,i);
	//hit to top
	else if((map[j][i]==16||map[j][i]==60)&&map[j][i+1]=='#'&&map[j][i+2]=='#'&&map[j+1][i+1]=='#') hitme_top(j,i); 
	//hit to bottom
	else if((map[j][i]==16||map[j][i]==60)&&map[j][i+1]=='#'&&map[j][i+2]=='#'&&map[j-1][i+1]=='#') hitme_bottom(j,i); 
}

//increase hp
void inhp()
{
	hp.ship++;	//increase hp
	hp.shipc=1;	//help to know hp have change
}

//decrease hp
void dehp()
{
	gunstatus--;	//decrease gun status if hit
	gunc=1;			//help to know  gun status have change
	if(gunstatus<=1) gunstatus=1; //if gun status is basic no decrease
	hp.ship--;		//decrease hp
	hp.shipc=1;		//help to know hp have change
}

//gunchange form
void gunchange()
{
	gunstatus++;	//increase gun status if hit
	if(gunstatus>=3) gunstatus=3;	//if gun status is maxx no increase
	gunc=1;			//help to know  gun status have change
}

////////////////////// hit the monster function //////////////////////

//ship get hit by item or monster
void hitship(int j,int i)
{
	if(map[j][i+1]==21) gunchange();	//get item
	if(map[j][i+1]==3&&hp.ship<10) inhp();	//get heart
	else if(map[j][i+1]=='#')  { dehp(); hitme(j,i);}	//get hit by monster
}

//change position and hit monster
void hit_moveup(int c)	//deleter monster
{
	if(c==1) n--;
	map[m-2][n]=0;
	map[m-3][n]=0;
	map[m-3][n-1]=0;
	map[m-4][n]=0;
	map[m-2][n+1]=0;
	map[m-3][n+1]=0;
	map[m-4][n+1]=0;
	if(c==1) n++;
}

//change position and hit monster
void hit_movedown(int c) //deleter monster
{
	if(c==1) n--;
	map[m+2][n]=0;
	map[m+3][n]=0;
	map[m+3][n-1]=0;
	map[m+4][n]=0;
	map[m+2][n+1]=0;
	map[m+3][n+1]=0;
	map[m+4][n+1]=0;
	if(c==1) n++;
}

//shoot to center
void shoot_cen(int j,int i,int c) //deleter monster
{
	map[j][i]=0;
	if(c==1) i++;
	map[j][i+1]=0;
	map[j][i+2]=0;
	map[j][i+3]=0;
	map[j+1][i+2]=0;
	map[j+1][i+3]=0;
	map[j-1][i+2]=0;
	map[j-1][i+3]=0;
	if(c==1) i--;
	point++;
}

//shoot to top
void shoot_top(int j,int i,int c) //deleter monster
{
	map[j][i]=0;
	if(c==1) i++;
	map[j][i+1]=0;
	map[j][i+2]=0;
	map[j+1][i]=0;
	map[j+1][i+1]=0;
	map[j+1][i+2]=0;
	map[j+2][i+1]=0;
	map[j+2][i+2]=0;
	if(c==1) i--;
	point++;
}

//shoot to bottom
void shoot_bottom(int j,int i,int c) //deleter monster
{
	map[j][i]=0;
	if(c==1) i++;
	map[j][i+1]=0;
	map[j][i+2]=0;
	map[j-1][i]=0;
	map[j-1][i+1]=0;
	map[j-1][i+2]=0;
	map[j-2][i+1]=0;
	map[j-2][i+2]=0;
	if(c==1) i--;
	point++;
}

//check bullet hit monster
void hitmonster(int j,int i)
{
	//shoot to center
	if(map[j][i]=='-'&&map[j][i+1]=='#'&&map[j][i+2]=='#'&&map[j][i+3]=='#') shoot_cen(j,i,0);
	if(map[j][i]=='-'&&map[j][i+2]=='#'&&map[j][i+3]=='#'&&map[j][i+4]=='#') shoot_cen(j,i,1);
	//shoot to top
	if(map[j][i]=='-'&&map[j][i+1]=='#'&&map[j][i+2]=='#'&&map[j+1][i+1]=='#') shoot_top(j,i,0);
	if(map[j][i]=='-'&&map[j][i+2]=='#'&&map[j][i+3]=='#'&&map[j][i+4]!='#'&&map[j+1][i+2]=='#') shoot_top(j,i,1);
	//shoot to bottom
	if(map[j][i]=='-'&&map[j][i+1]=='#'&&map[j][i+2]=='#'&&map[j-1][i+1]=='#') shoot_bottom(j,i,0);
	if(map[j][i]=='-'&&map[j][i+2]=='#'&&map[j][i+3]=='#'&&map[j][i+4]!='#'&&map[j-1][i+2]=='#') shoot_bottom(j,i,1);
}

//bullet hit item
void bul_hit_item(int j,int i,int c)
{
	map[j][i]=0;	//delete bullet
	if(c==0) map[j][i+2]='-';	//make bullet go through item case1
	else map[j][i+1]='-';	////make bullet go through item csae2
}

//decrease boss health
void lose_bosshp(int j,int i)
{
	map[j][i]=0;	//delete bullet
	hp.boss--;		//decrease boss hp
	hp.bossc=1;		//help to know boss hp has change
}

//main hitting function

void hit()
{
	int i,j;
	for(j=0;j<R;j++)
	{
		for(i=0;i<C;i++)
		{
			if((map[j][i]==16||map[j][i]==60)&&(map[j][i+1]=='#'||map[j][i+1]==3||map[j][i+1]==21)) //if monster hit the ship
				hitship(j,i); 
			if(map[j][i]=='-'&&map[j][i+1]=='+') //if bullet hit the boss 
				lose_bosshp(j,i); 	
			if(map[j][i]=='-'&&(map[j][i+1]==3||map[j][i+1]==21)) bul_hit_item(j,i,0); //if bullet hit the item case1
			if(map[j][i]=='-'&&(map[j][i+1]==3||map[j][i+1]==21)) bul_hit_item(j,i,1); //if bullet hit the item case2
			hitmonster(j,i); //check if bullet hit the monster
		}
	}
}

////////////////////// printing interface //////////////////////

//gotoxy function
void gotoxy(short x, short y)
{
	COORD pos = {x, y};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

//print blank
void blank()
{
	int b;
	for(b=0;b<B;b++)
	{
		printf(" ");
	}
}

//print straight line border
void line()
{
	int i,j;
	for(i=0;i<C+1;i++)
	{
		printf("%c",219);
	}
	printf("%c",219);
}

//print straight 2line border
void linell()
{
	int i,j;
	color(darkgray,black);
	for(i=0;i<8;i++)
	{
		gotoxy(13,R+1+i);
		printf("%c",186);
		gotoxy(65,R+1+i);
		printf("%c",186);
	}
}

//print body of frame (ex. |        | )
void line2()
{
	int i,j;
	printf("\n");
	for(j=0;j<R-1;j++)
	{
		blank();
		printf("%c",219);
		for(i=0;i<C;i++)
		{
			printf(" ");
		}
		printf("%c\n",219);
	}
}

//print short straight line border
void line3()
{
	int i,j;
	for(i=0;i<4;i++)
	{
		printf("%c",219);
	}
}

//printing hp tank
void hptank()
{
	int i;
	gotoxy(0,0);	printf("    ");
	gotoxy(0,1);	printf("    ");
	gotoxy(0,3);	printf("    ");
	gotoxy(0,2);	printf("    ");
	color(white,darkviolet);
	gotoxy(1,2);	printf("HP");reset();
	color(darkgray,darkgray);
	gotoxy(0,14);	printf("    ");
	for(i=10;i>0;i--)
	{ 
		gotoxy(0,i+3);  
		printf(" ",186); 
		gotoxy(3,i+3);
		printf(" ",186); 
	}
}

//printing boss hp tank
void bhptank()
{
	int i;
	color(darkred,darkgray);
	gotoxy(76,0);	printf("    ");
	gotoxy(76,1);	printf("    ");
	gotoxy(76,2);	printf("    ");
	gotoxy(76,14);	printf("BOSS");
	color(white,darkred);
	gotoxy(77,2);	printf("HP");reset();
	color(darkgray,darkgray);
	for(i=10;i>0;i--)
	{ 
		gotoxy(76,i+2);  
		printf(" ",186); 
		gotoxy(79,i+2);
		printf(" ",186); 
	}
	reset();
}

//line vertical
void line4()
{
	int i;
	for(i=0;i<=14;i++)
	{ 
		gotoxy(76,i);
		printf("    ");
	}
}

//print game frame
void border()
{
	int i,j;
	gotoxy(0,0);
	color(darkgray,darkgray);
	blank();
	line();
	line2();
	blank();
	line();
	gotoxy(B+C+2,R); line3();
	gotoxy(0,R); line3();
	gotoxy(0,24); { line3(); line(); line3();}
	line4();
	hptank();
	linell();
	gotoxy(0,0); 
	reset();
}

//print ship hp bar
void hpbar()
{
	int i;
	if(hp.shipc==1)
	{
		for(i=10;i>0;i--) { gotoxy(1,i+2); color(violet,black); printf("%c%c",0,0);} //print all hp
		for(i=10;i>10-hp.ship;i--) { gotoxy(1,i+2); color(black,violet); printf("  "); } //print present hp
		hp.shipc=0;	//help to know change finnish 
	}
	reset();
}

//delete previous gun frame
void pregun()
{
	gotoxy(6,R+5); printf(" "); 
	gotoxy(5,R+4); printf(" "); 
	gotoxy(5,R+6); printf(" ");
}

//print gun bullet frame
void printgun()
{
	pregun(); //delete previous gun frame
	color(cyan,black);
	if(gunstatus==1) { gotoxy(6,R+5); printf("-"); } //check what gunstatus to print
	else if(gunstatus==2)//check what gunstatus to print
	{
		gotoxy(5,R+4); printf("-"); 
		gotoxy(5,R+6); printf("-");
	}
	else if(gunstatus==3) //check what gunstatus to print
	{ 
		gotoxy(6,R+5); printf("-"); 
		gotoxy(5,R+4); printf("-"); 
		gotoxy(5,R+6); printf("-"); 
	}
	reset();
	gunc=0; //help to know change finnish 
}

//ship gun frame
void gunbar()
{
	int i;
	gotoxy(2,R+2);
	printf(" BULLET");
	gotoxy(2,R+4);
	printf("%c",60);
	gotoxy(2,R+5);
	printf("%c%c%c",185,219,16);
	gotoxy(2,R+6);
	printf("%c",60);
	if(gunc) printgun(); //if gun have change re print
}

//print win logo
void winbar()
{
	int i;
	for(i=1;i<6;i++)
	{
		gotoxy(20,R+2+i);
		color(green,black);
		printf("%s",win[i]);reset();
	}
}

//print warn logo
void warnbar()
{
	int i;
	for(i=0;i<6;i++)
	{
		gotoxy(17,R+3+i);
		color(red,black);
		printf("%s",warn[i]);reset();
	}
}

//print lose logo
void losebar()
{
	int i;
	for(i=0;i<6;i++)
	{
		gotoxy(20,R+2+i);
		color(red,black);
		printf("%s",lose[i]);reset();
	}
}

//print game logo 
void logobar()
{
	int i;
	for(i=0;i<4;i++)
	{
		gotoxy(24,R+2+i);
		color(blue,black);
		printf("%s",logosml[i]);reset();
	}
	gotoxy(24,R+7);
	color(black,blue);
	printf("%s",logosml[4]);reset();
}

//delete old logo
void dellogo()
{
	int i,j;
	color(darkgray,black);
	for(j=R+1;j<R+9;j++)
	{
		for(i=15;i<65;i=i++)
		{
			gotoxy(i,j);
			printf("%c",32);
		}
	}
}


//select what logo to print
void bar()
{
	if(bo==1&&t.game<=BTIME+4) { dellogo(); warnbar();} //if boss come out print warn logo
	else if(hp.ship==0) { dellogo(); losebar();}	//if lose print lose logo
	else if(hp.boss==0) { dellogo(); winbar();}		//if win print win logo
	else { dellogo(); logobar();}	//if nothing happen print game logo 
}

//boss hp bar
void boss_hpbar()
{
	int i;
	if(bo)
	{
		if(hp.bossc==1)
		{
		for(i=10;i>0;i--) { gotoxy(77,i+2); color(violet,black); printf("%c%c",0,0);} //print all hp
		for(i=10;i>10-hp.boss;i--) { gotoxy(77,i+2); color(black,darkyellow); printf("  "); } //print present hp
		hp.bossc=0; //help to know change finnish 
		}
	reset();
	bhptank(); //print boss hp tank
	}
}

//print information
void info()
{
	gotoxy(68,R+2);
	color(white,black); printf("KILLS : ");	//print how many monster are kills
	color(red,black);
	printf("%d",point);reset();
	gotoxy(68,R+3);
	color(white,black); printf("TIME  : ");	//print time 
	color(cyan,black);
	printf("%d",t.game);
	hpbar();	//print hp
	boss_hpbar();	//print boss hp
	if(bo==1&&t.game==BTIME) barc=1;	//if boss come out change to warn logo
	if(bo==2&&t.game==BTIME+4) barc=1;	//if boss come out finnish change to game logo
	if(hp.ship==0) barc=1;	//if die change to lose logo
	if(hp.boss==0) barc=1;	//if boss die change to win logo
	if(barc){ bar(); barc=0;}	//change logo
	gunbar();	//print gun frame
}

////////////////////// moving monster && bullet && item //////////////////////

//delete monster that out of the map
void clear()
{
	int i;
	for(i=0;i<R;i++)
	{
		map[i][-1]=0;
	}
}

//random monster position
int randompos()
{
	int i;
	srand(time(0));
    i=rand()% 8;	
	return i;
}

//moving monster from right to left
void move_mon()
{
	int i,j;
	for(j=0;j<R;j++)
	{
		for(i=0;i<C;i++)
		{
			if(map[j][i]=='#')
			{
				map[j][i-1]=map[j][i];
				map[j][i]=0;	
			}
		}
	}
}
 
//moving item from right to left
void move_item()
{
	int i,j;
	for(j=0;j<R;j++)
	{
		for(i=0;i<C;i++)
		{
			if(map[j][i]==3||map[j][i]==21)
			{
				map[j][i-1]=map[j][i];
				map[j][i]=0;			
			}
		}
	}
}

//moving bullet from left toright 
void move_bullet()
{
	int i,j;
	for(j=0;j<R;j++)
	{
		for(i=C;i>=0;i--)
		{
			if(map[j][i]=='-')
			{
				map[j][i+1]=map[j][i];
				map[j][i]=0;
			}
		}
	}
}

//create monster
void summon_mons()
{
	int i,j,x,r,e;
	p=0;	//set time to release to 0
	x=randompos();	//random position to plus in original position
	x=x*pow(-1,sq);	//to make position up and down
	sq++;	//to make position plus and next minus and next plus
	while(x>4) x=4;	//make position it not out of map
	for(j=0,r=C-4;j<3;j++,r++)
	{
		for(i=0,e=7;i<3;i++,e++)
		{
			map[e+x][r]=mon1[i][j];	//put monster in map
		}
	}
}

//create boss
void summon_boss()
{
	int i,j,x,r,e;
	e=3;
	for(j=0;j<8;j++,e++)
	{
		r=53;
		for(i=0;r<C-4;i++,r++)
		{
			map[e][r]=boss[j][i]; //put boss in map
		}
	}
	bo=2;
	p=0;
}

//boss bullet
void boss_beam()
{
	int i,j,x,r,e;
	if(p==3&&bo==2)	//check it time to release and boss had come out
	{
		p=0;	//set time to release to 0
		x=randompos();	//random position to plus in original position
		x=x*pow(-1,sq);	//to make position up and down
		sq++;	//to make position plus and next minus and next plus
		while(x>4) x=4; //make position it not out of map
		for(j=0,r=50;j<3;j++,r++)
		{
			for(i=0,e=7;i<3;i++,e++)
			{
				map[e+x][r]=mon1[i][j];	//put boss bullet in map
			}
		}
	}
}

//random item position
int randompositem()
{
	int i;
	srand(time(0));
    i=rand()% 15;	
	return i;
}
//change item position if it same as monster position
int change(int x)
{
	while(map[x][C-3]=='#')
	{
		x=x++;	//if it same as monster position move it down 1 position
		if(x>=15) x=1;
	}
	return x;
}

//change item position if it same as monster position
int change2(int x)
{
	while(map[x][51]=='#')
	{
		x=x++;	//if it same as monster position move it down 1 position
		if(x>=15) x=1;
	}
	return x;
}

//create heart
void item()
{
	int x;
	x=randompositem();	//random item poistion
	//heart
	if(!bo&&t.game==item1){ x=change(x); map[x][C-3]=3; item1=item1+HEARTD;}	//release heart when boss not come out
	else if(t.game==item1) { x=change2(x); map[x][51]=3; item1=item1+HEARTD;}	//release heart when boss come out
	//item
	if(!bo&&t.game==item2){ x=change(x); map[x][C-3]=21; item2=item2+ITEMD;}	//release item when boss not come out
	else if(t.game==item2) { x=change2(x); map[x][51]=21; item2=item2+ITEMD;}	//release item when boss come out
}


//main moving function
void movemap()
{
	if(t.game==BTIME) bo=1;	//relaser boss
	if(t.game==40) { monsterdelay=4, p=0;}	//make more monster 
	move_mon();	//move monster
	move_bullet();	//move bullet
	move_item();	//move item
	if(p==monsterdelay&&!bo) summon_mons();	//release monster
	if(bo==1&&t.game==BTIME+4) summon_boss();	//release boss
	boss_beam();	//move boss bullet
	item();	//release item
	p++;	//plus	mosnter delay time
	bul++;	//plus bullet delay time
	if(bul>=DELAYBUL) bul=DELAYBUL; //if bullet delay time max dont plus
}

////////////////////// update map //////////////////////

//color in map
void mapcolor(int j,int i)
{
	if((map[j][i]=='-'||map[j][i]=='|'||map[j][i]==15||map[j][i]=='/'||map[j][i]==92)&&i<50&&hp.ship==0) color(red,black); //color when die
	else if(bo&&i>50&&map[j][i]!='-') color(darkyellow,black);	//color boss
	else if(map[j][i]=='-') color(cyan,black);	//color bullet
	else if(map[j][i]==15) color(red,black);	//collor ship when die
	else if(map[j][i]==21) color(yellow,black);	//color item
	else if(map[j][i]==3) color(violet,black);	//color heart
	else if(map[j][i]=='#'&&bo==2) color(darkred,black);	//color boss bullet
	else if(map[j][i]=='#'&&monsterdelay==5) color(darkgreen,black); //color monster
	else if(map[j][i]=='#'&&monsterdelay==4) color(darkviolet,black); //color monster 2
	else color(white,black);
}

//update map
void update()
{
	int i,j;
	t.g2=time(NULL);	//use in time function
	t.game=difftime(t.g2,t.g1);	//count time
	t.game=t.game-t.ptotal;	//minus pause time out
	for(j=0;j<R-1;j++)
	{
		gotoxy(B+1,j+1);
		for(i=0;i<C;i++)
		{
			mapcolor(j,i);
			printf("%c",map[j][i]);	//print map
			reset();
		}
	}
}

////////////////////// control //////////////////////

//position of ship
void spaceship()
{
	map[m][n]=219;
	map[m][n-1]=185;
	map[m][n+1]=16;
	map[m+1][n-1]=60;
	map[m-1][n-1]=60;
}

//delete old ship position
void del()
{
	map[m][n]=0;
	map[m][n-1]=0;
	map[m][n+1]=0;
	map[m+1][n-1]=0;
	map[m-1][n-1]=0;
}

//change position and hit heart
void move_hitheart(char key)
{
	if(key==77&&n<C-6&&(map[m][n+1]==3||map[m+1][n+1]==3||map[m-1][n+1]==3)&&hp.ship<10) inhp();
	if(key==72&&n<C-6&&(map[m-1][n+2]==3||map[m-1][n+1]==3||map[m-2][n]==3)&&hp.ship<10) inhp();
	if(key==80&&n<C-6&&(map[m+1][n+2]==3||map[m+1][n+1]==3||map[m+2][n]==3)&&hp.ship<10) inhp();
}

//change position and hit item
void move_hititem(char key)
{
	if(key==77&&n<C-6&&(map[m][n+1]==21||map[m+1][n+1]==21||map[m-1][n+1]==21)) gunchange();
	if(key==72&&n<C-6&&(map[m-1][n+2]==21||map[m-1][n+1]==21||map[m-2][n]==21)) gunchange();
	if(key==80&&n<C-6&&(map[m+1][n+2]==21||map[m+1][n+1]==21||map[m+2][n]==21)) gunchange();
}


//change position and hit monster
void move_hitmon(char key)
{
	int i,j;
	if(key==72&&n<C-6&&(map[m-1][n+2]=='#'||map[m-1][n+1]=='#'||map[m-2][n]=='#')) 
	{
		if(map[m-2][n]=='#'&&map[m-2][n-1]!='#') hit_moveup(0); //move up and hit monster case 1
		if(map[m-2][n]=='#'&&map[m-2][n-1]=='#') hit_moveup(1);	//move up and hit monster case 2
		dehp();	
	}
	if(key==80&&n<C-6&&(map[m+1][n+2]=='#'||map[m+1][n+1]=='#'||map[m+2][n]=='#'))
	{
		if(map[m+2][n]=='#'&&map[m+2][n-1]!='#') hit_movedown(0); //move down and hit monster case 1
		if(map[m+2][n]=='#'&&map[m+2][n-1]=='#') hit_movedown(1); //move down and hit monster case 2
		dehp();	
	}
}

//gunstatus
void gun()
{
	if(gunstatus==1) map[m][n+1]='-';	//gun status 1 = 1bullet
	if(gunstatus==2) {map[m+1][n]='-'; map[m-1][n]='-';} //gun status 2 = 2bullet
	if(gunstatus==3) {map[m][n+1]='-'; map[m+1][n]='-'; map[m-1][n]='-';} //gun status 3 = 3bullet
}

//pause the game
void pausegame()
{
	 t.p1=time(NULL);
	 gotoxy(30,R+7);
	 color(black,blue);
	 printf("ANYKEY TO CONTINUE");reset();
	 getch();
	 bar();
	 t.p2=time(NULL); 
	 t.pause=difftime(t.p2,t.p1); 	//count pause time
	 t.ptotal=t.ptotal+t.pause;		//count pause time total
}

//change ship position
void move(char key)
{
	if(key==72&&m>1){del();m=m--;}	//move up
	if(key==80&&m<R-3){del();m=m++;}	//move down
	if(key==75&&n>2){del();n=n--;}	//move left
	if(key==77&&n<C-6&&map[m+1][n+1]!='#'&&map[m-1][n+1]!='#'){del();n=n++;} //move right
	if(key==32&&bul==DELAYBUL) {gun(); bul=0; }	//shoot
	if(key=='p'){ pausegame();} //pause
}

//input direction
void get()
{
	char key;
	if(kbhit())
	{
		gotoxy(79,24);
		key=getch();	//get key
		move_hititem(key);	//check hit item
		move_hitheart(key);//check hit heart
		move_hitmon(key);//check hit monster
		move(key);	//move position
	} 
 }

//change the ship to explode when die
void die()
{
	del();
	map[m][n]=15;
	map[m+1][n]='|';
	map[m-1][n]='|';
	map[m+1][n+1]=92;
	map[m-1][n+1]='/';
	map[m+1][n-1]='/';
	map[m-1][n-1]=92;
	map[m][n+1]='-';
	map[m][n-1]='-';
	map[m][n+2]='-';
	map[m][n-2]='-';
	update();
	Sleep(3000); 
}

//boss die
void bossdie()
{
	int i,j;
	for(j=0;j<R;j++)
	{
		for(i=0;i<C;i++)
		{
			map[j][i]=0;	// make all map blank
		}
	}
	spaceship();
	update();
	Sleep(3000);
}

////////////////////// page //////////////////////

int chose(int l)
{
	int enter;
	if(l==0) enter=1;	//chose start game
	if(l==1) enter=2;	//chose how how to play
	if(l==2) enter=3;	//chose high score
	if(l==3) { enter=1; quit=1; };	//chose quit
	return enter;
}

//menu in start page
int menu()
{
	int enter=0,i,j,k,l=0,scroll[4][1]={0,0,0,0};
	char input;
	while(!enter) //loop until key enter
  	{
		scroll[l][0]=16; // the arrow in front menu
		for(j=13,k=0;j<20;j=j+2,k++) //print the arrow in front menu
		{
			gotoxy(31,j);
			color(darkgreen,black);
			printf("%c",scroll[k][0]);
			reset();
		}
		gotoxy(79,24);
		input=getch();	//get key (move up down or enter)
		if(input==80&&l<3) { scroll[l][0]=0; l++; }	//move down
		if(input==72&&l>0) { scroll[l][0]=0; l--;}	//move up
		if(input==13) enter=chose(l);// enter
	}
	return enter;
}

//start page
int start()
{
	int i,j,l=0,pos=27,enter;
	for(i=0;i<10;i++) //print header logo
	{
		gotoxy(6,i+4);
		if(i<=5) color(blue,black);
		printf("%s",logo[i]);reset();
	}
	i=2;
  	gotoxy(pos,13);
  	printf("      START THE GAME");
  	gotoxy(pos,15);
  	printf("      HOW TO PLAY");
  	gotoxy(pos,17);
  	printf("      HIGH SCORE");
  	gotoxy(pos,19);
  	printf("      EXIT");
  	enter=menu(); //enter menu choice
  	return enter;
}

//print time and kill and bonus point
void show_stat(int boss_bonus)
{
	int pos=30;
	gotoxy(pos,11);
  	printf("TIME        : %d",t.game);
  	Sleep(800);
  	gotoxy(pos,12);
  	printf("KILLS       : %d",point);
  	Sleep(800);
  	gotoxy(pos,13);
  	printf("BOSS BONUS  : %d",boss_bonus);
  	Sleep(800);
}

//calculate score
void calcscore(int boss_bonus)
{
	int timeb;
	if(t.game<=220&&hp.boss==0) timeb=600; //kill boss in 220 sec bonus poit
	else if(t.game>220&&hp.boss==0) timeb=500;	//kill boss use time > 220 sec	bonus poit
	else if(t.game>220&&bo) timeb=400;	//boss come out and use time > 220 sec	bonus poit
	else if(t.game<=220&&bo) timeb=300;	//boss come out die in 220 sec	bonus poit
	else if(t.game>70) timeb=200;	//die before boss come out and use time > 70 sec bonus poit
	else if(t.game<=70) timeb=100;	//die before boss come out and use time <= 70 sec bonus poit
	else if(t.game==0) timeb=0;	//open game and die no bonus poit
	totalscore=(point*10)+boss_bonus+timeb; //calculate score
}

//print score
void printscore()
{
	int i;
	gotoxy(30,15);
  	printf("SCORE       :");
  	color(yellow,black);
  	for(i=0;i<=totalscore;i++) //print score by increase by 1//for beautie
  	{	
	  	gotoxy(44,15);
  		printf("%d",i);
  		Sleep(0.97);
  	}	

  	reset();
}

//print score logo
void printscorelogo()
{
	int i;
	for(i=0;i<10;i++)
	{
		gotoxy(23,i+4);
		if(i<=5) color(blue,black);
		printf("%s",scorelogo[i]);reset();
	}
}

//check highscore rank
int checkhs()
{
	int i;
	for(i=0;i<5;i++)
	{
		if(totalscore>score[i])//check does score higher
		{
			break;
		}
	}
	return i;
}

//new high score
void new_hs()
{
	int j,newhs;
	char newh[15];
	gotoxy(27,17);
	color(green,black); printf("YOU ARE THE NEW HIGHSCORE !! ");
	gotoxy(27,18);
	color(darkblue,black); printf("ENTER YOUR NAME : "); color(red,black);
	gets(newh); reset(); //input name
	newhs=checkhs(); //check rank
	j=newhs;
	for(j=4;j>newhs;j--)	// arrange new highscore
	{
		strcpy(name[j],name[j-1]);
		score[j]=score[j-1];
	}
	strcpy(name[newhs],newh);	//set new highscore name
	score[newhs]=totalscore;	//set new highscore score
	whs(); //export new highscore
}

//finnish game page
void endgame()
{
	int i,pos=30,boss_bonus=0;
	char x=33;
	system("cls");
	if(hp.boss==0) boss_bonus=1000; //check boss die
	printscorelogo();	//print hader logo
	show_stat(boss_bonus);	//show kills time and bonus point
	calcscore(boss_bonus);	//calculate score
	printscore();	//print score
	if(totalscore>score[4]) new_hs();	//check new high score
	gotoxy(pos+1,22);
	Sleep(800);
  	printf("ENTER TO CONTINUE");
  	while(x!=13) //enter to go next page
  	{
  		x=getch();
  	}
}

//print highscore logo
void printhslogo()
{
	int i;
	for(i=0;i<10;i++)
	{
		gotoxy(10,i+4);
		if(i<=5) color(blue,black);
		printf("%s",hslogo[i]);reset();
	}
}

//high score page
void hspage()
{
	int i,j,pos=27;
	char x=33;
	printhslogo(); //print hader logo
	for(i=13,j=0;j<5;i++,j++)	//print list high score name and score
  	{
	  	gotoxy(pos-3,i); if(j==0) color(darkyellow,black);
	  	printf("%s",name[j]);
	  	gotoxy(pos+25,i);
		printf("%d",score[j]);reset();
  	}
	gotoxy(pos+5,20);
  	printf("ENTER TO CONTINUE"); 
  	while(x!=13) //enter to go next page
  	{
  		x=getch();
  	}
  	system("cls");
}

//print how to play logo
void printhwlogo()
{
	int i;
	for(i=0;i<10;i++)
	{
		gotoxy(10,i+2);
		if(i<=5) color(blue,black);
		printf("%s",hwlogo[i]);reset();
	}
}

//print how to play text
void printhw()
{
	int i;
	for(i=0;i<12;i++)
	{
		gotoxy(18,i+8);
		printf("%s",hw[i]);
	}
}

//how to play page
void howtopage()
{
	int i,j,pos=27;
	char x=33;
	printhwlogo(); //print header logo
	printhw(); //print how to play text
	gotoxy(pos+5,22);
  	printf("ENTER TO CONTINUE");
  	while(x!=13) //enter to go next page
  	{
  		x=getch();
  	}
  	system("cls");
}

//loading bar just for beautie
void loding()
{
	int i;
	for(i=0;i<23;i++)
	{
		gotoxy(28+i,14);
		color(black,gray);
		printf(" ");
		Sleep(200);
	}
}

//how creditpage
void credit()
{
	gotoxy(28,10);
	printf("SAHAPONG.PATHIWONGPAISAN");
	gotoxy(28,11);
	printf("        5688098");
	gotoxy(28,12);color(blue,black);
	printf("         MUICT");
	loding();
	reset();
	system("cls");
}

////////////////////// utility //////////////////////

//reset every variable
void resetvalue()
{
	int i,j;
	bo=0,item1=30,item2=60; 					
	m=6,n=2;			
	point=0,totalscore=0;	
	p=0,monsterdelay=5;			
	gunstatus=1,gunc=1,bul=0; 
	barc=1,quit=0,sq=0;	
	hp.ship=HP,hp.shipc=1,hp.boss=HP,hp.bossc=1;
	for(j=0;j<R;j++)
	{
		for(i=0;i<C;i++)
		{
			map[j][i]=0;
		}
	}
}

//import all file
void importfile()
{
	getboss();
	getmon();  
	getlogo();
	getlogosml();
	getwin();
	getwarn();
	getlose();
	getscorelogo();
	gethslogo();
	geths();
	gethw();
	gethwlogo();
}
//check die or not
void checkdie()
{
	if(hp.boss<=0) bossdie(); //check boss die
	if(hp.ship<=0) die(); //check user die
}

//running game process
void run_game()
{
	get();	//get input
	movemap();	//move item,monster
	clear();	//delete out of map monster
	spaceship();	//get spcaeship position
	update();	//update and re print map
	hit();	//check hitting
	info();	//print information in down frame
	checkdie();	//check die
}

//start the game
void entergame()
{
		t.g1=time(NULL);
		border();	//print frame
		update();	//update and re print map
		while(hp.ship>0&&hp.boss>0&&!quit)
		{
			run_game(); //running game process
		}
		endgame();	//go to end game page to show score
		system("cls");
}

//process the program
void porcess()
{
	int enter;
	resetvalue();
	enter=start();
	system("cls");
	if(!quit&&enter==1) entergame();	//start game
	if(!quit&&enter==2) howtopage();	//enter how to play page
	if(!quit&&enter==3) hspage();		//enter high score page
}

////////////////////// MAIN //////////////////////

int main()
{	
	int i,j;
	importfile();
	credit();
	while(!quit)	//loop until quit
	{
		porcess();	//process the program
	}
	credit();
	return 0;
}
