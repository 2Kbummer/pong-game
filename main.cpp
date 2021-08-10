#include <iostream>
#include <conio.h>
#include <windows.h>
#include <random>
#include <ctime>
using namespace std;

//global variables
bool gameOver;
const float width = 50;
const float height = 20;
float pongX,pongY, pXd,pYd, pongStart, player1X,player1Y, player2X,player2Y, scoreP1, scoreP2;
enum eDirection {STOP = 0, UP, DOWN};
eDirection dirP1;
eDirection dirP2;

void Start(){
    gameOver = false;
    dirP1 = STOP;
    dirP2 = STOP;
    player1X = 2;
    player1Y = height/2;
    player2X = width - 3;
    player2Y = height/2;
    pongX = width/2;
    pongY = height/2;
    pXd = 1; //R: 1; L: -1
    pYd = 0;//dUp: -2; dDown: 2; straight: 0
    pongStart = false;
    scoreP1 = 0;
    scoreP2 = 0;
}

void Looks(){
    system("cls"); //will refresh screen; will cause flickering
    cout << "Press G to Start Pong" << "   " << pXd << "  " << pYd << endl;

    for(float i = 0; i < width+2; i++) //TOP WALL
        cout << "#";
    cout << endl;
    for(float i = 0; i < height; i++) //filling top to bottom
    {
        for(float j = 0; j < width; j++) //filling left to right
        {
            if(j == 0) //LEFT WALL
                cout << "#";
            if(i == player1Y && j == player1X || i == player2Y && j == player2X)
                cout << "|";
                else if(i == pongY && j == pongX)
                    cout << "O";
                else
                    cout << " ";
            if(j == width - 1) //RIGHT WALL
            cout << "#";
        }
        cout << endl;
    }
    for(float i = 0; i < width+2; i++) //BOTTOM WALL
        cout << "#";
    cout << endl;
    cout << "Score for Player 1: " << scoreP1 << endl;
    cout << "Score for Player 2: " << scoreP2;
}

void Input(){
    if(_kbhit())
    {
        switch(_getch())
        {
            case 'w': //player 1
                dirP1 = UP; break;
            case 's':
                dirP1 = DOWN; break;
            case 'i': //player 2
                dirP2 = UP; break;
            case 'k':
                dirP2 = DOWN; break;
            case 'x':
                gameOver = true; break;
            case 'g':
                pongStart = true; break;
            default:
                break;
        }
    }
}

void PongStart(){
    //pXd: 1, -1      pYd: -2, 0, 2
        srand(time(0));
        float pX1[2] = {1, -1};
        float pY1[3] = {-2, 0, 2};
        int pX2 = rand() % (2); //2 numbers
        int pY2 = rand() % (3); //3 numbers
        pXd = pX1[pX2];
        pYd = pY1[pY2];
}

void Logic(){
    //moving paddle up/down
    switch (dirP1)
    {
        case UP:
            player1Y-=3; break;
        case DOWN:
            player1Y+=3; break;
        default: break;
    }
    switch (dirP2)
    {
        case UP:
            player2Y-=3; break;
        case DOWN:
            player2Y+=3; break;
        default: break;
    }

    //moving paddle through up & down walls
    if(player1Y >= height)
        player1Y = 0;
        else if(player1Y < 0)
            player1Y = height - 1;
    if(player2Y >= height)
        player2Y = 0;
        else if(player2Y < 0)
            player2Y = height - 1;

    //when press g, ball randomly goes to one side in a random direction: diagonal up, straight, diagonal down


    if(pongStart)
    {
        pongX+=pXd;
        pongY+=pYd;
        if(pongY <= 0 || pongY >= height)
            pYd = -pYd;

        /*
        if want to bounce off right/left walls
            LEFT wall
                if(x <= 0)
                    pXd = -pXd;
            RIGHT wall
                if(x <= width)
                    pXd = -pXd;
        */
    }

    //ball hits opponents wall, player gets points or ball hits paddle goes random direction, also reset ball to 0 starting point;
    if(pongX == player1X && pongY == player1Y || pongX == player2X && pongY == player2Y){
        pXd = -pXd;
        pYd = -pYd;
        PongStart();
    }else if(pongX == width){
        scoreP1 += 1;
        pongX = width/2;
        pongY = height /2;
        PongStart;
    }else if(pongX == 0){
        scoreP2 += 1;
        pongX = width/2;
        pongY = height/2;
        PongStart;
    }


    //once ball hits a wall, then ball restarts to middle position where goes into random direction: diagonal up, straight, diagonal down


    //once score gets to 3 gameOver = true; whoever higher score, player winner prompt
    if(scoreP1 == 3){
        cout << "\nplayer 2 sucks!";
        gameOver = true;
    }
    if(scoreP2 == 3){
        cout << "\n\nplayer 1 sucks!\n";
        gameOver = true;
    }
}

int main()
{
    Start();
    PongStart();
    while(!gameOver){
        Looks();
        Input();
        Logic();
        Sleep(50);
    }
}
