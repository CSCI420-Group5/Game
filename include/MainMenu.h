#ifndef MAINMENU_H
#define MAINMENU_H
#include "SFML/Graphics.hpp"

class MainMenu
{
    public:
        MainMenu(float width, float height);
        virtual ~MainMenu();

        void init();

    	void draw(sf::RenderWindow &window);

		void moveUp();
		void moveDown();

        void navigate(sf::RenderWindow &window);

        int getStatus();

		int selected;
        int inMenu;

		sf::Font font;
		sf::Text text[3];
        sf::RectangleShape highlight;

    protected:
    private:

    	

};

#endif // MAINMENU_H