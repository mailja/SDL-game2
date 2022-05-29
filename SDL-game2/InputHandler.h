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

   // init joysticks
   void initialiseJoysticks();
   bool joysticksInitialised() const { return m_bJoysticksInitialised; }

   //void reset();

   // update and clean the input handler
   void update();
   void clean();

   // joystick events
   int getAxisX(int joy, int stick) const;
   int getAxisY(int joy, int stick) const;
private:
   InputHandler();

   ~InputHandler() {}
   static InputHandler* s_pInstance;

   // joystick specific
   std::vector<SDL_Joystick*> m_joysticks;
   std::vector<std::pair<Vector2D*, Vector2D*>> m_joystickValues;
   bool m_bJoysticksInitialised;
   const int m_joystickDeadZone = 10000;  // ToDo : Change according to concrete controller
};

typedef InputHandler TheInputHandler;

