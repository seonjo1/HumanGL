#ifndef MODEL_H
# define MODEL_H

# include "mesh.h"
# include "program.h"
# include "animation.h"
# include <cmath>
# include <algorithm>
# include <string>
# include <stack>

struct PartInfo {
	ePart part; // 파트
    glmath::vec3 position;    // 각 파트의 상대 위치
	glmath::vec3 translation; // 각 파트의 이동
	glmath::vec3 rotateTranslation; // 각 파트의 회전축으로의 이동
    glmath::quat rotation;    // 각 파트의 회전 (x, y, z 축의 각도)
    glmath::vec3 scale;       // 각 파트의 크기
    glmath::vec3 color;       // 각 파트의 색상
};

class Model {
public:
	static std::unique_ptr<Model> createHuman(ePart part = ePart::BODY);
	static std::unique_ptr<Model> createGround();
	static std::stack<glmath::mat4> s_stack;
	void draw(Program* program);
	void update(std::map<ePart, Transform>& transformList);

private:
	void createMesh(ePart part);
	bool createChildren(std::vector<ePart> parts);
	PartInfo getPartInfo(ePart part);
	std::vector<ePart> getPartChildrenInfo(ePart part);
	
	std::vector<std::unique_ptr<Model>> m_children;
	std::unique_ptr<Mesh> m_mesh;
	PartInfo m_partInfo;
};

#endif