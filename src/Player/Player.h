#pragma once
//#include <SFML/Graphics.hpp>
#include <SDL.h>

#include "../Entity.h"

class Player : public Entity
{
    public:
        Player();

        void handleInput(); //const const SDL_Window& window);

        void update(float dt);

    private:
        void keyboardInput();
        void mouseInput();// const SDL_Window& window);

        glm::vec3 m_velocity;
};



