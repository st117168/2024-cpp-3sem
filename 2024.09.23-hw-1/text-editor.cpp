#include"text-editor.h"

TextEditor::TextEditor() : _text(""), _position(0) {}

void TextEditor::addText(std::string text)
{
	_text.insert(_position, text);
}

int TextEditor::deleteText(int k)
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

std::string TextEditor::cursorLeft(int k)
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

std::string TextEditor::cursorRight(int k)
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

std::ostream& operator<<(std::ostream& stream, TextEditor& text)
{
	stream << text._text;
	return stream;
}
