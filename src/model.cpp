#include "../include/model.h"

std::stack<glmath::mat4> Model::s_stack;

std::unique_ptr<Model> Model::createGround() {
	std::unique_ptr<Model> model(new Model());
	model->createMesh(ePart::GROUND);
	return model;
}

std::unique_ptr<Model> Model::createHuman(ePart part) {
	std::unique_ptr<Model> model(new Model());
	model->createMesh(part);

	if (!model->createChildren(model->getPartChildrenInfo(part))) {
		return nullptr;
	}

	return model;
}

bool Model::createChildren(std::vector<ePart> parts) {
	for (ePart part : parts) {
		if (part == ePart::NONE) {
			continue;
		}
		if (std::unique_ptr<Model> child = createHuman(part)) {
			m_children.push_back(std::move(child));
		} else {
			return false;
		}
	}
	return true;
}

std::vector<ePart> Model::getPartChildrenInfo(ePart part) {
	static std::map<ePart, std::vector<ePart>> partChildrenInfo = {
		{ ePart::BODY, { ePart::HEAD, ePart::LEFT_UPPER_ARM, ePart::LEFT_UPPER_LEG, ePart::RIGHT_UPPER_ARM, ePart::RIGHT_UPPER_LEG } },
		{ ePart::HEAD, { ePart::HAIR, ePart::LEFT_EYE, ePart::RIGHT_EYE, ePart::NOSE, ePart::MOUSE } },
		{ ePart::HAIR, { ePart::NONE } },
		{ ePart::LEFT_EYE, { ePart::LEFT_PUPIL } },
		{ ePart::LEFT_PUPIL, { ePart::NONE } },
		{ ePart::RIGHT_EYE, { ePart::RIGHT_PUPIL } },
		{ ePart::RIGHT_PUPIL, { ePart::NONE } },
		{ ePart::NOSE, { ePart::NONE } },
		{ ePart::MOUSE, { ePart::NONE } },
		{ ePart::LEFT_UPPER_ARM, { ePart::LEFT_LOWER_ARM, ePart::LEFT_SLEEVE } },
		{ ePart::LEFT_SLEEVE, { ePart::NONE } },
		{ ePart::LEFT_LOWER_ARM, { ePart::NONE } },
		{ ePart::RIGHT_UPPER_ARM, { ePart::RIGHT_LOWER_ARM, ePart::RIGHT_SLEEVE } },
		{ ePart::RIGHT_SLEEVE, { ePart::NONE } },
		{ ePart::RIGHT_LOWER_ARM, { ePart::NONE } },
		{ ePart::LEFT_UPPER_LEG, { ePart::LEFT_LOWER_LEG } },
		{ ePart::LEFT_LOWER_LEG, { ePart::LEFT_FOOT } },
		{ ePart::RIGHT_UPPER_LEG, { ePart::RIGHT_LOWER_LEG } },
		{ ePart::RIGHT_LOWER_LEG, { ePart::RIGHT_FOOT } },
		{ ePart::LEFT_FOOT, {ePart::NONE} },
		{ ePart::RIGHT_FOOT, {ePart::NONE} },
	};

	return partChildrenInfo[part];
}

