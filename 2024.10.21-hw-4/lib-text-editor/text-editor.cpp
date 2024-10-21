#include"text-editor.h"

TextEditor::TextEditor() : _text(""), _position(0) {}

void TextEditor::addText(std::string text)
{
	_text.insert(_position, text);
}

size_t TextEditor::deleteText(size_t k)
{
	if (_position == 0 || k <= 0)
	{
		return 0;
	}
	if (_position < k)
	{
		_text.erase(0, _position);
		size_t count = 0;
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

long long TextEditor::length()
{
	return _text.length();
}

size_t TextEditor::posistion()
{
	return _position;
}

size_t TextEditor::find(std::string str)
{
	return _text.find(str);
}

std::string TextEditor::substr(size_t pos, size_t count)
{
	if (count == 0)
	{
		return _text.substr(pos);
	}
	return _text.substr(pos, count);	
}
