#pragma once
#include "GameObjectFactory.h"
#include "Player.h"

class PlayerCreator : public BaseCreator
{
   GameObject* createGameObject() const
   {
      return new Player();
   }
};
