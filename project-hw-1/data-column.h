#ifndef DATA_SET_COLUMN_H
#define DATA_SET_COLUMN_H

#include <string>
#include <vector>
#include <sstream>

struct Column {
    Column();
    ~Column();
    std::string type;
    std::string name;
    size_t size;
    void* value;
};

struct Names
{
    Names() {};
    Names(std::string& string);
    std::vector<std::string> names;
};

#endif