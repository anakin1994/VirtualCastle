#pragma once
#include <vector>

class ModelObjectDTO
{
public:
	ModelObjectDTO();
	ModelObjectDTO(std::vector < std::vector<float> > vertices, std::vector < std::vector<float> > uvs, std::vector < std::vector<float> > normals);
	~ModelObjectDTO();
	std::vector < std::vector<float> > Vertices;
	std::vector < std::vector<float> > Uvs;
	std::vector < std::vector<float> > Normals;
};

