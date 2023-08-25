#include<iostream>
#include<conio.h>
#include<windows.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>


using namespace std;

#define SCREEN_WIDTH 52
#define SCREEN_HEIGHT 20

#define MINX 2
#define MINY 2
#define MAXX 49
#define MAXY 19

// For Ping Pong Border

#define a1 45
#define b 10

char l[] = "ooooo";
int i;

HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
COORD CursorPosition;

void gotoxy(int x, int y)
{
    CursorPosition.X = x;
    CursorPosition.Y = y;
    SetConsoleCursorPosition(console, CursorPosition);

}

void setcursor( bool visible, DWORD size)
{
    if (size == 0)
    {
        size = 20;
    }
    CONSOLE_CURSOR_INFO lpCursor;
    lpCursor.bVisible = visible;
    lpCursor.dwSize = size;
    SetConsoleCursorInfo(console, & lpCursor);
}

void printBorder()  //Ping Pong Border
{
    for (i = 2; i <= 79; i++)
    {
        gotoxy(i + a1, 1 + b);
        cout<<'-';
        gotoxy(i + a1, 25 + b);
        cout<<'-';
    }
    for (i = 1; i <= 25; i++)
    {
        gotoxy(2 + a1, i + b);
        cout<<'|';
        gotoxy(79 + a1, i + b);
        cout<<'|';
    }
}

void setplayers()
{
    system("cls");
    printBorder();
    gotoxy(4 + a1, 3 + b);
    cout<<"Score: 0";
    gotoxy(50 + a1, 3 + b);
    cout<<"Press Esc key to quit the game";
    for(i = 3; i<=78; i++)
    {
        gotoxy(i + a1, 4 + b);
        cout<<"-";
    }
    for(i = 0; i <= strlen(l); i++)
    {
        gotoxy(5 + a1, 5+i + b);
        cout<< l[i];
    }
    for(i = 0; i <= strlen(l); i++)
    {
        gotoxy(76 + a1, 5 + i + b);
        cout<< l[i];
    }
}

void gameplay()
{
    setplayers();
    void displayMenu();
    int sc = 0, pp = 0, st = 1;
    int c = 5, k = 5, x = 73, y = 6 + rand() % 15;
    int d = rand() % 2, px, py;
    int op = 1, go = 1;
    int rld = 0, rlu = 0, lru = 0, lrd = 0;

    while(1)
    {
        if(go == 1)
        {
            while(!kbhit() && op)
            {
                px = x;
                py = y;
                gotoxy(x + a1, y + b);
                cout<<"O";
                Sleep(50);
                gotoxy(x + a1, y + b);
                cout<<" ";

                if(st == 1)
                {
                    st = 0;
                    if(d == 0)
                    {
                        x--;
                        y++;
                    }
                    else
                    {
                        x--;
                        y--;
                    }
                }

                if(rld)
                {
                    x--;
                    y++;
                }
                if(rlu)
                {
                    x--;
                    y--;
                }
                if(lru)
                {
                    x++;
                    y--;
                }
                if(lrd)
                {
                    x++;
                    y++;
                }

                if(x < px && y > py) rld = 1;
                if(x < px && y < py) rlu = 1;
                if(y == 5 && rlu)
                {
                    rld = 1;
                    rlu = 0;
                }
                if(y == 24 && rld)
                {
                    rlu = 1;
                    rld = 0;
                }
                if(x == 6 && rlu)
                {
                    lru = 1;
                    rlu = 0;
                }
                if(x == 6 && rld)
                {
                    lrd = 1;
                    rld = 0;
                }
                if(y == 5 && lru)
                {
                    lrd = 1;
                    lru = 0;
                }
                if(y == 24 && lrd)
                {
                    lru = 1;
                    lrd = 0;
                }
                if(x == 75 && lrd)
                {
                    rld = 1;
                    lrd = 0;
                }
                if(x == 75 && lru)
                {
                    rlu = 1;
                    lru = 0;
                }

                if(x == 75 || x == 6)
                {
                    Sleep(50);
                }
                if(y == 5 || y == 24)
                {
                    Sleep(50);
                }

                if(lru || lrd)
                {
                    if(y >= 6 && y <= 22)
                    {
                        if(y > k + strlen(l) -3)
                        {
                            gotoxy(76 + a1, k + strlen(l) + b);
                            cout<<"o";
                            gotoxy(76 + a1, k + b);
                            if(k != 4) cout<<' ';
                            k++;
                        }
                        if(y < k + strlen(l) - 3)
                        {
                            gotoxy(76 + a1, k + b);
                            cout<<"o";
                            gotoxy(76 + a1, k + strlen(l) + b);
                            if(k + strlen(l) != 25) cout<<' ';
                            k--;
                        }
                    }
                }

                if(x == 6 && (y < c || y > c + strlen(l) - 1))
                {
                    gotoxy(x + a1, y + b);
                    cout<<"YOU LOSE! Press 'r' or ENTER to play again";
                    op = 0;
                    break;  
                }

                if(x == 6 && op == 1)
                {
                    gotoxy(4 + a1, 3 + b);
                    cout<<"SCORE: "<< ++sc;
                }
            }
        }

        char ch = getch();

        if(ch == ' ' && op == 1)
        {
            pp = 1;
            go = 0;
            gotoxy(22 + a1,12 + b);
            cout<<"GAME PAUSED! PRESS ENTER to continue !";
        }

        if(ch == 13 && pp && op == 1)
        {
            pp = 0;
            go = 1;
            gotoxy(x + a1, y + b);
            cout<<"                                      ";
        }

        if((ch == 'r' || ch == 'R' || ch == 13) && op == 0)
        {
            op = 1;
            if(sc > 5)
                gameplay();
            else
                break;
        }

        if((ch == 's' || ch == 'S' || ch == 80) && c <= 19 && op)
        {
            gotoxy(5 + a1, c + strlen(l) + b);
            cout<<"o";  
            gotoxy(5 + a1, c + b);
            cout<<' ';
            c++;
        }

        if((ch == 'w' || ch == 'W' || ch == 72) && c >= 6 && op)
        {
            gotoxy(5 + a1, c - 1 + b);
            cout<<"o";
            gotoxy(5 + a1, c + 4 + b);
            cout<<' ';
            c--;
        }

        if(ch == 27)
        {
            displayMenu();
            break;
        }
    }
}

void displayMenu()
{
    system("cls");
    void htpwindow();
    int cp = 1;
    gotoxy(34 + a1, 4 + b);
    cout<<"PING PONG";
    for(i = 8; i<= 73; i++)
    {
        gotoxy(i + a1, 6 + b);
        cout<<'-';
    }
    gotoxy(34 + a1, 10 + b);
    cout<<"1. PLAY THE GAME!";
    gotoxy(34 + a1, 12 + b);
    cout<<"2. HOW TO PLAY!";
    gotoxy(34 + a1, 14 + b);
    cout<<"3. EXIT!";
    gotoxy(34 + a1, 16 + b);
    cout<<"Enter Option from the Menu: ";

    char op = getche();
    if( op == '1') gameplay();
    if( op == '2') htpwindow();
    if( op == '3') exit(0);
}

void htpwindow()
{
    system("cls");
    printBorder();
    gotoxy(4 + a1, 3 + b);
    cout<<"INTRUCTIONS!";
    gotoxy(4 + a1, 4 + b);
    cout<<"------------";
    gotoxy(4 + a1, 5 + b);
    cout<<"- Press w or Up Arrow to move up.";
    gotoxy(4 + a1, 7 + b);
    cout<<"- Press s or Down Arrow to move down.";
    gotoxy(4 + a1, 9 + b);
    cout<<"- Press Spacebar to Pause the game.";
    gotoxy(4 + a1, 11 + b);
    cout<<"- Press Esc to quit the game.";
    gotoxy(4 + a1, 15 + b);
    cout<<"- Press any key to go to menu...";
    getch();
    displayMenu();
}

void PingPong()
{   
    setcursor(0, 0);
    srand((unsigned) time(NULL));
    system("cls");
    displayMenu();   
}

//BRICKS GAME START

int bricks[24][2] =  {
                        {2,7}, {2,17},{2,22},{2,27},{2,32},{2,37},{2,42},
                        {4,7}, {4,17},{4,22},{4,27},{4,32},{4,37},{4,42},
                        {6,7}, {6,17},{6,22},{6,27},{6,32},{6,37},{6,42},
                     };

int visibleBricks[24] = {1,1,1,1, 1,1,1,1, 1,1,1,1, 1,1,1,1, 1,1,1,1, 1,1,1,1};

int sliderPos[2] = {18,22};
int ballPos[2] = {17,26};
int startBall = 0;
int direc = 1;     //1- TopRight, 2- TopLeft, 3- BottomLeft, 4- BottomRight
int bricksLeft = 24;
int win = 0;
int lose = 0; 
bool gover = true;

void drawBorder()
{
    gotoxy(0, 0); cout<<"-----------------------------------------------------";
    gotoxy(0, SCREEN_HEIGHT); cout<<"-----------------------------------------------------";

    for(int i = 0; i < SCREEN_HEIGHT; i++)
    {
        gotoxy(0,i); cout<<"|";
        gotoxy(SCREEN_WIDTH, i); cout<<"|";
    }
}

void drawBricks()
{
    for(int i = 0; i < 24; i++)
    {
        if( visibleBricks[i] == 1)
        {
            gotoxy(bricks[i][1], bricks[i][0]);
            cout<<"±±±±";
        }
    }
}       //±±±±

void ballHitSlider()
{
    if(ballPos[1] >= sliderPos[1] && ballPos[1] <= sliderPos[1]+8)
    {
        if(ballPos[0] == sliderPos[0]-1)
        {
            if(direc == 3)
            {
                direc = 2;
            }
            else if(direc == 4)
                direc = 1;
        }
    }
}

void ballHitBrick()
{
    for(int i = 0; i < 24; i++)
    {
        if(visibleBricks[i] == 1)
        {
            if(ballPos[1] >= bricks[i][1] && ballPos[1] <= bricks[i][1]+8)
            {
                if(ballPos[0] == bricks[i][0])
                {
                    visibleBricks[i] = 0;
                    bricksLeft--;
                }
            }
        }
    }
}

