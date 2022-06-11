#pragma once
#include <SDL.h>
#include <vector>

#include "Player.h"
#include "TextureManager.h"
#include "GameStateMachine.h"

#ifndef __Game__
#define __Game__

class Game
{
public:
   static Game* Instance()
   {
      if (s_pInstance == 0)
      {
         s_pInstance = new Game();
         return s_pInstance;
      }
      return s_pInstance;
   }
   ~Game() = default;
   // simply set the running variable to true
   void init() { m_bRunning = true; }
   void render();
   void update();
   void handleEvents();
   void draw();
   void clean();
   void quit();
   // a function to access the private running variable
   bool running() { return m_bRunning; }

   bool init(const char* title, int xpos, int ypos, int width, int
      height, bool fullscreen);

   SDL_Renderer* getRenderer() const { return m_pRenderer; }
   GameStateMachine* m_pGameStateMachine;
   GameStateMachine* getStateMachine() { return m_pGameStateMachine; }

   int getGameWidth() const { return m_gameWidth; }
   int getGameHeight() const { return m_gameHeight; }

private:

   Game() = default;
   // create the s_pInstance member variable
   static Game* s_pInstance;

   int m_gameWidth;
   int m_gameHeight;

   SDL_Window* m_pWindow = 0;
   SDL_Renderer* m_pRenderer = 0;

   std::vector<GameObject*> m_gameObjects;

   int m_currentFrame;

   bool m_bRunning;

   GameObject* m_go;
   GameObject* m_player;
   GameObject* m_enemy;

};
typedef Game TheGame;

#endif /* defined(__Game__) */

