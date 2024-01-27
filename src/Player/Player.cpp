#include "Player.h"

//#include <SFML/Graphics.hpp>

#include <SDL.h>
#include <iostream>

Player::Player() : m_velocity({ 0, 0, 0 })
{
    //position = glm::vec3(0.0f, 0.0f, -5.0f);
    position = { 0, 0, 0 };//-5};
}

void Player::handleInput()//const SDL_Window& window)//sf::RenderWindow& window)
{
    keyboardInput();
    mouseInput();//window);
}

void Player::update(float dt)
{
    position += m_velocity * dt;
    m_velocity *= 0.95f;
    //std::cout << position.x << ", " << position.y << ", " << position.z << "\n"; //FEEL LIKE SHOULD WORK :')

}

void Player::keyboardInput()
{

    glm::vec3 change = { 0, 0, 0 };
    float speed = 0.2f;

    const Uint8* keyState = SDL_GetKeyboardState(NULL);

    if (keyState[SDL_SCANCODE_LCTRL])
    {
        speed /= 3;
    }

    if (keyState[SDL_SCANCODE_Z])
    {
        speed *= 5;
    }

    // Handle forward movement (W)
    if (keyState[SDL_SCANCODE_W])
    {
        change.x += glm::cos(glm::radians(rotation.y + 90)) * speed;
        change.z += glm::sin(glm::radians(rotation.y + 90)) * speed;
    }

    // Handle backward movement (S)
    if (keyState[SDL_SCANCODE_S])
    {
        change.x -= glm::cos(glm::radians(rotation.y + 90)) * speed;
        change.z -= glm::sin(glm::radians(rotation.y + 90)) * speed;
    }

    // Handle left movement (A)
    if (keyState[SDL_SCANCODE_A])
    {
        change.x += glm::cos(glm::radians(rotation.y)) * speed;
        change.z += glm::sin(glm::radians(rotation.y)) * speed;
    }

    // Handle right movement (D)
    if (keyState[SDL_SCANCODE_D])
    {
        change.x -= glm::cos(glm::radians(rotation.y)) * speed;
        change.z -= glm::sin(glm::radians(rotation.y)) * speed;
    }

    if (keyState[SDL_SCANCODE_LSHIFT])
    {
        change.y += speed;
    }

    if (keyState[SDL_SCANCODE_SPACE])
    {
        change.y -= speed;
    }

    m_velocity -= change;
}

float sensitivity = 0.1f;

void Player::mouseInput()//const SDL_Window& window)
{
    /*
    static auto const BOUND = 80;
    static auto lastMousePosition = sf::Mouse::getPosition(window);
    auto change = sf::Mouse::getPosition() - lastMousePosition;

    rotation.y += change.x * 0.05;
    rotation.x += change.y * 0.05;

    if      (rotation.x >  BOUND) rotation.x =  BOUND;
    else if (rotation.x < -BOUND) rotation.x = -BOUND;

    if      (rotation.y >  360) rotation.y = 0;
    else if (rotation.y < 0)    rotation.y = 360;

    auto cx = static_cast<int>(window.getSize().x / 4);
    auto cy = static_cast<int>(window.getSize().y / 4);

    sf::Mouse::setPosition({cx, cy}, window);

    lastMousePosition = sf::Mouse::getPosition();
    */
    static SDL_Point lastMousePosition = { 0, 0 };
    int deltaX, deltaY;
    SDL_GetRelativeMouseState(&deltaX, &deltaY);

    rotation.y += static_cast<float>(deltaX) * sensitivity;
    rotation.x += static_cast<float>(deltaY) * sensitivity;

    if (rotation.x > 90)
    {
        rotation.x = 90;
    }
    else if (rotation.x < -90)
    {
        rotation.x = -90;
    }
    if (rotation.y < 0)
    {
        rotation.y = 360;
    }
    else if (rotation.y > 360)
    {
        rotation.y = 0;
    }
    SDL_GetMouseState(&lastMousePosition.x, &lastMousePosition.y);
    //std::cout << lastMousePosition.x << ", " << lastMousePosition.y << "\n";
}

    
























