#include "ModelObjectDTO.h"



ModelObjectDTO::ModelObjectDTO()
{
}


ModelObjectDTO::ModelObjectDTO(std::vector<std::vector<float>> vertices, std::vector<std::vector<float>> uvs, std::vector<std::vector<float>> normals)
{
	Vertices = vertices;
	Uvs = uvs;
	Normals = normals;
}

ModelObjectDTO::~ModelObjectDTO()
{
}
