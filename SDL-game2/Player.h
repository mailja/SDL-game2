#pragma once
#include "GameObject.h"
#include "GameObjectFactory.h"
#include "SDLGameObject.h"

class Player : public SDLGameObject
{
public:

   Player();
   virtual void draw();
   virtual void update();
   virtual void clean();
   virtual void load(const LoaderParams* pParams);
private:
   void handleInput();
};

// for the factory
class PlayerCreator : public BaseCreator
{
   GameObject* createGameObject() const
   {
      return new Player();
   }
};
