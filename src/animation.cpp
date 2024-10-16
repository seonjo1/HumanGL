#include "../include/animation.h"


Animation::Animation() {
	m_state = static_cast<int>(eAct::STOP);

	m_actionList[eAct::STOP] = std::make_unique<Stop>();
	m_actionList[eAct::ROTATE] = std::make_unique<Rotate>();
	m_actionList[eAct::JUMP] = std::make_unique<Jump>();
	m_actionList[eAct::WALK] = std::make_unique<Walk>();

	for (int part = static_cast<int>(ePart::BODY); part < static_cast<int>(ePart::NONE); part++) {
		m_transformList[static_cast<ePart>(part)] = Transform();
		m_objectInfoList[static_cast<ePart>(part)] = ObjectInfo();
	}
}


std::unique_ptr<Animation> Animation::createAnimationManager() {
	std::unique_ptr<Animation> animationManager(new Animation());

	return animationManager;
}


void Animation::changeState(const int inputState, const glmath::vec3& dir) {
	if (!inputState && !m_state) {
		m_state = static_cast<int>(eAct::STOP);
		return ;
	} else {
		m_state = m_state & ~static_cast<int>(eAct::STOP);
	}

	if (inputState & eAct::ROTATE) {
		m_objectInfoList[ePart::BODY].targetDirection = dir;
		m_state = m_state | eAct::ROTATE;
	}

	if (m_state & eAct::JUMP) {
		return ;
	}

	if (inputState & eAct::JUMP) {
		m_state = m_state & eAct::ROTATE;
		m_state = m_state | eAct::JUMP;
		return ;
	}

	if (inputState & eAct::WALK) {
		m_state = m_state | eAct::WALK;
	}
}

std::map<ePart,Transform> Animation::getTransform() {

	static int size = m_actionList.size();
	std::vector<eAct> actions;

	for (int i = 0; i < size; i++) {
		if (m_state & (1 << i)) {
			actions.push_back(eAct(1 << i));
		}
	}

	for (eAct action : actions) {
		m_state = m_state & m_actionList[action]->doAction(m_transformList, m_objectInfoList);
	}

	return m_transformList;
}