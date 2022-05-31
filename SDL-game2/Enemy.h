#pragma once
#include "GameObject.h"
#include "GameObjectFactory.h"
#include "Player.h"
#include "SDLGameObject.h"

class Enemy : public SDLGameObject
{
public:
   Enemy();
   virtual void draw();
   virtual void update();
   virtual void clean();
   virtual void load(const LoaderParams* pParams);
private:
   int m_numFrames = 6;

};

// for the factory
class EnemyCreator : public BaseCreator
{
   GameObject* createGameObject() const
   {
      return new Enemy();
   }
};
