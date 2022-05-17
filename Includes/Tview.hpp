#ifndef TVIEW
#define TVIEW

#include <string>
#include <list>
#include <map>
#include <vector>

#include "view.hpp"
#include "model.hpp"

void SignHandler(int n);

class Tview : public View
{
    public:
    Tview();
    size_t Draw() override;
    void DrawRabbits(const std::map<int, int>& rabbits) override;
    void CleanScreen() override;  
    void DrawSnake(const std::vector<std::pair<int, int>>& snake_body, Dir dir) override;
    void DrawStones(std::map<int, int>& stones, const size_t length_x, const size_t length_y);
    ~Tview();

    private:   
    void Move(int x, int y);
    void SetColor(int color);
    void DrawBoundary(const size_t length_x, const size_t length_y);
};


#endif // TVIEW