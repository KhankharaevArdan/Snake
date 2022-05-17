
#include <iostream>

#include "Gview.hpp"
#include "Tview.hpp"
#include "human.hpp"
#include "model.hpp"


int main(int argc, char** argv) {

    View* view = View::Get(argv[1]);   
    auto score = view->Draw();
    std::cout << "Your score is: " << score << std::endl;
    delete view;
    return 0;
}