void play()
{
    gover = true;
    while(gover)
    {
        system("cls");
        drawBricks();
        drawBorder();

        gotoxy(sliderPos[1], sliderPos[0]);
        cout<<"±±±±±±±±±";

        gotoxy(ballPos[1], ballPos[0]); cout<<"0"; 
        if(kbhit())
        {
            char ch = getch();

            if(ch == 'd' || ch == 'D' || ch == 77 )
            {
                if(sliderPos[1] < 44)
                    sliderPos[1] = sliderPos[1] + 2;
            }
            if(ch == 'a' || ch == 'A' || ch == 75 )
            {
                if(sliderPos[1] > 2)
                    sliderPos[1] = sliderPos[1] - 2;
            }
            if(ch == 32)
            { 
                startBall = 1;
            }
            if(ch == 27)
            {
                break;
            }
        }

        if(startBall == 1)
        {
            if( direc == 1)       //TOP RIGHT
            {
                ballPos[0] = ballPos[0] - 1;
                ballPos[1] = ballPos[1] + 2;
                if(ballPos[1] > MAXX)
                {
                    direc = 2;
                }
                else if(ballPos[0] < MINY)
                {
                    direc = 4;
                }
            }
            else if( direc == 2)       //TOP LEFT
            {
                ballPos[0] = ballPos[0] - 1;
                ballPos[1] = ballPos[1] - 2;
                if(ballPos[0] < MINY)
                {
                    direc = 3;
                }
                else if(ballPos[1] < MINX)
                {
                    direc = 1;
                }
            }
            else if( direc == 3)       //BOTTOM LEFT
            {
                ballPos[0] = ballPos[0] + 1;
                ballPos[1] = ballPos[1] - 2;
                
                if(ballPos[0] > MAXY)
                {
                    lose = 1;
                    gover = false;
                    break;
                }
                else if(ballPos[1] < MINX)
                {
                    direc = 4;
                }
            }
            else if( direc == 4)       //BOTTOM RIGHT
            {
                ballPos[0] = ballPos[0] + 1;
                ballPos[1] = ballPos[1] + 2;
                
                if(ballPos[1] > MAXX)
                {
                    direc = 3;
                }
                else if(ballPos[0] > MAXY)
                {
                    lose = 1;
                    gover = false;
                    break;
                }
            }
            ballHitSlider();
        }
        ballHitBrick();

        if( bricksLeft == 0)
        {
            win = 1;
            break;
        }

        Sleep(30);
    }
    
    if(lose == 1)
    {
        system("cls");

        gotoxy(10,5); cout<<"---------------------------------------";
        gotoxy(10,6); cout<<"|              YOU LOSE               |";
        gotoxy(10,7); cout<<"---------------------------------------";
        gotoxy(10,9); cout<<"Press any key to go back to quiz game.";
        gover = false;
        getch();
    }
    if(win == 1)
    {
        system("cls");
        gotoxy(10,5); cout<<"---------------------------------------";
        gotoxy(10,6); cout<<"|              YOU WIN                |";
        gotoxy(10,7); cout<<"---------------------------------------";
        gotoxy(10,9); cout<<"Press any key to go back to quiz game.";
        getch();
        gover = true;
    }
}

void Instructions()
{
    system("cls");
    cout<<"Instructions!";
    cout<<"\n----------------";
    cout<<"\n1. Use 'a' key to move slider  to left";
    cout<<"\n2. Use 'd' key to move slider  to right";
    cout<<"\n3. Press spacebar to start the game";
    cout<<"\n\n Press any key to go back to the menu";
    getch();
}

// BRICKS game fucntion call

void BRICKS()
{
    gover = true;
    setcursor(0,0);
    do
    {
        system("cls");
        gotoxy(10,5); cout<<"---------------------------------------";
        gotoxy(10,6); cout<<"|           BRICK BREAKER             |";
        gotoxy(10,7); cout<<"---------------------------------------";
        gotoxy(10,9); cout<<"1. Start Game.";
        gotoxy(10,10); cout<<"2. Instructions";
        // gotoxy(10,11); cout<<"\n3. Quit";
        gotoxy(10,13); cout<<"SELECT OPTION";
        char op = getche();

        if(op == '1') play();
        else if(op == '2') Instructions();
        // else if(op == '3') exit(0);
    }while(gover);
    // play();
    cout<<endl<<endl;
}

//BRICKS GAME END

//SNAKE BUILDUP START

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

//SNAKE GAME END

// General Knowledge 10 Questions

void Q1()
{
    system("cls");
    
    cout<<"\n\n\n\n\n\n\n\n\n\n\n\n\n";
    int ans;
    char ak;
    cout<<"\t\t\t\t\t\t\t\t\t\t Who is our current(2023) prime minister of India?\n ";
    cout<<"\t\t\t\t\t\t\t\t\t\t 1. Pranab Mukherjee \t\t 2. Narendra Modi \n \t\t\t\t\t\t\t\t\t\t 3. Rahul Gandhi \t\t 4. Arvind Kejriwal\n";
a:  cout<<"\t\t\t\t\t\t\t\t\t\t Your Answer: ";
    cin>>ans;
    cout<<"\n\t\t\t\t\t\t\t\t\t\t Is "<<ans<<" your final answer?(y/n): ";
    cin>>ak;
    if(ak == 'y' || ak == 'Y')
    {
        if (ans == 2)
        {
            cout<<"\n\t\t\t\t\t\t\t\t\t\t Correct Answer!!\n";
            cout<<"\n\t\t\t\t\t\t\t\t\t\t Noice, Press any key for NEXT QUESTION!!";
            score1 += 5;
            count++;
            getch();
            // SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {1,1});
        }
        else
        {
           cout<<"\n\t\t\t\t\t\t\t\t\t\t Uh-Ohh Wrong Answer!\n";
           cout<<"\n\t\t\t\t\t\t\t\t\t\t Correct answer is: 2. Narendra Modi\n";
           cout<<"\n\t\t\t\t\t\t\t\t\t\t Press any KEY to CONTINUE!!";
           getch();
           
           gameover = false;
        }
    }
    else  goto a;       
}

void Q2()
{
    system("cls");
    
    cout<<"\n\n\n\n\n\n\n\n\n\n\n\n\n";
    int ans;
    char ak;
    cout<<"\t\t\t\t\t\t\t\t\t\t How many states does INDIA currently(2023) have? \n";
    cout<<"\t\t\t\t\t\t\t\t\t\t 1. 27 \t\t 2. 28 \n \t\t\t\t\t\t\t\t\t\t 3. 29 \t\t 4. 30\n";
a:  cout<<"\t\t\t\t\t\t\t\t\t\t Your Answer: ";
    cin>>ans;
    cout<<"\n\t\t\t\t\t\t\t\t\t\t Is "<<ans<<" your final answer?(y/n): ";
    cin>>ak;
    if(ak == 'y' || ak == 'Y')
    {
        if (ans == 2)
        {
            cout<<"\n\t\t\t\t\t\t\t\t\t\t Correct Answer!!\n";
            cout<<"\n\t\t\t\t\t\t\t\t\t\t Noice, Press any key for NEXT QUESTION!!";
            score1 += 5;
            count++;
            getch();
                
        }
        else
        {
           cout<<"\n\t\t\t\t\t\t\t\t\t\t Uh-Ohh Wrong Answer!";
           cout<<"\n\t\t\t\t\t\t\t\t\t\t Correct answer is: 2. 28\n";
           cout<<"\n\t\t\t\t\t\t\t\t\t\t Press any KEY to CONTINUE!!";
           getch();
           
           gameover = false;
        }    
    }
    else  goto a; 
    
}

void Q3()
{
    system("cls");
    
    cout<<"\n\n\n\n\n\n\n\n\n\n\n\n\n";
    int ans;
    char ak;
    cout<<"\t\t\t\t\t\t\t\t\t\t In which year of First World War Germany declared war on Russia and France? \n";
    cout<<"\t\t\t\t\t\t\t\t\t\t 1. 1914 \t\t 2. 1915 \n \t\t\t\t\t\t\t\t\t\t 3. 1916 \t\t 4. 1917\n";
a:  cout<<"\t\t\t\t\t\t\t\t\t\t Your Answer: ";
    cin>>ans;
    cout<<"\n\t\t\t\t\t\t\t\t\t\t Is "<<ans<<" your final answer?(y/n): ";
    cin>>ak;
    if(ak == 'y' || ak == 'Y')
    {
        if (ans == 1)
        {
            cout<<"\n\t\t\t\t\t\t\t\t\t\t Correct Answer!!\n";
            cout<<"\n\t\t\t\t\t\t\t\t\t\t Noice, Press any key for NEXT QUESTION!!";
            score1 += 5;
            count++;
            getch();
            // SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {1,1});
        }
        else
        {
           cout<<"\n\t\t\t\t\t\t\t\t\t\t Uh-Ohh Wrong Answer!\n";
           cout<<"\n\t\t\t\t\t\t\t\t\t\t Correct answer is: 1. 1914\n";
           cout<<"\n\t\t\t\t\t\t\t\t\t\t Press any KEY to CONTINUE!!";
           getch();
           
           gameover = false;
        }    
    }
    else  goto a; 
    
}

void Q4()
{
    system("cls");
    cout<<"\n\n\n\n\n\n\n\n\n\n\n\n\n";
    int ans;
    char ak;
    cout<<"\t\t\t\t\t\t\t\t\t\t Which is the INDIA's National Bird? \n";
    cout<<"\t\t\t\t\t\t\t\t\t\t 1. Eagle \t\t 2. Sparrow \n \t\t\t\t\t\t\t\t\t\t 3. Crow \t\t 4. Peacock\n";
a:  cout<<"\t\t\t\t\t\t\t\t\t\t Your Answer: ";
    cin>>ans;
    cout<<"\n\t\t\t\t\t\t\t\t\t\t Is "<<ans<<" your final answer?(y/n): ";
    cin>>ak;
    if(ak == 'y' || ak == 'Y')
    {
        if (ans == 4)
        {
            cout<<"\n\t\t\t\t\t\t\t\t\t\t Correct Answer!!\n";
            cout<<"\n\t\t\t\t\t\t\t\t\t\t Noice, Press any key for NEXT QUESTION!!";
            score1 += 5;
            count++;
            getch();
            
        }
        else
        {
           cout<<"\n\t\t\t\t\t\t\t\t\t\t Uh-Ohh Wrong Answer!\n";
           cout<<"\n\t\t\t\t\t\t\t\t\t\t Correct answer is: 4. Peacock\n";
           cout<<"\n\t\t\t\t\t\t\t\t\t\t Press any KEY to CONTINUE!!";
           getch();
           
           gameover = false;
        }    
    }
    else  goto a; 
    
}

void Q5()
{
    system("cls");
    cout<<"\n\n\n\n\n\n\n\n\n\n\n\n\n";
    int ans;
    char ak;
    cout<<"\t\t\t\t\t\t\t\t\t\t Which is the INDIA's National Animal? \n";
    cout<<"\t\t\t\t\t\t\t\t\t\t 1. Lion \t\t 2. Cheetah \n \t\t\t\t\t\t\t\t\t\t 3. Tiger \t\t 4. Leapord\n";
a:  cout<<"\t\t\t\t\t\t\t\t\t\t Your Answer: ";
    cin>>ans;
    cout<<"\n\t\t\t\t\t\t\t\t\t\t Is "<<ans<<" your final answer?(y/n): ";
    cin>>ak;
    if(ak == 'y' || ak == 'Y')
    {
        if (ans == 3)
        {
            cout<<"\n\t\t\t\t\t\t\t\t\t\t Correct Answer!!\n";
            cout<<"\n\t\t\t\t\t\t\t\t\t\t Noice, Press any key for NEXT QUESTION!!";
            score1 += 5;
            count++;
            getch();
            
        }
        else
        {
           cout<<"\n\t\t\t\t\t\t\t\t\t\t Uh-Ohh Wrong Answer!\n";
           cout<<"\n\t\t\t\t\t\t\t\t\t\t Correct answer is: 3. Tiger\n";
           cout<<"\n\t\t\t\t\t\t\t\t\t\t Press any KEY to CONTINUE!!";
           getch();
           
           gameover = false;
        }    
    }
    else  goto a; 
    
}

