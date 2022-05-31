#pragma once
#include <iostream>
#include <SDL_render.h>

#include "LoaderParams.h"

class GameObject
{
public:
   virtual void draw() = 0;
   virtual void update() = 0;
   virtual void clean() = 0;

   // new load function
   virtual void load(const LoaderParams* pParams) = 0;

protected:

   GameObject() {}
   virtual ~GameObject() = default;
};

