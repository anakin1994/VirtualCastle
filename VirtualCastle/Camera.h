#pragma once
#include <windows.h>
#include "GL/glew.h"
#include "gl\gl.h"
#include "GL/glut.h"
#include "glm/glm.hpp"

using namespace glm;
class Camera
{
public:
	const float centerRadius = 10.0f;
	vec3 center;
	vec3 observer;
	vec3 noseVector;
	float alpha;
	Camera();
	~Camera();
	void determineCenterPoint();
	void stepForward();
	void stepBack();
};