void Q6()
{
    system("cls");
    cout<<"\n\n\n\n\n\n\n\n\n\n\n\n\n";
    int ans;
    char ak;
    cout<<"\t\t\t\t\t\t\t\t\t\t India has largest deposits of ____ in the world. \n";
    cout<<"\t\t\t\t\t\t\t\t\t\t 1. gold \t\t 2. copper \n \t\t\t\t\t\t\t\t\t\t 3. mica \t\t 4. Iron\n";
a:  cout<<"\t\t\t\t\t\t\t\t\t\t Your Answer: ";
    cin>>ans;
    cout<<"\n\t\t\t\t\t\t\t\t\t\t Is "<<ans<<" your final answer?(y/n): ";
    cin>>ak;
    if(ak == 'y' || ak == 'Y')
    {
        if (ans == 3)
        {
            cout<<"\n\t\t\t\t\t\t\t\t\t\t Correct Answer!!\n";
            cout<<"\n\t\t\t\t\t\t\t\t\t\t Noice, Press any key for NEXT QUESTION!!";
            score1 += 5;
            count++;
            getch();
            
        }
        else
        {
           cout<<"\n\t\t\t\t\t\t\t\t\t\t Uh-Ohh Wrong Answer!\n";
           cout<<"\n\t\t\t\t\t\t\t\t\t\t Correct answer is: 3. Mica\n";
           cout<<"\n\t\t\t\t\t\t\t\t\t\t Press any KEY to CONTINUE!!";
           getch();
           
           gameover = false;
        }    
    }
    else  goto a; 
    
}

void Q7()
{
    system("cls");
    cout<<"\n\n\n\n\n\n\n\n\n\n\n\n\n";
    int ans;
    char ak;
    cout<<"\t\t\t\t\t\t\t\t\t\t How much districts are there in Meghalaya? \n";
    cout<<"\t\t\t\t\t\t\t\t\t\t 1. 12 \t\t 2. 2 \n \t\t\t\t\t\t\t\t\t\t 3. 5 \t\t 4. 9\n";
a:  cout<<"\t\t\t\t\t\t\t\t\t\t Your Answer: ";
    cin>>ans;
    cout<<"\n\t\t\t\t\t\t\t\t\t\t Is "<<ans<<" your final answer?(y/n): ";
    cin>>ak;
    if(ak == 'y' || ak == 'Y')
    {
        if (ans == 1)
        {
            cout<<"\n\t\t\t\t\t\t\t\t\t\t Correct Answer!!\n";
            cout<<"\n\t\t\t\t\t\t\t\t\t\t Noice, Press any key for NEXT QUESTION!!";
            score1 += 5;
            count++;
            getch();
            
        }
        else
        {
           cout<<"\n\t\t\t\t\t\t\t\t\t\t Uh-Ohh Wrong Answer!\n";
           cout<<"\n\t\t\t\t\t\t\t\t\t\t Correct answer is: 1. 12\n";
           cout<<"\n\t\t\t\t\t\t\t\t\t\t Press any KEY to CONTINUE!!";
           getch();
           
           gameover = false;
        }    
    }
    else  goto a; 
    
}

void Q8()
{
    system("cls");
    cout<<"\n\n\n\n\n\n\n\n\n\n\n\n\n";
    int ans;
    char ak;
    cout<<"\t\t\t\t\t\t\t\t\t\t How many Lok Sabha seats belong to Rajasthan? \n";
    cout<<"\t\t\t\t\t\t\t\t\t\t 1. 32 \t\t 2. 25 \n \t\t\t\t\t\t\t\t\t\t 3. 30 \t\t 4. 17\n";
a:  cout<<"\t\t\t\t\t\t\t\t\t\t Your Answer: ";
    cin>>ans;
    cout<<"\n\t\t\t\t\t\t\t\t\t\t Is "<<ans<<" your final answer?(y/n): ";
    cin>>ak;
    if(ak == 'y' || ak == 'Y')
    {
        if (ans == 2)
        {
            cout<<"\n\t\t\t\t\t\t\t\t\t\t Correct Answer!!\n";
            cout<<"\n\t\t\t\t\t\t\t\t\t\t Noice, Press any key for NEXT QUESTION!!";
            score1 += 5;
            count++;
            getch();
            
        }
        else
        {
           cout<<"\n\t\t\t\t\t\t\t\t\t\t Uh-Ohh Wrong Answer!\n";
           cout<<"\n\t\t\t\t\t\t\t\t\t\t Correct answer is: 2. 25\n";
           cout<<"\n\t\t\t\t\t\t\t\t\t\t Press any KEY to CONTINUE!!";
           getch();
           
           gameover = false;
        }    
    }
    else  goto a; 
    
}

void Q9()
{
    system("cls");
    cout<<"\n\n\n\n\n\n\n\n\n\n\n\n\n";
    int ans;
    char ak;
    cout<<"\t\t\t\t\t\t\t\t\t\t India's first satellite is named after \n";
    cout<<"\t\t\t\t\t\t\t\t\t\t 1. Aryabhatta \t\t 2. Bhaskara II \n \t\t\t\t\t\t\t\t\t\t 3. Bhaskara I \t\t 4. Albert Einstein \n";
a:  cout<<"\t\t\t\t\t\t\t\t\t\t Your Answer: ";
    cin>>ans;
    cout<<"\n\t\t\t\t\t\t\t\t\t\t Is "<<ans<<" your final answer?(y/n): ";
    cin>>ak;
    if(ak == 'y' || ak == 'Y')
    {
        if (ans == 1)
        {
            cout<<"\n\t\t\t\t\t\t\t\t\t\t Correct Answer!!\n";
            cout<<"\n\t\t\t\t\t\t\t\t\t\t Noice, Press any key for NEXT QUESTION!!";
            score1 += 5;
            count++;
            getch();
            
        }
        else
        {
           cout<<"\n\t\t\t\t\t\t\t\t\t\t Uh-Ohh Wrong Answer!\n";
           cout<<"\n\t\t\t\t\t\t\t\t\t\t Correct answer is: 1. Aryabhatta\n";
           cout<<"\n\t\t\t\t\t\t\t\t\t\t Press any KEY to CONTINUE!!";
           getch();
           
           gameover = false;
        }    
    }
    else  goto a; 
    
}

void Q10()
{
    system("cls");
    cout<<"\n\n\n\n\n\n\n\n\n\n\n\n\n";
    int ans;
    char ak;
    cout<<"\t\t\t\t\t\t\t\t\t\t India's tallest stone statue of the Jain sage Gomateswara is at \n";
    cout<<"\t\t\t\t\t\t\t\t\t\t 1. Mysore, Karnakata \t\t 2. New Delhi \n \t\t\t\t\t\t\t\t\t\t 3. Sravanabelagola, Karnataka \t\t 4. Mandu, Madhya Pradesh \n";
a:  cout<<"\t\t\t\t\t\t\t\t\t\t Your Answer: ";
    cin>>ans;
    cout<<"\n\t\t\t\t\t\t\t\t\t\t Is "<<ans<<" your final answer?(y/n): ";
    cin>>ak;
    if(ak == 'y' || ak == 'Y')
    {
        if (ans == 3)
        {
            cout<<"\n\t\t\t\t\t\t\t\t\t\t Correct Answer!!\n";
            cout<<"\n\t\t\t\t\t\t\t\t\t\t Noice, Press any key for NEXT QUESTION!!";
            score1 += 5;
            count++;
            getch();
            
        }
        else
        {
           cout<<"\n\t\t\t\t\t\t\t\t\t\t Uh-Ohh Wrong Answer!\n";
           cout<<"\n\t\t\t\t\t\t\t\t\t\t Correct answer is: 3. Sravanabelagola, Karnataka \n";
           cout<<"\n\t\t\t\t\t\t\t\t\t\t Press any KEY to CONTINUE!!";
           getch();
           
           gameover = false;
        }    
    }
    else  goto a; 
    
}

// Literature 10 questions

void Q11()
{
    system("cls");
    cout<<"\n\n\n\n\n\n\n\n\n\n\n\n\n";
    int ans;
    char ak;
    cout<<"\t\t\t\t\t\t\t\t\t\t Which of the following is NOT written by Munshi Premchand? \n";
    cout<<"\t\t\t\t\t\t\t\t\t\t 1. Gaban \t\t 2. Guide \n \t\t\t\t\t\t\t\t\t\t 3. Godan \t\t 4. Manasorovar \n";
a:  cout<<"\t\t\t\t\t\t\t\t\t\t Your Answer: ";
    cin>>ans;
    cout<<"\n\t\t\t\t\t\t\t\t\t\t Is "<<ans<<" your final answer?(y/n): ";
    cin>>ak;
    if(ak == 'y' || ak == 'Y')
    {
        if (ans == 2)
        {
            cout<<"\n\t\t\t\t\t\t\t\t\t\t Correct Answer!!\n";
            cout<<"\n\t\t\t\t\t\t\t\t\t\t Noice, Press any key for NEXT QUESTION!!";
            score1 += 5;
            count++;
            getch();
            
        }
        else
        {
           cout<<"\n\t\t\t\t\t\t\t\t\t\t Uh-Ohh Wrong Answer!\n";
           cout<<"\n\t\t\t\t\t\t\t\t\t\t Correct answer is: 2. Guide \n";
           cout<<"\n\t\t\t\t\t\t\t\t\t\t Press any KEY to CONTINUE!!";
           getch();
           
           gameover = false;
        }    
    }
    else  goto a; 
    
}

void Q12()
{
    system("cls");
    cout<<"\n\n\n\n\n\n\n\n\n\n\n\n\n";
    int ans;
    char ak;
    cout<<"\t\t\t\t\t\t\t\t\t\t The book 'To Live or Not Live' was written by \n";
    cout<<"\t\t\t\t\t\t\t\t\t\t 1. V.S. Naipaul \t\t 2. Nirad C. Chaudhuri \n \t\t\t\t\t\t\t\t\t\t 3. George Elliot \t\t 4. Alexandra Dumas \n";
a:  cout<<"\t\t\t\t\t\t\t\t\t\t Your Answer: ";
    cin>>ans;
    cout<<"\n\t\t\t\t\t\t\t\t\t\t Is "<<ans<<" your final answer?(y/n): ";
    cin>>ak;
    if(ak == 'y' || ak == 'Y')
    {
        if (ans == 4)
        {
            cout<<"\n\t\t\t\t\t\t\t\t\t\t Correct Answer!!\n";
            cout<<"\n\t\t\t\t\t\t\t\t\t\t Noice, Press any key for NEXT QUESTION!!";
            score1 += 5;
            count++;
            getch();
            
        }
        else
        {
           cout<<"\n\t\t\t\t\t\t\t\t\t\t Uh-Ohh Wrong Answer!\n";
           cout<<"\n\t\t\t\t\t\t\t\t\t\t Correct answer is: 4. Alexandra Dumas \n";
           cout<<"\n\t\t\t\t\t\t\t\t\t\t Press any KEY to CONTINUE!!";
           getch();
           
           gameover = false;
        }    
    }
    else  goto a; 
    
}

