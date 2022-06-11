﻿#pragma once
#include <map>
#include <SDL_render.h>
#include <string>

class TextureManager
{
private:
   TextureManager() = default;
   ~TextureManager() = default;

public:


   static TextureManager* s_pInstance;

   bool load(std::string fileName, std::string id, SDL_Renderer* pRenderer);

   void clearTextureMap();
   void clearFromTextureMap(std::string id);


   // draw
   void draw(std::string id, int x, int y, int width, int height, SDL_Renderer* pRenderer, SDL_RendererFlip flip = SDL_FLIP_NONE);
   // draw frame
   void drawFrame(std::string id, int x, int y, int width, int height, int currentRow, int currentFrame, SDL_Renderer* pRenderer, SDL_RendererFlip flip = SDL_FLIP_NONE);
   void drawTile(std::string id, int margin, int spacing, int x, int y, int width, int height, int currentRow, int currentFrame, SDL_Renderer* pRenderer);

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

typedef TextureManager TheTextureManager;
