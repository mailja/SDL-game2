#include "InputHandler.h"

#include <iostream>

#include "Game.h"

InputHandler* InputHandler::s_pInstance = nullptr;

InputHandler::InputHandler() : m_bJoysticksInitialised(false)
{
   // create button states for the mouse
   for (int i = 0; i < 3; i++)
   {
      m_mouseButtonStates.push_back(false);
   }
}

void InputHandler::initialiseJoysticks()
{
   // if we haven't already initialised the joystick subystem, we will do it here
   if (SDL_WasInit(SDL_INIT_JOYSTICK) == 0)
   {
      SDL_InitSubSystem(SDL_INIT_JOYSTICK);
   }

   // get the number of joysticks, skip init if there aren't any
   if (SDL_NumJoysticks() > 0)
   {
      for (int i = 0; i < SDL_NumJoysticks(); i++)
      {
         // create a new joystick
         SDL_Joystick* joy = SDL_JoystickOpen(i);

         // if the joystick opened correctly we need to populate our arrays
         if (joy)
         {
            // push back into the array to be closed later
            m_joysticks.push_back(joy);
            // create a pair of values for the axes, a vector for each stick
            m_joystickValues.push_back(std::make_pair(new
               Vector2D(0, 0), new Vector2D(0, 0))); // add our pair

            // create an array to hold the button values
            std::vector<bool> tempButtons;

            // fill the array with a false value for each button
            for (int j = 0; j < SDL_JoystickNumButtons(joy); j++)
            {
               tempButtons.push_back(false);
            }
            // push the button array into the button state array
            m_buttonStates.push_back(tempButtons);
         }
         else
         {
            std::cout << SDL_GetError();
         }
      }

      // enable joystick events
      SDL_JoystickEventState(SDL_ENABLE);
      m_bJoysticksInitialised = true;

      std::cout << "Initialised " << m_joysticks.size() << "joystick(s)";
   }
   else
   {
      m_bJoysticksInitialised = false;
   }
}

int InputHandler::getAxisX(int joy, int stick) const
{
   if (m_joystickValues.size() > 0)
   {
      if (stick == 1)
      {
         return m_joystickValues[joy].first->getX();
      }
      else if (stick == 2)
      {
         return m_joystickValues[joy].second->getX();
      }
   }
   return 0;
}

int InputHandler::getAxisY(int joy, int stick) const
{
   if (m_joystickValues.size() > 0)
   {
      if (stick == 1)
      {
         return m_joystickValues[joy].first->getY();
      }
      else if (stick == 2)
      {
         return m_joystickValues[joy].second->getY();
      }
   }
   return 0;
}

bool InputHandler::getButtonState(int joy, int buttonNumber) const
{
   return m_buttonStates[joy][buttonNumber];
}

bool InputHandler::getMouseButtonState(int buttonNumber) const
{
   return m_mouseButtonStates[buttonNumber];
}

void InputHandler::clean()
{
   if (m_bJoysticksInitialised)
   {
      for (unsigned int i = 0; i < SDL_NumJoysticks(); i++)
      {
         SDL_JoystickClose(m_joysticks[i]);
      }
   }
}

void InputHandler::update()
{
   SDL_Event event;

   while (SDL_PollEvent(&event))
   {
      if (event.type == SDL_QUIT)
      {
         TheGame::Instance()->quit();
      }

      if (event.type == SDL_JOYAXISMOTION)
      {
         int whichOne = event.jaxis.which;

         // left stick move left or right
         if (event.jaxis.axis == 0)
         {
            if (event.jaxis.value > m_joystickDeadZone)
            {
               m_joystickValues[whichOne].first->setX(1);
            }
            else if (event.jaxis.value < -m_joystickDeadZone)
            {
               m_joystickValues[whichOne].first->setX(-1);
            }
            else
            {
               m_joystickValues[whichOne].first->setX(0);
            }
         }
         // left stick move up or down
         if (event.jaxis.axis == 1)
         {
            if (event.jaxis.value > m_joystickDeadZone)
            {
               m_joystickValues[whichOne].first->setY(1);
            }
            else if (event.jaxis.value < -m_joystickDeadZone)
            {
               m_joystickValues[whichOne].first->setY(-1);
            }
            else
            {
               m_joystickValues[whichOne].first->setY(0);
            }
         }
         //right stick move left or right
         if (event.jaxis.axis == 3)
         {
            if (event.jaxis.value > m_joystickDeadZone)
            {
               m_joystickValues[whichOne].second->setX(1);
            }
            else if (event.jaxis.value < -m_joystickDeadZone)
            {
               m_joystickValues[whichOne].second->setX(-1);
            }
            else
            {
               m_joystickValues[whichOne].second->setX(0);
            }
         }

         // right stick move up or down
         if (event.jaxis.axis == 4)
         {
            if (event.jaxis.value > m_joystickDeadZone)
            {
               m_joystickValues[whichOne].second->setY(1);
            }
            else if (event.jaxis.value < -m_joystickDeadZone)
            {
               m_joystickValues[whichOne].second->setY(-1);
            }
            else
            {
               m_joystickValues[whichOne].second->setY(0);
            }
         }
      }

      if (event.type == SDL_JOYBUTTONDOWN)
      {
         int whichOne = event.jaxis.which;
         m_buttonStates[whichOne][event.jbutton.button] = true;
      }
      if (event.type == SDL_JOYBUTTONUP)
      {
         int whichOne = event.jaxis.which;
         m_buttonStates[whichOne][event.jbutton.button] = false;
      }

      if (event.type == SDL_MOUSEBUTTONDOWN)
      {
         if (event.button.button == SDL_BUTTON_LEFT)
         {
            m_mouseButtonStates[LEFT] = true;
         }
         if (event.button.button == SDL_BUTTON_MIDDLE)
         {
            m_mouseButtonStates[MIDDLE] = true;
         }
         if (event.button.button == SDL_BUTTON_RIGHT)
         {
            m_mouseButtonStates[RIGHT] = true;
         }
      }

      if (event.type == SDL_MOUSEBUTTONUP)
      {
         if (event.button.button == SDL_BUTTON_LEFT)
         {
            m_mouseButtonStates[LEFT] = false;
         }
         if (event.button.button == SDL_BUTTON_MIDDLE)
         {
            m_mouseButtonStates[MIDDLE] = false;
         }
         if (event.button.button == SDL_BUTTON_RIGHT)
         {
            m_mouseButtonStates[RIGHT] = false;
         }
      }

   }
}
