#pragma once
#include <SDL.h>

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
   void update() {}
   void handleEvents();
   void clean();
   // a function to access the private running variable
   bool running() { return m_bRunning; }

   bool init(const char* title, int xpos, int ypos, int width, int
      height, bool fullscreen);
private:
   SDL_Window* m_pWindow = 0;
   SDL_Renderer* m_pRenderer = 0;

   SDL_Texture* m_pTexture; // the new SDL_Texture variable
   SDL_Rect m_sourceRectangle; // the first rectangle
   SDL_Rect m_destinationRectangle; // another rectangle

   bool m_bRunning;
};

#endif /* defined(__Game__) */

