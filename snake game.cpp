#include<bits/stdc++.h>
#include<conio.h>
#include<stdio.h>
#include<windows.h>
using namespace std;


bool gameOver;
int fruitX, fruitY, posx, posy;
const int height = 25;
const int width = 80;
int score;
enum direc { STOP=0, LEFT, RIGHT, UP, DOWN };
direc dir;
int tailX[1000], tailY[1000];
int nTail;

void setup()
{
    posx = height/2;
    posy = width/2;
    fruitX = rand()%(height-2) + 1;
    fruitY = rand()%(width-2) +1;
    dir = STOP;
    gameOver = false;
    score = 0;
    nTail = 0;
}
int is=0;
void draw()
{
    int i, j, k;
    system("cls");

    for(i = 0; i < height; ++i){
        for(j = 0; j < width; ++j){
             if( (i==0 && j==0) || (i==0 && j==width-1) || (i==height-1 && j==0) || (i==height-1 && j==width-1) )
                cout << "+";
            else if(i==0 || i==(height-1))
                cout << "-";
            else if(j==0 || j==(width-1))
                cout << "|";
            else if((i==posx) && (j==posy))
                cout << "O"
            else if((i==fruitX) && (j==fruitY))
                cout << "F";
            else {
                bool printSpace = true;
                for(k = 0; k < nTail; ++k){
                    if((tailX[k] == i) && (tailY[k] == j)){
                        cout << "0";
                        printSpace = false;
                        break;
                    }
                }
                if(printSpace)
                    cout << " ";
            }
        }
        cout << endl;
    }

    bool scoreFlag = true;
    bool pauseFlag = true;
    for(i = 0; i < 5; ++i)
    {
        for(j = 0; j < width; ++j)
        {
            if( (i==0 && j==0) || (i==0 && j==width-1) || (i==4 && j==0) || (i==4 && j==width-1) )
                cout << "+";
            else if(i==0 || i==4)
                cout << "-";
            else if(j==0 || j==width-1)
                cout << "|";
            else if(i==1 && scoreFlag)
            {
                cout << "Score is : " << score;
                if(score < 10)
                    j = 12;
                else if (score >=10 && score < 99)
                    j = 13;
                else if(score >= 100 && score < 999)
                    j = 14;
                else
                    j = 15;
                scoreFlag = false;
            }
            else if(i==3 && pauseFlag){
                cout << "Pause : 'p'                Resume: 'p'                Exit : 'o'";
                j = 64;
                pauseFlag = false;
            }
            else
                cout << " ";
        }
        cout << endl;
    }

}
void input()
{
    if(_kbhit())
    {
        switch(_getch())
        {
        case 'a':
            dir = LEFT;
            break;
        case 'd':
            dir = RIGHT;
            break;
        case 'w':
            dir = UP;
            break;
        case 's':
            dir = DOWN;
            break;
        case 'o':
            gameOver = true;
            break;
        case 'O':
            gameOver = true;
            break;
        case 'p':
            char ch;
            do {
                ch = _getch();
                if(ch == 'p' || ch == 'P')
                    break;
                if(ch == '0' || ch == 'O')
                    gameOver = true;
            }while(1);
            break;
        }
    }
}
void logic()
{
    int prevx, prevy, prev2x, prev2y;
    prevx = tailX[0];
    prevy = tailY[0];

    tailX[0] = posx;
    tailY[0] = posy;


    for(int it = 1; it < nTail; ++it){
        prev2x = tailX[it];
        prev2y = tailY[it];

        tailX[it] = prevx;
        tailY[it] = prevy;

        prevx = prev2x;
        prevy = prev2y;

    }

    switch(dir)
    {
    case LEFT:
        posy--;
        break;
    case RIGHT:
        posy++;
        break;
    case UP:
        posx--;
        break;
    case DOWN:
        posx++;
        break;
    default:
        break;
    }

    if((posx==fruitX) && (posy==fruitY)){
        tailX[nTail] = prevx;
        tailY[nTail] = prevy;

        score += 10;
        fruitX = rand()%(height-2) + 1;
        fruitY = rand()%(width-2) +1;
        nTail++;
    }

    for(int it = 0; it < nTail; ++it)
        if((tailX[it]==posx) && (tailY[it]==posy))
            gameOver = true;

    if(posx==0 || posx==height-1 || posy==0 || posy==width-1)
        gameOver = true;
}

main()
{
    srand( time(NULL) );
    setup();
    while(!gameOver){
        draw();
        input();
        logic();
        Sleep(50);
    }
    cout << "Game is over now\n\n";
}

