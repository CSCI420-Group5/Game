#ifndef TERRAIN_H
#define TERRAIN_H
#include <SFML/Graphics.hpp>

class Terrain : public sf::Drawable, public sf::Transformable
{
public:
	Terrain();
	bool load(const std::string& tileset, sf::Vector2u tileSize, const int* tiles, unsigned int width, unsigned int height);
private:
	sf::VertexArray m_vertices;
    sf::Texture m_tileset;
    //bool accessable = true;
    //int accessible[]; //0 and 1 indicates whether a tile is accessable
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif // LEVELHANDLER_H
