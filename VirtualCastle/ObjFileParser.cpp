#include "ObjFileParser.h"
#include <iostream>

using namespace std;

ObjFileParser::ObjFileParser()
{
}

ObjFileParser::ObjFileParser(std::string filePath)
{
	_filePath = filePath;
}


ObjFileParser::~ObjFileParser()
{
}

ModelObjectDTO ObjFileParser::Parse()
{
	vector < vector<float> > out_vertices;
	vector < vector<float> > out_uvs;
	vector < vector<float> > out_normals;
	vector< unsigned int > vertexIndices, uvIndices, normalIndices;
	vector< vector<float> > temp_vertices;
	vector< vector<float> > temp_uvs;
	vector< vector<float> > temp_normals;

	FILE * file;
	fopen_s(&file, _filePath.c_str(), "r");
	if (file == NULL)
	{
		printf("Impossible to open the file !\n");
		//return null;							//TODO: jak zwróciæ null w tym chorym jêzyku?
	}

	while (1)
	{

		char lineHeader[128];
		// read the first word of the line
		int res = fscanf_s(file, "%s", lineHeader, 128);
		if (res == EOF)
			break; // EOF = End Of File. Quit the loop.

				   // else : parse lineHeader

		if (strcmp(lineHeader, "v") == 0)
		{
			std::vector<float> vertex;
			vertex.push_back(0);
			vertex.push_back(0);
			vertex.push_back(0);
			fscanf_s(file, "%f %f %f\n", &vertex[0], &vertex[1], &vertex[2]);
			temp_vertices.push_back(vertex);
		}
		else if (strcmp(lineHeader, "vt") == 0) {
			std::vector<float> uv;
			uv.push_back(0);
			uv.push_back(0);
			fscanf_s(file, "%f %f\n", &uv[0], &uv[1]);
			temp_uvs.push_back(uv);
		}
		else if (strcmp(lineHeader, "vn") == 0) {
			std::vector<float> normal;
			normal.push_back(0);
			normal.push_back(0);
			normal.push_back(0);
			fscanf_s(file, "%f %f %f\n", &normal[0], &normal[1], &normal[2]);
			temp_normals.push_back(normal);
		}
		else if (strcmp(lineHeader, "f") == 0)
		{
			std::string vertex1, vertex2, vertex3;
			int vertexIndex[3], uvIndex[3], normalIndex[3];
			int matches = fscanf_s(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2]);
			if (matches != 9)
			{
				printf("File can't be read by our simple parser : ( Try exporting with other options\n");
				//return null;						//TODO
			}

			if (vertexIndex[0] > 0)
			{
				vertexIndices.push_back(vertexIndex[0]);
				vertexIndices.push_back(vertexIndex[1]);
				vertexIndices.push_back(vertexIndex[2]);
				uvIndices.push_back(uvIndex[0]);
				uvIndices.push_back(uvIndex[1]);
				uvIndices.push_back(uvIndex[2]);
				normalIndices.push_back(normalIndex[0]);
				normalIndices.push_back(normalIndex[1]);
				normalIndices.push_back(normalIndex[2]);
			}
		}
		else
		{
			// Probably a comment, eat up the rest of the line
			char stupidBuffer[1000];
			fgets(stupidBuffer, 1000, file);
		}
	}
	fclose(file);
	// For each vertex of each triangle
	for (unsigned int i = 0; i < vertexIndices.size(); i++)
	{
		unsigned int vertexIndex = vertexIndices[i];
		vector <float> vertex;
		vertex.push_back(0);
		vertex.push_back(0);
		vertex.push_back(0);
		if (vertexIndex > temp_vertices.size()) cout << vertexIndex;
		vertex = temp_vertices[vertexIndex - 1];
		out_vertices.push_back(vertex);
	}

	for (unsigned int i = 0; i < normalIndices.size(); i++)
	{
		unsigned int normalIndex = normalIndices[i];
		vector <float> normals;
		normals.push_back(0);
		normals.push_back(0);
		normals.push_back(0);
		normals = temp_normals[normalIndex - 1];
		out_normals.push_back(normals);
	}

	for (unsigned int i = 0; i < uvIndices.size(); i++)
	{
		unsigned int uvIndex = uvIndices[i];
		vector<float> uvs;
		uvs.push_back(0);
		uvs.push_back(0);
		uvs = temp_uvs[uvIndex - 1];
		out_uvs.push_back(uvs);
	}
	return ModelObjectDTO(out_vertices, out_uvs, out_normals);
}
