#pragma once
#include <vector>


#include "GameState.h"

class Level;
class SDLGameObject;
class GameObject;

class PlayState : public GameState
{
public:
   virtual void update();
   virtual void render();
   virtual bool onEnter();
   virtual bool onExit();
   virtual std::string getStateID() const { return s_playID; }
private:
   static const std::string s_playID;

   bool checkCollision(SDLGameObject* p1, SDLGameObject* p2);

   std::vector<GameObject*> m_gameObjects;

   Level* pLevel;
};

