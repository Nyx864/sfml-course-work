#include "TextBox.h"

TextBox::TextBox(float width, float height,std::string FontPath)
	:Button("images\\textBox.png",height,width)
{
	font.loadFromFile(FontPath);
	text.setCharacterSize(height - 15);
	text.setFont(font);
	text.setFillColor(sf::Color::Color(51, 54, 56, 255));
	text.setOrigin(width / 2-10, height/2+1);
}

void TextBox::setPosition(const float& x, const float& y)
{
	this->text.setPosition(x, y);
	this->getSprite().setPosition(x, y);
}

void TextBox::updateText()
{
	this->text.setString(str);
}

void TextBox::setStr(const std::string& str)
{
	this->str = str;
	updateText();
}

void TextBox::addSym(const char& sym)
{
	if (str.size() < 15) {
		str += sym;
		updateText();
	}
}

void TextBox::setLocked(const bool& locked)
{
	this->locked = locked;
	if (!locked) 
	{
		this->setChosen();
	}
	else
	{
		this->setNotChosen();
		updateText();
	}
}

bool TextBox::isLocked()
{
	return this->locked;
}

void TextBox::draw(sf::RenderWindow& window)
{
	window.draw(this->getSprite());
	window.draw(this->text);
}

void TextBox::removeLast()
{
	if(str.size()>0)
	this->str.resize(str.size() - 1);
		updateText();
}

std::string TextBox::getStr()
{
	return this->str;
}



