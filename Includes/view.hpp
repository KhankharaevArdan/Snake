#ifndef VIEW
#define VIEW

#include <string>
#include <list>
#include <map>
#include <vector>
#include <set>
#include "model.hpp"

class View
{
    public:
    static View* Get(const std::string& string);
    virtual size_t Draw() = 0;
    virtual void DrawRabbits(const std::map<int, int>& rabits) = 0;
    virtual void DrawSnake(const std::vector<std::pair<int, int>>& snake_body, Dir dir) = 0;
    virtual void CatchRabbit(std::map<int, int>& rabits, Snake& snake) = 0;
    virtual void CleanScreen() = 0;
    virtual ~View() {}
    private:

    static View* obj;

};

#endif //VIEW
