#include "../include/action.h"

int operator&(int bit, eAct act) {
	return bit & static_cast<int>(act);
}

int operator|(int bit, eAct act) {
	return bit | static_cast<int>(act);
}

bool operator==(int bit, eAct act) {
	return bit == static_cast<int>(act);
}

Transform operator*(const Transform& t1, const Transform& t2) {
	Transform transform;

	transform.translation = t1.translation * t2.translation;
	transform.rotation = t1.rotation * t2.rotation;
	transform.scale = t1.scale * t2.scale;

	return transform;
}

int Stop::doAction(std::map<ePart, Transform>& transformList, ObjectInfo& objinfo) {
	return static_cast<int>(eAct::FULLBIT);
}

int Rotate::doAction(std::map<ePart, Transform>& transformList, ObjectInfo& objectInfo) {
	static float rotateSpeed = glmath::radians(1.0f);
	
	if (glmath::cross(objectInfo.direction, objectInfo.destDirection).y >= 0) {
		objectInfo.direction = glmath::rotate(glmath::mat4(1.0f), rotateSpeed, glmath::vec3(0.0f, 1.0f, 0.0f)) * glmath::vec4(objectInfo.direction, 0.0f);
		if (glmath::cross(objectInfo.direction, objectInfo.destDirection).y < 0) {
			objectInfo.direction = objectInfo.destDirection;
		}
	} else {
		objectInfo.direction = glmath::rotate(glmath::mat4(1.0f), -rotateSpeed, glmath::vec3(0.0f, 1.0f, 0.0f)) * glmath::vec4(objectInfo.direction, 0.0f);
		if (glmath::cross(objectInfo.direction, objectInfo.destDirection).y > 0) {
			objectInfo.direction = objectInfo.destDirection;
		}
	}

	objectInfo.yaw = std::atan2(-objectInfo.direction.x, -objectInfo.direction.z);

	if (objectInfo.yaw < 0) { objectInfo.yaw += 2 * glmath::pi; }
	if (objectInfo.yaw > glmath::pi * 2) { objectInfo.yaw -= 2 * glmath::pi; }

	transformList[ePart::BODY].rotation = glmath::quat(glmath::vec3(0.0f, 1.0f, 0.0f), objectInfo.yaw);

	return ~static_cast<int>(eAct::ROTATE);
}

int Jump::doAction(std::map<ePart, Transform>& transformList, ObjectInfo& objinfo) {
	return ~static_cast<int>(eAct::JUMP);
}

int Walk::doAction(std::map<ePart, Transform>& transformList, ObjectInfo& objinfo) {
	static float moveeSpeed = 0.1f;

	return ~static_cast<int>(eAct::WALK);
}

