#include "Game.h"
#include <iostream>
#include <SDL_image.h>
#include <vector>



#include "AnimatedGraphic.h"
#include "Enemy.h"
#include "InputHandler.h"
#include "MainMenuState.h"
#include "MenuButton.h"
#include "MenuState.h"
#include "PlayState.h"
#include "TextureManager.h"


Game* Game::s_pInstance = nullptr;

bool Game::init(const char* title, int xpos, int ypos, int width,
   int height, bool fullscreen)
{
   // attempt to initialize SDL
   if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
   {
      int flags = 0;
      if (fullscreen)
      {
         flags = SDL_WINDOW_FULLSCREEN;
      }
      std::cout << "SDL init success\n";
      // init the window
      m_pWindow = SDL_CreateWindow(title, xpos, ypos,
         width, height, flags);
      if (m_pWindow != 0) // window init success
      {
         std::cout << "window creation success\n";
         m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, 0);
         if (m_pRenderer != 0) // renderer init success
         {
            std::cout << "renderer creation success\n";
            SDL_SetRenderDrawColor(m_pRenderer, 0, 128, 128, 255);
         }
         else
         {
            std::cout << "renderer init fail\n";
            return false; // renderer init fail
         }
      }
      else
      {
         std::cout << "window init fail\n";
         return false; // window init fail
      }

      // register the types for the game
      TheGameObjectFactory::Instance()->registerType("MenuButton", new MenuButtonCreator());
      TheGameObjectFactory::Instance()->registerType("Player", new PlayerCreator());
      TheGameObjectFactory::Instance()->registerType("Enemy", new EnemyCreator());
      TheGameObjectFactory::Instance()->registerType("AnimatedGraphic", new AnimatedGraphicCreator());

      TheInputHandler::Instance()->initialiseJoysticks();

      m_pGameStateMachine = new GameStateMachine();
      m_pGameStateMachine->changeState(new MainMenuState());
   }
   else
   {
      std::cout << "SDL init fail\n";
      return false; // SDL init fail
   }
   std::cout << "init success\n";
   m_bRunning = true; // everything initiated successfully, start the main loop
   return true;
}

void Game::render()
{
   SDL_RenderClear(m_pRenderer); // clear the renderer to the draw color
   //// loop through our objects and draw them
   //for (std::vector<GameObject*>::size_type i = 0; i != m_gameObjects.size(); i++)
   //{
   //   m_gameObjects[i]->draw();
   //}

   m_pGameStateMachine->render();
   SDL_RenderPresent(m_pRenderer); // draw to the screen
}

void Game::update()
{
   //// loop through and update our objects
   //for (std::vector<GameObject*>::size_type i = 0; i != m_gameObjects.size(); i++)
   //{
   //   m_gameObjects[i]->update();
   //}
   m_pGameStateMachine->update();
}

void Game::clean()
{
   std::cout << "cleaning game\n";
   TheInputHandler::Instance()->clean();

   //m_pGameStateMachine->clean();

   m_pGameStateMachine = 0;
   delete m_pGameStateMachine;

   TheTextureManager::Instance()->clearTextureMap();
   SDL_DestroyWindow(m_pWindow);
   SDL_DestroyRenderer(m_pRenderer);
   SDL_Quit();
}

void Game::quit()
{
   SDL_Quit();
}

void Game::handleEvents()
{
   TheInputHandler::Instance()->update();
   if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_RETURN))
   {
      m_pGameStateMachine->changeState(new PlayState());
   }
}

void Game::draw()
{
   for (std::vector<GameObject*>::size_type i = 0; i != m_gameObjects.size(); i++)
   {
      m_gameObjects[i]->draw();
   }
}
