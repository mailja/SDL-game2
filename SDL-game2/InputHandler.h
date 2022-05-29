#pragma once
#include <vector>

#include "SDL.h"
#include "Vector2D.h"

class InputHandler
{
public:
   static InputHandler* Instance()
   {
      if (s_pInstance == 0)
      {
         s_pInstance = new InputHandler();
      }
      return s_pInstance;
   }
   void initialiseJoysticks();
   bool joysticksInitialised() const { return m_bJoysticksInitialised; }

   //void reset();

   void update();
   void clean();

   int xvalue(int joy, int stick);
   int yvalue(int joy, int stick);
private:
   InputHandler();

   ~InputHandler() {}
   static InputHandler* s_pInstance;

   std::vector<SDL_Joystick*> m_joysticks;

   std::vector<std::pair<Vector2D*, Vector2D*>> m_joystickValues;

   bool m_bJoysticksInitialised;
   const int m_joystickDeadZone = 10000;  // ToDo : Change according to concrete controller
};

typedef InputHandler TheInputHandler;

