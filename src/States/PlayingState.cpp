#include "PlayingState.h"

#include "../Renderer/RenderMaster.h"
#include "../Application.h"
#include <iostream>

StatePlaying::StatePlaying(Application& app)
:   StateBase   (app)
{
    app.getCamera().hookEntity(m_player);
}

void StatePlaying::handleEvent(SDL_Event e)//sf::Event e)
{

}

void StatePlaying::handleInput()
{
    m_player.handleInput();//m_pApplication->getWindow().getWindow());
}

void StatePlaying::update(float deltaTime)
{
    m_player.update(deltaTime);
}

void StatePlaying::render(RenderMaster& renderer)
{
    //renderer.drawQuad({0, 0, 0});
    //renderer.drawCube({ -1.1, 0, -1.1 });
    renderer.drawCube({ -0.5, -0.5, -1.5 });
}
