#ifndef TEXT_EDITOR_H
#define TEXT_EDITOR_H

#include<iostream>

class TextEditor
{
public:
	TextEditor();
	void addText(std::string text);
	int deleteText(int k);
	std::string cursorLeft(int k);
	std::string cursorRight(int k);
	friend std::ostream& operator<<(std::ostream& stream, TextEditor& text);
private:
	std::string _text;
	int _position;
};

#endif