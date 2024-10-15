#ifndef ANIMATION_H
# define ANIMATION_H

# include "HumanGL.h"
# include "action.h"

class Animation {
public:
	static std::unique_ptr<Animation> createAnimationManager();
	void changeState(int inputState, float yaw);
	std::map<ePart,Transform> getTransform();

private:
	Animation();
	
	int m_state;
	ObjectInfo m_objectInfo;
	std::map<ePart, Transform> m_transformList;
	std::map<eAct, std::unique_ptr<Action>> m_actionList;
};

#endif