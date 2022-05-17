#include <iostream>
#include <sys/ioctl.h>
#include <unistd.h>
#include <ctime>
#include <termios.h>
#include <signal.h>
#include <sys/poll.h>
#include <string>
#include <algorithm>

#include "Tview.hpp"
#include "model.hpp" 

//Foreground Colors
#define FOREGROUND_COL_BLACK 30
#define FOREGROUND_COL_RED 31
#define FOREGROUND_COL_GREEN 32
#define FOREGROUND_COL_YELLOW 33
#define FOREGROUND_COL_BLUE 34
#define FOREGROUND_COL_MAGENTA 35
#define FOREGROUND_COL_CYAN 36
#define FOREGROUND_COL_WHITE 37

//Background Colors
#define BACKGROUND_COL_BLACK 40
#define BACKGROUND_COL_RED 41
#define BACKGROUND_COL_GREEN 42
#define BACKGROUND_COL_YELLOW 43
#define BACKGROUND_COL_BLUE 44
#define BACKGROUND_COL_MAGENTA 45
#define BACKGROUND_COL_CYAN 46
#define BACKGROUND_COL_WHITE 47

const size_t precision = 1;

struct termios old_term;
bool final = false;

void SignHandler(int n) 
{
    final = true;
}

Tview::Tview() 
{
    struct termios term;
    tcgetattr(0, &term);
    
    old_term = term;

    cfmakeraw(&term);
    term.c_lflag |= ISIG; 
    tcsetattr(0, TCSANOW, &term);
    signal(SIGINT, SignHandler);
}

Tview::~Tview() 
{
    tcsetattr(0, TCSANOW, &old_term);
    CleanScreen();
}

void Tview::CleanScreen() 
{
    printf("\e[H\e[J");
}

void Tview::Move(int x, int y) 
{
    printf("\e[%d;%dH", y, x);
}

void Tview::SetColor(int color) 
{
    printf("\033[0;%dm", color);
}

size_t Tview::Draw()
{    
    struct winsize w;
    ioctl(1, TIOCGWINSZ, &w);

    const size_t length_x  = w.ws_col;
    const size_t length_y  = w.ws_row;

    size_t start_x = length_x / 2;
    size_t start_y = length_y / 2;

    size_t rabbits_num = 50;

    Snake snake(start_x, start_y, length_x, length_y);
    Rabbit rabbits(length_x, length_y, rabbits_num);

    while(!final) 
    {
        struct pollfd arr;
        arr.fd = 0;
        arr.events = POLLIN;

        int n = poll(&arr, 1, 500);
        if( n == 1 ) 
        {
            char c;
            scanf("%c", &c);
            
            if(c == 'q')
            {
                break;
            } 

            else 
            {
                switch (c) 
                {
                    case 's' :
                        snake.ChangeDir(Dir::UP);
                    break;

                    case 'w' :
                        snake.ChangeDir(Dir::DOWN);
                    break;

                    case 'a' :
                        snake.ChangeDir(Dir::LEFT);
                    break;

                    case 'd' :
                        snake.ChangeDir(Dir::RIGHT);
                    break;

                    default:
                    break;
                }
            }
        }
        CleanScreen();
        DrawBoundary(length_x, length_y);
        DrawSnake(snake.snake_body, snake.GetDir());
        DrawRabbits(rabbits.map);
        Move(3, 2);  
        printf("score: %d", (int)snake.GetScore());
        final = snake.Move();  
        snake.CatchRabbit(rabbits.map, precision);
        fflush(stdout);
    }
    return snake.GetScore();
}

void Tview::DrawRabbits(const std::map<int, int>& rabbits) 
{
    for(const auto& coord: rabbits) 
    {
        Move(coord.first, coord.second);
        SetColor(FOREGROUND_COL_WHITE);
        printf("@");
        fflush(stdout);               
    }
}

void Tview::DrawSnake(const std::vector<std::pair<int, int>>& snake_body, Dir dir) 
{
    for(int i = 0; i < snake_body.size(); ++i) 
    {
        Move(snake_body.at(i).first, snake_body.at(i).second);
        if(i == 0) 
        {
            SetColor(FOREGROUND_COL_GREEN);
            switch (dir)
            {
            case Dir::DOWN :
                printf("^");
                break;
            
            case Dir::LEFT :
                printf("<");
                break;
            
            case Dir::RIGHT :
                printf(">");
                break;

            case Dir::UP :
                printf("v");
                break;

            default:
                break;
            }
        } 
        else 
        {
            SetColor(FOREGROUND_COL_GREEN);
            printf("o");
        }
    }
}

void Tview::DrawBoundary(const size_t length_x, const size_t length_y) 
{
    SetColor(FOREGROUND_COL_WHITE);
    Move(1, 1);
    for(int i = 1; i < length_x; ++i) 
    {
        printf("#");
    }

    Move(1, length_y);
    for(int i = 1; i < length_x; ++i) 
    {
        printf("#");
    }
        
    for(int i = 1; i < length_y; ++i) 
    {
        Move(1, i);
        printf("#");
        Move(length_x, i);
        printf("#");
    }
}


