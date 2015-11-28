#ifndef PROFILE_H
#define PROFILE_H
#include <string>
#include <SFML/Graphics.hpp>

class Profile
{
    public:
        Profile();
        virtual ~Profile();

        void setCharacter(std::string char_name);
        std::string getCharacter();

        void setLevel(std::string level_name);
        std::string getLevel();

        void setLives(int remaining);
        int livesRemaining();

        void setCheckpoint(unsigned int checkpoint_num);
        unsigned int getCheckpoint();
    protected:
    private:
        std::string character;
        std::string level;
        int lives;
        unsigned int cur_checkpoint_num;
};

#endif // PROFILE_H
