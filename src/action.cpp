#include "../include/action.h"

float Action::walkTheta = 0.0f;
float Action::breathTheta = 0.0f;
float Action::landTheta = 0.0f;
float Action::jumpTime = 0.0f;
float Action::frameTime = 0.1f;


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
	static const float moveSpeed = 0.05f;
	static const float breateSpeed = 0.025f;
	static const float rotateSpeed = 0.05f;
	static const float upperArmMax = 20.0f;
	static const float upperArmMin = 20.0f;
	static const float lowerArmMax = 10.0f;
	static const float lowerArmMin = 0.0f;
	static const float upperLegMax = 25.0f;
	static const float upperLegMin = 20.0f;
	static const float lowerLegMax = -10.0f;
	static const float lowerLegMin = 10.0f;
	static const float yMin = -0.3f;
	static const float breath = 0.01f;

	objectInfoList[ePart::PELVIS].velocity = (moveSpeed * std::abs(std::sin(walkTheta)));
	objectInfoList[ePart::PELVIS].translation = objectInfoList[ePart::PELVIS].translation + objectInfoList[ePart::PELVIS].targetDirection * objectInfoList[ePart::PELVIS].velocity;

	if (std::sin(walkTheta) == 0 ) {
		Action::breathTheta += breateSpeed;
		if (Action::breathTheta >= glmath::pi * 2) {
			Action::breathTheta = Action::breathTheta - glmath::pi * 2;
		}
		objectInfoList[ePart::BODY].scale = 1.0f + breath * std::sin(Action::breathTheta);
		objectInfoList[ePart::LEFT_SLEEVE].scale = 1.0f + (breath * 1.2) * std::sin(Action::breathTheta);
		objectInfoList[ePart::RIGHT_SLEEVE].scale = 1.0f + (breath * 1.2) * std::sin(Action::breathTheta);

		transformList[ePart::PELVIS].scale = 1.0f;
		transformList[ePart::BODY].scale = objectInfoList[ePart::BODY].scale;
		transformList[ePart::LEFT_SLEEVE].scale = objectInfoList[ePart::LEFT_SLEEVE].scale;
		transformList[ePart::RIGHT_SLEEVE].scale = objectInfoList[ePart::RIGHT_SLEEVE].scale;
		return ~static_cast<int>(eAct::STOP);
	} else {
		Action::breathTheta = 0.0f;
		transformList[ePart::BODY].scale = 1.0f;
		transformList[ePart::LEFT_SLEEVE].scale = 1.0f;
		transformList[ePart::RIGHT_SLEEVE].scale = 1.0f;
	}

	float prevTheta = walkTheta;

	if (std::tan(walkTheta) > 0) {
		walkTheta -= rotateSpeed;
	} else {
		walkTheta += rotateSpeed;
	}

	if (std::sin(walkTheta) * std::sin(prevTheta) < 0) {
		walkTheta = 0.0f;
	}

	objectInfoList[ePart::PELVIS].velocity = moveSpeed * std::abs(std::sin(walkTheta));
	objectInfoList[ePart::PELVIS].translation.y = yMin * std::abs(std::sin(walkTheta));

	if (walkTheta < glmath::pi) {
		objectInfoList[ePart::LEFT_UPPER_ARM].currentAngle.x = std::sin(walkTheta + glmath::pi) * upperArmMin;
		objectInfoList[ePart::RIGHT_UPPER_ARM].currentAngle.x = std::sin(walkTheta) * upperArmMax;
		objectInfoList[ePart::LEFT_LOWER_ARM].currentAngle.x = std::sin(walkTheta + glmath::pi) * lowerArmMin;
		objectInfoList[ePart::RIGHT_LOWER_ARM].currentAngle.x = std::sin(walkTheta) * lowerArmMax;
		objectInfoList[ePart::LEFT_UPPER_LEG].currentAngle.x = std::sin(walkTheta) * upperLegMax;
		objectInfoList[ePart::RIGHT_UPPER_LEG].currentAngle.x = std::sin(walkTheta + glmath::pi) * upperLegMin;
		objectInfoList[ePart::LEFT_LOWER_LEG].currentAngle.x = std::sin(walkTheta) * lowerLegMax;
		objectInfoList[ePart::RIGHT_LOWER_LEG].currentAngle.x = std::sin(walkTheta + glmath::pi) * lowerLegMin;
	} else {
		objectInfoList[ePart::LEFT_UPPER_ARM].currentAngle.x = std::sin(walkTheta + glmath::pi) * upperArmMax;
		objectInfoList[ePart::RIGHT_UPPER_ARM].currentAngle.x = std::sin(walkTheta) * upperArmMin;
		objectInfoList[ePart::LEFT_LOWER_ARM].currentAngle.x = std::sin(walkTheta + glmath::pi) * lowerArmMax;
		objectInfoList[ePart::RIGHT_LOWER_ARM].currentAngle.x = std::sin(walkTheta) * lowerArmMin;
		objectInfoList[ePart::LEFT_UPPER_LEG].currentAngle.x = std::sin(walkTheta) * upperLegMin;
		objectInfoList[ePart::RIGHT_UPPER_LEG].currentAngle.x = std::sin(walkTheta + glmath::pi) * upperLegMax;
		objectInfoList[ePart::LEFT_LOWER_LEG].currentAngle.x = std::sin(walkTheta) * lowerLegMin;
		objectInfoList[ePart::RIGHT_LOWER_LEG].currentAngle.x = std::sin(walkTheta + glmath::pi) * lowerLegMax;
	}

	transformList[ePart::PELVIS].translation = objectInfoList[ePart::PELVIS].translation;
	transformList[ePart::PELVIS].translation.y = objectInfoList[ePart::PELVIS].translation.y;
	transformList[ePart::PELVIS].scale = 1.0f;

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

	if (glmath::cross(objectInfoList[ePart::PELVIS].currentDirection, objectInfoList[ePart::PELVIS].targetDirection).y >= 0) {
		objectInfoList[ePart::PELVIS].currentDirection = glmath::rotate(glmath::mat4(1.0f), rotateSpeed, glmath::vec3(0.0f, 1.0f, 0.0f)) * glmath::vec4(objectInfoList[ePart::PELVIS].currentDirection, 0.0f);
		if (glmath::cross(objectInfoList[ePart::PELVIS].currentDirection, objectInfoList[ePart::PELVIS].targetDirection).y < 0) {
			objectInfoList[ePart::PELVIS].currentDirection = objectInfoList[ePart::PELVIS].targetDirection;
		}
	} else {
		objectInfoList[ePart::PELVIS].currentDirection = glmath::rotate(glmath::mat4(1.0f), -rotateSpeed, glmath::vec3(0.0f, 1.0f, 0.0f)) * glmath::vec4(objectInfoList[ePart::PELVIS].currentDirection, 0.0f);
		if (glmath::cross(objectInfoList[ePart::PELVIS].currentDirection, objectInfoList[ePart::PELVIS].targetDirection).y > 0) {
			objectInfoList[ePart::PELVIS].currentDirection = objectInfoList[ePart::PELVIS].targetDirection;
		}
	}

	objectInfoList[ePart::PELVIS].currentAngle.y = std::atan2(-objectInfoList[ePart::PELVIS].currentDirection.x, -objectInfoList[ePart::PELVIS].currentDirection.z);

	if (objectInfoList[ePart::PELVIS].currentAngle.y < 0) { objectInfoList[ePart::PELVIS].currentAngle.y += 2 * glmath::pi; }
	if (objectInfoList[ePart::PELVIS].currentAngle.y > glmath::pi * 2) { objectInfoList[ePart::PELVIS].currentAngle.y -= 2 * glmath::pi; }

	transformList[ePart::PELVIS].rotation = glmath::quat(glmath::vec3(0.0f, 1.0f, 0.0f), objectInfoList[ePart::PELVIS].currentAngle.y);

	return ~static_cast<int>(eAct::ROTATE);
}

