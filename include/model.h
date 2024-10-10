#ifndef MODEL_H
# define MODEL_H

# include "mesh.h"
# include "program.h"
# include <cmath>
# include <algorithm>
# include <map>
# include <string>
# include <stack>

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
	NONE,
};

struct PartInfo {
	std::string name; // 파트 이름
    glmath::vec3 position;    // 각 파트의 상대 위치
	glmath::vec3 translation; // 각 파트의 이동
    glmath::vec3 eulerAngle;    // 각 파트의 회전 (x, y, z 축의 각도)
    glmath::vec3 scale;       // 각 파트의 크기
    glmath::vec3 color;       // 각 파트의 색상
};

class Model {
public:
	static std::unique_ptr<Model> createHuman(ePart part = ePart::BODY);
	static std::stack<glmath::mat4> s_stack;
	void draw(Program* program);

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