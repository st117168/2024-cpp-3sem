#include <iostream>

class TextEditor
{
public:
	TextEditor() : _text(""), _position(0) {}
	void addText(std::string text)
	{
		_text.insert(_position, text);
	}
	int deleteText(int k)
	{
		if (_position == 0 || k <= 0)
		{
			return 0;
		}
		if (_position < k)
		{
			_text.erase(0, _position);
			int count = 0;
			count = _position;
			_position = 0;
			return count;
		}
		_text.erase(_position - k, k);
		_position -= k;
		return k;
	}
	std::string cursorLeft(int k)
	{
		if (_position == 0 || k < 0)
		{
			return "";
		}
		if (_position < k)
		{
			_position = 0;
			return "";
		}
		_position -= k;
		return _text.substr(0, _position);
	}
	std::string cursorRight(int k)
	{
		if ((_position == _text.length() - 1) || k < 0)
		{
			return "";
		}
		if ((_text.length() - _position) < k)
		{
			_position = _text.length();
			return "";
		}
		_position += k;
		return _text.substr(_position, _text.length() - _position);
	}
	friend std::ostream& operator<<(std::ostream& stream, TextEditor& text)
	{
		stream << text._text;
		return stream;
	}
private:
	std::string _text;
	int _position;
};

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