#ifndef PROFILE_H
#define PROFILE_H
#include <string>

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
    protected:
    private:
        std::string character;
        std::string level;
        int lives;
};

#endif // PROFILE_H
