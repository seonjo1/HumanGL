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

int Stop::doAction(std::map<ePart, Transform>& transformList, std::map<ePart, ObjectInfo>& objectInfoList) {
	return static_cast<int>(eAct::FULLBIT);
}

int Rotate::doAction(std::map<ePart, Transform>& transformList, std::map<ePart, ObjectInfo>& objectInfoList) {
	static float rotateSpeed = glmath::radians(5.0f);
	
	if (glmath::cross(objectInfoList[ePart::BODY].currentDirection, objectInfoList[ePart::BODY].targetDirection).y >= 0) {
		objectInfoList[ePart::BODY].currentDirection = glmath::rotate(glmath::mat4(1.0f), rotateSpeed, glmath::vec3(0.0f, 1.0f, 0.0f)) * glmath::vec4(objectInfoList[ePart::BODY].currentDirection, 0.0f);
		if (glmath::cross(objectInfoList[ePart::BODY].currentDirection, objectInfoList[ePart::BODY].targetDirection).y < 0) {
			objectInfoList[ePart::BODY].currentDirection = objectInfoList[ePart::BODY].targetDirection;
		}
	} else {
		objectInfoList[ePart::BODY].currentDirection = glmath::rotate(glmath::mat4(1.0f), -rotateSpeed, glmath::vec3(0.0f, 1.0f, 0.0f)) * glmath::vec4(objectInfoList[ePart::BODY].currentDirection, 0.0f);
		if (glmath::cross(objectInfoList[ePart::BODY].currentDirection, objectInfoList[ePart::BODY].targetDirection).y > 0) {
			objectInfoList[ePart::BODY].currentDirection = objectInfoList[ePart::BODY].targetDirection;
		}
	}

	objectInfoList[ePart::BODY].currentAngle.y = std::atan2(-objectInfoList[ePart::BODY].currentDirection.x, -objectInfoList[ePart::BODY].currentDirection.z);

	if (objectInfoList[ePart::BODY].currentAngle.y < 0) { objectInfoList[ePart::BODY].currentAngle.y += 2 * glmath::pi; }
	if (objectInfoList[ePart::BODY].currentAngle.y > glmath::pi * 2) { objectInfoList[ePart::BODY].currentAngle.y -= 2 * glmath::pi; }

	transformList[ePart::BODY].rotation = glmath::quat(glmath::vec3(0.0f, 1.0f, 0.0f), objectInfoList[ePart::BODY].currentAngle.y);

	return ~static_cast<int>(eAct::ROTATE);
}

int Jump::doAction(std::map<ePart, Transform>& transformList, std::map<ePart, ObjectInfo>& objectInfoList) {
	return ~static_cast<int>(eAct::JUMP);
}

int Walk::doAction(std::map<ePart, Transform>& transformList, std::map<ePart, ObjectInfo>& objectInfoList) {
	static float moveSpeed = 0.1f;

	objectInfoList[ePart::BODY].translation = objectInfoList[ePart::BODY].translation + moveSpeed * objectInfoList[ePart::BODY].targetDirection;
	transformList[ePart::BODY].translation = objectInfoList[ePart::BODY].translation;

	return ~static_cast<int>(eAct::WALK);
}

