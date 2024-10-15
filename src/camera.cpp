#include "../include/camera.h"

void Camera::rotate(glmath::vec2& pos) {
	glmath::vec2 deltaPos = pos - m_prevMousePos;

	m_cameraYaw -= deltaPos.x * m_cameraRotSpeed;
	m_cameraPitch -= deltaPos.y * m_cameraRotSpeed;

	if (m_cameraYaw < 0.0f) { m_cameraYaw += 360.0f; }
	if (m_cameraYaw > 360.0f) { m_cameraYaw -= 360.0f; }

	if (m_cameraPitch > 89.0f) { m_cameraPitch = 89.0f; }
	if (m_cameraPitch < -89.0f) { m_cameraPitch = -89.0f; }

	m_prevMousePos = pos;
}

void Camera::move(bool pressW, bool pressS, bool pressD,
					bool pressA, bool pressE, bool pressQ) {

	glmath::vec3 cameraRight = glmath::normalize(glmath::cross(m_cameraUp, -1 * m_cameraFront));
	glmath::vec3 cameraUp = glmath::normalize(glmath::cross(-1 * m_cameraFront, cameraRight));

	if (pressW) {
		m_cameraPos = m_cameraPos + m_cameraSpeed * m_cameraFront;
	}

	if (pressS) {
		m_cameraPos = m_cameraPos - m_cameraSpeed * m_cameraFront;
	}

	if (pressD) {
		m_cameraPos = m_cameraPos + m_cameraSpeed * cameraRight;
	}

	if (pressA) {
		m_cameraPos = m_cameraPos - m_cameraSpeed * cameraRight;
	}

	if (pressE) {
		m_cameraPos = m_cameraPos + m_cameraSpeed * cameraUp;
	}

	if (pressQ) {
		m_cameraPos = m_cameraPos - m_cameraSpeed * cameraUp;
	}
}

void Camera::saveCurrentPos(float x, float y) {
	m_prevMousePos = glmath::vec2((float)x, (float)y);
}

glmath::mat4 Camera::getViewMatrix() {
	glmath::vec3 eulerAngle(m_cameraPitch, m_cameraYaw, 0);
	glmath::vec4 cameraFront = glmath::mat4_cast(glmath::quat(eulerAngle)) * glmath::vec4(0.0f, 0.0f, -1.0f, 0.0f);
	m_cameraFront = glmath::vec3(cameraFront.x, cameraFront.y, cameraFront.z);
	
	return glmath::lookAt(m_cameraPos, m_cameraPos + m_cameraFront, m_cameraUp);
}
