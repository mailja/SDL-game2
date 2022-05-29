#pragma once
#include <vector>

#include "SDL.h"
#include "Vector2D.h"


enum mouse_buttons
{
   LEFT = 0,
   MIDDLE = 1,
   RIGHT = 2
};

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
   bool getButtonState(int joy, int buttonNumber) const;

   // mouse events
   bool getMouseButtonState(int buttonNumber) const;


private:
   InputHandler();

   ~InputHandler() {}
   static InputHandler* s_pInstance;

   // joystick specific
   std::vector<SDL_Joystick*> m_joysticks;
   std::vector<std::pair<Vector2D*, Vector2D*>> m_joystickValues;
   std::vector<std::vector<bool>> m_buttonStates;
   bool m_bJoysticksInitialised;
   const int m_joystickDeadZone = 10000;  // ToDo : Change according to concrete controller

   // mouse specific
   std::vector<bool> m_mouseButtonStates;

};

typedef InputHandler TheInputHandler;

