#include<iostream>
#include"TextEditor.h"

int main(int argc, char* argv[])
{
	TextEditor text;

	text.addText("hello, teacher!");
	std::cout << text << '\n';

	std::cout << text.cursorRight(9) << '\n';

	std::cout << text.deleteText(3) << '\n';
	std::cout << text << '\n';

	std::cout << text.deleteText(2) << '\n';
	std::cout << text << '\n';

	std::cout << text.cursorLeft(3) << '\n';

	std::cout << text.cursorRight(1) << '\n';

	std::cout << text.cursorLeft(0) << '\n';

	text.addText("ADS");
	std::cout << text << '\n';

	return 0;
}