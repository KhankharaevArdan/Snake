#include <iostream>
#include <unistd.h>
#include "SFML/Graphics.hpp"
#include <SFML/Audio.hpp>

#include "view.hpp"
#include "model.hpp"

class Gview : public View 
{
    public:
    Gview();
    size_t Draw() override;
    void DrawRabbits(const std::map<int, int>& rabbits) override;
    void CleanScreen() override {}
    void DrawSnake(const std::vector<std::pair<int, int>>& snake_body, Dir dir) override;
    ~Gview();
    private:
    void DrawBoundary();
    void DrawRectangles(sf::RectangleShape& rectangle);
    sf::RenderWindow* window_;
    sf::Texture texture_rabbit_;
    sf::Texture texture_head_left_;
    sf::Texture texture_head_right_;
    sf::Texture texture_head_up_;
    sf::Texture texture_head_down_;
};