#pragma once
#include "GameObject.h"
#include "SDLGameObject.h"

class Enemy : public SDLGameObject
{
public:
   Enemy(const LoaderParams* pParams);
   virtual void draw();
   virtual void update();
   virtual void clean();
private:
   int m_numFrames = 6;

};

