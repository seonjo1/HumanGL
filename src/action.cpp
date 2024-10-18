#include "../include/action.h"

float Action::walkTheta = 0.0f;

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
	static const float rotateSpeed = 0.05f;
	static const float upperArmMax = 10.0f;
	static const float upperArmMin = 10.0f;
	static const float lowerArmMax = 5.0f;
	static const float lowerArmMin = 0.0f;
	static const float upperLegMax = 25.0f;
	static const float upperLegMin = 20.0f;
	static const float lowerLegMax = -10.0f;
	static const float lowerLegMin = 10.0f;
	static const float yMin = -0.2f;


	if (std::sin(Action::walkTheta) == 0 ) {
		return ~static_cast<int>(eAct::STOP);
	}

	float prevTheta = Action::walkTheta;

	if (std::tan(Action::walkTheta) > 0) {
		Action::walkTheta -= rotateSpeed;
	} else {
		Action::walkTheta += rotateSpeed;
	}

	if (std::sin(Action::walkTheta) * std::sin(prevTheta) < 0) {
		Action::walkTheta = 0.0f;
	}

	objectInfoList[ePart::BODY].translation.y = yMin * std::abs(std::sin(Action::walkTheta));

	if (Action::walkTheta < glmath::pi) {
		objectInfoList[ePart::LEFT_UPPER_ARM].currentAngle.x = std::sin(Action::walkTheta + glmath::pi) * upperArmMin;
		objectInfoList[ePart::RIGHT_UPPER_ARM].currentAngle.x = std::sin(Action::walkTheta) * upperArmMax;
		objectInfoList[ePart::LEFT_LOWER_ARM].currentAngle.x = std::sin(Action::walkTheta + glmath::pi) * lowerArmMin;
		objectInfoList[ePart::RIGHT_LOWER_ARM].currentAngle.x = std::sin(Action::walkTheta) * lowerArmMax;
		objectInfoList[ePart::LEFT_UPPER_LEG].currentAngle.x = std::sin(Action::walkTheta) * upperLegMax;
		objectInfoList[ePart::RIGHT_UPPER_LEG].currentAngle.x = std::sin(Action::walkTheta + glmath::pi) * upperLegMin;
		objectInfoList[ePart::LEFT_LOWER_LEG].currentAngle.x = std::sin(Action::walkTheta) * lowerLegMax;
		objectInfoList[ePart::RIGHT_LOWER_LEG].currentAngle.x = std::sin(Action::walkTheta + glmath::pi) * lowerLegMin;
	} else {
		objectInfoList[ePart::LEFT_UPPER_ARM].currentAngle.x = std::sin(Action::walkTheta + glmath::pi) * upperArmMax;
		objectInfoList[ePart::RIGHT_UPPER_ARM].currentAngle.x = std::sin(Action::walkTheta) * upperArmMin;
		objectInfoList[ePart::LEFT_LOWER_ARM].currentAngle.x = std::sin(Action::walkTheta + glmath::pi) * lowerArmMax;
		objectInfoList[ePart::RIGHT_LOWER_ARM].currentAngle.x = std::sin(Action::walkTheta) * lowerArmMin;
		objectInfoList[ePart::LEFT_UPPER_LEG].currentAngle.x = std::sin(Action::walkTheta) * upperLegMin;
		objectInfoList[ePart::RIGHT_UPPER_LEG].currentAngle.x = std::sin(Action::walkTheta + glmath::pi) * upperLegMax;
		objectInfoList[ePart::LEFT_LOWER_LEG].currentAngle.x = std::sin(Action::walkTheta) * lowerLegMin;
		objectInfoList[ePart::RIGHT_LOWER_LEG].currentAngle.x = std::sin(Action::walkTheta + glmath::pi) * lowerLegMax;
	}

	transformList[ePart::BODY].translation.y = objectInfoList[ePart::BODY].translation.y;

	transformList[ePart::LEFT_UPPER_ARM].rotation = glmath::quat(glmath::vec3(objectInfoList[ePart::LEFT_UPPER_ARM].currentAngle.x, 0.0f, 0.0f));
	transformList[ePart::RIGHT_UPPER_ARM].rotation = glmath::quat(glmath::vec3(objectInfoList[ePart::RIGHT_UPPER_ARM].currentAngle.x, 0.0f, 0.0f));
	transformList[ePart::LEFT_LOWER_ARM].rotation = glmath::quat(glmath::vec3(objectInfoList[ePart::LEFT_LOWER_ARM].currentAngle.x, 0.0f, 0.0f));
	transformList[ePart::RIGHT_LOWER_ARM].rotation = glmath::quat(glmath::vec3(objectInfoList[ePart::RIGHT_LOWER_ARM].currentAngle.x, 0.0f, 0.0f));

	transformList[ePart::LEFT_UPPER_LEG].rotation = glmath::quat(glmath::vec3(objectInfoList[ePart::LEFT_UPPER_LEG].currentAngle.x, 0.0f, 0.0f));
	transformList[ePart::RIGHT_UPPER_LEG].rotation = glmath::quat(glmath::vec3(objectInfoList[ePart::RIGHT_UPPER_LEG].currentAngle.x, 0.0f, 0.0f));
	transformList[ePart::LEFT_LOWER_LEG].rotation = glmath::quat(glmath::vec3(objectInfoList[ePart::LEFT_LOWER_LEG].currentAngle.x, 0.0f, 0.0f));
	transformList[ePart::RIGHT_LOWER_LEG].rotation = glmath::quat(glmath::vec3(objectInfoList[ePart::RIGHT_LOWER_LEG].currentAngle.x, 0.0f, 0.0f));

	return ~static_cast<int>(eAct::STOP);
}

