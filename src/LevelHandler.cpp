#include "LevelHandler.h"
#include "Projectile.h"
#include "stdexcept"
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <cmath>

LevelHandler::LevelHandler()
{
    //ctor
}

bool sortCollidablesByXPos (const Collidable* actor1, const Collidable* actor2)
{
    return (actor1->getPos().x < actor2->getPos().x);
}

bool sortVectorsByXPos (const sf::Vector2f vec1, const sf::Vector2f vec2)
{
    return (vec1.x < vec2.x);
}

void LevelHandler::loadLevel(Terrain& level, Terrain& layer, LocationalMap&
loc_map, std::string level_name, Profile& profile, int &num_bad_guys)
{
    int level_w = 0;
    int level_h = 0;
    int cell_size = 32;

    std::string file1_name = "resources/" + level_name + "_Tile Layer 1.csv";
    std::string file2_name = "resources/" + level_name + "_Tile Layer 2.csv";
    std::string file3_name = "resources/" + level_name + "_Tile Layer 3.csv";

    //For the level's first layer
    std::vector<int> level_vec;

    //Populate vector by csv file
    std::ifstream infile(file1_name.c_str());
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


    //For the level's second layer
    std::vector<int> layer_vec;

    //Populate vector by csv file
    std::ifstream infile2(file2_name.c_str());
    std::string line2;
    while (std::getline(infile2, line2))
    {
        std::stringstream ss2(line2);
        int i2;
        while (ss2 >> i2){
            layer_vec.push_back(i2);

            if (ss2.peek() == ',' || ss2.peek() == ' '){
                ss2.ignore();
            }
        }
    }
    if (!layer.load("resources/hyptosis.png", sf::Vector2u(cell_size, cell_size), layer_vec, level_w, level_h)){
        throw std::invalid_argument("Could not load the resource file");
    }


    //For the level's third layer (which is actors and checkpoints)
    int ai_x = 0;
    int ai_y = 0;

    //Populate checkpoints and actors by csv file
    std::ifstream infile3(file3_name.c_str());
    std::string line3;
    while (std::getline(infile3, line3))
    {
        std::stringstream ss3(line3);
        int i3;
        while (ss3 >> i3){

            // This will tell what the object of interest is:
            if (i3 == 329){ // Grey robot
                Wrestler* ai_sumo = new Wrestler();
                ai_sumo->init(30, 30, ai_x, ai_y);
                ai_sumo->setIsHuman(false);
                ai_sumo->setIsWrestler(true);
                ai_sumo->setHasProjectile(false);
                ai_sumo->setCharacter("GreyRobot");
                future_actors.push_back(ai_sumo);
                num_bad_guys++;
            }
            if (i3 == 389){ // Blue robot
                Wrestler* ai_sumo = new Wrestler();
                ai_sumo->init(30, 30, ai_x, ai_y);
                ai_sumo->setIsHuman(false);
                ai_sumo->setIsWrestler(true);
                ai_sumo->setHasProjectile(false);
                ai_sumo->setCharacter("BlueRobot");
                future_actors.push_back(ai_sumo);
                num_bad_guys++;
            }
            if (i3 == 419){ // Green robot
                Wrestler* ai_sumo = new Wrestler();
                ai_sumo->init(30, 30, ai_x, ai_y);
                ai_sumo->setIsHuman(false);
                ai_sumo->setIsWrestler(true);
                ai_sumo->setHasProjectile(false);
                ai_sumo->setCharacter("GreenRobot");
                future_actors.push_back(ai_sumo);
                num_bad_guys++;
            }
            if (i3 == 449){ // Red robot
                Wrestler* ai_sumo = new Wrestler();
                ai_sumo->init(30, 30, ai_x, ai_y);
                ai_sumo->setIsHuman(false);
                ai_sumo->setIsWrestler(true);
                ai_sumo->setHasProjectile(false);
                ai_sumo->setCharacter("RedRobot");
                future_actors.push_back(ai_sumo);
                num_bad_guys++;
            }
            if (i3 == 359){ // Takeshi
                Wrestler* ai_sumo = new Wrestler();
                ai_sumo->init(30, 30, ai_x, ai_y);
                ai_sumo->setIsHuman(false);
                ai_sumo->setIsWrestler(true);
                ai_sumo->setHasProjectile(false);
                ai_sumo->setCharacter("Takeshi");
                future_actors.push_back(ai_sumo);
                num_bad_guys++;
            }
            if (i3 == 479){ // Projectile
                Projectile* proj = new Projectile();
                proj->init(30, 30, ai_x, ai_y);
                proj->setIsWrestler(false);
                proj->setHasProjectile(true);
                proj->setName("Cannon");
                future_actors.push_back(proj);
            }
            if (i3 == 509){ // Checkpoint flag
                checkpoints.push_back(sf::Vector2f(ai_x, ai_y));
            }

            if (ss3.peek() == ',' || ss3.peek() == ' '){
                ss3.ignore();
            }
            ai_x += cell_size;
        }
        ai_y += cell_size;
        ai_x = 0;
    }
    //Sort the list of Future actors and checkpoints based on their x position
    std::sort(future_actors.begin(), future_actors.end(), sortCollidablesByXPos);
    std::sort(checkpoints.begin(), checkpoints.end(), sortVectorsByXPos);

    loc_map.init(level_w, level_h, cell_size, level_vec, layer_vec);
    profile.setLevel(level_name);
    profile.setCheckpoint(0);
}

