#include <windows.h>
#include "GL/glew.h"
#include "gl\gl.h"
#include "GL/glut.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include <stdio.h>
#include "ObjFileParser.h"
#include "ModelObjectDTO.h"
#include <cmath>
#include <iostream>
#include "Camera.h"
#include "OpenGLHelper.h"
#include "tga.h"
#include "DisplayableObject.h"

using namespace std;
using namespace glm;

Camera camera;

DisplayableObject castle;
DisplayableObject grass;

void displayFrame(void) {
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	float fovy = 50.0f;
	float aspect = 1.0f;
	float zNear = 1.0f;
	float zFar = 1000.0f;
	mat4 M = mat4(1.0f);
	mat4 V = lookAt(camera.observer, camera.center, camera.noseVector);
	mat4 P = perspective(fovy, aspect, zNear, zFar);
	
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixf(value_ptr(P));
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixf(value_ptr(V*M));

	//glColor3d(0, 1, 0);

	grass.Display();
	castle.Display();
	
	glutSwapBuffers();
}

void keyDown(int c, int x, int y)
{
	switch (c)
	{
	case GLUT_KEY_RIGHT:
		camera.alpha += 2.0f;
		break;
	case GLUT_KEY_LEFT:
		camera.alpha -= 2.0f;
		break;
	case GLUT_KEY_UP:
		camera.stepForward();
		break;
	case GLUT_KEY_DOWN:
		camera.stepBack();
	}

	camera.determineCenterPoint();
	glutPostRedisplay();
}

int main(int argc, char** argv) {
	OpenGLHelper::initializeGLUT(&argc, argv);
	glutDisplayFunc(displayFrame);
	OpenGLHelper::initializeGLEW();
	
	//Initializing code here
	glEnable(GL_LIGHTING);			//TODO: przetestować 2 tryby cieniowania i przenieść do osobnej funkcji
	glEnable(GL_LIGHT0);
	//glShadeModel(GL_FLAT);
	glShadeModel(GL_SMOOTH);

	//TODO: ogarnąć Z-buffor:
	glEnable(GL_DEPTH_TEST);
	castle.LoadFromFile("castle.obj");
	castle.LoadTexture("fl1.tga");
	grass.geomVertices = new float[12]{
		-400,-20,400,400,-20,-400,-400,-20,400,400,-20,400
	};
	grass.geomTexCoords = new float[8] {0, 0, 1, 0, 1, 1, 0, 1};
	grass.geomNormals = new float[12]{ 0,1,0,0,1,0,0,1,0,0,1,0 };
	grass.geomVertexCount = 4;
	grass.LoadTexture("grass.tga");
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_TEXTURE_2D);

	glEnable(GL_NORMALIZE);
	glutSpecialFunc(keyDown);
	glutMainLoop();
	//Resource releasing code here
	return 0;
}
