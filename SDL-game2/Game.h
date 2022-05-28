#pragma once
#include <SDL.h>
#include <vector>

#include "Player.h"
#include "TextureManager.h"

#ifndef __Game__
#define __Game__

class Game
{
public:
   Game() {}
   ~Game() {}
   // simply set the running variable to true
   void init() { m_bRunning = true; }
   void render();
   void update();
   void handleEvents();
   void draw();
   void clean();
   // a function to access the private running variable
   bool running() { return m_bRunning; }

   bool init(const char* title, int xpos, int ypos, int width, int
      height, bool fullscreen);
private:
   SDL_Window* m_pWindow = 0;
   SDL_Renderer* m_pRenderer = 0;

   std::vector<GameObject*> m_gameObjects;

   int m_currentFrame;

   bool m_bRunning;

   GameObject* m_go;
   GameObject* m_player;
   GameObject* m_enemy;

};

#endif /* defined(__Game__) */

