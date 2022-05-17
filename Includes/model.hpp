#ifndef MODEL
#define MODEL

#include <iostream>
#include <vector>
#include <utility>
#include <map>

enum class Dir
{
    UP,
    DOWN,
    RIGHT,
    LEFT
};

class Snake 
{
    public:
    Snake(const size_t start_x, const size_t start_y, 
          const size_t length_x, const size_t length_y);
    bool IsAlive() const;
    bool Move();
    void ChangeDir(Dir dir);
    void CatchRabbit(std::map<int, int>& rabits, const size_t precision);
    void EatRabbit(std::pair<int, int> head_coord);
    std::vector<std::pair<int, int>> snake_body;
    size_t GetScore() const;
    Dir GetDir() const;
    ~Snake();

    private:
    Dir dir_;
    size_t start_x_, start_y_;
    size_t length_x_, length_y_;
    size_t score_;
};

class Rabbit
{
    public:
    Rabbit(const size_t length_x, const size_t length_y, const size_t rabbits_num);
    std::pair<int, int> RandCooord(const size_t length_x, const size_t length_y);
    size_t rabbits_num_;
    std::map<int, int> map;
    ~Rabbit();
};

#endif //MODEL