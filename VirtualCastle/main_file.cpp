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

float WindowWidth;
float WindowHeight;

DisplayableObject castle;
DisplayableObject grass;
DisplayableObject knight;
DisplayableObject roof;
DisplayableObject ceiling;
DisplayableObject armour;
DisplayableObject entrance;
DisplayableObject ghost;
DisplayableObject throne;
DisplayableObject table;
DisplayableObject wallpaper;

float knightSpeed = 1.5;
float ghostSpeed = 4;
int lastTime = 0;
int steps = 0;
float knightX = -1;
float ghostX = -1;
float ghostZ = 0;

void DisplayObjects()
{
	grass.Display();
	castle.Display();
	knight.Display();
	wallpaper.Display();
	roof.Display();
	ceiling.Display();
	armour.Display();
	entrance.Display();
	ghost.Display();
	throne.Display();
	table.Display();
}

void displayFrame(void) {
	glClearColor(0.57, 0.77, 0.71, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	float fovy = 50.0f;
	float aspect = WindowWidth/WindowHeight;
	float zNear = 1.0f;
	float zFar = 1000.0f;
	mat4 M = mat4(1.0f);
	mat4 V = lookAt(camera.observer, camera.center, camera.noseVector);
	mat4 P = perspective(fovy, aspect, zNear, zFar);
	
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixf(value_ptr(P));
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixf(value_ptr(V*M));

	GLfloat ambientColor[] = { 0.1f, 0.1f, 0.1f, 1.0f };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientColor);

	vec3 lightPos(2.0f, 10.0f, 51.0f);

	//Add positioned light
	GLfloat lightColor0[] = { 0.2f, 0.2f, 0.2f, 1.0f };
	GLfloat lightPos0[] = { 0.0f, 100.0f, 100.0f, 1.0f };
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor0);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos0);

	//Add directed light
	GLfloat lightColor1[] = { 0.5f, 0.2f, 0.2f, 1.0f };
	GLfloat lightPos1[] = { 30.0f, 5.0f, 5.0f, 0.0f };
	glLightfv(GL_LIGHT1, GL_DIFFUSE, lightColor1);
	glLightfv(GL_LIGHT1, GL_POSITION, lightPos1);
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, lightPos1);
	glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 128);
	glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 5);

	DisplayObjects();
	
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
	float knightStep = knightSpeed * interval / 1000.0;
	float ghostStep = ghostSpeed * interval / 1000.0;
	if (steps == 1)
	{
		ghostX = -1;
		ghostZ = 0;
	}
	if (steps == 500)
	{
		ghostX = 0;
		ghostZ = -1;
	}
	if (steps == 1000)
	{
		ghostX = 1;
		ghostZ = 0;
	}
	if (steps == 1500)
	{
		ghostX = 0;
		ghostZ = 1;
	}
	if (steps == 2000)
	{
		knightX *= -1;
		steps = 0;
	}
	knight.Move(vec3(knightX, 0, 0), knightStep);
	ghost.Move(vec3(ghostX, 0, ghostZ), ghostStep);
	steps++;
	glutPostRedisplay();
}

void reshape(int width, int height)
{
	glViewport(0, 0, width, height);
	WindowWidth = width;
	WindowHeight = height;
}

void LoadObjects()
{
	castle.LoadFromFile("castle.obj");
	castle.LoadTexture("Stone.tga");
	grass.LoadFromFile("ground.obj");
	grass.LoadTexture("Earth.tga");
	knight.LoadFromFile("Knight.obj");
	knight.LoadTexture("Metal.tga");
	roof.LoadFromFile("Roof.obj");
	roof.LoadTexture("Stone.tga");
	ceiling.LoadFromFile("Ceiling.obj");
	ceiling.LoadTexture("Wood.tga");
	
	armour.LoadFromFile("Armour.obj");
	armour.LoadTexture("Metal.tga");
	
	entrance.LoadFromFile("Entrance.obj");
	entrance.LoadTexture("Stone.tga");
	ghost.LoadFromFile("Ghost.obj");
	ghost.LoadTexture("Bedsheet.tga");
	throne.LoadFromFile("Throne.obj");
	throne.LoadTexture("Gold.tga");
	table.LoadFromFile("Table.obj");
	table.LoadTexture("Table.tga");
	wallpaper.LoadFromFile("wallpaper.obj");
	wallpaper.LoadTexture("fleurdelis-tile.tga");

}

int main(int argc, char** argv) {
	OpenGLHelper::initializeGLUT(&argc, argv);
	glutDisplayFunc(displayFrame);
	OpenGLHelper::initializeGLEW();
	glutIdleFunc(nextFrame);
	
	glutReshapeFunc(reshape);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);

	

	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);
	
	LoadObjects();

	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_TEXTURE_2D);

	glEnable(GL_NORMALIZE);
	glutSpecialFunc(keyDown);
	lastTime = glutGet(GLUT_ELAPSED_TIME);
	glutMainLoop();
	return 0;
}
