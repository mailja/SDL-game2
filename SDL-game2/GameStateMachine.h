#pragma once

#include <vector>

#include "GameState.h"

class GameStateMachine
{
public:

   GameStateMachine() {}
   ~GameStateMachine() {}

   void update();
   void render();

   void pushState(GameState* pState);
   void changeState(GameState* pState);
   void popState();
private:
   std::vector<GameState*> m_gameStates;
};

