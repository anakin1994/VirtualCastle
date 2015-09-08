#include "DisplayableObject.h"

using namespace std;

DisplayableObject::DisplayableObject()
{
}


DisplayableObject::~DisplayableObject()
{
}

void DisplayableObject::Display()
{
	glBindTexture(GL_TEXTURE_2D, tex);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, geomVertices);
	glNormalPointer(GL_FLOAT, 0, geomNormals);
	glTexCoordPointer(2, GL_FLOAT, 0, geomTexCoords);
	glDrawArrays(GL_QUADS, 0, geomVertexCount);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
}

void DisplayableObject::modelToArrays(ModelObjectDTO * model, float * vertArray, float * uvsArray, float * normalsArray)
{
	int i = 0;
	for each (vector<float> vertex in model->Vertices)
	{
		vertArray[i] = vertex[0];
		vertArray[i + 1] = vertex[1];
		vertArray[i + 2] = vertex[2];
		i += 3;
	}
	i = 0;
	for each (vector<float> uv in model->Uvs)
	{
		uvsArray[i] = uv[0];
		uvsArray[i + 1] = uv[1];
		i += 2;
	}
	i = 0;
	for each (vector<float> normal in model->Normals)
	{
		normalsArray[i] = normal[0];
		normalsArray[i + 1] = normal[1];
		normalsArray[i + 2] = normal[2];
		i += 3;
	}
}

void DisplayableObject::LoadTexture(string fileName)
{
	TGAImg img;
	if (img.Load(_strdup(fileName.c_str())) == IMG_OK) {
		glGenTextures(1, &tex); //Zainicjuj uchwyt tex
		glBindTexture(GL_TEXTURE_2D, tex); //Przetwarzaj uchwyt tex
		if (img.GetBPP() == 24) //Obrazek 24bit
			glTexImage2D(GL_TEXTURE_2D, 0, 3, img.GetWidth(), img.GetHeight(), 0,
				GL_RGB, GL_UNSIGNED_BYTE, img.GetImg());
		else if (img.GetBPP() == 32) //Obrazek 32bit
			glTexImage2D(GL_TEXTURE_2D, 0, 4, img.GetWidth(), img.GetHeight(), 0,
				GL_RGBA, GL_UNSIGNED_BYTE, img.GetImg());
		else {
			//Obrazek 16 albo 8 bit, takimi siê nie przejmujemy
		}
	}
	else {
		fprintf(stderr, "Error: failed to load texture\n");
	}
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

void DisplayableObject::LoadFromFile(string filePath)
{
	ObjFileParser ofp(filePath);
	model = ofp.Parse();
	geomVertices = new float[model.Vertices.size() * 3];
	geomTexCoords = new float[model.Uvs.size() * 2];
	geomNormals = new float[model.Normals.size() * 3];
	modelToArrays(&model, geomVertices, geomTexCoords, geomNormals);
	geomVertexCount = model.Vertices.size();
}