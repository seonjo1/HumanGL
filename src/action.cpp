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
	static const float rotateSpeed = 1.0f;
	static const float upperAngleMax = 0.0f;
	static const float upperAngleMin = 0.0f;
	static const float lowerAngleMax = 0.0f;
	static const float lowerAngleMin = 0.0f;

	float ratio = rotateSpeed / (upperAngleMax - objectInfoList[ePart::LEFT_UPPER_LEG].currentAngle.x);
	objectInfoList[ePart::LEFT_UPPER_LEG].currentAngle.x += rotateSpeed;
	if (objectInfoList[ePart::LEFT_UPPER_LEG].currentAngle.x >= upperAngleMax) {
		objectInfoList[ePart::LEFT_UPPER_LEG].currentAngle.x = upperAngleMax;
		objectInfoList[ePart::RIGHT_UPPER_LEG].currentAngle.x = upperAngleMin;
		objectInfoList[ePart::LEFT_LOWER_LEG].currentAngle.x = lowerAngleMax;
		objectInfoList[ePart::RIGHT_LOWER_LEG].currentAngle.x = lowerAngleMin;
	} else {
		float rightUpperSpeed = ratio * (upperAngleMin - objectInfoList[ePart::RIGHT_UPPER_LEG].currentAngle.x);
		objectInfoList[ePart::RIGHT_UPPER_LEG].currentAngle.x += rightUpperSpeed;

		float leftLowerSpeed = ratio * (lowerAngleMax - objectInfoList[ePart::LEFT_LOWER_LEG].currentAngle.x);
		objectInfoList[ePart::LEFT_LOWER_LEG].currentAngle.x += leftLowerSpeed;

		float rightLowerSpeed = ratio * (lowerAngleMin - objectInfoList[ePart::RIGHT_LOWER_LEG].currentAngle.x);
		objectInfoList[ePart::RIGHT_LOWER_LEG].currentAngle.x += rightLowerSpeed;

		float downSpeed = ratio * (0.0f - objectInfoList[ePart::BODY].translation.y);
		objectInfoList[ePart::BODY].translation.y += downSpeed;
	}

	transformList[ePart::LEFT_UPPER_LEG].rotation = glmath::quat(glmath::vec3(objectInfoList[ePart::LEFT_UPPER_LEG].currentAngle.x, 0.0f, 0.0f));
	transformList[ePart::RIGHT_UPPER_LEG].rotation = glmath::quat(glmath::vec3(objectInfoList[ePart::RIGHT_UPPER_LEG].currentAngle.x, 0.0f, 0.0f));
	transformList[ePart::LEFT_LOWER_LEG].rotation = glmath::quat(glmath::vec3(objectInfoList[ePart::LEFT_LOWER_LEG].currentAngle.x, 0.0f, 0.0f));
	transformList[ePart::RIGHT_LOWER_LEG].rotation = glmath::quat(glmath::vec3(objectInfoList[ePart::RIGHT_LOWER_LEG].currentAngle.x, 0.0f, 0.0f));
	transformList[ePart::BODY].translation.y = objectInfoList[ePart::BODY].translation.y;
	return ~static_cast<int>(eAct::STOP);
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

	std::cout << objectInfoList[ePart::BODY].currentAngle.y << "\n";
	transformList[ePart::BODY].rotation = glmath::quat(glmath::vec3(0.0f, 1.0f, 0.0f), objectInfoList[ePart::BODY].currentAngle.y);

	return ~static_cast<int>(eAct::ROTATE);
}

int Jump::doAction(std::map<ePart, Transform>& transformList, std::map<ePart, ObjectInfo>& objectInfoList) {
	return ~static_cast<int>(eAct::JUMP);
}

