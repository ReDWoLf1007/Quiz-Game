#This code is not my original work, I learned it from Angulars from Youtube.

#include<iostream>
#include<conio.h>
#include<dos.h>
#include<stdlib.h>
#include<stdlib.h>
#include<string.h>
#include<windows.h>
#include<time.h>

#define a 45
#define b 10

using namespace std;

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

void printBorder()
{
    for (i = 2; i <= 79; i++)
    {
        gotoxy(i + a, 1 + b);
        cout<<'-';
        gotoxy(i + a, 25 + b);
        cout<<'-';
    }
    for (i = 1; i <= 25; i++)
    {
        gotoxy(2 + a, i + b);
        cout<<'|';
        gotoxy(79 + a, i + b);
        cout<<'|';
    }
}

void setplayers()
{
    system("cls");
    printBorder();
    gotoxy(4 + a, 3 + b);
    cout<<"Score: 0";
    gotoxy(50 + a, 3 + b);
    cout<<"Press Esc key to quit the game";
    for(i = 3; i<=78; i++)
    {
        gotoxy(i + a, 4 + b);
        cout<<"-";
    }
    for(i = 0; i <= strlen(l); i++)
    {
        gotoxy(5 + a, 5+i + b);
        cout<< l[i];
    }
    for(i = 0; i <= strlen(l); i++)
    {
        gotoxy(76 + a, 5 + i + b);
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
                gotoxy(x + a, y + b);
                cout<<"O";
                Sleep(50);
                gotoxy(x + a, y + b);
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
                            gotoxy(76 + a, k + strlen(l) + b);
                            cout<<"o";
                            gotoxy(76 + a, k + b);
                            if(k != 4) cout<<' ';
                            k++;
                        }
                        if(y < k + strlen(l) - 3)
                        {
                            gotoxy(76 + a, k + b);
                            cout<<"o";
                            gotoxy(76 + a, k + strlen(l) + b);
                            if(k + strlen(l) != 25) cout<<' ';
                            k--;
                        }
                    }
                }

                if(x == 6 && (y < c || y > c + strlen(l) - 1))
                {
                    gotoxy(x + a, y + b);
                    cout<<"YOU LOSE! Press 'r' or ENTER to play again";
                    op = 0;
                    break;  
                }

                if(x == 6 && op == 1)
                {
                    gotoxy(4 + a, 3 + b);
                    cout<<"SCORE: "<< ++sc;
                }
            }
        }

        char ch = getch();

        if(ch == ' ' && op == 1)
        {
            pp = 1;
            go = 0;
            gotoxy(22 + a,12 + b);
            cout<<"GAME PAUSED! PRESS ENTER to continue !";
        }

        if(ch == 13 && pp && op == 1)
        {
            pp = 0;
            go = 1;
            gotoxy(x + a, y + b);
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
            gotoxy(5 + a, c + strlen(l) + b);
            cout<<"o";  
            gotoxy(5 + a, c + b);
            cout<<' ';
            c++;
        }

        if((ch == 'w' || ch == 'W' || ch == 72) && c >= 6 && op)
        {
            gotoxy(5 + a, c - 1 + b);
            cout<<"o";
            gotoxy(5, c + 4);
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
    gotoxy(34 + a, 4 + b);
    cout<<"PING PONG";
    for(i = 8; i<= 73; i++)
    {
        gotoxy(i + a, 6 + b);
        cout<<'-';
    }
    gotoxy(34 + a, 10 + b);
    cout<<"1. PLAY THE GAME!";
    gotoxy(34 + a, 12 + b);
    cout<<"2. HOW TO PLAY!";
    gotoxy(34 + a, 14 + b);
    cout<<"3. EXIT!";
    gotoxy(34 + a, 16 + b);
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
    gotoxy(4 + a, 3 + b);
    cout<<"INTRUCTIONS!";
    gotoxy(4 + a, 4 + b);
    cout<<"------------";
    gotoxy(4 + a, 5 + b);
    cout<<"- Press w or Up Arrow to move up.";
    gotoxy(4 + a, 7 + b);
    cout<<"- Press s or Down Arrow to move down.";
    gotoxy(4 + a, 9 + b);
    cout<<"- Press Spacebar to Pause the game.";
    gotoxy(4 + a, 11 + b);
    cout<<"- Press Esc to quit the game.";
    gotoxy(4 + a, 15 + b);
    cout<<"- Press any key to go to menu...";
    getch();
    displayMenu();
}

int main()
{   
    setcursor(0, 0);
    srand((unsigned) time(NULL));
    system("cls");
    displayMenu();   
    return 0;
}
