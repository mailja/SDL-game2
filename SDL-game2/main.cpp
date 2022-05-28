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

   std::cout << "game init attempt...\n";
   if (TheGame::Instance()->init("Chapter 1", 100, 100, 640, 480,
      false))
   {
      std::cout << "game init success!\n";
      while (TheGame::Instance()->running())
      {
         TheGame::Instance()->handleEvents();
         TheGame::Instance()->update();
         TheGame::Instance()->render();
         SDL_Delay(10);
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