int Walk::doAction(std::map<ePart, Transform>& transformList, std::map<ePart, ObjectInfo>& objectInfoList) {
	static const float moveSpeed = 0.05f;
	static const float rotateSpeed = 0.5f;
	static const  float upperAngleMax = 40.0f;
	static const float upperAngleMin = -30.0f;
	static const float lowerAngleMax = -30.0f;
	static const float lowerAngleMin = -15.0f;
	static const float yMin = -0.2f;
	static float isLeft = true;
	static float isDown = true;

	objectInfoList[ePart::BODY].translation = objectInfoList[ePart::BODY].translation + moveSpeed * objectInfoList[ePart::BODY].targetDirection;
	transformList[ePart::BODY].translation = objectInfoList[ePart::BODY].translation;

	if (isLeft) {
		float ratio = rotateSpeed / (upperAngleMax - objectInfoList[ePart::LEFT_UPPER_LEG].currentAngle.x);
		objectInfoList[ePart::LEFT_UPPER_LEG].currentAngle.x += rotateSpeed;
		if (objectInfoList[ePart::LEFT_UPPER_LEG].currentAngle.x >= upperAngleMax) {
			objectInfoList[ePart::LEFT_UPPER_LEG].currentAngle.x = upperAngleMax;
			objectInfoList[ePart::RIGHT_UPPER_LEG].currentAngle.x = upperAngleMin;
			objectInfoList[ePart::LEFT_LOWER_LEG].currentAngle.x = lowerAngleMax;
			objectInfoList[ePart::RIGHT_LOWER_LEG].currentAngle.x = lowerAngleMin;
			objectInfoList[ePart::BODY].translation.y = yMin;
			isLeft = !isLeft;
			isDown = !isDown;
		} else {
			float rightUpperSpeed = ratio * (upperAngleMin - objectInfoList[ePart::RIGHT_UPPER_LEG].currentAngle.x);
			objectInfoList[ePart::RIGHT_UPPER_LEG].currentAngle.x += rightUpperSpeed;

			float leftLowerSpeed = ratio * (lowerAngleMax - objectInfoList[ePart::LEFT_LOWER_LEG].currentAngle.x);
			objectInfoList[ePart::LEFT_LOWER_LEG].currentAngle.x += leftLowerSpeed;

			float rightLowerSpeed = ratio * (lowerAngleMin - objectInfoList[ePart::RIGHT_LOWER_LEG].currentAngle.x);
			objectInfoList[ePart::RIGHT_LOWER_LEG].currentAngle.x += rightLowerSpeed;

			if (isDown) {
				float downSpeed = ratio * (yMin - objectInfoList[ePart::BODY].translation.y);
				objectInfoList[ePart::BODY].translation.y += downSpeed;
			} else {
				if (objectInfoList[ePart::LEFT_UPPER_LEG].currentAngle.x >= 0) {
					objectInfoList[ePart::BODY].translation.y = 0.0f;
					isDown = !isDown;
				} else {
					float yRatio = rotateSpeed / (0.0f - objectInfoList[ePart::LEFT_UPPER_LEG].currentAngle.x);
					float upSpeed = yRatio * (0.0f - objectInfoList[ePart::BODY].translation.y);
					objectInfoList[ePart::BODY].translation.y += upSpeed;
				}
			}
		}
	} else {
		float ratio = rotateSpeed / (upperAngleMax - objectInfoList[ePart::RIGHT_UPPER_LEG].currentAngle.x);
		objectInfoList[ePart::RIGHT_UPPER_LEG].currentAngle.x += rotateSpeed;
		if (objectInfoList[ePart::RIGHT_UPPER_LEG].currentAngle.x >= upperAngleMax) {
			objectInfoList[ePart::RIGHT_UPPER_LEG].currentAngle.x = upperAngleMax;
			objectInfoList[ePart::LEFT_UPPER_LEG].currentAngle.x = upperAngleMin;
			objectInfoList[ePart::RIGHT_LOWER_LEG].currentAngle.x = lowerAngleMax;
			objectInfoList[ePart::LEFT_LOWER_LEG].currentAngle.x = lowerAngleMin;
			objectInfoList[ePart::BODY].translation.y = yMin;
			isLeft = !isLeft;
			isDown = !isDown;
		} else {
			float leftUpperSpeed = ratio * (upperAngleMin - objectInfoList[ePart::LEFT_UPPER_LEG].currentAngle.x);
			objectInfoList[ePart::LEFT_UPPER_LEG].currentAngle.x += leftUpperSpeed;

			float rightLowerSpeed = ratio * (lowerAngleMax - objectInfoList[ePart::RIGHT_LOWER_LEG].currentAngle.x);
			objectInfoList[ePart::RIGHT_LOWER_LEG].currentAngle.x += rightLowerSpeed;

			float leftLowerSpeed = ratio * (lowerAngleMin - objectInfoList[ePart::LEFT_LOWER_LEG].currentAngle.x);
			objectInfoList[ePart::LEFT_LOWER_LEG].currentAngle.x += leftLowerSpeed;
			
			if (isDown) {
				float downSpeed = ratio * (yMin - objectInfoList[ePart::BODY].translation.y);
				objectInfoList[ePart::BODY].translation.y += downSpeed;
			} else {
				if (objectInfoList[ePart::RIGHT_UPPER_LEG].currentAngle.x >= 0) {
					objectInfoList[ePart::BODY].translation.y = 0.0f;
					isDown = !isDown;
				} else {
					float zRatio = rotateSpeed / (0.0f - objectInfoList[ePart::RIGHT_UPPER_LEG].currentAngle.x);
					float upSpeed = zRatio * (0.0f - objectInfoList[ePart::BODY].translation.y);
					objectInfoList[ePart::BODY].translation.y += upSpeed;
				}
			}
		}
	}
	transformList[ePart::LEFT_UPPER_LEG].rotation = glmath::quat(glmath::vec3(objectInfoList[ePart::LEFT_UPPER_LEG].currentAngle.x, 0.0f, 0.0f));
	transformList[ePart::RIGHT_UPPER_LEG].rotation = glmath::quat(glmath::vec3(objectInfoList[ePart::RIGHT_UPPER_LEG].currentAngle.x, 0.0f, 0.0f));
	transformList[ePart::LEFT_LOWER_LEG].rotation = glmath::quat(glmath::vec3(objectInfoList[ePart::LEFT_LOWER_LEG].currentAngle.x, 0.0f, 0.0f));
	transformList[ePart::RIGHT_LOWER_LEG].rotation = glmath::quat(glmath::vec3(objectInfoList[ePart::RIGHT_LOWER_LEG].currentAngle.x, 0.0f, 0.0f));
	transformList[ePart::BODY].translation.y = objectInfoList[ePart::BODY].translation.y;
	return ~static_cast<int>(eAct::WALK);
}

