#pragma once
#include <string>
#include "ModelObjectDTO.h"

class ObjFileParser
{
public:
	ObjFileParser();
	ObjFileParser(std::string filePath);
	~ObjFileParser();
	ModelObjectDTO Parse();
private:
	std::string _filePath;
};

