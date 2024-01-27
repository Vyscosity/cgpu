#pragma once

#include "StateBase.h"
#include "../Player/Player.h"

class StatePlaying : public StateBase
{
    public:
        StatePlaying(Application& app);

        void handleEvent(SDL_Event e);//sf::Event e);
        void handleInput();

        void update(float deltaTime);

        void render(RenderMaster& renderer);

    private:
        Player m_player;
};

