#ifndef ACTION_H
# define ACTION_H

# include "humanGL.h"
# include <map>
# include <cmath>


enum class eAct
{
	STOP = (1 << 0),
	ROTATE = (1 << 1),
	JUMP = (1 << 2),
	WALK = (1 << 3),
	FULLBIT = (1 << 4) - 1,
};

int operator&(int bit, eAct act);
int operator|(int bit, eAct act);
bool operator==(int bit, eAct act);

enum class ePart
{
	BODY,
	HAIR,
	LEFT_EYE,
	RIGHT_EYE,
	NOSE,
	MOUSE,
	HEAD,
	LEFT_UPPER_ARM,
	LEFT_LOWER_ARM,
	RIGHT_UPPER_ARM,
	RIGHT_LOWER_ARM,
	LEFT_UPPER_LEG,
	LEFT_LOWER_LEG,
	RIGHT_UPPER_LEG,
	RIGHT_LOWER_LEG,
	GROUND,
	NONE,
};

struct Transform {
	glmath::vec3 translation;
	glmath::quat rotation;
	glmath::vec3 scale;

	Transform() : translation(glmath::vec3(0.0f)), rotation(glmath::quat(0.0f)), scale(glmath::vec3(1.0f)) {};
};

struct ObjectInfo {
	glmath::vec3 velocity;
	glmath::vec3 translation;
	glmath::vec3 currentAngle;
	glmath::vec3 targetAngle;
	glmath::vec3 currentDirection;
	glmath::vec3 targetDirection;

	ObjectInfo()
		: velocity(glmath::vec3(0.0f)), translation(glmath::vec3(0.0f)),
		  currentAngle(glmath::vec3(0.0f)), targetAngle(glmath::vec3(0.0f)),
		  currentDirection(glmath::vec3(0.0f, 0.0f, -1.0f)), targetDirection(glmath::vec3(0.0f, 0.0f, -1.0f)) {};
};

Transform operator*(const Transform& t1, const Transform& t2);

class Action {
public:
	virtual int doAction(std::map<ePart, Transform>& transformList, std::map<ePart, ObjectInfo>& objectInfoList) = 0;
	virtual ~Action() = default;
protected:
	static float walkTheta;
};

class Stop : public Action {
public:
	virtual int doAction(std::map<ePart, Transform>& transformList, std::map<ePart, ObjectInfo>& objectInfoList) override;
	virtual ~Stop() override = default;
};

class Rotate : public Action {
public:
	virtual int doAction(std::map<ePart, Transform>& transformList, std::map<ePart, ObjectInfo>& objectInfoList) override;
	virtual ~Rotate() override = default;
};

class Jump : public Action {
public:
	virtual int doAction(std::map<ePart, Transform>& transformList, std::map<ePart, ObjectInfo>& objectInfoList) override;
	virtual ~Jump() override = default;
};

class Walk : public Action {
public:
	virtual int doAction(std::map<ePart, Transform>& transformList, std::map<ePart, ObjectInfo>& objectInfoList) override;
	virtual ~Walk() override = default;
};

#endif