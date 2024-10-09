#include "../include/model.h"

std::unique_ptr<Model> Model::createHuman(ePart part) {
	std::unique_ptr<Model> model(new Model());
	model->createMesh(part);

	if (!model->createChildren(model->getPartChildrenInfo(part))) {
		return nullptr;
	}

	std::cout << "Part " << model->m_partInfo.name << " is complete!\n";

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
		{ ePart::HEAD, { ePart::NONE } },
		{ ePart::LEFT_UPPER_ARM, { ePart::LEFT_LOWER_ARM } },
		{ ePart::LEFT_UPPER_LEG, { ePart::LEFT_LOWER_LEG } },
		{ ePart::RIGHT_UPPER_ARM, { ePart::RIGHT_LOWER_ARM } },
		{ ePart::RIGHT_UPPER_LEG, { ePart::RIGHT_LOWER_LEG } },
		{ ePart::LEFT_LOWER_ARM, { ePart::NONE } },
		{ ePart::LEFT_LOWER_LEG, { ePart::NONE } },
		{ ePart::RIGHT_LOWER_ARM, { ePart::NONE } },
		{ ePart::RIGHT_LOWER_LEG, { ePart::NONE } },
	};

	return partChildrenInfo.at(part);
}

PartInfo Model::getPartInfo(ePart part) {
	static std::map<ePart, PartInfo> partInfoMap = {
		{ ePart::BODY, {"BODY", glmath::vec3(0.0f, 0.0f, 0.0f), glmath::vec3(0.0f), glmath::vec3(0.0f), glmath::vec3(1.0f), glmath::vec3(1.0f, 0.5f, 0.3f) } },  // 몸통
		{ ePart::HEAD, {"HEAD", glmath::vec3(0.0f, 1.5f, 0.0f), glmath::vec3(0.0f), glmath::vec3(0.0f), glmath::vec3(0.8f), glmath::vec3(0.8f, 0.8f, 0.8f) } },  // 머리
		{ ePart::LEFT_UPPER_ARM, {"LU_ARM", glmath::vec3(-1.0f, 1.0f, 0.0f), glmath::vec3(0.0f), glmath::vec3(0.0f), glmath::vec3(0.5f), glmath::vec3(0.3f, 0.3f, 1.0f) } }, // 왼쪽 상박
		{ ePart::LEFT_LOWER_ARM, {"LL_ARM", glmath::vec3(-1.0f, 0.5f, 0.0f), glmath::vec3(0.0f), glmath::vec3(0.0f), glmath::vec3(0.5f), glmath::vec3(0.3f, 0.3f, 0.8f) } }, // 왼쪽 하박
		{ ePart::RIGHT_UPPER_ARM, {"RU_ARM", glmath::vec3(1.0f, 1.0f, 0.0f), glmath::vec3(0.0f), glmath::vec3(0.0f), glmath::vec3(0.5f), glmath::vec3(1.0f, 0.3f, 0.3f) } }, // 오른쪽 상박
		{ ePart::RIGHT_LOWER_ARM, {"RL_ARM", glmath::vec3(1.0f, 0.5f, 0.0f), glmath::vec3(0.0f), glmath::vec3(0.0f), glmath::vec3(0.5f), glmath::vec3(0.8f, 0.3f, 0.3f) } }, // 오른쪽 하박
		{ ePart::LEFT_UPPER_LEG, {"LU_LEG", glmath::vec3(-0.5f, -1.0f, 0.0f), glmath::vec3(0.0f), glmath::vec3(0.0f), glmath::vec3(0.6f), glmath::vec3(0.3f, 1.0f, 0.3f) } }, // 왼쪽 상박 (다리)
		{ ePart::LEFT_LOWER_LEG, {"LL_LEG", glmath::vec3(-0.5f, -1.5f, 0.0f), glmath::vec3(0.0f), glmath::vec3(0.0f), glmath::vec3(0.6f), glmath::vec3(0.3f, 0.8f, 0.3f) } }, // 왼쪽 하박 (다리)
		{ ePart::RIGHT_UPPER_LEG, {"RU_LEG", glmath::vec3(0.5f, -1.0f, 0.0f), glmath::vec3(0.0f), glmath::vec3(0.0f), glmath::vec3(0.6f), glmath::vec3(1.0f, 0.5f, 0.3f) } }, // 오른쪽 상박 (다리)
		{ ePart::RIGHT_LOWER_LEG, {"RL_LEG", glmath::vec3(0.5f, -1.5f, 0.0f), glmath::vec3(0.0f), glmath::vec3(0.0f), glmath::vec3(0.6f), glmath::vec3(1.0f, 0.3f, 0.3f) } }  // 오른쪽 하박 (다리)
	};
	return partInfoMap.at(part);
}

void Model::createMesh(ePart part) {
	m_mesh = Mesh::createBox();
	m_partInfo = getPartInfo(part);
}
