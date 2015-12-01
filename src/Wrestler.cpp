#include "Wrestler.h"
#include "SFML/Graphics.hpp"
#include <cmath>

Wrestler::Wrestler()
{
    //ctor
}

void Wrestler::init(int hit_height, int hit_width, int x, int y)
{
    //Maybe should be a more unique id
    id = reinterpret_cast<long int>(&id);

    current_state = NORMAL;
    sprite_state = STAND_RIGHT;
    first_step = false;
    frozen_frames = 0;

    id_of_grabbed = 0;

    height = hit_height;
    width = hit_width;

    position.x = x;
    position.y = y;

    velocity.x = 0;
    velocity.y = 0;

    stamina = 100;
}

void Wrestler::reset(std::vector<Collidable*> &actors, sf::Vector2f checkpoint)
{
    // should only ever be human
    if (isHuman()) {
        current_state = NORMAL;
        sprite_state = STAND_RIGHT;
        frozen_frames = 0;

        id_of_grabbed = 0;

        off_edge = true;

        // make sure we don't just reset right next to the edge
//        if (velocity.x > 0)
//            position.x -= 100;
//        else if (velocity.x < 0)
//            position.x += 100;
//
//        if (velocity.y > 0)
//            position.y -= 100;
//        else if (velocity.y < 0)
//            position.y += 100;
//
//        sf::RectangleShape human_box(sf::Vector2f(width, height));
//        human_box.setPosition(position);
//        sf::FloatRect human_bounds = human_box.getGlobalBounds();
//        // make sure we didn't cause a collision with our reset
//        for (unsigned int i=0; i<actors.size(); i++) {
//            if (id == actors[i]->getID()) {
//                continue;
//            }
//            else {
//                sf::RectangleShape
//                actor_box(sf::Vector2f(actors[i]->getWidth(),actors[i]->getHeight()));
//                actor_box.setPosition(actors[i]->getPos());
//                sf::FloatRect actor_bounds = actor_box.getGlobalBounds();
//
//                while (human_bounds.intersects(actor_bounds)) {
//                    human_box.setPosition(human_box.getPosition().x+10,human_box.getPosition().y);
//                    human_bounds = human_box.getGlobalBounds();
//                }
//            }
//        }
//        position.x = human_box.getPosition().x;
        position = checkpoint;

        velocity.x = 0;
        velocity.y = 0;

        stamina = 100;
    }
}

void Wrestler::useGrab(Wrestler* grabee, int level_w, int level_h)
{
    current_state = GRABBING;
    grabee->setCurrentState(Wrestler::GRABBED);

    //Stop actors' movement
    grabee->setVelocity(0, 0, level_w, level_h);
    setVelocity(0, 0, level_w, level_h);

    id_of_grabbed = grabee->getID();

    resetFrozenFrames();
    grabee->resetFrozenFrames();

    stamina -= 25;
}

void Wrestler::useThrow(Wrestler* throwee, int level_w, int level_h)
{
    int str = strength;

    // up / right
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)
        && sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
        throwee->setVelocity(str/std::sqrt(2), -str/std::sqrt(2), level_w,
        level_h);
    }

    // down / right
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)
        && sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
        throwee->setVelocity(str/std::sqrt(2), str/std::sqrt(2), level_w,
        level_h);
    }

    // down / left
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)
        && sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
        throwee->setVelocity(-str/std::sqrt(2), str/std::sqrt(2), level_w,
        level_h);
    }

    // up / left
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)
        && sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
        throwee->setVelocity(-str/std::sqrt(2), -str/std::sqrt(2), level_w,
        level_h);
    }

    // up
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
        throwee->setVelocity(0, -str, level_w, level_h);
    }

    // down
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
        throwee->setVelocity(0, str, level_w, level_h);
    }

    // left
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
        throwee->setVelocity(-str, 0, level_w, level_h);
    }

    // right
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
        throwee->setVelocity(str, 0, level_w, level_h);
    }

    current_state = NOGRAB;
    resetFrozenFrames();
    throwee->setCurrentState(Wrestler::THROWN);
    throwee->resetFrozenFrames();
}

void Wrestler::increaseStamina()
{
    if (stamina < 100)
    {
        stamina += 1;
    }
}

void Wrestler::depleteStamina(int loss)
{
    stamina -= loss;
    if (stamina < 0){
        stamina = 0;
    }
}

