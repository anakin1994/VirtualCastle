#pragma once
#include <windows.h>
#include "GL/glew.h"
#include "gl\gl.h"
#include "GL/glut.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include <string>
#include "ObjFileParser.h"
#include "tga.h"

class DisplayableObject
{
public:
	GLuint tex;
	float *geomVertices;
	float *geomTexCoords;
	float *geomNormals;
	int geomVertexCount;
	ModelObjectDTO model;
	DisplayableObject();
	~DisplayableObject();
	void Display();
	void LoadFromFile(std::string filePath);
	void modelToArrays(ModelObjectDTO *model, float *vertArray, float *uvsArray, float *normalsArray);
	void LoadTexture(std::string fileName);
	void Move(glm::vec3 direction, float distance);
};