PartInfo Model::getPartInfo(ePart part) {
	static std::map<ePart, PartInfo> partInfoMap = {
		{ ePart::BODY, { ePart::BODY, glmath::vec3(0.0f, 6.0f, 0.0f), glmath::vec3(0.0f), glmath::quat(), glmath::vec3(2.0f, 3.0f, 0.8f), glmath::vec3(0.184f, 0.184f, 0.184f) } },  // 몸통
		{ ePart::HEAD, { ePart::HEAD, glmath::vec3(0.0f, 2.0f, 0.0f), glmath::vec3(0.0f), glmath::quat(), glmath::vec3(1.0f), glmath::vec3(0.95f, 0.80f, 0.72f) } },  // 머리
		{ ePart::HAIR, { ePart::HAIR, glmath::vec3(0.0f, 0.3f, 0.0f), glmath::vec3(0.0f), glmath::quat(), glmath::vec3(1.05f, 0.5f, 1.05f), glmath::vec3(0.11f, 0.11f, 0.11f) } },
		{ ePart::LEFT_EYE, { ePart::LEFT_EYE, glmath::vec3(-0.25f, -0.1f, -0.5f), glmath::vec3(0.0f), glmath::quat(), glmath::vec3(0.3f, 0.2f, 0.05f), glmath::vec3(1.0f, 1.0f, 1.0f) } },
		{ ePart::LEFT_PUPIL, { ePart::LEFT_PUPIL, glmath::vec3(0.075f, 0.0f, 0.0f), glmath::vec3(0.0f), glmath::quat(), glmath::vec3(0.15f, 0.2f, 0.06f), glmath::vec3(0.0f, 0.0f, 0.0f) } },
		{ ePart::RIGHT_EYE, { ePart::RIGHT_EYE, glmath::vec3(0.25f, -0.1f, -0.5f), glmath::vec3(0.0f), glmath::quat(), glmath::vec3(0.3f, 0.2f, 0.05f), glmath::vec3(1.0f, 1.0f, 1.0f) } },
		{ ePart::RIGHT_PUPIL, { ePart::RIGHT_PUPIL, glmath::vec3(-0.075f, 0.0f, 0.0f), glmath::vec3(0.0f), glmath::quat(), glmath::vec3(0.15f, 0.2f, 0.06f), glmath::vec3(0.0f, 0.0f, 0.0f) } },
		{ ePart::NOSE, { ePart::NOSE, glmath::vec3(0.0f, -0.25f, -0.5f), glmath::vec3(0.0f), glmath::quat(), glmath::vec3(0.05f, 0.1f, 0.05f), glmath::vec3(0.0f, 0.0f, 0.0f) } },
		{ ePart::MOUSE, { ePart::MOUSE, glmath::vec3(0.0f, -0.4f, -0.5f), glmath::vec3(0.0f), glmath::quat(), glmath::vec3(0.5f, 0.1f, 0.05f), glmath::vec3(0.7f, 0.0f, 0.0f) } },
		{ ePart::LEFT_UPPER_ARM, { ePart::LEFT_UPPER_ARM, glmath::vec3(-1.25f, 0.75f, 0.0f), glmath::vec3(0.0f, 0.75f, 0.0f), glmath::quat(), glmath::vec3(0.5f, 1.5f, 0.5f), glmath::vec3(0.95f, 0.80f, 0.72f) } }, // 왼쪽 상박
		{ ePart::LEFT_SLEEVE, { ePart::LEFT_SLEEVE, glmath::vec3(0.0f, 0.26f, 0.0f), glmath::vec3(0.0f, 0.0f, 0.0f), glmath::quat(), glmath::vec3(0.6f, 1.0f, 0.6f), glmath::vec3(0.184f, 0.184f, 0.184f) } }, // 왼쪽 상박
		{ ePart::LEFT_LOWER_ARM, { ePart::LEFT_LOWER_ARM, glmath::vec3(0.0f, -1.5f, 0.0f), glmath::vec3(0.0f, 0.75f, 0.0f), glmath::quat(), glmath::vec3(0.5f, 1.5f, 0.5f), glmath::vec3(0.95f, 0.80f, 0.72f) } }, // 왼쪽 하박
		{ ePart::RIGHT_UPPER_ARM, { ePart::RIGHT_UPPER_ARM, glmath::vec3(1.25f, 0.75f, 0.0f), glmath::vec3(0.0f, 0.75f, 0.0f), glmath::quat(), glmath::vec3(0.5f, 1.5f, 0.5f), glmath::vec3(0.95f, 0.80f, 0.72f) } }, // 오른쪽 상박
		{ ePart::RIGHT_SLEEVE, { ePart::RIGHT_SLEEVE, glmath::vec3(0.0f, 0.26f, 0.0f), glmath::vec3(0.0f, 0.0f, 0.0f), glmath::quat(), glmath::vec3(0.6f, 1.0f, 0.6f), glmath::vec3(0.184f, 0.184f, 0.184f) } }, // 왼쪽 상박
		{ ePart::RIGHT_LOWER_ARM, { ePart::RIGHT_LOWER_ARM, glmath::vec3(0.0f, -1.5f, 0.0f), glmath::vec3(0.0f, 0.75f, 0.0f), glmath::quat(), glmath::vec3(0.5f, 1.5f, 0.5f), glmath::vec3(0.95f, 0.80f, 0.72f) } }, // 오른쪽 하박
		{ ePart::LEFT_UPPER_LEG, { ePart::LEFT_UPPER_LEG, glmath::vec3(-0.5f, -2.5f, 0.0f), glmath::vec3(0.0f, 1.0f, 0.0f), glmath::quat(), glmath::vec3(0.8f, 2.0f, 0.8f), glmath::vec3(0.483f, 0.424f, 0.359f) } }, // 왼쪽 상박 (다리)
		{ ePart::LEFT_LOWER_LEG, { ePart::LEFT_LOWER_LEG, glmath::vec3(0.0f, -2.0f, 0.0f), glmath::vec3(0.0f, 1.0f, 0.0f), glmath::quat(), glmath::vec3(0.8f, 2.0f, 0.8f), glmath::vec3(0.483f, 0.424f, 0.359f) } }, // 왼쪽 하박 (다리)
		{ ePart::RIGHT_UPPER_LEG, { ePart::RIGHT_UPPER_LEG, glmath::vec3(0.5f, -2.5f, 0.0f), glmath::vec3(0.0f, 1.0f, 0.0f), glmath::quat(), glmath::vec3(0.8f, 2.0f, 0.8f), glmath::vec3(0.483f, 0.424f, 0.359f) } }, // 오른쪽 상박 (다리)
		{ ePart::RIGHT_LOWER_LEG, { ePart::RIGHT_LOWER_LEG, glmath::vec3(0.0f, -2.0f, 0.0f), glmath::vec3(0.0f, 1.0f, 0.0f), glmath::quat(), glmath::vec3(0.8f, 2.0f, 0.8f), glmath::vec3(0.483f, 0.424f, 0.359f) } },  // 오른쪽 하박 (다리)
		{ ePart::LEFT_FOOT, { ePart::LEFT_FOOT, glmath::vec3(0.0f, -0.76f, -0.19f), glmath::vec3(0.0f, 0.0f, 0.0f), glmath::quat(), glmath::vec3(0.9f, 0.5f, 1.2f), glmath::vec3(0.394f, 0.312f, 0.229f) } },  
		{ ePart::RIGHT_FOOT, { ePart::RIGHT_FOOT, glmath::vec3(0.0f, -0.76f, -0.19f), glmath::vec3(0.0f, 0.0f, 0.0f), glmath::quat(), glmath::vec3(0.9f, 0.5f, 1.2f), glmath::vec3(0.394f, 0.312f, 0.229f) } }, 
		{ ePart::GROUND, { ePart::GROUND, glmath::vec3(0.0f, -0.5f, 0.0f), glmath::vec3(0.0f, 0.0f, 0.0f), glmath::quat(), glmath::vec3(100.0f, 1.0f, 100.0f), glmath::vec3(0.39f, 0.39f, 0.39f) } },  
	};
	return partInfoMap[part];
}

void Model::createMesh(ePart part) {
	m_mesh = Mesh::createBox();
	m_partInfo = getPartInfo(part);
}

void Model::draw(Program* program, std::map<ePart, Transform>& transformList) {

	glmath::mat4& parentsTransform = s_stack.top();
	glmath::mat4 childTransform = glmath::translate(glmath::mat4(1.0f), m_partInfo.position) *
								  glmath::translate(glmath::mat4(1.0f), transformList[m_partInfo.part].translation) *
								  glmath::translate(glmath::mat4(1.0f), m_partInfo.rotateTranslation) *
								  glmath::mat4_cast(transformList[m_partInfo.part].rotation * m_partInfo.rotation) *
								  glmath::translate(glmath::mat4(1.0f), -1 * m_partInfo.rotateTranslation);

	s_stack.push(parentsTransform * childTransform);

	program->setUniform("color", m_partInfo.color);
	program->setUniform("transform", s_stack.top() * glmath::scale(glmath::mat4(1.0f), transformList[m_partInfo.part].scale * m_partInfo.scale));

	m_mesh->draw();

	for (std::unique_ptr<Model>& child : m_children) {
		child->draw(program, transformList);
	}

	s_stack.pop();
}