void Q13()
{
    system("cls");
    cout<<"\n\n\n\n\n\n\n\n\n\n\n\n\n";
    int ans;
    char ak;
    cout<<"\t\t\t\t\t\t\t\t\t\t Which of the following English films was the first one to be dubbed in Hindi? \n";
    cout<<"\t\t\t\t\t\t\t\t\t\t 1. Aladdin \t\t 2. Universal Soldier \n \t\t\t\t\t\t\t\t\t\t 3. Speed \t\t 4. Iron Man \n";
a:  cout<<"\t\t\t\t\t\t\t\t\t\t Your Answer: ";
    cin>>ans;
    cout<<"\n\t\t\t\t\t\t\t\t\t\t Is "<<ans<<" your final answer?(y/n): ";
    cin>>ak;
    if(ak == 'y' || ak == 'Y')
    {
        if (ans == 1)
        {
            cout<<"\n\t\t\t\t\t\t\t\t\t\t Correct Answer!!\n";
            cout<<"\n\t\t\t\t\t\t\t\t\t\t Noice, Press any key for NEXT QUESTION!!";
            score1 += 5;
            count++;
            getch();
            
        }
        else
        {
           cout<<"\n\t\t\t\t\t\t\t\t\t\t Uh-Ohh Wrong Answer!\n";
           cout<<"\n\t\t\t\t\t\t\t\t\t\t Correct answer is: 1. Aladdin \n";
           cout<<"\n\t\t\t\t\t\t\t\t\t\t Press any KEY to CONTINUE!!";
           getch();
           
           gameover = false;
        }    
    }
    else  goto a; 
    
}

void Q14()
{
    system("cls");
    cout<<"\n\n\n\n\n\n\n\n\n\n\n\n\n";
    int ans;
    char ak;
    cout<<"\t\t\t\t\t\t\t\t\t\t 'Alice in Wonderland' the famous TV serial is based on a book written by \n";
    cout<<"\t\t\t\t\t\t\t\t\t\t 1. Father Discoste \t\t 2. Thomas Hardy \n \t\t\t\t\t\t\t\t\t\t 3. Charles Dickens \t\t 4. Lewis Caroll \n";
a:  cout<<"\t\t\t\t\t\t\t\t\t\t Your Answer: ";
    cin>>ans;
    cout<<"\n\t\t\t\t\t\t\t\t\t\t Is "<<ans<<" your final answer?(y/n): ";
    cin>>ak;
    if(ak == 'y' || ak == 'Y')
    {
        if (ans == 4)
        {
            cout<<"\n\t\t\t\t\t\t\t\t\t\t Correct Answer!!\n";
            cout<<"\n\t\t\t\t\t\t\t\t\t\t Noice, Press any key for NEXT QUESTION!!";
            score1 += 5;
            count++;
            getch();
            
        }
        else
        {
           cout<<"\n\t\t\t\t\t\t\t\t\t\t Uh-Ohh Wrong Answer!\n";
           cout<<"\n\t\t\t\t\t\t\t\t\t\t Correct answer is: 4. Lewis Caroll \n";
           cout<<"\n\t\t\t\t\t\t\t\t\t\t Press any KEY to CONTINUE!!";
           getch();
           
           gameover = false;
        }    
    }
    else  goto a; 
    
}

void Q15()
{
    system("cls");
    cout<<"\n\n\n\n\n\n\n\n\n\n\n\n\n";
    int ans;
    char ak;
    cout<<"\t\t\t\t\t\t\t\t\t\t Who wrote 'Where ignorance is bliss, it is folly to be wise'? \n";
    cout<<"\t\t\t\t\t\t\t\t\t\t 1. Browning \t\t 2. Marx \n \t\t\t\t\t\t\t\t\t 3. Shakespeare \t\t 4. Kipling \n";
a:  cout<<"\t\t\t\t\t\t\t\t\t\t Your Answer: ";
    cin>>ans;
    cout<<"\n\t\t\t\t\t\t\t\t\t\t Is "<<ans<<" your final answer?(y/n): ";
    cin>>ak;
    if(ak == 'y' || ak == 'Y')
    {
        if (ans == 3)
        {
            cout<<"\n\t\t\t\t\t\t\t\t\t\t Correct Answer!!\n";
            cout<<"\n\t\t\t\t\t\t\t\t\t\t Noice, Press any key for NEXT QUESTION!!";
            score1 += 5;
            count++;
            getch();
            
        }
        else
        {
           cout<<"\n\t\t\t\t\t\t\t\t\t\t Uh-Ohh Wrong Answer!\n";
           cout<<"\n\t\t\t\t\t\t\t\t\t\t Correct answer is: 3. Shakespeare \n";
           cout<<"\n\t\t\t\t\t\t\t\t\t\t Press any KEY to CONTINUE!!";
           getch();
           
           gameover = false;
        }    
    }
    else  goto a; 
    
}

void Q16()
{
    system("cls");
    cout<<"\n\n\n\n\n\n\n\n\n\n\n\n\n";
    int ans;
    char ak;
    cout<<"\t\t\t\t\t\t\t\t\t\t Name the book which opens with the line 'All children, except one grew up'? \n";
    cout<<"\t\t\t\t\t\t\t\t\t\t 1. The Railway Children \t\t 2. Winnie the Poo \n \t\t\t\t\t\t\t\t\t\t 3. Jungle book \t\t 4. Peter Pan \n";
a:  cout<<"\t\t\t\t\t\t\t\t\t\t Your Answer: ";
    cin>>ans;
    cout<<"\n\t\t\t\t\t\t\t\t\t\t Is "<<ans<<" your final answer?(y/n): ";
    cin>>ak;
    if(ak == 'y' || ak == 'Y')
    {
        if (ans == 4)
        {
            cout<<"\n\t\t\t\t\t\t\t\t\t\t Correct Answer!!\n";
            cout<<"\n\t\t\t\t\t\t\t\t\t\t Noice, Press any key for NEXT QUESTION!!";
            score1 += 5;
            count++;
            getch();
            
        }
        else
        {
           cout<<"\n\t\t\t\t\t\t\t\t\t\t Uh-Ohh Wrong Answer!\n";
           cout<<"\n\t\t\t\t\t\t\t\t\t\t Correct answer is: 4. Peter Pan \n";
           cout<<"\n\t\t\t\t\t\t\t\t\t\t Press any KEY to CONTINUE!!";
           getch();
           
           gameover = false;
        }    
    }
    else  goto a; 
    
}

void Q17()
{
    system("cls");
    cout<<"\n\n\n\n\n\n\n\n\n\n\n\n\n";
    int ans;
    char ak;
    cout<<"\t\t\t\t\t\t\t\t\t\t Who is the author of the book 'My Experiments with Truth'? \n";
    cout<<"\t\t\t\t\t\t\t\t\t\t 1. Mahatma Gandhi \t\t 2. Michael Anderson \n \t\t\t\t\t\t\t\t\t\t 3. Winston Churchill \t\t 4. Jarnes Morris \n";
a:  cout<<"\t\t\t\t\t\t\t\t\t\t Your Answer: ";
    cin>>ans;
    cout<<"\n\t\t\t\t\t\t\t\t\t\t Is "<<ans<<" your final answer?(y/n): ";
    cin>>ak;
    if(ak == 'y' || ak == 'Y')
    {
        if (ans == 1)
        {
            cout<<"\n\t\t\t\t\t\t\t\t\t\t Correct Answer!!\n";
            cout<<"\n\t\t\t\t\t\t\t\t\t\t Noice, Press any key for NEXT QUESTION!!";
            score1 += 5;
            count++;
            getch();
            
        }
        else
        {
           cout<<"\n\t\t\t\t\t\t\t\t\t\t Uh-Ohh Wrong Answer!\n";
           cout<<"\n\t\t\t\t\t\t\t\t\t\t Correct answer is: 1. Mahatma Gandhi \n";
           cout<<"\n\t\t\t\t\t\t\t\t\t\t Press any KEY to CONTINUE!!";
           getch();
           
           gameover = false;
        }    
    }
    else  goto a; 
    
}

void Q18()
{
    system("cls");
    cout<<"\n\n\n\n\n\n\n\n\n\n\n\n\n";
    int ans;
    char ak;
    cout<<"\t\t\t\t\t\t\t\t\t\t The author of controversial book 'Lajja' is a citizen of \n";
    cout<<"\t\t\t\t\t\t\t\t\t\t 1. Pakistan \t\t 2. Indonesia \n \t\t\t\t\t\t\t\t\t\t 3. Bangladesh \t\t 4. India \n";
a:  cout<<"\t\t\t\t\t\t\t\t\t\t Your Answer: ";
    cin>>ans;
    cout<<"\n\t\t\t\t\t\t\t\t\t\t Is "<<ans<<" your final answer?(y/n): ";
    cin>>ak;
    if(ak == 'y' || ak == 'Y')
    {
        if (ans == 3)
        {
            cout<<"\n\t\t\t\t\t\t\t\t\t\t Correct Answer!!\n";
            cout<<"\n\t\t\t\t\t\t\t\t\t\t Noice, Press any key for NEXT QUESTION!!";
            score1 += 5;
            count++;
            getch();
            
        }
        else
        {
           cout<<"\n\t\t\t\t\t\t\t\t\t\t Uh-Ohh Wrong Answer!\n";
           cout<<"\n\t\t\t\t\t\t\t\t\t\t Correct answer is: 3. Bangladesh \n";
           cout<<"\n\t\t\t\t\t\t\t\t\t\t Press any KEY to CONTINUE!!";
           getch();
           
           gameover = false;
        }    
    }
    else  goto a; 
    
}

void Q19()
{
    system("cls");
    cout<<"\n\n\n\n\n\n\n\n\n\n\n\n\n";
    int ans;
    char ak;
    cout<<"\t\t\t\t\t\t\t\t\t\t The author of controversial book 'Lajja' is a citizen of \n";
    cout<<"\t\t\t\t\t\t\t\t\t\t 1. Euclid \t\t 2. Herodotus \n \t\t\t\t\t\t\t\t\t\t 3. Aristotle \t\t 4. Julius Caesar \n";
a:  cout<<"\t\t\t\t\t\t\t\t\t\t Your Answer: ";
    cin>>ans;
    cout<<"\n\t\t\t\t\t\t\t\t\t\t Is "<<ans<<" your final answer?(y/n): ";
    cin>>ak;
    if(ak == 'y' || ak == 'Y')
    {
        if (ans == 2)
        {
            cout<<"\n\t\t\t\t\t\t\t\t\t\t Correct Answer!!\n";
            cout<<"\n\t\t\t\t\t\t\t\t\t\t Noice, Press any key for NEXT QUESTION!!";
            score1 += 5;
            count++;
            getch();
            
        }
        else
        {
           cout<<"\n\t\t\t\t\t\t\t\t\t\t Uh-Ohh Wrong Answer!\n";
           cout<<"\n\t\t\t\t\t\t\t\t\t\t Correct answer is: 2. Herodotus \n";
           cout<<"\n\t\t\t\t\t\t\t\t\t\t Press any KEY to CONTINUE!!";
           getch();
           
           gameover = false;
        }    
    }
    else  goto a; 
    
}

