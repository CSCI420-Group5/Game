#ifndef LEVELMENU_H
#define LEVELMENU_H
#include <SFML/Graphics.hpp>


class LevelMenu
{
    public:
        LevelMenu();
        virtual ~LevelMenu();

        void init(float width, float height);

    	void draw(sf::RenderWindow &window);

		void moveUp();
		void moveDown();

        std::string navigate(sf::Event &event);

    protected:
    private:
		unsigned int selected;

		sf::Font font;
		std::vector<sf::Text> texts;
        sf::RectangleShape highlight;
};

#endif // LEVELMENU_H
