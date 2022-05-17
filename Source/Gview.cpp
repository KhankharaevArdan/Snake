#include <cmath>

#include "Gview.hpp"
#include "model.hpp" 

const size_t precision = 1.9;
const size_t default_time = 1000000;
const size_t rabbits_num = 200;
const size_t Cell_size = 20;

const size_t boundary_x = 20;
const size_t boundary_y = 20;

const size_t screen_resolution_x = 1920;
const size_t screen_resolution_y = 1080;

const size_t x_blocks = (screen_resolution_x - boundary_x * 2) / Cell_size;
const size_t y_blocks = (screen_resolution_y - boundary_y * 2) / Cell_size;

Gview::Gview() 
{
    window_ = new sf::RenderWindow(sf::VideoMode(screen_resolution_x, screen_resolution_y), "");

    if(!texture_rabbit_.loadFromFile("Images/rabbit.png")) 
    {
        delete window_;
        exit(-1);
    }
    texture_rabbit_.setSmooth(true);

    if(!texture_head_left_.loadFromFile("Images/head_left.png")) 
    {
        delete window_;
        exit(-1);
    }
    texture_head_left_.setSmooth(true);

    if(!texture_head_right_.loadFromFile("Images/head_right.png")) 
    {
        delete window_;
        exit(-1);
    }
    texture_head_right_.setSmooth(true);

    if(!texture_head_up_.loadFromFile("Images/head_down.png")) 
    {
        delete window_;
        exit(-1);
    }
    texture_head_up_.setSmooth(true);

    if(!texture_head_down_.loadFromFile("Images/head_up.png")) 
    {
        delete window_;
        exit(-1);
    }
    texture_head_down_.setSmooth(true);
}

size_t Gview::Draw() 
{
    sf::Music music;
    if(!music.openFromFile("Sounds/sound.wav"))
    {
        delete window_;
        exit(-1);
    }
    music.play();
    //music.setLoop(true);

    Rabbit rabbits(x_blocks, y_blocks, rabbits_num);
    Snake snake(x_blocks/2, y_blocks/2, x_blocks, y_blocks);

    while(window_->isOpen()) 
    {
        if(snake.IsAlive()) 
        {
            DrawBoundary();
            sf::Event event;
            while (window_->pollEvent(event)) 
            {    
                switch (event.type) 
                {
                    case sf::Event::Closed :
                        window_->close();
                        break;

                    case sf::Event::KeyPressed :
                        switch (event.key.code) 
                        {
                        case sf::Keyboard::Escape : 
                            window_->close();
                            break;
                        
                        case sf::Keyboard::D :
                            snake.ChangeDir(Dir::RIGHT);
                            snake.Move();
                            break;
                        
                        case sf::Keyboard::W :
                            snake.ChangeDir(Dir::DOWN);
                            snake.Move();
                            break;

                        case sf::Keyboard::S :
                            snake.ChangeDir(Dir::UP);
                            snake.Move();
                            break;
                        
                        case sf::Keyboard::A :
                            snake.ChangeDir(Dir::LEFT);
                            snake.Move();
                            break;

                        default:
                            break;
                        }
                        break;
                    default:  
                        break;
                }
            }
            DrawRabbits(rabbits.map);
            DrawSnake(snake.snake_body, snake.GetDir());
            snake.Move();
            snake.CatchRabbit(rabbits.map, precision);
            window_->display();
            window_->clear();
            usleep(default_time / Cell_size);
        }
        else 
        {
            return snake.GetScore();;
        }
    }
    return snake.GetScore();
}

void Gview::DrawBoundary() 
{
    std::array<sf::RectangleShape, 2> boundary;
    boundary.at(0) = sf::RectangleShape(sf::Vector2f(window_->getSize().x, boundary_y)); 
    boundary.at(1) = sf::RectangleShape(sf::Vector2f(boundary_x, window_->getSize().y));

    boundary.at(0).setFillColor(sf::Color::White);
    boundary.at(1).setFillColor(sf::Color::White);
    
    boundary.at(0).setPosition(0, 0);
    boundary.at(1).setPosition(0, 0);
    DrawRectangles(boundary.at(0));
    DrawRectangles(boundary.at(1));

    boundary.at(0).setPosition(0, window_->getSize().y - boundary_y);
    boundary.at(1).setPosition(window_->getSize().x - boundary_x, 0);
    DrawRectangles(boundary.at(0));
    DrawRectangles(boundary.at(1));
}

void Gview::DrawRectangles(sf::RectangleShape& rectangle) 
{
    window_->draw(rectangle);
}

void Gview::DrawRabbits(const std::map<int, int>& rabbits) 
{

    sf::RectangleShape rectangle(sf::Vector2f(Cell_size, Cell_size));
    rectangle.setTexture(&texture_rabbit_);
    for(const auto el : rabbits) 
    {
        rectangle.setPosition(sf::Vector2f(el.first * Cell_size, el.second * Cell_size));
        window_->draw(rectangle);
    }
}

void Gview::DrawSnake(const std::vector<std::pair<int, int>>& snake_body, Dir dir) 
{
    sf::RectangleShape rectangle(sf::Vector2f(Cell_size, Cell_size));
    sf::CircleShape circle;
    circle.setRadius(Cell_size / 5);
    circle.setFillColor(sf::Color::Yellow);
    circle.setOutlineColor(sf::Color::Green);
    circle.setOutlineThickness(Cell_size / 15);
    size_t offset_x = Cell_size / 3;
    size_t offset_y = Cell_size / 3;

    switch (dir) 
    {
        case Dir::UP :
            rectangle.setTexture(&texture_head_up_);
            break;

        case Dir::DOWN :
            rectangle.setTexture(&texture_head_down_);
            break;

        case Dir::LEFT :
            rectangle.setTexture(&texture_head_left_);
            break;

        case Dir::RIGHT :
            rectangle.setTexture(&texture_head_right_);
            break;
        
        default:
            break;
    }
    rectangle.setPosition(sf::Vector2f(snake_body.at(0).first * Cell_size - offset_x, snake_body.at(0).second * Cell_size - offset_y));
    window_->draw(rectangle);
    for(int i = 1; i < snake_body.size(); ++i) 
    {
        circle.setPosition(sf::Vector2f(snake_body.at(i).first * Cell_size, snake_body.at(i).second * Cell_size));
        window_->draw(circle);
    }
}

Gview::~Gview() 
{
    delete window_;
}