void Q20()
{
    system("cls");
    cout<<"\n\n\n\n\n\n\n\n\n\n\n\n\n";
    int ans;
    char ak;
    cout<<"\t\t\t\t\t\t\t\t\t\t The creator of 'Sherlock Holmes' was \n";
    cout<<"\t\t\t\t\t\t\t\t\t\t 1. Arthur Conan Doyle \t\t 2. Ian Fleming \n \t\t\t\t\t\t\t\t\t\t 3. Dr.Watson \t\t 4. Shakespeare \n";
a:  cout<<"\t\t\t\t\t\t\t\t\t\t Your Answer: ";
    cin>>ans;
    cout<<"\n\t\t\t\t\t\t\t\t\t\t Is "<<ans<<" your final answer?(y/n): ";
    cin>>ak;
    if(ak == 'y' || ak == 'Y')
    {
        if (ans == 1)
        {
            cout<<"\n\t\t\t\t\t\t\t\t\t\t Correct Answer!!\n";
            cout<<"\n\t\t\t\t\t\t\t\t\t\t Noice, Press any key for NEXT QUESTION!!";
            score1 += 5;
            count++;
            getch();
            
        }
        else
        {
           cout<<"\n\t\t\t\t\t\t\t\t\t\t Uh-Ohh Wrong Answer!\n";
           cout<<"\n\t\t\t\t\t\t\t\t\t\t Correct answer is: 1. Arthur Conan Doyle \n";
           cout<<"\n\t\t\t\t\t\t\t\t\t\t Press any KEY to CONTINUE!!";
           getch();
           
           gameover = false;
        }    
    }
    else  goto a; 
    
}

// Indian Culture 10 questions
void Q21()
{
    system("cls");
    cout<<"\n\n\n\n\n\n\n\n\n\n\n\n\n";
    int ans;
    char ak;
    cout<<"\t\t\t\t\t\t\t\t\t\t The ratio of width of our National flag to its length is \n";
    cout<<"\t\t\t\t\t\t\t\t\t\t 1. 3:5 \t\t 2. 2:3 \n \t\t\t\t\t\t\t\t\t\t 3. 2:4 \t\t 4. 3:4 \n";
a:  cout<<"\t\t\t\t\t\t\t\t\t\t Your Answer: ";
    cin>>ans;
    cout<<"\n\t\t\t\t\t\t\t\t\t\t Is "<<ans<<" your final answer?(y/n): ";
    cin>>ak;
    if(ak == 'y' || ak == 'Y')
    {
        if (ans == 2)
        {
            cout<<"\n\t\t\t\t\t\t\t\t\t\t Correct Answer!!\n";
            cout<<"\n\t\t\t\t\t\t\t\t\t\t Noice, Press any key for NEXT QUESTION!!";
            score1 += 5;
            count++;
            getch();
            
        }
        else
        {
           cout<<"\n\t\t\t\t\t\t\t\t\t\t Uh-Ohh Wrong Answer!\n";
           cout<<"\n\t\t\t\t\t\t\t\t\t\t Correct answer is: 2. 2:3 \n";
           cout<<"\n\t\t\t\t\t\t\t\t\t\t Press any KEY to CONTINUE!!";
           getch();
           
           gameover = false;
        }    
    }
    else  goto a; 
    
}

void Q22()
{
    system("cls");
    cout<<"\n\n\n\n\n\n\n\n\n\n\n\n\n";
    int ans;
    char ak;
    cout<<"\t\t\t\t\t\t\t\t\t\t Rabindranath Tagore's 'Jana Gana Mana' has been adopted as India's National Anthem.\n\t\t\t\t\t\t\t\t\t\t How many stanzas of the said song were adopted? \n";
    cout<<"\t\t\t\t\t\t\t\t\t\t 1. Only the first stanza \t\t 2. The whole song \n \t\t\t\t\t\t\t\t\t\t 3. Third and Fourth stanza \t\t 4. First and Second stanza \n";
a:  cout<<"\t\t\t\t\t\t\t\t\t\t Your Answer: ";
    cin>>ans;
    cout<<"\n\t\t\t\t\t\t\t\t\t\t Is "<<ans<<" your final answer?(y/n): ";
    cin>>ak;
    if(ak == 'y' || ak == 'Y')
    {
        if (ans == 1)
        {
            cout<<"\n\t\t\t\t\t\t\t\t\t\t Correct Answer!!\n";
            cout<<"\n\t\t\t\t\t\t\t\t\t\t Noice, Press any key for NEXT QUESTION!!";
            score1 += 5;
            count++;
            getch();
            
        }
        else
        {
           cout<<"\n\t\t\t\t\t\t\t\t\t\t Uh-Ohh Wrong Answer!\n";
           cout<<"\n\t\t\t\t\t\t\t\t\t\t Correct answer is: 1. Only the first stanza \n";
           cout<<"\n\t\t\t\t\t\t\t\t\t\t Press any KEY to CONTINUE!!";
           getch();
           
           gameover = false;
        }    
    }
    else  goto a; 
    
}

void Q23()
{
    system("cls");
    cout<<"\n\n\n\n\n\n\n\n\n\n\n\n\n";
    int ans;
    char ak;
    cout<<"\t\t\t\t\t\t\t\t\t\t 'Dandia' is a popular dance of \n";
    cout<<"\t\t\t\t\t\t\t\t\t\t 1. Punjab \t\t 2. Gujarat \n \t\t\t\t\t\t\t\t\t\t 3. Tamil Nadu \t\t 4. Maharashtra \n";
a:  cout<<"\t\t\t\t\t\t\t\t\t\t Your Answer: ";
    cin>>ans;
    cout<<"\n\t\t\t\t\t\t\t\t\t\t Is "<<ans<<" your final answer?(y/n): ";
    cin>>ak;
    if(ak == 'y' || ak == 'Y')
    {
        if (ans == 2)
        {
            cout<<"\n\t\t\t\t\t\t\t\t\t\t Correct Answer!!\n";
            cout<<"\n\t\t\t\t\t\t\t\t\t\t Noice, Press any key for NEXT QUESTION!!";
            score1 += 5;
            count++;
            getch();
            
        }
        else
        {
           cout<<"\n\t\t\t\t\t\t\t\t\t\t Uh-Ohh Wrong Answer!\n";
           cout<<"\n\t\t\t\t\t\t\t\t\t\t Correct answer is: 2. Gujarat \n";
           cout<<"\n\t\t\t\t\t\t\t\t\t\t Press any KEY to CONTINUE!!";
           getch();
           
           gameover = false;
        }    
    }
    else  goto a; 
    
}

void Q24()
{
    system("cls");
    cout<<"\n\n\n\n\n\n\n\n\n\n\n\n\n";
    int ans;
    char ak;
    cout<<"\t\t\t\t\t\t\t\t\t\t 'Kathakali' is a folk dance prevalent in which state? \n";
    cout<<"\t\t\t\t\t\t\t\t\t\t 1. Tamil Nadu \t\t 2. Orissa \n \t\t\t\t\t\t\t\t\t\t 3. Kerala \t\t 4. Karnataka \n";
a:  cout<<"\t\t\t\t\t\t\t\t\t\t Your Answer: ";
    cin>>ans;
    cout<<"\n\t\t\t\t\t\t\t\t\t\t Is "<<ans<<" your final answer?(y/n): ";
    cin>>ak;
    if(ak == 'y' || ak == 'Y')
    {
        if (ans == 3)
        {
            cout<<"\n\t\t\t\t\t\t\t\t\t\t Correct Answer!!\n";
            cout<<"\n\t\t\t\t\t\t\t\t\t\t Noice, Press any key for NEXT QUESTION!!";
            score1 += 5;
            count++;
            getch();
            
        }
        else
        {
           cout<<"\n\t\t\t\t\t\t\t\t\t\t Uh-Ohh Wrong Answer!\n";
           cout<<"\n\t\t\t\t\t\t\t\t\t\t Correct answer is: 3. Kerala \n";
           cout<<"\n\t\t\t\t\t\t\t\t\t\t Press any KEY to CONTINUE!!";
           getch();
           
           gameover = false;
        }    
    }
    else  goto a; 
    
}

void Q25()
{
    system("cls");
    cout<<"\n\n\n\n\n\n\n\n\n\n\n\n\n";
    int ans;
    char ak;
    cout<<"\t\t\t\t\t\t\t\t\t\t The National Anthem was first sung in the year \n";
    cout<<"\t\t\t\t\t\t\t\t\t\t 1. 1911 \t\t 2. 1913 \n \t\t\t\t\t\t\t\t\t\t 3. 1945 \t\t 4. 1947 \n";
a:  cout<<"\t\t\t\t\t\t\t\t\t\t Your Answer: ";
    cin>>ans;
    cout<<"\n\t\t\t\t\t\t\t\t\t\t Is "<<ans<<" your final answer?(y/n): ";
    cin>>ak;
    if(ak == 'y' || ak == 'Y')
    {
        if (ans == 1)
        {
            cout<<"\n\t\t\t\t\t\t\t\t\t\t Correct Answer!!\n";
            cout<<"\n\t\t\t\t\t\t\t\t\t\t Noice, Press any key for NEXT QUESTION!!";
            score1 += 5;
            count++;
            getch();
            
        }
        else
        {
           cout<<"\n\t\t\t\t\t\t\t\t\t\t Uh-Ohh Wrong Answer!\n";
           cout<<"\n\t\t\t\t\t\t\t\t\t\t Correct answer is: 1. 1911 \n";
           cout<<"\n\t\t\t\t\t\t\t\t\t\t Press any KEY to CONTINUE!!";
           getch();
           
           gameover = false;
        }    
    }
    else  goto a; 
    
}

void Q26()
{
    system("cls");
    cout<<"\n\n\n\n\n\n\n\n\n\n\n\n\n";
    int ans;
    char ak;
    cout<<"\t\t\t\t\t\t\t\t\t\t Thillana is a format of \n";
    cout<<"\t\t\t\t\t\t\t\t\t\t 1. Kuchipudi \t\t 2. Odissi \n \t\t\t\t\t\t\t\t\t\t 3. Bharatanatyam \t 4. Kathak \n";
a:  cout<<"\t\t\t\t\t\t\t\t\t\t Your Answer: ";
    cin>>ans;
    cout<<"\n\t\t\t\t\t\t\t\t\t\t Is "<<ans<<" your final answer?(y/n): ";
    cin>>ak;
    if(ak == 'y' || ak == 'Y')
    {
        if (ans == 3)
        {
            cout<<"\n\t\t\t\t\t\t\t\t\t\t Correct Answer!!\n";
            cout<<"\n\t\t\t\t\t\t\t\t\t\t Noice, Press any key for NEXT QUESTION!!";
            score1 += 5;
            count++;
            getch();
            
        }
        else
        {
           cout<<"\n\t\t\t\t\t\t\t\t\t\t Uh-Ohh Wrong Answer!\n";
           cout<<"\n\t\t\t\t\t\t\t\t\t\t Correct answer is: 3. Bharatanatyam \n";
           cout<<"\n\t\t\t\t\t\t\t\t\t\t Press any KEY to CONTINUE!!";
           getch();
           
           gameover = false;
        }    
    }
    else  goto a; 
    
}