void Wrestler::useDash()
{
    int spd = speed;

    if (stamina > 49)
    {
         // up / right
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)
            && sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            {
                velocity.x = spd/std::sqrt(2);
                velocity.y = -spd/std::sqrt(2);
                setCurSpriteState(DASH_RIGHT);
            }

        // down / right
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)
            && sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            {
                velocity.x = spd/std::sqrt(2);
                velocity.y = spd/std::sqrt(2);
                setCurSpriteState(DASH_RIGHT);
            }

        // down / left
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)
            && sf::Keyboard::isKeyPressed(sf::Keyboard::A))
            {
                velocity.x = -spd/std::sqrt(2);
                velocity.y = spd/std::sqrt(2);
                setCurSpriteState(DASH_LEFT);
            }

        // up / left
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)
            && sf::Keyboard::isKeyPressed(sf::Keyboard::A))
            {
                velocity.x = -spd/std::sqrt(2);
                velocity.y = -spd/std::sqrt(2);
                setCurSpriteState(DASH_LEFT);
            }

            // up
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
            {
                velocity.x = 0;
                velocity.y = -spd;
                setCurSpriteState(DASH_UP);
            }

            // down
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
            {
                velocity.x = 0;
                velocity.y = spd;
                setCurSpriteState(DASH_DOWN);
            }

            // left
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
            {
                velocity.x = -spd;
                velocity.y = 0;
                setCurSpriteState(DASH_LEFT);
            }

            // right
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            {
                velocity.x = spd;
                velocity.y = 0;
                setCurSpriteState(DASH_RIGHT);
            }

        stamina -= 50;
    }

    current_state = DASH;
    resetFrozenFrames();
}

int Wrestler::getStrength()
{
    return strength;
}
int Wrestler::getStamina()
{
    return stamina;
}
float Wrestler::getAcceleration()
{
    return acceleration;
}

void Wrestler::setStats(float spd, int str, float wgt, int stm)
{
    speed = spd;
    strength = str;
    weight = wgt;
    stamina = stm;
    acceleration = float(str) / float(wgt);
}

bool Wrestler::isHuman()
{
    return is_human;
}

void Wrestler::setIsHuman(bool val)
{
    is_human = val;
}

void Wrestler::setUpState(bool val)
{
    first_up_state = val;
}

void Wrestler::setDownState(bool val)
{
    first_down_state = val;
}

bool Wrestler::getUpState()
{
    return first_up_state;
}

bool Wrestler::getDownState()
{
    return first_down_state;
}

void Wrestler::setStep(bool val)
{
    first_step = val;
}

bool Wrestler::getStep()
{
    return first_step;
}

Wrestler::State Wrestler::getCurrentState()
{
    return current_state;
}

void Wrestler::setCurrentState(State new_state)
{
    current_state = new_state;
}

Wrestler::SpriteState Wrestler::getCurSpriteState()
{
    return sprite_state;
}

void Wrestler::setCurSpriteState(SpriteState new_state)
{
    sprite_state = new_state;
}

void Wrestler::incFrozenFrames()
{
    frozen_frames++;
}
void Wrestler::resetFrozenFrames()
{
    frozen_frames = 0;
}
int Wrestler::getFrozenFrames()
{
    return frozen_frames;
}
long int Wrestler::getIDOfGrabbed()
{
    return id_of_grabbed;
}
void Wrestler::setIDOfGrabbed(long int id)
{
    id_of_grabbed = id;
}

void Wrestler::setCharacter(std::string character_name)
{
    // acceleration = float(str) / float(wgt); (0.2)
    // setStats(spd str wgt stm)
    if (character_name == "Fumio"){
        setStats(14, 10, 20, 100);
    }
    else if(character_name == "GreyRobot") {
        setStats(5, 5, 15, 50);
    }
    else if(character_name == "BlueRobot") {
        setStats(4, 6, 22, 50);
    }
    else if(character_name == "GreenRobot") {
        setStats(8, 6, 10, 50);
    }
    else if(character_name == "RedRobot") {
        setStats(15, 5, 9, 50);
    }
    else if(character_name == "Takeshi"){
        setStats(12, 12, 25, 100);
    }

    setName(character_name);
}

Wrestler::~Wrestler()
{
    //dtor
}
