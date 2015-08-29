#include "Camera.h"



Camera::Camera()
{
	float distanceFromCenter = 40;
	center = vec3(0.0f, 0.0f, 0.0f);
	observer = vec3(0.0f, 0.0f, distanceFromCenter * centerRadius);
	noseVector = vec3(0.0f, 1.0f, 0.0f);
	alpha = 0.0f;
}


Camera::~Camera()
{
}

void Camera::determineCenterPoint(){	center.x = observer.x + centerRadius * sin(radians(alpha));	center.z = observer.z - centerRadius * cos(radians(alpha));}void Camera::stepForward(){	observer.x += (center.x - observer.x) / centerRadius;	observer.z += (center.z - observer.z) / centerRadius;}void Camera::stepBack(){	observer.x -= (center.x - observer.x) / centerRadius;	observer.z -= (center.z - observer.z) / centerRadius;}