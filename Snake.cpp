#This code is not my original work, I learned it from Angulars from Youtube.

#include<iostream>
#include<conio.h>
#include<windows.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

#define width 100
#define height 40

bool gameOver;
int count = 0;
int x, y, fruitx, fruity, score;
int tailX[100], tailY[100];
int ntail;

enum eDirection{STOP = 0, LEFT, RIGHT, UP, DOWN};
eDirection dir;

//Snake Game Functions

void Setup()
{
    gameOver = false;
    dir = STOP;
    x = width / 2;
    y = height / 2;
    fruitx = rand() % width;
    fruity = rand() % height;
    score = 0;
}

void Draw()
{
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {1,1});
    cout<<"\n\n\n\n\t\t\t\t\t\t#";  //first line border
    for (int i = 0; i < width; i++)
    {
        cout<<"#";      //Upper border loop
    }
    cout<<endl;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (j == 0) cout<<"\t\t\t\t\t\t#";      //Side Border
            else if(i == y && j == x)   cout<<"O";  //Snake head
            else if(i == fruity && j == fruitx)   cout<<"0";    //Fruit
            else 
            {
                bool print = false;
                for (int k = 0; k < ntail; k++)
                {
                    if (tailX[k] == j && tailY[k] == i)
                    {
                        cout<<"o";      //Snake Body
                        print = true;
                    }                                       
                }
                if (!print)
                    {
                        cout<<" ";
                    }
            }
            if (j == width - 1) cout<<"#";
        }
        cout<<endl;
    }
    cout<<"\t\t\t\t\t\t#";
    for (int i = 0; i < width; i++)
    {
        cout<<"#";
    }
    cout<<endl;
    cout<<"\n\t\t\t\t\t\tScore: "<<score<<endl;     //Score per eaten fruit
    
}

void Input()
{
    if(kbhit())
    {
        switch (getch())
        {
        case 'w':dir = UP; break;
        case 'a':dir = LEFT; break;
        case 's':dir = DOWN; break;
        case 'd':dir = RIGHT; break;
        case 'x':gameOver = true; break;
        }
    }
}

void Logic()
{
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;
    tailX[0] = x;
    tailY[0] = y;

    for(int i = 1; i < ntail ; i++)
    {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }
    switch (dir)
    {
        case LEFT: x--; break;
        case RIGHT: x++; break;
        case UP: y--; break;
        case DOWN: y++; break;
        default: break;
    }

    // if(x > width || x < 0 || y > height || y < 0)
    //     gameOver = true;  
    if (x >= width) x = 0; else if(x < 0) x = width - 1;
    if (y >= height) y = 0; else if(y < 0) y = height - 1;
    
    for (int i = 0; i < ntail; i++)
    {
        if (tailX[i] == x && tailY[i] == y)
            gameOver = true;     
               
    }
    
    if(x == fruitx && y == fruity)
    {
        score += 10;
        fruitx = rand() % width;
        fruity = rand() % height;
        ntail++;
    }
        
}

bool gameover = true;

int score1 = 0;

//Snake Game function

void Snake()
{
    system("cls");
    Setup();
    while (!gameOver)
    {
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {150,50});
        Draw();
        Input();
        Logic();
        
    }
    // system("cls");
}
