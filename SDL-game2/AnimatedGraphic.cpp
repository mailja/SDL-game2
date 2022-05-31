#include "AnimatedGraphic.h"

#include <SDL_timer.h>

AnimatedGraphic::AnimatedGraphic() : SDLGameObject()
{
}

void AnimatedGraphic::load(const LoaderParams* pParams)
{
   SDLGameObject::load(pParams);
}

void AnimatedGraphic::update()
{
   m_currentFrame = int(((SDL_GetTicks() / (1000 / m_animSpeed)) % m_numFrames));
}

void AnimatedGraphic::clean()
{
   SDLGameObject::clean();
}

void AnimatedGraphic::draw()
{
   SDLGameObject::draw(); // use the base class drawing
}
