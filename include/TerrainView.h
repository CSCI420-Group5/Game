#include <SFML/Graphics.hpp>
#include "Terrain.h"
#include "LocationalMap.h"

/*
 * Blend Terrain and Locational Map
*/

class TerrainView : public sf::Drawable, public sf::Transformable
{
public:
	TerrainView();
	
private:
	Terrain map;
    //bool accessable = true;
    int accessible[]; //0 and 1 indicates whether a tile is accessable
};