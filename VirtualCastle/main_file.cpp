#include "GL/glew.h"
#include "GL/glut.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include <stdio.h>
#include "ObjFileParser.h"
#include "ModelObjectDTO.h"

void displayFrame() {
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glutSwapBuffers();
}
void initializeGLUT(int* pargc, char** argv) {
	glutInit(pargc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(800, 800);
	glutCreateWindow("Program OpenGL");
	glutDisplayFunc(displayFrame);
}void initializeGLEW() {
	GLenum err = glewInit();
	if (GLEW_OK != err) {
		/* Problem: falied to initialize GLEW library. */
		fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
		exit(1);
	}
	fprintf(stdout, "Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));
}
int main(int argc, char** argv) {
	initializeGLUT(&argc, argv);
	initializeGLEW();
	ObjFileParser ofp("Cube.obj");
	ModelObjectDTO model = ofp.Parse();
	//Initializing code here
	glutMainLoop();
	//Resource releasing code here
}