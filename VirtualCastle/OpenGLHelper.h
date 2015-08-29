#pragma once
#include <windows.h>
#include "GL/glew.h"
#include "gl\gl.h"
#include "GL/glut.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include <stdio.h>
class OpenGLHelper
{
public:
	OpenGLHelper();
	~OpenGLHelper();
	static void initializeGLUT(int* pargc, char** argv);
	static void initializeGLEW();
};

