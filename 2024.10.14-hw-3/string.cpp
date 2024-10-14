#include "string.h"

String::String(const char * str) {
    size = strlen(str);
    this->str = new char[size+1];
    for(size_t i = 0; i <= size; ++i)
        this->str[i] = str[i];
}

String::String(size_t n, char c): size(n), str(0)
{
    this->str = new char[size + 1];
    for (int i = 0; i < size; this->str[i] = c, ++i);
    str[size] = '\0';
}

String::~String()
{
    delete[] str;
}

String::String(const String& other) :size(other.size)
{
    str = new char[size + 1];
    strcpy(str, other.str);
}

String &String::operator=(const String &other)
    {
        if (this != &other)
        {
            delete[] this->str;
            this->size = other.size;
            this->str = new char[this->size + 1];
            strcpy(this->str, other.str);
        }

        return *this;
    }

String String::operator[](size_t index) const
{
    if (this->size == index)
    {
        String curr;
        return curr;
    }
    if (this->size < strlen(this->str))
    {
        String curr(index - this->size, 'a');
        for (int i = 0; i < curr.size; ++i)
        {
            curr.str[i] = this->str[this->size + i];
        }
        return curr;
    }
    String curr(this->str);
    curr.size = index;
    return curr;
}

std::ostream& operator<<(std::ostream& stream, const String& text)
{
    for (int i = 0; i < text.size; i++)
    {
        stream << text.str[i];
    }
    return stream;
}

void String::append(const String &other)
{
    size += other.size;
    char* new_str = new char[size + 1];
    strcpy(new_str, str);
    strcat(new_str, other.str);
    delete[] str;
    str = new_str;
}