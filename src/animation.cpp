#include "../include/animation.h"

int operator&(int bit, eAct act){
	return bit & static_cast<int>(act);
}

int operator&(eAct act, int bit){
	return bit & static_cast<int>(act);
}

int operator|(int bit, eAct act){
	return bit | static_cast<int>(act);
}

int operator|(eAct act, int bit){
	return bit | static_cast<int>(act);
}

void Animation::changeState(int input) {
	if (m_state & eAct::JUMP) {
		return ;
	}
	if (input & eAct::JUMP) {
		m_state = static_cast<int>(eAct::JUMP);
	} else if (input & eAct::WALK) {
		m_state = static_cast<int>(eAct::WALK);
	} else {
		m_state = static_cast<int>(eAct::STOP);
	}
}


std::map<ePart,Transform> Animation::getTransform() {
	
}