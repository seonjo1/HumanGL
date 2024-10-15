#ifndef CAMERA_H
# define CAMERA_H

# include "humanGL.h"

class Camera {
public:
	Camera() = default;
	void move(bool pressW, bool pressS, bool pressD,
			  bool pressA, bool pressE, bool pressQ);
	void rotate(glmath::vec2& pos);
	void saveCurrentPos(float x, float y);
	glmath::mat4 getViewMatrix();

private:
	float m_cameraPitch { 0.0f };
	float m_cameraYaw { 0.0f };
	glmath::vec2 m_prevMousePos { glmath::vec2(0.0f)};
	glmath::vec3 m_cameraPos {0.0f, 6.0f, 20.0f};
	glmath::vec3 m_cameraFront {0.0f, 0.0f, -1.0f};
	glmath::vec3 m_cameraUp {0.0f, 1.0f, 0.0f};
	const float m_cameraSpeed { 0.04f };
	const float m_cameraRotSpeed { 0.2f };
};

#endif