#include <cstdio>
#include<SDL.h>
#include "Game.h"

// our Game object
Game* g_game = 0;

SDL_Window* g_pWindow = 0;
SDL_Renderer* g_pRenderer = 0;

bool g_bRunning = false; // this will create a loop

//void render()
//{
//   // set to black
//   SDL_SetRenderDrawColor(g_pRenderer, 0, 0, 0, 255);
//   // clear the window to black
//   SDL_RenderClear(g_pRenderer);
//   // show the window
//   SDL_RenderPresent(g_pRenderer);
//}


int main(int argc, char* args[])
{

   g_game = new Game();
   g_game->init("Chapter 1", 100, 100, 640, 580, false);
   while (g_game->running())
   {
      g_game->handleEvents();
      g_game->update();
      g_game->render();
   }
   g_game->clean();
   return 0;

   //if (init("Chapter 1: Setting up SDL",
   //   SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640,
   //   480, SDL_WINDOW_SHOWN))
   //{
   //   g_bRunning = true;
   //}
   //else
   //{
   //   return 1; // something's wrong
   //}

   //while (g_bRunning)
   //{
   //   render();
   //}
   //// clean up SDL
   //SDL_Quit();
   //return 0;
}