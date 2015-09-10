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

float speed = 30;
int lastTime = 0;
int steps = 0;
float sgn = 1.0f;

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

void nextFrame(void)
{
	int actTime = glutGet(GLUT_ELAPSED_TIME);
	int interval = actTime - lastTime;
	lastTime = actTime;
	float step = speed*interval / 1000.0;
	if (steps == 1000)
	{
		sgn *= -1;
		steps = 0;
	}
	castle.Move(vec3(sgn, 0, 0), step);
	steps++;
	glutPostRedisplay();
}

int main(int argc, char** argv) {
	OpenGLHelper::initializeGLUT(&argc, argv);
	glutDisplayFunc(displayFrame);
	OpenGLHelper::initializeGLEW();
	glutIdleFunc(nextFrame);
	
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
	lastTime = glutGet(GLUT_ELAPSED_TIME);
	glutMainLoop();
	//Resource releasing code here
	return 0;
}
