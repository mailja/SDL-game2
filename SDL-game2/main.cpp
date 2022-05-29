#include <cstdio>
#include<SDL.h>
#include "Game.h"

// our Game object
Game* g_game = 0;

SDL_Window* g_pWindow = 0;
SDL_Renderer* g_pRenderer = 0;

bool g_bRunning = false; // this will create a loop

const int FPS = 60;
const int DELAY_TIME = 1000.0f / FPS;

int main(int argc, char* args[])
{

   std::cout << "game init attempt...\n";

   Uint32 frameStart, frameTime;

   if (TheGame::Instance()->init("Chapter 1", 100, 100, 640, 480,
                                 false))
   {
      std::cout << "game init success!\n";
      while (TheGame::Instance()->running())
      {
         frameStart = SDL_GetTicks();

         TheGame::Instance()->handleEvents();
         TheGame::Instance()->update();
         TheGame::Instance()->render();

         frameTime = SDL_GetTicks() - frameStart;
         if (frameTime < DELAY_TIME)
         {
            SDL_Delay((int)(DELAY_TIME - frameTime));
         }
      }
   }
   else
   {
      std::cout << "game init failure - " << SDL_GetError() << "\n";
      return -1;
   }

   std::cout << "game closing...\n";
   TheGame::Instance()->clean();

   return 0;

}