void LevelHandler::spawnActors(std::vector<Collidable*> &actors, int scrn_right_side)
{
    while ((future_actors.size() > 0) && (future_actors[0]->getPos().x < scrn_right_side + 50)){
        actors.push_back(future_actors[0]);
        future_actors.erase(future_actors.begin());
    }
}

void LevelHandler::checkCheckpoints(Collidable* player, Profile& profile)
{
    if (checkpoints.size() - 1 > profile.getCheckpoint()){
        sf::Vector2f next_cp = checkpoints[profile.getCheckpoint()+ 1];
        sf::Vector2f plyr = player->getPos();

        if (std::sqrt((plyr.x - next_cp.x)*(plyr.x - next_cp.x) + (plyr.y - next_cp.y)*(plyr.y - next_cp.y)) < 500){
            profile.setCheckpoint(profile.getCheckpoint()+ 1);
        }
    }
}

sf::Vector2f LevelHandler::getCheckpoint(Profile& profile)
{
    return checkpoints[profile.getCheckpoint()];
}

//void LevelHandler::loadLevel2(Terrain& level, Terrain& layer, LocationalMap& loc_map)
//{
//
//    const int background[] =
//    {
//        116, 116, 116, 116, 116, 116, 116, 116, 116, 116, 116, 116, 116, 116, 116, 116, 116, 116, 116, 116, 116, 116, 116, 116, 116,
//        207, 207, 207, 207, 207, 207, 207, 207, 207, 207, 207, 207, 207, 207, 207, 207, 207, 207, 207, 207, 207, 207, 207, 207, 207,
//        77, 78, 78, 78, 78, 78, 78, 78, 78, 78, 78, 78, 78, 78, 78, 78, 78, 78, 78, 78, 78, 78, 78, 78, 79,
//        77, 78, 78, 78, 78, 78, 78, 78, 78, 78, 78, 78, 78, 78, 78, 78, 78, 78, 78, 78, 78, 78, 78, 78, 79,
//        77, 78, 78, 78, 78, 695, 696, 696, 696, 696, 696, 696, 696, 696, 696, 696, 696, 696, 696, 697, 78, 78, 78, 78, 79,
//        77, 78, 78, 78, 78, 21, 21, 22, 23, 21, 20, 20, 21, 20, 21, 21, 20, 21, 20, 21, 78, 78, 78, 78, 79,
//        77, 78, 78, 78, 78, 21, 51, 52, 53, 20, 110, 111, 111, 112, 20, 21, 20, 21, 20, 21, 78, 78, 78, 78, 79,
//        77, 78, 78, 78, 78, 21, 81, 82, 83, 20, 140, 141, 141, 142, 20, 21, 25, 26, 21, 21, 78, 78, 78, 78, 79,
//        77, 78, 78, 78, 78, 21, 21, 20, 20, 21, 170, 171, 171, 172, 20, 21, 20, 21, 20, 21, 78, 78, 78, 78, 79,
//        77, 78, 78, 78, 78, 21, 24, 25, 26, 20, 21, 24, 25, 20, 21, 20, 21, 20, 21, 21, 78, 78, 78, 78, 79,
//        77, 78, 78, 78, 78, 21, 21, 20, 113, 114, 115, 21, 20, 20, 24, 25, 26, 21, 20, 21, 78, 78, 78, 78, 79,
//        77, 78, 78, 78, 78, 21, 20, 20, 143, 144, 145, 21, 20, 20, 54, 55, 56, 21, 20, 21, 78, 78, 78, 78, 79,
//        77, 78, 78, 78, 78, 21, 21, 21, 173, 174, 175, 25, 26, 20, 84, 85, 86, 20, 21, 21, 78, 78, 78, 78, 79,
//        77, 78, 78, 78, 78, 21, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 21, 78, 78, 78, 78, 79,
//        77, 78, 78, 78, 78, 755, 756, 756, 756, 756, 756, 756, 756, 756, 756, 756, 756, 756, 756, 757, 78, 78, 78, 78, 79,
//        77, 78, 78, 78, 78, 78, 78, 78, 78, 78, 78, 78, 78, 78, 78, 78, 78, 78, 78, 78, 78, 78, 78, 78, 79,
//        107, 108, 108, 108, 108, 108, 108, 108, 108, 108, 108, 108, 108, 108, 108, 108, 108, 108, 108, 108, 108, 108, 108, 108, 109,
//        207, 207, 207, 207, 207, 207, 207, 207, 207, 207, 207, 207, 207, 207, 207, 207, 207, 207, 207, 207, 207, 207, 207, 207, 207,
//        207, 207, 207, 207, 207, 207, 207, 207, 207, 207, 207, 207, 207, 207, 207, 207, 207, 207, 207, 207, 207, 207, 207, 207, 207,
//        207, 207, 207, 207, 207, 207, 207, 207, 207, 207, 207, 207, 207, 207, 207, 207, 207, 207, 207, 207, 207, 207, 207, 207, 207,
//    };
//
////    if (!level.load("resources/hyptosis.png", sf::Vector2u(cell_size, cell_size), background, level_w, level_h)){
////        throw std::invalid_argument("Could not load the resource file");
////    }
//
//     const int accents[] =
//    {
//        298, 298, 298, 298, 298, 298, 298, 298, 298, 298, 298, 298, 298, 298, 298, 298, 298, 298, 298, 298, 298, 298, 298, 298, 298,
//        298, 298, 298, 298, 298, 298, 298, 298, 298, 298, 298, 298, 298, 298, 298, 298, 298, 298, 298, 298, 298, 298, 298, 298, 298,
//        298, 298, 298, 298, 298, 298, 298, 298, 298, 298, 298, 298, 298, 298, 298, 298, 298, 298, 298, 298, 298, 298, 298, 298, 298,
//        298, 298, 298, 298, 298, 298, 298, 298, 298, 298, 298, 298, 298, 298, 298, 298, 298, 298, 298, 298, 298, 298, 298, 298, 298,
//        298, 298, 298, 298, 298, 695, 696, 696, 696, 696, 696, 696, 696, 696, 696, 696, 696, 696, 696, 697, 298, 298, 298, 298, 298,
//        298, 298, 298, 298, 298, 725, 298, 298, 298, 298, 298, 298, 298, 298, 298, 298, 298, 298, 298, 727, 298, 298, 298, 298, 298,
//        298, 298, 298, 298, 298, 725, 298, 134, 298, 298, 298, 298, 298, 298, 298, 134, 298, 298, 298, 727, 298, 298, 298, 298, 298,
//        298, 298, 298, 298, 298, 725, 298, 298, 298, 298, 298, 298, 298, 298, 298, 298, 298, 298, 298, 727, 298, 298, 298, 298, 298,
//        298, 298, 298, 298, 298, 725, 298, 298, 298, 298, 298, 356, 298, 298, 298, 298, 298, 298, 298, 727, 298, 298, 298, 298, 298,
//        298, 298, 298, 298, 298, 725, 298, 298, 298, 298, 298, 298, 298, 133, 298, 298, 298, 298, 298, 727, 298, 298, 298, 298, 298,
//        298, 298, 298, 298, 298, 725, 132, 298, 298, 298, 298, 298, 298, 298, 298, 298, 298, 298, 298, 727, 298, 298, 298, 298, 298,
//        298, 298, 298, 298, 298, 725, 298, 298, 298, 298, 298, 298, 298, 298, 298, 298, 298, 298, 298, 727, 298, 298, 298, 298, 298,
//        298, 298, 298, 298, 298, 725, 298, 298, 298, 298, 298, 298, 357, 298, 298, 298, 298, 298, 298, 727, 298, 298, 298, 298, 298,
//        298, 298, 298, 298, 298, 725, 298, 298, 134, 298, 298, 298, 298, 298, 298, 298, 132, 298, 298, 727, 298, 298, 298, 298, 298,
//        298, 298, 298, 298, 298, 755, 756, 756, 756, 756, 756, 756, 756, 756, 756, 756, 756, 756, 756, 757, 298, 298, 298, 298, 298,
//        298, 298, 298, 298, 298, 298, 298, 298, 298, 298, 298, 298, 298, 298, 298, 298, 298, 298, 298, 298, 298, 298, 298, 298, 298,
//        298, 298, 298, 298, 298, 298, 298, 298, 298, 298, 298, 298, 298, 298, 298, 298, 298, 298, 298, 298, 298, 298, 298, 298, 298,
//        105, 106, 163, 14, 15, 14, 16, 14, 16, 15, 17, 14, 15, 16, 14, 16, 15, 14, 16, 14, 14, 16, 15, 14, 15,
//        197, 198, 199, 44, 198, 199, 44, 198, 199, 44, 198, 199, 198, 44, 199, 198, 199, 44, 198, 44, 199, 198, 199, 198, 199,
//    };
//
////    if (!layer.load("resources/hyptosis.png", sf::Vector2u(cell_size, cell_size), accents, level_w, level_h)){
////        throw std::invalid_argument("Could not load the resource file");
////    }
//
//    const int test_level[] =
//    {
//        66, 67, 67, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 67, 67, 68,
//        78, 79, 80, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 78, 79, 80,
//        78, 79, 80, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 78, 79, 80,
//        78, 79, 80, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 78, 79, 80,
//        78, 79, 80, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 78, 79, 80,
//        78, 79, 80, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 78, 79, 80,
//        78, 79, 80, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 78, 79, 80,
//        78, 79, 80, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 78, 79, 80,
//        78, 79, 80, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 78, 79, 80,
//        78, 79, 80, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 78, 79, 80,
//        78, 79, 80, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 78, 79, 80,
//        78, 79, 80, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 78, 79, 80,
//        78, 79, 80, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 78, 79, 80,
//        78, 79, 80, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 78, 79, 80,
//        78, 79, 80, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 78, 79, 80,
//        78, 79, 80, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 78, 79, 80,
//        90, 91, 92, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 90, 91, 92,
//        102, 103, 104, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 102, 103, 104,
//        114, 115, 115, 115, 115, 115, 115, 115, 115, 115, 115, 115, 115, 115, 115, 115, 115, 115, 115, 115, 115, 115, 115, 115, 116,
//    };
//    const int genlevel[] =
//    {
//        695, 67, 67, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 67, 67, 68,
//        78, 79, 80, 695, 696, 696, 696, 696, 696, 696, 696, 696, 696, 696, 696, 696, 696, 696, 696, 696, 696, 697, 78, 79, 80,
//        78, 79, 80, 725, 80, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 727, 78, 79, 80,
//        78, 79, 80, 725, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 727, 78, 79, 80,
//        78, 79, 80, 725, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 727, 78, 79, 80,
//        78, 79, 80, 725, 103, 103, 103, 695, 696, 696, 696, 696, 696, 696, 696, 696, 697, 103, 103, 103, 103, 727, 78, 79, 80,
//        78, 79, 80, 725, 103, 103, 103, 725, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 727, 78, 79, 80,
//        78, 79, 80, 725, 103, 103, 103, 725, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 727, 78, 79, 80,
//        78, 79, 80, 725, 103, 103, 103, 725, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 727, 78, 79, 80,
//        78, 79, 80, 725, 103, 103, 103, 725, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 727, 78, 79, 80,
//        78, 79, 80, 725, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 727, 78, 79, 80,
//        78, 79, 80, 725, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 727, 78, 79, 80,
//        78, 79, 80, 725, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 727, 78, 79, 80,
//        78, 79, 80, 725, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 727, 78, 79, 80,
//        78, 79, 80, 725, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 727, 78, 79, 80,
//        78, 79, 80, 725, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 727, 78, 79, 80,
//        90, 91, 92, 755, 756, 756, 756, 756, 756, 756, 756, 756, 756, 756, 756, 756, 756, 756, 756, 756, 756, 757, 90, 91, 92,
//        102, 103, 104, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 102, 103, 104,
//        114, 115, 115, 115, 115, 115, 115, 115, 115, 115, 115, 115, 115, 115, 115, 115, 115, 115, 115, 115, 115, 115, 115, 115, 116,
//    };
//}

LevelHandler::~LevelHandler()
{
    //dtor
}
