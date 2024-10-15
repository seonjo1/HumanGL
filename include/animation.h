#ifndef ANIMATION_H
# define ANIMATION_H

# include "HumanGL.h"
# include <map>

enum class eAct
{
	STOP = 0,
	JUMP = (1 << 0),
	WALK = (1 << 1),
};

int operator&(int bit, eAct act);
int operator&(eAct act, int bit);
int operator|(int bit, eAct act);
int operator|(eAct act, int bit);

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
	glmath::vec3 position;
	glmath::quat rotation;
	glmath::vec3 scale;
};

class Animation {
public:
	void changeState(int input);
	std::map<ePart,Transform> getTransform();

private:
	int m_state;
};

#endif