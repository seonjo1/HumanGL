#include "../include/animation.h"


Animation::Animation() {
	m_state = static_cast<int>(eAct::STOP);

	m_actionList[eAct::STOP] = std::make_unique<Stop>();
	m_actionList[eAct::ROTATE] = std::make_unique<Rotate>();
	m_actionList[eAct::JUMP] = std::make_unique<Jump>();
	m_actionList[eAct::WALK] = std::make_unique<Walk>();

	for (int part = static_cast<int>(ePart::BODY); part < static_cast<int>(ePart::NONE); part++) {
		m_transformList[static_cast<ePart>(part)] = Transform();
	}
}


std::unique_ptr<Animation> Animation::createAnimationManager() {
	std::unique_ptr<Animation> animationManager(new Animation());

	return animationManager;
}


void Animation::changeState(int inputState, float yaw) {
	if (inputState & eAct::ROTATE) {
		m_objectInfo.destYaw = yaw;
		m_state = m_state | eAct::ROTATE;
	}
}

std::map<ePart,Transform> Animation::getTransform() {

	static int size = m_actionList.size() - 1;
	std::vector<eAct> actions;

	for (int i = 0; i < size; i++) {
		if (m_state & (1 << i)) {
			actions.push_back(eAct(1 << i));
		}
	}

	for (eAct action : actions) {
		m_state = m_state & m_actionList[action]->doAction(m_transformList, m_objectInfo);
	}

	return m_transformList;
}