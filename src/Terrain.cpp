#include "Terrain.h"

    Terrain::Terrain(){
        //
    }


    bool Terrain::load(const std::string& tileset, sf::Vector2u tileSize, std::vector<int>& tiles, unsigned int width, unsigned int height)
    {
        //Find the number of tiles needed for the screen size
        unsigned int num_tiles_w = width/tileSize.x;
        if (num_tiles_w*tileSize.x < width){
            num_tiles_w++;
        }
        unsigned int num_tiles_h = height/tileSize.y;
        if (num_tiles_h*tileSize.y < height){
            num_tiles_h++;
        }

        // load the tileset texture
        if (!m_tileset.loadFromFile(tileset))
            return false;

        // resize the vertex array to fit the level size
        m_vertices.setPrimitiveType(sf::Quads);
        m_vertices.resize(num_tiles_w * num_tiles_h * 4);

        // populate the vertex array, with one quad per tile
        for (unsigned int i = 0; i < num_tiles_w; ++i)
            for (unsigned int j = 0; j < num_tiles_h; ++j)
            {
                // get the current tile number
                int tileNumber = tiles[i + j * num_tiles_w];

                // find its position in the tileset texture
                int tu = tileNumber % (m_tileset.getSize().x / tileSize.x);
                int tv = tileNumber / (m_tileset.getSize().x / tileSize.x);

                // get a pointer to the current tile's quad
                sf::Vertex* quad = &m_vertices[(i + j * num_tiles_w) * 4];

                // define its 4 corners
                quad[0].position = sf::Vector2f(i * tileSize.x, j * tileSize.y);
                quad[1].position = sf::Vector2f((i + 1) * tileSize.x, j * tileSize.y);
                quad[2].position = sf::Vector2f((i + 1) * tileSize.x, (j + 1) * tileSize.y);
                quad[3].position = sf::Vector2f(i * tileSize.x, (j + 1) * tileSize.y);

                if (tileNumber != -1){
                    // define its 4 texture coordinates
                    quad[0].texCoords = sf::Vector2f(tu * tileSize.x, tv * tileSize.y);
                    quad[1].texCoords = sf::Vector2f((tu + 1) * tileSize.x, tv * tileSize.y);
                    quad[2].texCoords = sf::Vector2f((tu + 1) * tileSize.x, (tv + 1) * tileSize.y);
                    quad[3].texCoords = sf::Vector2f(tu * tileSize.x, (tv + 1) * tileSize.y);
                }
                else{
                    quad[0].color.a = 0;
                    quad[1].color.a = 0;
                    quad[2].color.a = 0;
                    quad[3].color.a = 0;
                }
            }

        return true;
    }



    void Terrain::draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        // apply the transform
        states.transform *= getTransform();

        // apply the tileset texture
        states.texture = &m_tileset;

        // draw the vertex array
        target.draw(m_vertices, states);
    }


