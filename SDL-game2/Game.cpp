#include "Game.h"
#include <iostream>
#include <SDL_image.h>
#include <vector>


#include "Enemy.h"
#include "TextureManager.h"

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
            SDL_SetRenderDrawColor(m_pRenderer, 255, 0, 0, 255);
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

      if(!TheTextureManager::Instance()->load("assets/animate-alpha.png", "animate", m_pRenderer))
      {
         return false;
      }

      m_go = new GameObject();
      m_player = new Player();
      m_enemy = new Enemy();

      m_go->load(100, 100, 128, 82, "animate");
      m_player->load(300, 300, 128, 82, "animate");
      m_enemy->load(0, 0, 128, 82, "animate");

      m_gameObjects.push_back(m_go);
      m_gameObjects.push_back(m_player);
      m_gameObjects.push_back(m_enemy);
       
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
   // loop through our objects and draw them
   for (std::vector<GameObject*>::size_type i = 0; i != m_gameObjects.size(); i++)
   {
      m_gameObjects[i]->draw(m_pRenderer);
   }
   SDL_RenderPresent(m_pRenderer); // draw to the screen
}

void Game::update()
{
   // loop through and update our objects
   for (std::vector<GameObject*>::size_type i = 0; i != m_gameObjects.size(); i++)
   {
      m_gameObjects[i]->update();
   }
}

void Game::clean()
{
   std::cout << "cleaning game\n";
   SDL_DestroyWindow(m_pWindow);
   SDL_DestroyRenderer(m_pRenderer);
   SDL_Quit();
}

void Game::handleEvents()
{
   SDL_Event event;
   if (SDL_PollEvent(&event))
   {
      switch (event.type)
      {
      case SDL_QUIT:
         m_bRunning = false;
         break;
      default:
         break;
      }
   }
}

void Game::draw()
{
   for (std::vector<GameObject*>::size_type i = 0; i != m_gameObjects.size(); i++)
   {
      m_gameObjects[i]->draw(m_pRenderer);
   }
}
