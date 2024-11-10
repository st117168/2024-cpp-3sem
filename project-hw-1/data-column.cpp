#include "data-column.h"

Column::Column()
{
    value = nullptr;
    size = 0;
    name = "";
}

Column::~Column()
{
    value = nullptr;
    size = 0;
    name = "";
}

Names::Names(std::string& string)
{   
    std::stringstream s(string);
    std::string name = "";
    while (getline(s, name, ','))
    {
        names.push_back(name);
    }
}
