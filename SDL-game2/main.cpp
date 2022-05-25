#include <cstdio>
#include<SDL.h>
#include "Game.h"

// our Game object
Game* g_game = 0;

SDL_Window* g_pWindow = 0;
SDL_Renderer* g_pRenderer = 0;

bool g_bRunning = false; // this will create a loop


int main(int argc, char* args[])
{

   g_game = new Game();
   g_game->init("Chapter 1", 100, 100, 640, 580, false);
   while (g_game->running())
   {
      g_game->handleEvents();
      g_game->update();
      g_game->render();

      SDL_Delay(10); // add the delay
   }
   g_game->clean();
   return 0;

}