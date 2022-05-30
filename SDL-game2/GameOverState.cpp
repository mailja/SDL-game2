#include "GameOverState.h"


#include "AnimatedGraphic.h"
#include "Game.h"
#include "InputHandler.h"
#include "MenuButton.h"
#include "MenuState.h"
#include "PlayState.h"

const std::string GameOverState::s_gameOverID = "GAMEOVER";

void GameOverState::s_gameOverToMain()
{
   TheGame::Instance()->getStateMachine()->changeState(new MenuState());
}
void GameOverState::s_restartPlay()
{
   TheGame::Instance()->getStateMachine()->changeState(new PlayState());
}

void GameOverState::update()
{
   for (int i = 0; i < m_gameObjects.size(); i++)
   {
      m_gameObjects[i]->update();
   }
}

void GameOverState::render()
{
   for (int i = 0; i < m_gameObjects.size(); i++)
   {
      m_gameObjects[i]->draw();
   }
}

bool GameOverState::onEnter()
{
   if (!TheTextureManager::Instance()->load("assets/gameover_r.png",
      "gameovertext", TheGame::Instance()->getRenderer()))
   {
      return false;
   }
   if (!TheTextureManager::Instance()->load("assets/main_r.png",
      "mainbutton", TheGame::Instance()->getRenderer()))
   {
      return false;
   }
   if (!TheTextureManager::Instance()->load("assets/restart_r.png",
      "restartbutton", TheGame::Instance()->getRenderer()))
   {
      return false;
   }
   GameObject* gameOverText = new AnimatedGraphic(new LoaderParams(200, 100, 190, 30, "gameovertext", 2), 2);
   GameObject* button1 = new MenuButton(new LoaderParams(200, 200, 200, 80, "mainbutton"), s_gameOverToMain);
   GameObject* button2 = new MenuButton(new LoaderParams(200, 300, 200, 80, "restartbutton"), s_restartPlay);
   m_gameObjects.push_back(gameOverText);

   m_gameObjects.push_back(button1);
   m_gameObjects.push_back(button2);
   std::cout << "entering PauseState\n";
   return true;
}

bool GameOverState::onExit()
{
   for (int i = 0; i < m_gameObjects.size(); i++)
   {
      m_gameObjects[i]->clean();
   }
   m_gameObjects.clear();
   TheTextureManager::Instance()->clearFromTextureMap("gameovertext");
   TheTextureManager::Instance()->clearFromTextureMap("restartbutton");
   TheTextureManager::Instance()->clearFromTextureMap("mainbutton");
   // reset the mouse button states to false
   TheInputHandler::Instance()->reset();
   std::cout << "exiting GameOverState\n";
   return true;
}