int Jump::doAction(std::map<ePart, Transform>& transformList, std::map<ePart, ObjectInfo>& objectInfoList) {
	static const float gravity = 0.1f;
	static const float jumpVelocity = 1.1f;
	static const float jumpPelvisMax = -20.0f;
	static const float jumpBodyMax = 5.0f;
	static const float jumpUpperArmMax[2] = { 60.0f, 50.0f };
	static const float jumpLowerArmMax[2] = { 40.0f, 10.0f };
	static const float jumpUpperLegMax[2] = { 90.0f, 60.0f };
	static const float jumpLowerLegMax[2] = { -110.0f, -80.0f };

	int left = 0;
	int right = 1;

	if (walkTheta > glmath::pi) {
		left = 1;
		right = 0;
	}

	jumpTime += frameTime;
	float jumpTheta[2] = { std::max(0.0f, std::min(glmath::pi * (gravity / (2 * jumpVelocity)) * jumpTime + glmath::pi * 0.2f , glmath::pi)),
						   std::min(glmath::pi * (gravity / (2 * jumpVelocity)) * jumpTime, glmath::pi)};
	if (jumpTheta[1] <= glmath::pi * 0.2f) {
		jumpTheta[0] = jumpTheta[1] * 2.0f;
	}
	objectInfoList[ePart::PELVIS].velocity.y = jumpVelocity - gravity * jumpTime;
	objectInfoList[ePart::PELVIS].translation.y += objectInfoList[ePart::PELVIS].velocity.y * frameTime;
	objectInfoList[ePart::PELVIS].translation.x += objectInfoList[ePart::PELVIS].velocity.x * objectInfoList[ePart::PELVIS].targetDirection.x;
	objectInfoList[ePart::PELVIS].translation.z += objectInfoList[ePart::PELVIS].velocity.z * objectInfoList[ePart::PELVIS].targetDirection.z;

	objectInfoList[ePart::PELVIS].actionAngle.x = jumpPelvisMax * std::sin(jumpTheta[0]);
	objectInfoList[ePart::BODY].actionAngle.x = jumpBodyMax * std::sin(jumpTheta[0]);
	objectInfoList[ePart::LEFT_UPPER_ARM].actionAngle.z = -jumpUpperArmMax[left] * std::sin(jumpTheta[left]);
	objectInfoList[ePart::RIGHT_UPPER_ARM].actionAngle.z = jumpUpperArmMax[right] * std::sin(jumpTheta[right]);
	objectInfoList[ePart::LEFT_LOWER_ARM].actionAngle.x = jumpLowerArmMax[left] * std::sin(jumpTheta[left]);
	objectInfoList[ePart::RIGHT_LOWER_ARM].actionAngle.x = jumpLowerArmMax[right] * std::sin(jumpTheta[right]);
	objectInfoList[ePart::LEFT_UPPER_LEG].actionAngle.x = jumpUpperLegMax[left] * std::sin(jumpTheta[left]);
	objectInfoList[ePart::RIGHT_UPPER_LEG].actionAngle.x = jumpUpperLegMax[right] * std::sin(jumpTheta[right]);
	objectInfoList[ePart::LEFT_LOWER_LEG].actionAngle.x = jumpLowerLegMax[left] * std::sin(jumpTheta[left]);
	objectInfoList[ePart::RIGHT_LOWER_LEG].actionAngle.x = jumpLowerLegMax[right] * std::sin(jumpTheta[right]);

	if (objectInfoList[ePart::PELVIS].velocity.y <= -jumpVelocity) {
		jumpTime = 0.0f;
		objectInfoList[ePart::PELVIS].translation.y = 0.0f;
		objectInfoList[ePart::PELVIS].velocity.y = 0.0f;

		return ~static_cast<int>(eAct::JUMP);
	}

	transformList[ePart::PELVIS].rotation = glmath::quat(glmath::vec3(objectInfoList[ePart::PELVIS].currentAngle.x + objectInfoList[ePart::PELVIS].actionAngle.x, 0.0f, 0.0f)) * transformList[ePart::PELVIS].rotation;
	transformList[ePart::PELVIS].translation = objectInfoList[ePart::PELVIS].translation;
	transformList[ePart::BODY].rotation = glmath::quat(glmath::vec3(objectInfoList[ePart::BODY].currentAngle.x + objectInfoList[ePart::BODY].actionAngle.x, 0.0f, 0.0f));


	transformList[ePart::LEFT_UPPER_ARM].rotation = glmath::quat(glmath::vec3(0.0f, 0.0f, objectInfoList[ePart::LEFT_UPPER_ARM].currentAngle.z + objectInfoList[ePart::LEFT_UPPER_ARM].actionAngle.z));
	transformList[ePart::RIGHT_UPPER_ARM].rotation = glmath::quat(glmath::vec3(0.0f, 0.0f, objectInfoList[ePart::RIGHT_UPPER_ARM].currentAngle.z + objectInfoList[ePart::RIGHT_UPPER_ARM].actionAngle.z));
	transformList[ePart::LEFT_LOWER_ARM].rotation = glmath::quat(glmath::vec3(objectInfoList[ePart::LEFT_LOWER_ARM].currentAngle.x + objectInfoList[ePart::LEFT_LOWER_ARM].actionAngle.x, 0.0f, 0.0f));
	transformList[ePart::RIGHT_LOWER_ARM].rotation = glmath::quat(glmath::vec3(objectInfoList[ePart::RIGHT_LOWER_ARM].currentAngle.x + objectInfoList[ePart::RIGHT_LOWER_ARM].actionAngle.x, 0.0f, 0.0f));

	transformList[ePart::LEFT_UPPER_LEG].rotation = glmath::quat(glmath::vec3(objectInfoList[ePart::LEFT_UPPER_LEG].currentAngle.x + objectInfoList[ePart::LEFT_UPPER_LEG].actionAngle.x, 0.0f, 0.0f));
	transformList[ePart::RIGHT_UPPER_LEG].rotation = glmath::quat(glmath::vec3(objectInfoList[ePart::RIGHT_UPPER_LEG].currentAngle.x + objectInfoList[ePart::RIGHT_UPPER_LEG].actionAngle.x, 0.0f, 0.0f));
	transformList[ePart::LEFT_LOWER_LEG].rotation = glmath::quat(glmath::vec3(objectInfoList[ePart::LEFT_LOWER_LEG].currentAngle.x + objectInfoList[ePart::LEFT_LOWER_LEG].actionAngle.x, 0.0f, 0.0f));
	transformList[ePart::RIGHT_LOWER_LEG].rotation = glmath::quat(glmath::vec3(objectInfoList[ePart::RIGHT_LOWER_LEG].currentAngle.x + objectInfoList[ePart::RIGHT_LOWER_LEG].actionAngle.x, 0.0f, 0.0f));
	
	return static_cast<int>(eAct::FULLBIT);
}

