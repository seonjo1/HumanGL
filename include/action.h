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
	glmath::vec3 position;
	glmath::vec3 direction;
	glmath::vec3 destDirection;
	float yaw {0.0f};
};

Transform operator*(const Transform& t1, const Transform& t2);

class Action {
public:
	virtual int doAction(std::map<ePart, Transform>& transformList, ObjectInfo& objinfo) = 0;
	virtual ~Action() = default;
};

class Stop : public Action {
public:
	virtual int doAction(std::map<ePart, Transform>& transformList, ObjectInfo& objinfo) override;
	virtual ~Stop() override = default;
};

class Rotate : public Action {
public:
	virtual int doAction(std::map<ePart, Transform>& transformList, ObjectInfo& objinfo) override;
	virtual ~Rotate() override = default;
};

class Jump : public Action {
public:
	virtual int doAction(std::map<ePart, Transform>& transformList, ObjectInfo& objinfo) override;
	virtual ~Jump() override = default;
};

class Walk : public Action {
public:
	virtual int doAction(std::map<ePart, Transform>& transformList, ObjectInfo& objinfo) override;
	virtual ~Walk() override = default;
};


#endif