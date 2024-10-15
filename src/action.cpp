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
	static float rotateSpeed = 1.0f;
	
	float deltaYaw = objectInfo.destYaw - objectInfo.yaw;
	if (deltaYaw < 0.0f) {
		if (deltaYaw < -180.0f) {
			objectInfo.yaw += std::min(360.f + deltaYaw, rotateSpeed);
		} else {
			objectInfo.yaw -= std::min(-deltaYaw, rotateSpeed);
		}
	} else {
		if (deltaYaw > 180.0f) {
			objectInfo.yaw -= std::min(360.f - deltaYaw, rotateSpeed);
		} else {
			objectInfo.yaw += std::min(deltaYaw, rotateSpeed);
		}
	}

	if (objectInfo.yaw < 0.0f) { objectInfo.yaw += 360.0f; }
	if (objectInfo.yaw > 360.0f) { objectInfo.yaw -= 360.0f; }

	transformList[ePart::BODY].rotation = glmath::quat(glmath::vec3(0.0f, 1.0f, 0.0f), glmath::radians(objectInfo.yaw));

	if (objectInfo.yaw == objectInfo.destYaw) {
		return ~static_cast<int>(eAct::ROTATE);
	} else {
		return static_cast<int>(eAct::FULLBIT);
	}
}

int Jump::doAction(std::map<ePart, Transform>& transformList, ObjectInfo& objinfo) {
	return static_cast<int>(eAct::FULLBIT);
}

int Walk::doAction(std::map<ePart, Transform>& transformList, ObjectInfo& objinfo) {
	return static_cast<int>(eAct::FULLBIT);
}

