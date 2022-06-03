#pragma once
#include <string>
#include <vector>
#include "tinyxml.h"

class GameObject;

class StateParser
{
public:
   StateParser() = default;
   ~StateParser() = default;

   bool parseState(const char* stateFile, std::string stateID, std::vector<GameObject*>* pObjects, std::vector<std::string>* pTextureIDs);
private:
   void parseObjects(TiXmlElement* pStateRoot, std::vector<GameObject*>* pObjects);
   void parseTextures(TiXmlElement* pStateRoot, std::vector<std::string>* pTextureIDs);
};