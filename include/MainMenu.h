#ifndef MAINMENU_H
#define MAINMENU_H
#include "SFML/Graphics.hpp"

class MainMenu
{
    public:
        MainMenu();
        virtual ~MainMenu();

        void init(float width, float height);

    	void draw(sf::RenderWindow &window);

		void moveUp();
		void moveDown();

        bool navigate(sf::RenderWindow &window, sf::Event &event);

    protected:
    private:
		int selected;

		sf::Font font;
		sf::Text text[3];
        sf::RectangleShape highlight;
};

#endif // MAINMENU_H
