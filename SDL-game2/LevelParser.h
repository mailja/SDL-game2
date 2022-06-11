#pragma once
#include "Level.h"

class TiXmlElement;

class LevelParser
{
public:
   Level* parseLevel(const char* levelFile);
private:
   void parseTilesets(TiXmlElement* pTilesetRoot, std::vector<Tileset>* pTilesets);
   void parseTileLayer(TiXmlElement* pTileElement, std::vector<Layer*>* pLayers, const std::vector<Tileset>* pTilesets);
   std::vector<std::string> split_string(const std::string& stringToSplit, const std::string& delimiter);
   int m_tileSize;
   int m_width;
   int m_height;

};

