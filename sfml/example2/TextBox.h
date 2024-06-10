#pragma once
#include "Button.h"
class TextBox : public Button
{
private:
	std::string str;
	sf::Text text;
	sf::Font font;
	bool locked{ true };
public:
	TextBox(float width, float height, std::string FontPath);

	void setPosition(const float& x,const float& y);

	void updateText();

	void setStr(const std::string& str);

	void addSym(const char& sym);

	void setLocked(const bool& locked);

	bool isLocked();

	void draw(sf::RenderWindow& window);

	void removeLast();

	std::string getStr();
};

