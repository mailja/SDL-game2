#include "Player.h"

#include <SDL_timer.h>

#include "InputHandler.h"


Player::Player(const LoaderParams* pParams) :
   SDLGameObject(pParams)
{
   
}

void Player::draw()
{
   SDLGameObject::draw(); // we now use SDLGameObject
}
void Player::update()
{
   m_velocity.setX(0);
   m_velocity.setY(0);

   handleInput(); // add our function

   m_currentFrame = int(((SDL_GetTicks() / 100) % 6));

   SDLGameObject::update();
}
void Player::clean()
{
}

void Player::handleInput()
{
   if (TheInputHandler::Instance()->joysticksInitialised())
   {
      if (TheInputHandler::Instance()->getAxisX(0, 1) > 0 ||
         TheInputHandler::Instance()->getAxisX(0, 1) < 0)
      {
         m_velocity.setX(1 * TheInputHandler::Instance()->getAxisX(0,
            1));
      }
      if (TheInputHandler::Instance()->getAxisY(0, 1) > 0 ||
         TheInputHandler::Instance()->getAxisY(0, 1) < 0)
      {
         m_velocity.setY(1 * TheInputHandler::Instance()->getAxisY(0,
            1));
      }
      if (TheInputHandler::Instance()->getAxisX(0, 2) > 0 ||
         TheInputHandler::Instance()->getAxisX(0, 2) < 0)
      {
         m_velocity.setX(1 * TheInputHandler::Instance()->getAxisX(0,
            2));
      }
      if (TheInputHandler::Instance()->getAxisY(0, 2) > 0 ||
         TheInputHandler::Instance()->getAxisY(0, 2) < 0)
      {
         m_velocity.setY(1 * TheInputHandler::Instance()->getAxisY(0,
            2));
      }
      if (TheInputHandler::Instance()->getButtonState(0, 3))
      {
         m_velocity.setX(1);
      }
   }
}