void Q27()
{
    system("cls");
    cout<<"\n\n\n\n\n\n\n\n\n\n\n\n\n";
    int ans;
    char ak;
    cout<<"\t\t\t\t\t\t\t\t\t\t 'Madhubani', a style of folk paintings, is popular in which of the following states in India? \n";
    cout<<"\t\t\t\t\t\t\t\t\t\t 1. Uttar Pradesh \t\t 2. Rajasthan \n \t\t\t\t\t\t\t\t\t\t 3. Madhya Pradesh \t\t 4. Bihar \n";
a:  cout<<"\t\t\t\t\t\t\t\t\t\t Your Answer: ";
    cin>>ans;
    cout<<"\n\t\t\t\t\t\t\t\t\t\t Is "<<ans<<" your final answer?(y/n): ";
    cin>>ak;
    if(ak == 'y' || ak == 'Y')
    {
        if (ans == 4)
        {
            cout<<"\n\t\t\t\t\t\t\t\t\t\t Correct Answer!!\n";
            cout<<"\n\t\t\t\t\t\t\t\t\t\t Noice, Press any key for NEXT QUESTION!!";
            score1 += 5;
            count++;
            getch();
            
        }
        else
        {
           cout<<"\n\t\t\t\t\t\t\t\t\t\t Uh-Ohh Wrong Answer!\n";
           cout<<"\n\t\t\t\t\t\t\t\t\t\t Correct answer is: 4. Bihar \n";
           cout<<"\n\t\t\t\t\t\t\t\t\t\t Press any KEY to CONTINUE!!";
           getch();
           
           gameover = false;
        }    
    }
    else  goto a; 
    
}

void Q28()
{
    system("cls");
    cout<<"\n\n\n\n\n\n\n\n\n\n\n\n\n";
    int ans;
    char ak;
    cout<<"\t\t\t\t\t\t\t\t\t\t Kathak is a classical dance of \n";
    cout<<"\t\t\t\t\t\t\t\t\t\t 1. North India \t\t 2. Tamilnadu \n \t\t\t\t\t\t\t\t\t\t 3. Manipur \t\t 4. Kerala \n";
a:  cout<<"\t\t\t\t\t\t\t\t\t\t Your Answer: ";
    cin>>ans;
    cout<<"\n\t\t\t\t\t\t\t\t\t\t Is "<<ans<<" your final answer?(y/n): ";
    cin>>ak;
    if(ak == 'y' || ak == 'Y')
    {
        if (ans == 1)
        {
            cout<<"\n\t\t\t\t\t\t\t\t\t\t Correct Answer!!\n";
            cout<<"\n\t\t\t\t\t\t\t\t\t\t Noice, Press any key for NEXT QUESTION!!";
            score1 += 5;
            count++;
            getch();
            
        }
        else
        {
           cout<<"\n\t\t\t\t\t\t\t\t\t\t Uh-Ohh Wrong Answer!\n";
           cout<<"\n\t\t\t\t\t\t\t\t\t\t Correct answer is: 1. North India \n";
           cout<<"\n\t\t\t\t\t\t\t\t\t\t Press any KEY to CONTINUE!!";
           getch();
           
           gameover = false;
        }    
    }
    else  goto a; 
    
}

void Q29()
{
    system("cls");
    cout<<"\n\n\n\n\n\n\n\n\n\n\n\n\n";
    int ans;
    char ak;
    cout<<"\t\t\t\t\t\t\t\t\t\t The last Mahakumbh of the 20th century was held at \n";
    cout<<"\t\t\t\t\t\t\t\t\t\t 1. Nasik \t\t 2. Ujjain \n \t\t\t\t\t\t\t\t\t\t 3. Allahabad \t\t 4. Haridwar \n";
a:  cout<<"\t\t\t\t\t\t\t\t\t\t Your Answer: ";
    cin>>ans;
    cout<<"\n\t\t\t\t\t\t\t\t\t\t Is "<<ans<<" your final answer?(y/n): ";
    cin>>ak;
    if(ak == 'y' || ak == 'Y')
    {
        if (ans == 4)
        {
            cout<<"\n\t\t\t\t\t\t\t\t\t\t Correct Answer!!\n";
            cout<<"\n\t\t\t\t\t\t\t\t\t\t Noice, Press any key for NEXT QUESTION!!";
            score1 += 5;
            count++;
            getch();
            
        }
        else
        {
           cout<<"\n\t\t\t\t\t\t\t\t\t\t Uh-Ohh Wrong Answer!\n";
           cout<<"\n\t\t\t\t\t\t\t\t\t\t Correct answer is: 4. Haridwar \n";
           cout<<"\n\t\t\t\t\t\t\t\t\t\t Press any KEY to CONTINUE!!";
           getch();
           
           gameover = false;
        }    
    }
    else  goto a; 
    
}

void Q30()
{
    system("cls");
    cout<<"\n\n\n\n\n\n\n\n\n\n\n\n\n";
    int ans;
    char ak;
    cout<<"\t\t\t\t\t\t\t\t\t\t In which of the following festivals are boat races a special feature? \n";
    cout<<"\t\t\t\t\t\t\t\t\t\t 1. Onam \t\t 2. Rongali Bihu \n \t\t\t\t\t\t\t\t\t\t 3. Navratri \t\t 4. Pongal \n";
a:  cout<<"\t\t\t\t\t\t\t\t\t\t Your Answer: ";
    cin>>ans;
    cout<<"\n\t\t\t\t\t\t\t\t\t\t Is "<<ans<<" your final answer?(y/n): ";
    cin>>ak;
    if(ak == 'y' || ak == 'Y')
    {
        if (ans == 1)
        {
            cout<<"\n\t\t\t\t\t\t\t\t\t\t Correct Answer!!\n";
            cout<<"\n\t\t\t\t\t\t\t\t\t\t Noice, Press any key for NEXT QUESTION!!";
            score1 += 5;
            count++;
            getch();
            
        }
        else
        {
           cout<<"\n\t\t\t\t\t\t\t\t\t\t Uh-Ohh Wrong Answer!\n";
           cout<<"\n\t\t\t\t\t\t\t\t\t\t Correct answer is: 1. Onam \n";
           cout<<"\n\t\t\t\t\t\t\t\t\t\t Press any KEY to CONTINUE!!";
           getch();
           
           gameover = false;
        }    
    }
    else  goto a; 
    
}

// Maths 10 Questions

void Q31()
{
    system("cls");
    cout<<"\n\n\n\n\n\n\n\n\n\n\n\n\n";
    int ans;
    char ak;
    cout<<"\t\t\t\t\t\t\t\t\t\t What's the value of 'pi'  \n";
    cout<<"\t\t\t\t\t\t\t\t\t\t 1. 3.7326 \t\t 2. 3.14159 \n \t\t\t\t\t\t\t\t\t\t 3. 4.91834 \t\t 4. 2.2745 \n";
a:  cout<<"\t\t\t\t\t\t\t\t\t\t Your Answer: ";
    cin>>ans;
    cout<<"\n\t\t\t\t\t\t\t\t\t\t Is "<<ans<<" your final answer?(y/n): ";
    cin>>ak;
    if(ak == 'y' || ak == 'Y')
    {
        if (ans == 2)
        {
            cout<<"\n\t\t\t\t\t\t\t\t\t\t Correct Answer!!\n";
            cout<<"\n\t\t\t\t\t\t\t\t\t\t Noice, Press any key for NEXT QUESTION!!";
            score1 += 5;
            count++;
            getch();
            
        }
        else
        {
           cout<<"\n\t\t\t\t\t\t\t\t\t\t Uh-Ohh Wrong Answer!\n";
           cout<<"\n\t\t\t\t\t\t\t\t\t\t Correct answer is: 2. '3.14159' \n";
           cout<<"\n\t\t\t\t\t\t\t\t\t\t Press any KEY to CONTINUE!!";
           getch();
           
           gameover = false;
        }    
    }
    else  goto a; 
    
}

void Q32()
{
    system("cls");
    cout<<"\n\n\n\n\n\n\n\n\n\n\n\n\n";
    int ans;
    char ak;
    cout<<"\t\t\t\t\t\t\t\t\t\t If Ravi's age is 27 years in 2011, what was his age in 2003?  \n";
    cout<<"\t\t\t\t\t\t\t\t\t\t 1. 37 years\t\t 2. 17 years\n\t\t\t\t\t\t\t\t\t\t 3. 20 years \t\t 4. 19 years \n";
a:  cout<<"\t\t\t\t\t\t\t\t\t\t Your Answer: ";
    cin>>ans;
    cout<<"\n\t\t\t\t\t\t\t\t\t\t Is "<<ans<<" your final answer?(y/n): ";
    cin>>ak;
    if(ak == 'y' || ak == 'Y')
    {
        if (ans == 4)
        {
            cout<<"\n\t\t\t\t\t\t\t\t\t\t Correct Answer!!\n";
            cout<<"\n\t\t\t\t\t\t\t\t\t\t Noice, Press any key for NEXT QUESTION!!";
            score1 += 5;
            count++;
            getch();
            
        }
        else
        {
           cout<<"\n\t\t\t\t\t\t\t\t\t\t Uh-Ohh Wrong Answer!\n";
           cout<<"\n\t\t\t\t\t\t\t\t\t\t Correct answer is: 4. 19 years \n";
           cout<<"\n\t\t\t\t\t\t\t\t\t\t Press any KEY to CONTINUE!!";
           getch();
           
           gameover = false;
        }    
    }
    else  goto a; 
    
}

void Q33()
{
    system("cls");
    cout<<"\n\n\n\n\n\n\n\n\n\n\n\n\n";
    int ans;
    char ak;
    cout<<"\t\t\t\t\t\t\t\t\t\t What is '7%' Equal to  \n";
    cout<<"\t\t\t\t\t\t\t\t\t\t 1. 0.007\t\t 2. 0.7\n\t\t\t\t\t\t\t\t\t\t 3. 0.07 \t\t 4. 0.0007 \n";
a:  cout<<"\t\t\t\t\t\t\t\t\t\t Your Answer: ";
    cin>>ans;
    cout<<"\n\t\t\t\t\t\t\t\t\t\t Is "<<ans<<" your final answer?(y/n): ";
    cin>>ak;
    if(ak == 'y' || ak == 'Y')
    {
        if (ans == 3)
        {
            cout<<"\n\t\t\t\t\t\t\t\t\t\t Correct Answer!!\n";
            cout<<"\n\t\t\t\t\t\t\t\t\t\t Noice, Press any key for NEXT QUESTION!!";
            score1 += 5;
            count++;
            getch();
            
        }
        else
        {
           cout<<"\n\t\t\t\t\t\t\t\t\t\t Uh-Ohh Wrong Answer!\n";
           cout<<"\n\t\t\t\t\t\t\t\t\t\t Correct answer is: 3. 0.07 \n";
           cout<<"\n\t\t\t\t\t\t\t\t\t\t Press any KEY to CONTINUE!!";
           getch();
           
           gameover = false;
        }    
    }
    else  goto a; 
    
}

