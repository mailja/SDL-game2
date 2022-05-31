#pragma once
#include "GameObjectFactory.h"
#include "SDLGameObject.h"


class MenuButton : public SDLGameObject
{
public:
   MenuButton();
   virtual ~MenuButton() = default;

   virtual void load(const LoaderParams* pParams);

   virtual void draw();
   virtual void update();
   virtual void clean();
private:
   enum button_state
   {
      MOUSE_OUT = 0,
      MOUSE_OVER = 1,
      CLICKED = 2
   };

   bool m_bReleased;

   // C style function pointer,
   // syntax returnType (*functionName)(parameters);
   void (*m_callback)();  
};

class MenuButtonCreator : public BaseCreator
{
   GameObject* createGameObject() const
   {
      return new MenuButton();
   }
};


