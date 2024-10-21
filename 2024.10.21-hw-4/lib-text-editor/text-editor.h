#ifndef TEXT_EDITOR_H
#define TEXT_EDITOR_H

#include<iostream>

class TextEditor
{
public:
	TextEditor();
	void addText(std::string text);
	size_t deleteText(size_t k);
	std::string cursorLeft(int k);
	std::string cursorRight(int k);
	friend std::ostream& operator<<(std::ostream& stream, TextEditor& text);

	long long length();
	size_t posistion();
	size_t find(std::string str);
	std::string substr(size_t pos, size_t count = 0);
private:
	std::string _text;
	size_t _position;
};

#endif