void Q34()
{
    system("cls");
    cout<<"\n\n\n\n\n\n\n\n\n\n\n\n\n";
    int ans;
    char ak;
    cout<<"\t\t\t\t\t\t\t\t\t\t How many years are there in a decade?  \n";
    cout<<"\t\t\t\t\t\t\t\t\t\t 1. 20\t\t 2. 10 \n\t\t\t\t\t\t\t\t\t\t 3. 100 \t\t 4. 5 \n";
a:  cout<<"\t\t\t\t\t\t\t\t\t\t Your Answer: ";
    cin>>ans;
    cout<<"\n\t\t\t\t\t\t\t\t\t\t Is "<<ans<<" your final answer?(y/n): ";
    cin>>ak;
    if(ak == 'y' || ak == 'Y')
    {
        if (ans == 2)
        {
            cout<<"\n\t\t\t\t\t\t\t\t\t\t Correct Answer!!\n";
            cout<<"\n\t\t\t\t\t\t\t\t\t\t Noice, Press any key for NEXT QUESTION!!";
            score1 += 5;
            count++;
            getch();
            
        }
        else
        {
           cout<<"\n\t\t\t\t\t\t\t\t\t\t Uh-Ohh Wrong Answer!\n";
           cout<<"\n\t\t\t\t\t\t\t\t\t\t Correct answer is: 2. 10 \n";
           cout<<"\n\t\t\t\t\t\t\t\t\t\t Press any KEY to CONTINUE!!";
           getch();
           
           gameover = false;
        }    
    }
    else  goto a; 
    
}

void Q35()
{
    system("cls");
    cout<<"\n\n\n\n\n\n\n\n\n\n\n\n\n";
    int ans;
    char ak;
    cout<<"\t\t\t\t\t\t\t\t\t\t Square of 15 is?  \n";
    cout<<"\t\t\t\t\t\t\t\t\t\t 1. 225 \t\t 2. 252 \n\t\t\t\t\t\t\t\t\t\t 3. 205 \t\t 4. 220 \n";
a:  cout<<"\t\t\t\t\t\t\t\t\t\t Your Answer: ";
    cin>>ans;
    cout<<"\n\t\t\t\t\t\t\t\t\t\t Is "<<ans<<" your final answer?(y/n): ";
    cin>>ak;
    if(ak == 'y' || ak == 'Y')
    {
        if (ans == 1)
        {
            cout<<"\n\t\t\t\t\t\t\t\t\t\t Correct Answer!!\n";
            cout<<"\n\t\t\t\t\t\t\t\t\t\t Noice, Press any key for NEXT QUESTION!!";
            score1 += 5;
            count++;
            getch();
            
        }
        else
        {
           cout<<"\n\t\t\t\t\t\t\t\t\t\t Uh-Ohh Wrong Answer!\n";
           cout<<"\n\t\t\t\t\t\t\t\t\t\t Correct answer is: 1. 225 \n";
           cout<<"\n\t\t\t\t\t\t\t\t\t\t Press any KEY to CONTINUE!!";
           getch();
           
           gameover = false;
        }    
    }
    else  goto a; 
    
}

void Q36()
{
    system("cls");
    cout<<"\n\n\n\n\n\n\n\n\n\n\n\n\n";
    int ans;
    char ak;
    cout<<"\t\t\t\t\t\t\t\t\t\t Who is the Father of Mathematics?  \n";
    cout<<"\t\t\t\t\t\t\t\t\t\t 1. Aryabhatt \t\t 2. Pythagoras \n\t\t\t\t\t\t\t\t\t\t 3. Ramanujan \t\t 4. Archimedes \n";
a:  cout<<"\t\t\t\t\t\t\t\t\t\t Your Answer: ";
    cin>>ans;
    cout<<"\n\t\t\t\t\t\t\t\t\t\t Is "<<ans<<" your final answer?(y/n): ";
    cin>>ak;
    if(ak == 'y' || ak == 'Y')
    {
        if (ans == 4)
        {
            cout<<"\n\t\t\t\t\t\t\t\t\t\t Correct Answer!!\n";
            cout<<"\n\t\t\t\t\t\t\t\t\t\t Noice, Press any key for NEXT QUESTION!!";
            score1 += 5;
            count++;
            getch();
            
        }
        else
        {
           cout<<"\n\t\t\t\t\t\t\t\t\t\t Uh-Ohh Wrong Answer!\n";
           cout<<"\n\t\t\t\t\t\t\t\t\t\t Correct answer is: 4. Archimedes \n";
           cout<<"\n\t\t\t\t\t\t\t\t\t\t Press any KEY to CONTINUE!!";
           getch();
           
           gameover = false;
        }    
    }
    else  goto a; 
    
}

void Q37()
{
    system("cls");
    cout<<"\n\n\n\n\n\n\n\n\n\n\n\n\n";
    int ans;
    char ak;
    cout<<"\t\t\t\t\t\t\t\t\t\t How Many Months Make a Century?  \n";
    cout<<"\t\t\t\t\t\t\t\t\t\t 1. 12 \t\t 2. 120 \n\t\t\t\t\t\t\t\t\t\t 3. 1200 \t\t 4. 12000 \n";
a:  cout<<"\t\t\t\t\t\t\t\t\t\t Your Answer: ";
    cin>>ans;
    cout<<"\n\t\t\t\t\t\t\t\t\t\t Is "<<ans<<" your final answer?(y/n): ";
    cin>>ak;
    if(ak == 'y' || ak == 'Y')
    {
        if (ans == 3)
        {
            cout<<"\n\t\t\t\t\t\t\t\t\t\t Correct Answer!!\n";
            cout<<"\n\t\t\t\t\t\t\t\t\t\t Noice, Press any key for NEXT QUESTION!!";
            score1 += 5;
            count++;
            getch();
            
        }
        else
        {
           cout<<"\n\t\t\t\t\t\t\t\t\t\t Uh-Ohh Wrong Answer!\n";
           cout<<"\n\t\t\t\t\t\t\t\t\t\t Correct answer is: 3. 1200 \n";
           cout<<"\n\t\t\t\t\t\t\t\t\t\t Press any KEY to CONTINUE!!";
           getch();
           
           gameover = false;
        }    
    }
    else  goto a; 
    
}

void Q38()
{
    system("cls");
    cout<<"\n\n\n\n\n\n\n\n\n\n\n\n\n";
    int ans;
    char ak;
    cout<<"\t\t\t\t\t\t\t\t\t\t How Many Sides are there in a Decagon?  \n";
    cout<<"\t\t\t\t\t\t\t\t\t\t 1. 7 \t\t 2. 8 \n\t\t\t\t\t\t\t\t\t\t 3. 9 \t\t 4. 10 \n";
a:  cout<<"\t\t\t\t\t\t\t\t\t\t Your Answer: ";
    cin>>ans;
    cout<<"\n\t\t\t\t\t\t\t\t\t\t Is "<<ans<<" your final answer?(y/n): ";
    cin>>ak;
    if(ak == 'y' || ak == 'Y')
    {
        if (ans == 4)
        {
            cout<<"\n\t\t\t\t\t\t\t\t\t\t Correct Answer!!\n";
            cout<<"\n\t\t\t\t\t\t\t\t\t\t Noice, Press any key for NEXT QUESTION!!";
            score1 += 5;
            count++;
            getch();
            
        }
        else
        {
           cout<<"\n\t\t\t\t\t\t\t\t\t\t Uh-Ohh Wrong Answer!\n";
           cout<<"\n\t\t\t\t\t\t\t\t\t\t Correct answer is: 4. 10 \n";
           cout<<"\n\t\t\t\t\t\t\t\t\t\t Press any KEY to CONTINUE!!";
           getch();
           
           gameover = false;
        }    
    }
    else  goto a; 
    
}

void Q39()
{
    system("cls");
    cout<<"\n\n\n\n\n\n\n\n\n\n\n\n\n";
    int ans;
    char ak;
    cout<<"\t\t\t\t\t\t\t\t\t\t Look at this series: 36, 34, 30, 28, …, 22 What number should come to fill in the blank space  \n";
    cout<<"\t\t\t\t\t\t\t\t\t\t 1. 22 \t\t 2. 24 \n\t\t\t\t\t\t\t\t\t\t 3. 26 \t\t 4. 20 \n";
a:  cout<<"\t\t\t\t\t\t\t\t\t\t Your Answer: ";
    cin>>ans;
    cout<<"\n\t\t\t\t\t\t\t\t\t\t Is "<<ans<<" your final answer?(y/n): ";
    cin>>ak;
    if(ak == 'y' || ak == 'Y')
    {
        if (ans == 2)
        {
            cout<<"\n\t\t\t\t\t\t\t\t\t\t Correct Answer!!\n";
            cout<<"\n\t\t\t\t\t\t\t\t\t\t Noice, Press any key for NEXT QUESTION!!";
            score1 += 5;
            count++;
            getch();
            
        }
        else
        {
           cout<<"\n\t\t\t\t\t\t\t\t\t\t Uh-Ohh Wrong Answer!\n";
           cout<<"\n\t\t\t\t\t\t\t\t\t\t Correct answer is: 2. 24 \n";
           cout<<"\n\t\t\t\t\t\t\t\t\t\t Press any KEY to CONTINUE!!";
           getch();
           
           gameover = false;
        }    
    }
    else  goto a; 
    
}

void Q40()
{
    system("cls");
    cout<<"\n\n\n\n\n\n\n\n\n\n\n\n\n";
    int ans;
    char ak;
    cout<<"\t\t\t\t\t\t\t\t\t\t What is the area of square who's side is 9m ?  \n";
    cout<<"\t\t\t\t\t\t\t\t\t\t 1. 18 m sq \t\t 2. 81 m cube \n\t\t\t\t\t\t\t\t\t\t 3. 81 m sq \t\t 4. 91 m cube \n";
a:  cout<<"\t\t\t\t\t\t\t\t\t\t Your Answer: ";
    cin>>ans;
    cout<<"\n\t\t\t\t\t\t\t\t\t\t Is "<<ans<<" your final answer?(y/n): ";
    cin>>ak;
    if(ak == 'y' || ak == 'Y')
    {
        if (ans == 3)
        {
            cout<<"\n\t\t\t\t\t\t\t\t\t\t Correct Answer!!\n";
            cout<<"\n\t\t\t\t\t\t\t\t\t\t Noice, Press any key for NEXT QUESTION!!";
            score1 += 5;
            count++;
            getch();
            
        }
        else
        {
           cout<<"\n\t\t\t\t\t\t\t\t\t\t Uh-Ohh Wrong Answer!\n";
           cout<<"\n\t\t\t\t\t\t\t\t\t\t Correct answer is: 3. 81 m sq \n";
           cout<<"\n\t\t\t\t\t\t\t\t\t\t Press any KEY to CONTINUE!!";
           getch();
           
           gameover = false;
        }    
    }
    else  goto a; 
    
}

