#include <graphics.h>
#include <stdlib.h>
#include <dos.h>
#include <time.h>

void PrintPath(int i, int j, int color) {
    int x,y;
    setfillstyle(SOLID_FILL,color);
    x = 303+50*i;
    y = 152+50*j ;
    bar3d(x, y, x+50, y+50, 0, 0);
    rectangle(x,y,x+50,y+50);
}

void SetValues(int maze[12][12]) {
    int i,j;
    for(j=0 ; j<12 ; j++) {
        maze[0][j] = 1;
        maze[11][j] = 1;
        maze[j][0] = 1;
        maze[j][11] = 1;
    }
    for(i=1; i<11 ; i++) {
        for(j=1; j<11 ; j++) {
            maze[i][j] =((rand()%3)%2);
        }
    }
    maze[1][1] = 0;
    maze[10][10] =0;

}

void PrintMaze(int maze[12][12]) {
    int i,j;

    setfillstyle(1,RED);
    for(i = 0; i < 12;i++)
    {
	     for(j = 0;j < 12;j++)
	      {
 			rectangle(300+50*(i), 150+50*(j), 300+50*(i)+50, 150+50*(j)+50);
			if(maze[i][j] == 1)
			{
			     bar3d(300+50*(i), 150+50*(j), 300+50*(i)+50, 150+50*(j)+50, 0, 3);
			}
	      }
    }

    PrintPath(1, 1, 14);
    PrintPath(10, 10, 2);

    delay(1000);
}

main() {

    initwindow(1280,853,"Rat in a Maze");
    readimagefile("ratinmaze.jpg",0,0,1280,853);
    delay(1200);
    readimagefile("bg.jpg",0,0,1280,853);
    int i,j,l,m;
    srand(time(NULL));

    int maze[12][12];

    SetValues(maze);

    PrintMaze(maze);

    int mark[12][12];
    for(i=0; i<12 ; i++) {
        for(j=0 ; j<12 ; j++) {
            mark[i][j] = maze[i][j];
        }
    }

    int move[8][2] = {{-1,0},{-1,1},{0,1},{1,1},{1,0},{1,-1},{0,-1},{-1,-1}};

    int stack[144][3];

    int g, h, p, dir, top = 1;
    stack[top][0] = 1;
    stack[top][1] = 1;
    stack[top][2] = 1;

    while(top>0) {
        i = stack[top][0];
        j = stack[top][1];
        dir = ((stack[top][2])+1);
        top = top-1;
        while(dir<8) {
            g = i + move[dir][0];
            h = j + move[dir][1];
            if((g==10) && (h==10)) {
                for(p=1 ; p<= top ; p++) {
                    l = stack[p][0];
                    m = stack[p][1];
                }
                readimagefile("found.jpg",0,0,1280,853);
                getch();
                return(0);
            }

            if( (maze[g][h]==0)  && (mark[g][h]==0)) {
                mark[g][h] = 1;

                top = top+1;
                stack[top][0] = i;
                stack[top][1] = j;
                stack[top][2] = dir;
                i = g;
                j = h;
                setcolor(BLACK);
                PrintPath(g, h, 15);
                delay(300);
                dir = -1;
            }
            dir = dir+1;
        }
        setcolor(WHITE);
        PrintPath(i, j, 1);
        delay(300);
    }


    readimagefile("notfound.jpg",0,0,1280,853);
    getch();
}