int Rotate::doAction(std::map<ePart, Transform>& transformList, std::map<ePart, ObjectInfo>& objectInfoList) {
	static float rotateSpeed = glmath::radians(3.0f);

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
	static const float moveSpeed = 0.05f;
	static const float rotateSpeed = 0.05f;
	static const float upperArmMax = 10.0f;
	static const float upperArmMin = 10.0f;
	static const float lowerArmMax = 5.0f;
	static const float lowerArmMin = 0.0f;
	static const float upperLegMax = 25.0f;
	static const float upperLegMin = 20.0f;
	static const float lowerLegMax = -10.0f;
	static const float lowerLegMin = 10.0f;
	static const float yMin = -0.2f;

	Action::walkTheta += rotateSpeed;

	if (Action::walkTheta >= glmath::pi * 2.0f) {
		Action::walkTheta -= glmath::pi * 2.0f;
	}

	objectInfoList[ePart::BODY].translation = objectInfoList[ePart::BODY].translation + moveSpeed * objectInfoList[ePart::BODY].targetDirection;
	objectInfoList[ePart::BODY].translation.y = yMin * std::abs(std::sin(Action::walkTheta));

	if (Action::walkTheta < glmath::pi) {
		objectInfoList[ePart::LEFT_UPPER_ARM].currentAngle.x = std::sin(Action::walkTheta + glmath::pi) * upperArmMin;
		objectInfoList[ePart::RIGHT_UPPER_ARM].currentAngle.x = std::sin(Action::walkTheta) * upperArmMax;
		objectInfoList[ePart::LEFT_LOWER_ARM].currentAngle.x = std::sin(Action::walkTheta + glmath::pi) * lowerArmMin;
		objectInfoList[ePart::RIGHT_LOWER_ARM].currentAngle.x = std::sin(Action::walkTheta) * lowerArmMax;
		objectInfoList[ePart::LEFT_UPPER_LEG].currentAngle.x = std::sin(Action::walkTheta) * upperLegMax;
		objectInfoList[ePart::RIGHT_UPPER_LEG].currentAngle.x = std::sin(Action::walkTheta + glmath::pi) * upperLegMin;
		objectInfoList[ePart::LEFT_LOWER_LEG].currentAngle.x = std::sin(Action::walkTheta) * lowerLegMax;
		objectInfoList[ePart::RIGHT_LOWER_LEG].currentAngle.x = std::sin(Action::walkTheta + glmath::pi) * lowerLegMin;
	} else {
		objectInfoList[ePart::LEFT_UPPER_ARM].currentAngle.x = std::sin(Action::walkTheta + glmath::pi) * upperArmMax;
		objectInfoList[ePart::RIGHT_UPPER_ARM].currentAngle.x = std::sin(Action::walkTheta) * upperArmMin;
		objectInfoList[ePart::LEFT_LOWER_ARM].currentAngle.x = std::sin(Action::walkTheta + glmath::pi) * lowerArmMax;
		objectInfoList[ePart::RIGHT_LOWER_ARM].currentAngle.x = std::sin(Action::walkTheta) * lowerArmMin;
		objectInfoList[ePart::LEFT_UPPER_LEG].currentAngle.x = std::sin(Action::walkTheta) * upperLegMin;
		objectInfoList[ePart::RIGHT_UPPER_LEG].currentAngle.x = std::sin(Action::walkTheta + glmath::pi) * upperLegMax;
		objectInfoList[ePart::LEFT_LOWER_LEG].currentAngle.x = std::sin(Action::walkTheta) * lowerLegMin;
		objectInfoList[ePart::RIGHT_LOWER_LEG].currentAngle.x = std::sin(Action::walkTheta + glmath::pi) * lowerLegMax;
	}


	transformList[ePart::BODY].translation = objectInfoList[ePart::BODY].translation;
	transformList[ePart::BODY].translation.y = objectInfoList[ePart::BODY].translation.y;

	transformList[ePart::LEFT_UPPER_ARM].rotation = glmath::quat(glmath::vec3(objectInfoList[ePart::LEFT_UPPER_ARM].currentAngle.x, 0.0f, 0.0f));
	transformList[ePart::RIGHT_UPPER_ARM].rotation = glmath::quat(glmath::vec3(objectInfoList[ePart::RIGHT_UPPER_ARM].currentAngle.x, 0.0f, 0.0f));
	transformList[ePart::LEFT_LOWER_ARM].rotation = glmath::quat(glmath::vec3(objectInfoList[ePart::LEFT_LOWER_ARM].currentAngle.x, 0.0f, 0.0f));
	transformList[ePart::RIGHT_LOWER_ARM].rotation = glmath::quat(glmath::vec3(objectInfoList[ePart::RIGHT_LOWER_ARM].currentAngle.x, 0.0f, 0.0f));

	transformList[ePart::LEFT_UPPER_LEG].rotation = glmath::quat(glmath::vec3(objectInfoList[ePart::LEFT_UPPER_LEG].currentAngle.x, 0.0f, 0.0f));
	transformList[ePart::RIGHT_UPPER_LEG].rotation = glmath::quat(glmath::vec3(objectInfoList[ePart::RIGHT_UPPER_LEG].currentAngle.x, 0.0f, 0.0f));
	transformList[ePart::LEFT_LOWER_LEG].rotation = glmath::quat(glmath::vec3(objectInfoList[ePart::LEFT_LOWER_LEG].currentAngle.x, 0.0f, 0.0f));
	transformList[ePart::RIGHT_LOWER_LEG].rotation = glmath::quat(glmath::vec3(objectInfoList[ePart::RIGHT_LOWER_LEG].currentAngle.x, 0.0f, 0.0f));
	return ~static_cast<int>(eAct::WALK);
}
