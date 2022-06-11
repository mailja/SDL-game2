#include "LevelParser.h"



#include "base64.h"
#include "Game.h"
#include "TextureManager.h"
#include "TileLayer.h"
#include "tinyxml.h"
#include "zconf.h"
#include "zlib.h"

Level* LevelParser::parseLevel(const char* levelFile)
{
   // create a TinyXML document and load the map XML
   TiXmlDocument levelDocument;
   levelDocument.LoadFile(levelFile);
   // create the level object
   Level* pLevel = new Level();
   // get the root node
   TiXmlElement* pRoot = levelDocument.RootElement();
   pRoot->Attribute("tilewidth", &m_tileSize);
   pRoot->Attribute("width", &m_width);
   pRoot->Attribute("height", &m_height);
   // parse the tilesets
   for (TiXmlElement* e = pRoot->FirstChildElement(); e != NULL; e =
      e->NextSiblingElement())
   {
      if (e->Value() == std::string("tileset"))
      {
         parseTilesets(e, pLevel->getTilesets());
      }
   }
   // parse any object layers
   for (TiXmlElement* e = pRoot->FirstChildElement(); e != NULL; e =
      e->NextSiblingElement())
   {
      if (e->Value() == std::string("layer"))
      {
         parseTileLayer(e, pLevel->getLayers(), pLevel->getTilesets());
      }
   }
   return pLevel;
}

void LevelParser::parseTilesets(TiXmlElement* pTilesetRoot, std::vector<Tileset>* pTilesets)
{
   // first add the tileset to texture manager
   TheTextureManager::Instance()->load(pTilesetRoot -> FirstChildElement()->Attribute("source"), pTilesetRoot -> Attribute("name"), TheGame::Instance()->getRenderer());
   // create a tileset object
   Tileset tileset;
   pTilesetRoot->FirstChildElement()->Attribute("width",
      &tileset.width);
   pTilesetRoot->FirstChildElement()->Attribute("height",
      &tileset.height);
   pTilesetRoot->Attribute("firstgid", &tileset.firstGridID);
   pTilesetRoot->Attribute("tilewidth", &tileset.tileWidth);
   pTilesetRoot->Attribute("tileheight", &tileset.tileHeight);
   pTilesetRoot->Attribute("spacing", &tileset.spacing);
   pTilesetRoot->Attribute("margin", &tileset.margin);
   tileset.name = pTilesetRoot->Attribute("name");
   tileset.numColumns = tileset.width / (tileset.tileWidth +
      tileset.spacing);
   pTilesets->push_back(tileset);
}

void LevelParser::parseTileLayer(TiXmlElement* pTileElement, std::vector<Layer*>* pLayers, const std::vector<Tileset>* pTilesets)
{
   TileLayer* pTileLayer = new TileLayer(m_tileSize, *pTilesets);
   // tile data
   std::vector<std::vector<int>> data;
   std::string decodedIDs;
   TiXmlElement* pDataNode {};
   for (TiXmlElement* e = pTileElement->FirstChildElement(); e !=
      NULL; e = e->NextSiblingElement())
   {
      if (e->Value() == std::string("data"))
      {
         pDataNode = e;
      }
   }

   std::string tileLayerString;

   for (TiXmlNode* e = pDataNode->FirstChild(); e != NULL; e =
      e->NextSibling())
   {
      TiXmlText* text = e->ToText();
      tileLayerString = text->Value();
      //decodedIDs = base64_decode(t);
   }
   auto tileLayerVector = split_string(tileLayerString, ",");

   // uncompress zlib compression
   uLongf numGids = m_width * m_height * sizeof(int);
   std::vector<unsigned> gids(numGids);
   //uncompress((Bytef*)&gids[0], &numGids, (const Bytef*)decodedIDs.c_str(), decodedIDs.size());
   std::vector<int> layerRow(m_width);
   auto positionInSource = 0;
   for (int j = 0; j < m_height; j++)
   {
      data.push_back(layerRow);
   }
   for (int rows = 0; rows < m_height; rows++)
   {
      for (int cols = 0; cols < m_width; cols++)
      {
         data[rows][cols] = std::stoi(tileLayerVector[positionInSource]);    //gids[rows * m_width + cols];
         positionInSource++;
      }
   }

   pTileLayer->setTileIDs(data);
   pLayers->push_back(pTileLayer);
}

// Split string
std::vector<std::string> LevelParser::split_string(const std::string& stringToSplit, const std::string& delimiter)
{
   std::vector<std::string> strings;

   std::string::size_type pos = 0;
   std::string::size_type prev = 0;
   while ((pos = stringToSplit.find(delimiter, prev)) != std::string::npos)
   {
      strings.push_back(stringToSplit.substr(prev, pos - prev));
      prev = pos + 1;
   }

   // To get the last substring (or only, if delimiter is not found)
   strings.push_back(stringToSplit.substr(prev));

   return strings;
}
