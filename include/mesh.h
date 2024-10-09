#ifndef MESH_H
# define MESH_H

# include "humanGL.h"
# include "vertexArray.h"
# include "buffer.h"

struct Vertex {
	glmath::vec3 pos;
	glmath::vec2 texCoord;
	glmath::vec3 normal;
};

class Mesh {
public:
	static std::unique_ptr<Mesh> createBox();
	void draw();

private:
	Mesh() = default;
	void init(std::vector<Vertex>& vertices, std::vector<uint32_t>& indices);

	std::unique_ptr<VertexArray> m_vertexArray;
	std::shared_ptr<Buffer> m_vertexBuffer; 
	std::shared_ptr<Buffer> m_elementBuffer;
	GLsizei m_elementSize;
};

#endif