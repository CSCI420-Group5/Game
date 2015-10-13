#ifndef FUMIOVIEW_H
#define FUMIOVIEW_H


class FumioView
{
    public:
        FumioView();
        virtual ~FumioView();

        void init(sf::Texture sprite_sht);
        void init();
    protected:
    private:
        sf::Sprite sprite;
        sf::RectangleShape hitbox:
};

#endif // FUMIOVIEW_H
