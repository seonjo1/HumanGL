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

	m_objectInfo.velocity = glmath::vec3(0.0f);
	m_objectInfo.position = glmath::vec3(0.0f);
	m_objectInfo.direction = glmath::vec3(0.0f, 0.0f, -1.0f);
	m_objectInfo.destDirection = glmath::vec3(0.0f, 0.0f, -1.0f);
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
		m_objectInfo.destDirection = dir;
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
		m_state = m_state & m_actionList[action]->doAction(m_transformList, m_objectInfo);
	}

	return m_transformList;
}