#include <iostream>
#include <cstddef>  // size_t
#include <cstring>  // strlen, strcpy

struct String {
    public:
        String(const char *str = "");
        String(size_t n, char c);
        ~String();

        String(const String &other);
        String &operator=(const String &other);
        String operator[](size_t index) const;
        friend std::ostream& operator<<(std::ostream& stream, const String& text);

        void append(const String &other);

    private:
        size_t size;
        char *str;
};
