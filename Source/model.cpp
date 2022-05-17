#include "model.hpp"
#include <vector>
#include <algorithm>
#include <random>

Snake::Snake(const size_t start_x, const size_t start_y, const size_t length_x, const size_t length_y) 
{
    start_x_ = start_x;
    start_y_ = start_y;
    length_x_ = length_x;
    length_y_ = length_y;
    score_ = 0;
    int snake_size = 7;
    for (int i = 0; i < snake_size; i++)
        snake_body.push_back(std::pair<float, float>(start_x - i, start_y));
    dir_ = Dir::RIGHT;
}

bool Snake::IsAlive() const 
{
    if(snake_body.at(0).first == length_x_ || !snake_body.at(0).first == 1 || snake_body.at(0).second == length_y_ || !snake_body.at(0).second == 1) 
    {
        return false;
    }
    else 
    {
        for(int i = 1; i < snake_body.size(); ++i) 
        {
            if(snake_body.at(i) == snake_body.at(0)) return false;
        }    
    }

    return true;
}

bool Snake::Move() 
{
    float step = 1.0;
    
    if(IsAlive()) 
    {
        if(snake_body.size() > 1) 
        {
            snake_body.emplace(snake_body.begin() + 1, snake_body.at(0));
            snake_body.pop_back();
        }

        switch (dir_) 
        {
        case Dir::RIGHT :
            snake_body.at(0).first += step;
            break;

        case Dir::LEFT :
            snake_body.at(0).first -= step;
            break;

        case Dir::UP :
            snake_body.at(0).second += step;
            break;

        case Dir::DOWN :
            snake_body.at(0).second -= step;
            break;
        
        default:
            break;
        }

        return false;
    } 
    else 
    {
        return true;
    }
}

void Snake::ChangeDir(Dir dir) 
{
    dir_ = dir;
}

size_t Snake::GetScore() const 
{
    return score_;
}

void Snake::EatRabbit(std::pair<int, int> coord) 
{
    switch (dir_) 
    {
    case Dir:: UP:
        snake_body.emplace(snake_body.begin(), std::pair<int, int>(coord.first, coord.second + 1));
        break;
    
    case Dir:: DOWN:
        snake_body.emplace(snake_body.begin(), std::pair<int, int>(coord.first, coord.second - 1));
        break;

    case Dir:: RIGHT:
        snake_body.emplace(snake_body.begin(), std::pair<int, int>(coord.first + 1, coord.second));
        break;

    case Dir:: LEFT:
        snake_body.emplace(snake_body.begin(), std::pair<int, int>(coord.first - 1, coord.second));
        break;

    default:
        break;
    }
    ++score_;
}

Dir Snake::GetDir() const 
{
    return dir_;
}

Snake::~Snake() {};

Rabbit::Rabbit(const size_t length_x, const size_t length_y)
{
    for(int i = 0; i < rabbits_num; ++i) 
    {
        std::pair<int, int> tmp = Rabbit::RandCooord(length_x, length_y);
        map[tmp.first] = tmp.second;
    }
}

std::pair<int, int> Rabbit::RandCooord(const size_t length_x, const size_t length_y) 
{
    std::pair<int, int> rand_coord;
    
    std::random_device random_device; 
    std::mt19937 generator(random_device());

    std::uniform_int_distribution<> distribution_x(2, length_x - 2);
    std::uniform_int_distribution<> distribution_y(2, length_y - 2);

    int x = distribution_x(generator);
    int y = distribution_y(generator); 

    rand_coord.first  = x;
    rand_coord.second = y;
    
    return rand_coord;
}