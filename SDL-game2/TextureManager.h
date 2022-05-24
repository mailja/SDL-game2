#pragma once
#include <map>
#include <SDL_render.h>
#include <string>

class TextureManager;
typedef TextureManager TheTextureManager;


class TextureManager
{
private:
   TextureManager() = default;

public:


   static TextureManager* s_pInstance;

   bool load(std::string fileName, std::string id, SDL_Renderer* pRenderer);

   // draw
   void draw(std::string id, int x, int y, int width, int height, SDL_Renderer* pRenderer, SDL_RendererFlip flip = SDL_FLIP_NONE);

   // draw frame
   void drawFrame(std::string id, int x, int y, int width, int height, int currentRow, int currentFrame, SDL_Renderer* pRenderer, SDL_RendererFlip flip = SDL_FLIP_NONE);

   std::map<std::string, SDL_Texture*> m_textureMap;

   static TextureManager* Instance()
   {
      if (s_pInstance == 0)
      {
         s_pInstance = new TextureManager();
         return s_pInstance;
      }
      return s_pInstance;
   }

};
