#include "PlayState.h"

#include <iostream>


#include "Enemy.h"
#include "Game.h"
#include "GameOverState.h"
#include "InputHandler.h"
#include "PauseState.h"

const std::string PlayState::s_playID = "PLAY";

void PlayState::update()
{
   if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_ESCAPE))
   {
      TheGame::Instance()->getStateMachine()->pushState(new PauseState());
   }
   for (int i = 0; i < m_gameObjects.size(); i++)
   {
      m_gameObjects[i]->update();
   }
   if (checkCollision(dynamic_cast<SDLGameObject*>
      (m_gameObjects[0]), dynamic_cast<SDLGameObject*>
      (m_gameObjects[1])))
   {
      TheGame::Instance()->getStateMachine()->pushState(new GameOverState());
   }
}
void PlayState::render()
{
   for (int i = 0; i < m_gameObjects.size(); i++)
   {
      m_gameObjects[i]->draw();
   }
}
bool PlayState::onEnter()
{
   if (!TheTextureManager::Instance()->load("assets/helicopter_r.png",
      "helicopter", TheGame::Instance()->getRenderer()))
   {
      return false;
   }
   if (!TheTextureManager::Instance()
      ->load("assets/helicopter2_r.png", "helicopter2",
         TheGame::Instance()->getRenderer()))
   {
      return false;
   }

   GameObject* player = new Player(new LoaderParams(300, 100, 128, 55, "helicopter"));
   GameObject* enemy = new Enemy(new LoaderParams(100, 100, 128, 55, "helicopter2"));

   m_gameObjects.push_back(player);
   m_gameObjects.push_back(enemy);

   std::cout << "entering PlayState\n";
   return true;
}
bool PlayState::onExit()
{
   for (int i = 0; i < m_gameObjects.size(); i++)
   {
      m_gameObjects[i]->clean();
   }
   m_gameObjects.clear();
   TheTextureManager::Instance()->clearFromTextureMap("helicopter");

   std::cout << "exiting PlayState\n";
   return true;
}

bool PlayState::checkCollision(SDLGameObject* p1, SDLGameObject* p2)
{
   int leftA = p1->getPosition().getX();
   int rightA = p1->getPosition().getX() + p1->getWidth();
   int topA = p1->getPosition().getY();
   int bottomA = p1->getPosition().getY() + p1->getHeight();
   //Calculate the sides of rect B
   int leftB = p2->getPosition().getX();
   int rightB = p2->getPosition().getX() + p2->getWidth();
   int topB = p2->getPosition().getY();
   int bottomB = p2->getPosition().getY() + p2->getHeight();
   //If any of the sides from A are outside of B
   if (bottomA <= topB) { return false; }
   if (topA >= bottomB) { return false; }
   if (rightA <= leftB) { return false; }
   if (leftA >= rightB) { return false; }
   return true;
}
