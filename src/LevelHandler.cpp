#include "LevelHandler.h"
#include "stdexcept"
#include <fstream>
#include <sstream>
#include <string>

LevelHandler::LevelHandler()
{
    //ctor
}

void LevelHandler::loadLevel(Terrain& level, Terrain& layer, LocationalMap& loc_map, std::string file_name)
{
    int level_w = 0;
    int level_h = 0;
    int cell_size = 32;

    std::vector<int> level_vec;

    //Populate vector by csv file
    std::ifstream infile(file_name.c_str());
    std::string line;
    while (std::getline(infile, line))
    {
        std::stringstream ss(line);
        int i;
        while (ss >> i){
            level_vec.push_back(i);

            //Find level width by how many digits are in the first row
            if (level_h == 0){
                level_w += cell_size;
            }

            if (ss.peek() == ',' || ss.peek() == ' '){
                ss.ignore();
            }
        }
        //Find level height by how many rows there are
        level_h += cell_size;
    }


    if (!level.load("resources/hyptosis.png", sf::Vector2u(cell_size, cell_size), level_vec, level_w, level_h)){
        throw std::invalid_argument("Could not load the resource file");
    }

    loc_map.init(level_w, level_h, cell_size, level_vec);
}

void LevelHandler::loadLevel2(Terrain& level, Terrain& layer, LocationalMap& loc_map)
{

    const int background[] =
    {
        116, 116, 116, 116, 116, 116, 116, 116, 116, 116, 116, 116, 116, 116, 116, 116, 116, 116, 116, 116, 116, 116, 116, 116, 116,
        207, 207, 207, 207, 207, 207, 207, 207, 207, 207, 207, 207, 207, 207, 207, 207, 207, 207, 207, 207, 207, 207, 207, 207, 207,
        77, 78, 78, 78, 78, 78, 78, 78, 78, 78, 78, 78, 78, 78, 78, 78, 78, 78, 78, 78, 78, 78, 78, 78, 79,
        77, 78, 78, 78, 78, 78, 78, 78, 78, 78, 78, 78, 78, 78, 78, 78, 78, 78, 78, 78, 78, 78, 78, 78, 79,
        77, 78, 78, 78, 78, 695, 696, 696, 696, 696, 696, 696, 696, 696, 696, 696, 696, 696, 696, 697, 78, 78, 78, 78, 79,
        77, 78, 78, 78, 78, 21, 21, 22, 23, 21, 20, 20, 21, 20, 21, 21, 20, 21, 20, 21, 78, 78, 78, 78, 79,
        77, 78, 78, 78, 78, 21, 51, 52, 53, 20, 110, 111, 111, 112, 20, 21, 20, 21, 20, 21, 78, 78, 78, 78, 79,
        77, 78, 78, 78, 78, 21, 81, 82, 83, 20, 140, 141, 141, 142, 20, 21, 25, 26, 21, 21, 78, 78, 78, 78, 79,
        77, 78, 78, 78, 78, 21, 21, 20, 20, 21, 170, 171, 171, 172, 20, 21, 20, 21, 20, 21, 78, 78, 78, 78, 79,
        77, 78, 78, 78, 78, 21, 24, 25, 26, 20, 21, 24, 25, 20, 21, 20, 21, 20, 21, 21, 78, 78, 78, 78, 79,
        77, 78, 78, 78, 78, 21, 21, 20, 113, 114, 115, 21, 20, 20, 24, 25, 26, 21, 20, 21, 78, 78, 78, 78, 79,
        77, 78, 78, 78, 78, 21, 20, 20, 143, 144, 145, 21, 20, 20, 54, 55, 56, 21, 20, 21, 78, 78, 78, 78, 79,
        77, 78, 78, 78, 78, 21, 21, 21, 173, 174, 175, 25, 26, 20, 84, 85, 86, 20, 21, 21, 78, 78, 78, 78, 79,
        77, 78, 78, 78, 78, 21, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 21, 78, 78, 78, 78, 79,
        77, 78, 78, 78, 78, 755, 756, 756, 756, 756, 756, 756, 756, 756, 756, 756, 756, 756, 756, 757, 78, 78, 78, 78, 79,
        77, 78, 78, 78, 78, 78, 78, 78, 78, 78, 78, 78, 78, 78, 78, 78, 78, 78, 78, 78, 78, 78, 78, 78, 79,
        107, 108, 108, 108, 108, 108, 108, 108, 108, 108, 108, 108, 108, 108, 108, 108, 108, 108, 108, 108, 108, 108, 108, 108, 109,
        207, 207, 207, 207, 207, 207, 207, 207, 207, 207, 207, 207, 207, 207, 207, 207, 207, 207, 207, 207, 207, 207, 207, 207, 207,
        207, 207, 207, 207, 207, 207, 207, 207, 207, 207, 207, 207, 207, 207, 207, 207, 207, 207, 207, 207, 207, 207, 207, 207, 207,
        207, 207, 207, 207, 207, 207, 207, 207, 207, 207, 207, 207, 207, 207, 207, 207, 207, 207, 207, 207, 207, 207, 207, 207, 207,
    };

//    if (!level.load("resources/hyptosis.png", sf::Vector2u(cell_size, cell_size), background, level_w, level_h)){
//        throw std::invalid_argument("Could not load the resource file");
//    }

     const int accents[] =
    {
        298, 298, 298, 298, 298, 298, 298, 298, 298, 298, 298, 298, 298, 298, 298, 298, 298, 298, 298, 298, 298, 298, 298, 298, 298,
        298, 298, 298, 298, 298, 298, 298, 298, 298, 298, 298, 298, 298, 298, 298, 298, 298, 298, 298, 298, 298, 298, 298, 298, 298,
        298, 298, 298, 298, 298, 298, 298, 298, 298, 298, 298, 298, 298, 298, 298, 298, 298, 298, 298, 298, 298, 298, 298, 298, 298,
        298, 298, 298, 298, 298, 298, 298, 298, 298, 298, 298, 298, 298, 298, 298, 298, 298, 298, 298, 298, 298, 298, 298, 298, 298,
        298, 298, 298, 298, 298, 695, 696, 696, 696, 696, 696, 696, 696, 696, 696, 696, 696, 696, 696, 697, 298, 298, 298, 298, 298,
        298, 298, 298, 298, 298, 725, 298, 298, 298, 298, 298, 298, 298, 298, 298, 298, 298, 298, 298, 727, 298, 298, 298, 298, 298,
        298, 298, 298, 298, 298, 725, 298, 134, 298, 298, 298, 298, 298, 298, 298, 134, 298, 298, 298, 727, 298, 298, 298, 298, 298,
        298, 298, 298, 298, 298, 725, 298, 298, 298, 298, 298, 298, 298, 298, 298, 298, 298, 298, 298, 727, 298, 298, 298, 298, 298,
        298, 298, 298, 298, 298, 725, 298, 298, 298, 298, 298, 356, 298, 298, 298, 298, 298, 298, 298, 727, 298, 298, 298, 298, 298,
        298, 298, 298, 298, 298, 725, 298, 298, 298, 298, 298, 298, 298, 133, 298, 298, 298, 298, 298, 727, 298, 298, 298, 298, 298,
        298, 298, 298, 298, 298, 725, 132, 298, 298, 298, 298, 298, 298, 298, 298, 298, 298, 298, 298, 727, 298, 298, 298, 298, 298,
        298, 298, 298, 298, 298, 725, 298, 298, 298, 298, 298, 298, 298, 298, 298, 298, 298, 298, 298, 727, 298, 298, 298, 298, 298,
        298, 298, 298, 298, 298, 725, 298, 298, 298, 298, 298, 298, 357, 298, 298, 298, 298, 298, 298, 727, 298, 298, 298, 298, 298,
        298, 298, 298, 298, 298, 725, 298, 298, 134, 298, 298, 298, 298, 298, 298, 298, 132, 298, 298, 727, 298, 298, 298, 298, 298,
        298, 298, 298, 298, 298, 755, 756, 756, 756, 756, 756, 756, 756, 756, 756, 756, 756, 756, 756, 757, 298, 298, 298, 298, 298,
        298, 298, 298, 298, 298, 298, 298, 298, 298, 298, 298, 298, 298, 298, 298, 298, 298, 298, 298, 298, 298, 298, 298, 298, 298,
        298, 298, 298, 298, 298, 298, 298, 298, 298, 298, 298, 298, 298, 298, 298, 298, 298, 298, 298, 298, 298, 298, 298, 298, 298,
        105, 106, 163, 14, 15, 14, 16, 14, 16, 15, 17, 14, 15, 16, 14, 16, 15, 14, 16, 14, 14, 16, 15, 14, 15,
        197, 198, 199, 44, 198, 199, 44, 198, 199, 44, 198, 199, 198, 44, 199, 198, 199, 44, 198, 44, 199, 198, 199, 198, 199,
    };

//    if (!layer.load("resources/hyptosis.png", sf::Vector2u(cell_size, cell_size), accents, level_w, level_h)){
//        throw std::invalid_argument("Could not load the resource file");
//    }

    const int test_level[] =
    {
        66, 67, 67, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 67, 67, 68,
        78, 79, 80, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 78, 79, 80,
        78, 79, 80, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 78, 79, 80,
        78, 79, 80, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 78, 79, 80,
        78, 79, 80, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 78, 79, 80,
        78, 79, 80, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 78, 79, 80,
        78, 79, 80, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 78, 79, 80,
        78, 79, 80, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 78, 79, 80,
        78, 79, 80, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 78, 79, 80,
        78, 79, 80, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 78, 79, 80,
        78, 79, 80, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 78, 79, 80,
        78, 79, 80, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 78, 79, 80,
        78, 79, 80, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 78, 79, 80,
        78, 79, 80, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 78, 79, 80,
        78, 79, 80, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 78, 79, 80,
        78, 79, 80, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 78, 79, 80,
        90, 91, 92, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 90, 91, 92,
        102, 103, 104, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 102, 103, 104,
        114, 115, 115, 115, 115, 115, 115, 115, 115, 115, 115, 115, 115, 115, 115, 115, 115, 115, 115, 115, 115, 115, 115, 115, 116,
    };
    const int genlevel[] =
    {
        695, 67, 67, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 67, 67, 68,
        78, 79, 80, 695, 696, 696, 696, 696, 696, 696, 696, 696, 696, 696, 696, 696, 696, 696, 696, 696, 696, 697, 78, 79, 80,
        78, 79, 80, 725, 80, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 727, 78, 79, 80,
        78, 79, 80, 725, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 727, 78, 79, 80,
        78, 79, 80, 725, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 727, 78, 79, 80,
        78, 79, 80, 725, 103, 103, 103, 695, 696, 696, 696, 696, 696, 696, 696, 696, 697, 103, 103, 103, 103, 727, 78, 79, 80,
        78, 79, 80, 725, 103, 103, 103, 725, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 727, 78, 79, 80,
        78, 79, 80, 725, 103, 103, 103, 725, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 727, 78, 79, 80,
        78, 79, 80, 725, 103, 103, 103, 725, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 727, 78, 79, 80,
        78, 79, 80, 725, 103, 103, 103, 725, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 727, 78, 79, 80,
        78, 79, 80, 725, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 727, 78, 79, 80,
        78, 79, 80, 725, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 727, 78, 79, 80,
        78, 79, 80, 725, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 727, 78, 79, 80,
        78, 79, 80, 725, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 727, 78, 79, 80,
        78, 79, 80, 725, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 727, 78, 79, 80,
        78, 79, 80, 725, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 727, 78, 79, 80,
        90, 91, 92, 755, 756, 756, 756, 756, 756, 756, 756, 756, 756, 756, 756, 756, 756, 756, 756, 756, 756, 757, 90, 91, 92,
        102, 103, 104, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 102, 103, 104,
        114, 115, 115, 115, 115, 115, 115, 115, 115, 115, 115, 115, 115, 115, 115, 115, 115, 115, 115, 115, 115, 115, 115, 115, 116,
    };
}

LevelHandler::~LevelHandler()
{
    //dtor
}
