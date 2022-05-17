#include <iostream>
#include <string>

#include "view.hpp"
#include "Gview.hpp"
#include "Tview.hpp"

const std::string tview = "Tview";
const std::string gview  = "Gview";

View* View::obj = nullptr;
View* View::Get(const std::string& string) 
{
    if(!obj)
    {
        if(string == tview)
            obj = new Tview;
        else if(string == gview)
            obj = new Gview;
    }
    return obj;
}