int Walk::doAction(std::map<ePart, Transform>& transformList, std::map<ePart, ObjectInfo>& objectInfoList) {
	static const float moveSpeed = 0.05f;
	static const float amplitude = 0.01f;
	static const float rotateSpeed = 0.04f;
	static const float upperArmMax = 20.0f;
	static const float upperArmMin = 20.0f;
	static const float lowerArmMax = 5.0f;
	static const float lowerArmMin = 0.0f;
	static const float upperLegMax = 25.0f;
	static const float upperLegMin = 20.0f;
	static const float lowerLegMax = -10.0f;
	static const float lowerLegMin = 10.0f;
	static const float yMin = -0.3f;

	walkTheta += rotateSpeed;

	if (walkTheta >= glmath::pi * 2.0f) {
		walkTheta -= glmath::pi * 2.0f;
	}
	
	if (glmath::length(objectInfoList[ePart::PELVIS].velocity) < moveSpeed) {
		objectInfoList[ePart::PELVIS].velocity = (moveSpeed * std::abs(std::sin(walkTheta)));
	} else {
		objectInfoList[ePart::PELVIS].velocity = (moveSpeed + amplitude * std::abs(std::sin(walkTheta)));
	}
	objectInfoList[ePart::PELVIS].translation = objectInfoList[ePart::PELVIS].translation + objectInfoList[ePart::PELVIS].targetDirection * objectInfoList[ePart::PELVIS].velocity;
	objectInfoList[ePart::PELVIS].translation.y = yMin * std::abs(std::sin(walkTheta));

	if (walkTheta < glmath::pi) {
		objectInfoList[ePart::LEFT_UPPER_ARM].currentAngle.x = std::sin(walkTheta + glmath::pi) * upperArmMin;
		objectInfoList[ePart::RIGHT_UPPER_ARM].currentAngle.x = std::sin(walkTheta) * upperArmMax;
		objectInfoList[ePart::LEFT_LOWER_ARM].currentAngle.x = std::sin(walkTheta + glmath::pi) * lowerArmMin;
		objectInfoList[ePart::RIGHT_LOWER_ARM].currentAngle.x = std::sin(walkTheta) * lowerArmMax;
		objectInfoList[ePart::LEFT_UPPER_LEG].currentAngle.x = std::sin(walkTheta) * upperLegMax;
		objectInfoList[ePart::RIGHT_UPPER_LEG].currentAngle.x = std::sin(walkTheta + glmath::pi) * upperLegMin;
		objectInfoList[ePart::LEFT_LOWER_LEG].currentAngle.x = std::sin(walkTheta) * lowerLegMax;
		objectInfoList[ePart::RIGHT_LOWER_LEG].currentAngle.x = std::sin(walkTheta + glmath::pi) * lowerLegMin;
	} else {
		objectInfoList[ePart::LEFT_UPPER_ARM].currentAngle.x = std::sin(walkTheta + glmath::pi) * upperArmMax;
		objectInfoList[ePart::RIGHT_UPPER_ARM].currentAngle.x = std::sin(walkTheta) * upperArmMin;
		objectInfoList[ePart::LEFT_LOWER_ARM].currentAngle.x = std::sin(walkTheta + glmath::pi) * lowerArmMax;
		objectInfoList[ePart::RIGHT_LOWER_ARM].currentAngle.x = std::sin(walkTheta) * lowerArmMin;
		objectInfoList[ePart::LEFT_UPPER_LEG].currentAngle.x = std::sin(walkTheta) * upperLegMin;
		objectInfoList[ePart::RIGHT_UPPER_LEG].currentAngle.x = std::sin(walkTheta + glmath::pi) * upperLegMax;
		objectInfoList[ePart::LEFT_LOWER_LEG].currentAngle.x = std::sin(walkTheta) * lowerLegMin;
		objectInfoList[ePart::RIGHT_LOWER_LEG].currentAngle.x = std::sin(walkTheta + glmath::pi) * lowerLegMax;
	}


	transformList[ePart::PELVIS].translation = objectInfoList[ePart::PELVIS].translation;
	transformList[ePart::PELVIS].translation.y = objectInfoList[ePart::PELVIS].translation.y;
	transformList[ePart::PELVIS].scale = glmath::vec3(1.0f, 1.6f, 1.0f);

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
