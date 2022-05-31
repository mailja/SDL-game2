#pragma once
#include "GameObjectFactory.h"
#include "SDLGameObject.h"



class AnimatedGraphic : public SDLGameObject
{
public:
   AnimatedGraphic();
   virtual ~AnimatedGraphic() = default;


   virtual void load(const LoaderParams* pParams);

   virtual void draw();
   virtual void update();
   virtual void clean();
private:
   int m_animSpeed;
   int m_numFrames;
};

class AnimatedGraphicCreator : public BaseCreator
{
   GameObject* createGameObject() const
   {
      return new AnimatedGraphic();
   }
};


