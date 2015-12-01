#include "LevelMenu.h"

LevelMenu::LevelMenu()
{
    //ctor
}

void LevelMenu::init(float width, float height)
{
	selected = 0;

	font.loadFromFile("resources/arial.ttf");

	std::vector<std::string> level_names;
    level_names.push_back("PracticeLevel");
	level_names.push_back("GavinsLevel");
	level_names.push_back("AlexsLevel");

    for (unsigned int i = 0; i < level_names.size(); i++){
        sf::Text text;
        text.setFont(font);
        text.setColor(sf::Color::White);
        text.setString(level_names[i]);
        text.setPosition(sf::Vector2f(width / 3, 50*(i+1) ));
        texts.push_back(text);
    }

	highlight.setSize(sf::Vector2f(300, 40));
  	highlight.setFillColor(sf::Color(150, 0, 35));
}

void LevelMenu::draw(sf::RenderWindow &window)
{
	window.clear(sf::Color::Black);

    highlight.setPosition(window.getSize().x/3 - 20, 50*(selected + 1));

	window.draw(highlight);

    for (unsigned int i = 0; i < texts.size(); i++){
        window.draw(texts[i]);
    }
}

std::string LevelMenu::navigate(sf::Event &event)
{
    if (event.key.code == sf::Keyboard::Up){
        moveUp();
    }

    else if (event.key.code == sf::Keyboard::Down){
        moveDown();
    }

    else if (event.key.code == sf::Keyboard::Return){
        return texts[selected].getString();
    }
    return "";
}

void LevelMenu::moveUp()
{
	if (selected > 0){
		selected--;
    }
}

void LevelMenu::moveDown()
{
	if (selected < texts.size() - 1){
		selected++;
    }
}

LevelMenu::~LevelMenu()
{
    //dtor
}