// main

int main()
{   
    
a:  
    gotoxy(20 + a1, 8 + b);
    cout<<"-----------------------------------------------------------\n";
    gotoxy(20 + a1, 10 + b);
    cout<<"                     GAMES OF MIND!                        \n";
    gotoxy(20 + a1, 12 + b);
    cout<<"                 Press ANY KEY to START!!";
    gotoxy(20 + a1, 14 + b);
    cout<<"-----------------------------------------------------------\n";
    getch();
    gameover = true;
    system("cls");
    int ch;
    gotoxy(20 + a1, 8 + b);
    cout<<"-----------------------------------------------------------\n";
    gotoxy(20 + a1, 10 + b);
    cout<<"         Choose the right option to move forward!!         \n";
    gotoxy(20 + a1, 12 + b);
    cout<<"                 Press ANY KEY to START!!                    ";
    gotoxy(20 + a1, 14 + b);
    cout<<"-----------------------------------------------------------\n";
    getch();
    
    
    
    system("cls");
    int t=0;
    
v:  
    gotoxy(20 + a1, 8 + b);
    cout<<" Chose your Topic            \n";
    gotoxy(20 + a1, 10 + b);
    cout<<" 1. General Knowledge \t 2. Literature ";
    gotoxy(20 + a1, 12 + b);
    cout<<" 3. Indian Culture \t 4. Maths";
    gotoxy(20 + a1, 14 + b);
    cout<<" => ";
    cin>>t;
    gameover = true;
    

    // question loop

    while(gameover)
    {
        if(t == 1)      //General Knowledge 
        {
            for (int i = 1; i < 11; i++)
            {
                
                switch(i)
                {
                    case 1: count = 0;
                            Q1(); break;
                    case 2: Q2(); break;
                    case 3: Q3(); break;
                    case 4: Q4(); break;
                    case 5: Q5(); 
                            if(count >=3)
                            {
                                s1: system("cls");
                                gotoxy(20 + a1, 8 + b);
                                cout<<" Chose which game you want to Play?: ";
                                gotoxy(20 + a1, 10 + b);
                                cout<<" 1. Snake game \t 2. Brick Breaker Game \t 3. Ping Pong Game ";
                                gotoxy(20 + a1, 12 + b);
                                cout<<" Enter: ";
                                int ch;
                                cin>>ch;
                                switch(ch)
                                {
                                    case 1: Snake();
                                            break;
                                    case 2: BRICKS();
                                            break;
                                    case 3: PingPong();
                                            break;
                                    default:cout<<" Invalid choice!!";
                                            goto s1;
                                            break;
                                }
                                
                            }
                            else i = 1000;
                            break;
                    case 6: Q6(); break;
                    case 7: Q7(); break;
                    case 8: Q8(); break;
                    case 9: Q9(); break;
                    case 10: Q10(); 
                            if(count >=3)
                            {
                                s2: system("cls");
                                gotoxy(20 + a1, 8 + b);
                                cout<<"\n Chose which game you want to Play?: ";
                                gotoxy(20 + a1, 10 + b);
                                cout<<"\n 1. Snake game \t 2. Brick Breaker Game \t 3. Ping Pong Game ";
                                gotoxy(20 + a1, 12 + b);
                                cout<<"\n Enter: ";
                                int ch;
                                cin>>ch;
                                switch(ch)
                                {
                                    case 1: Snake();
                                            break;
                                    case 2: BRICKS();
                                            break;
                                    case 3: PingPong();
                                            break;
                                    default:cout<<" Invalid choice!!";
                                            goto s2;
                                            break;
                                }
                            }
                            else i = 1000;
                            break;
                    default: break;
                }
                
                
            }
        }

        else if(t == 2)      //Literature 
        {
            for (int i = 1; i < 11; i++)
            {
                
                switch(i)
                {
                    case 1: count = 0;
                            Q11(); break;
                    case 2: Q12(); break;
                    case 3: Q13(); break;
                    case 4: Q14(); break;
                    case 5: Q15(); 
                            if(count >=3)
                            {
                                s3: system("cls");
                                gotoxy(20 + a1, 8 + b);
                                cout<<" Chose which game you want to Play?: ";
                                gotoxy(20 + a1, 10 + b);
                                cout<<" 1. Snake game \t 2. Brick Breaker Game \t 3. Ping Pong Game ";
                                gotoxy(20 + a1, 12 + b);
                                cout<<" Enter: ";
                                int ch;
                                cin>>ch;
                                switch(ch)
                                {
                                    case 1: Snake();
                                            break;
                                    case 2: BRICKS();
                                            break;
                                    case 3: PingPong();
                                            break;
                                    default:cout<<" Invalid choice!!";
                                            goto s3;
                                            break;
                                }
                            }
                            else i = 1000;
                            break;
                    case 6: Q16(); break;
                    case 7: Q17(); break;
                    case 8: Q18(); break;
                    case 9: Q19(); break;
                    case 10: Q20(); 
                            if(count >=3)
                            {
                                s4: system("cls");
                                gotoxy(20 + a1, 8 + b);
                                cout<<" Chose which game you want to Play?: ";
                                gotoxy(20 + a1, 10 + b);
                                cout<<" 1. Snake game \t 2. Brick Breaker Game \t 3. Ping Pong Game ";
                                gotoxy(20 + a1, 12 + b);
                                cout<<" Enter: ";
                                int ch;
                                cin>>ch;
                                switch(ch)
                                {
                                    case 1: Snake();
                                            break;
                                    case 2: BRICKS();
                                            break;
                                    case 3: PingPong();
                                            break;
                                    default:cout<<" Invalid choice!!";
                                            goto s4;
                                            break;
                                }
                            }
                            else i = 1000;
                            break;
                    default: break;
                }
                
                
            }
        }
        
        else if(t == 3)      //Indian Culture 
        {
            for (int i = 1; i < 11; i++)
            {
                
                switch(i)
                {
                    case 1: count = 0;
                            Q21(); break;
                    case 2: Q22(); break;
                    case 3: Q23(); break;
                    case 4: Q24(); break;
                    case 5: Q25(); 
                            if(count >=3)
                            {
                                s5: system("cls");
                                gotoxy(20 + a1, 8 + b);
                                cout<<" Chose which game you want to Play?: ";
                                gotoxy(20 + a1, 10 + b);
                                cout<<" 1. Snake game \t 2. Brick Breaker Game \t 3. Ping Pong Game ";
                                gotoxy(20 + a1, 12 + b);
                                cout<<" Enter: ";
                                int ch;
                                cin>>ch;
                                switch(ch)
                                {
                                    case 1: Snake();
                                            break;
                                    case 2: BRICKS();
                                            break;
                                    case 3: PingPong();
                                            break;
                                    default:cout<<" Invalid choice!!";
                                            goto s5;
                                            break;
                                }
                            }
                            else i = 1000;
                            break;
                    case 6: Q26(); break;
                    case 7: Q27(); break;
                    case 8: Q28(); break;
                    case 9: Q29(); break;
                    case 10: Q30(); 
                            if(count >=3)
                            {
                                s6: system("cls");
                                gotoxy(20 + a1, 8 + b);
                                cout<<" Chose which game you want to Play?: ";
                                gotoxy(20 + a1, 10 + b);
                                cout<<" 1. Snake game \t 2. Brick Breaker Game \t 3. Ping Pong Game ";
                                gotoxy(20 + a1, 12 + b);
                                cout<<" Enter: ";
                                int ch;
                                cin>>ch;
                                switch(ch)
                                {
                                    case 1: Snake();
                                            break;
                                    case 2: BRICKS();
                                            break;
                                    case 3: PingPong();
                                            break;
                                    default:cout<<" Invalid choice!!";
                                            goto s6;
                                            break;
                                }
                            }
                            else i = 1000;
                            break;
                    default: break;
                }
                
                
            }
        }
        
        else if(t == 4)      //Maths 
        {
            for (int i = 1; i < 11; i++)
            {
                
                switch(i)
                {
                    case 1: count = 0;
                            Q31(); break;
                    case 2: Q32(); break;
                    case 3: Q33(); break;
                    case 4: Q34(); break;
                    case 5: Q35(); 
                            if(count >=3)
                            {
                                s7: system("cls");
                                gotoxy(20 + a1, 8 + b);
                                cout<<" Chose which game you want to Play?: ";
                                gotoxy(20 + a1, 10 + b);
                                cout<<" 1. Snake game \t 2. Brick Breaker Game \t 3. Ping Pong Game ";
                                gotoxy(20 + a1, 12 + b);
                                cout<<" Enter: ";
                                int ch;
                                cin>>ch;
                                switch(ch)
                                {
                                    case 1: Snake();
                                            break;
                                    case 2: BRICKS();
                                            break;
                                    case 3: PingPong();
                                            break;
                                    default:cout<<" Invalid choice!!";
                                            goto s7;
                                            break;
                                }
                            }
                            else i = 1000;
                            break;
                    case 6: Q36(); break;
                    case 7: Q37(); break;
                    case 8: Q38(); break;
                    case 9: Q39(); break;
                    case 10: Q40(); 
                            if(count >=3)
                            {
                                s8: system("cls");
                                gotoxy(20 + a1, 8 + b);
                                cout<<" Chose which game you want to Play?: ";
                                gotoxy(20 + a1, 10 + b);
                                cout<<" 1. Snake game \t 2. Brick Breaker Game \t 3. Ping Pong Game ";
                                gotoxy(20 + a1, 12 + b);
                                cout<<" Enter: ";
                                int ch;
                                cin>>ch;
                                switch(ch)
                                {
                                    case 1: Snake();
                                            break;
                                    case 2: BRICKS();
                                            break;
                                    case 3: PingPong();
                                            break;
                                    default:cout<<" Invalid choice!!";
                                            goto s8;
                                            break;
                                }
                            }
                            else i = 1000;
                            break;
                    default: break;
                }
                
                
            }
        }
             
    }

    // End Screen

    system("cls");
    gotoxy(20 + a1, 8 + b);
    cout<<"-----------------------------------------------------------\n";
    gotoxy(20 + a1, 10 + b);
    cout<<"             Game Over!!  WELL PLAYED!!                    \n"; getch();
    gotoxy(20 + a1, 12 + b);
    cout<<"             Total Score: " << score1 + score << endl; getch();
    gotoxy(20 + a1, 14 + b);
    cout<<"             Press any key to TRY AGAIN                      ";
    gotoxy(20 + a1, 16 + b);
    cout<<"-----------------------------------------------------------\n";
    getch();
    system("cls");
    goto v;
    cout<<"\n\n\n";
    return 0;    
}
