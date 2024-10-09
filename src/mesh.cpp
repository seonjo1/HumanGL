#include "../include/mesh.h"

std::unique_ptr<Mesh> Mesh::createBox() {
	std::vector<Vertex> vertices = {
		Vertex { glmath::vec3(-0.5f, -0.5f, -0.5f), glmath::vec2(0.0f, 0.0f), glmath::vec3( 0.0f, 0.0f, -1.0f) },
		Vertex { glmath::vec3( 0.5f, -0.5f, -0.5f), glmath::vec2(1.0f, 0.0f), glmath::vec3( 0.0f, 0.0f, -1.0f) },
		Vertex { glmath::vec3( 0.5f,  0.5f, -0.5f), glmath::vec2(1.0f, 1.0f), glmath::vec3( 0.0f, 0.0f, -1.0f) },
		Vertex { glmath::vec3(-0.5f,  0.5f, -0.5f), glmath::vec2(0.0f, 1.0f), glmath::vec3( 0.0f, 0.0f, -1.0f) },

		Vertex { glmath::vec3(-0.5f, -0.5f, 0.5f), glmath::vec2(0.0f, 0.0f), glmath::vec3( 0.0f, 0.0f, 1.0f)},
		Vertex { glmath::vec3( 0.5f, -0.5f, 0.5f), glmath::vec2(1.0f, 0.0f), glmath::vec3( 0.0f, 0.0f, 1.0f)},
		Vertex { glmath::vec3( 0.5f,  0.5f, 0.5f), glmath::vec2(1.0f, 1.0f), glmath::vec3( 0.0f, 0.0f, 1.0f)},
		Vertex { glmath::vec3(-0.5f,  0.5f, 0.5f), glmath::vec2(0.0f, 1.0f), glmath::vec3( 0.0f, 0.0f, 1.0f)},

		Vertex { glmath::vec3(-0.5f,  0.5f,  0.5f), glmath::vec2(1.0f, 0.0f), glmath::vec3(-1.0f, 0.0f, 0.0f)},
		Vertex { glmath::vec3(-0.5f,  0.5f, -0.5f), glmath::vec2(1.0f, 1.0f), glmath::vec3(-1.0f, 0.0f, 0.0f)},
		Vertex { glmath::vec3(-0.5f, -0.5f, -0.5f), glmath::vec2(0.0f, 1.0f), glmath::vec3(-1.0f, 0.0f, 0.0f)},
		Vertex { glmath::vec3(-0.5f, -0.5f,  0.5f), glmath::vec2(0.0f, 0.0f), glmath::vec3(-1.0f, 0.0f, 0.0f)},

		Vertex { glmath::vec3( 0.5f,  0.5f,  0.5f), glmath::vec2(1.0f, 0.0f), glmath::vec3( 1.0f, 0.0f, 0.0f)},
		Vertex { glmath::vec3( 0.5f,  0.5f, -0.5f), glmath::vec2(1.0f, 1.0f), glmath::vec3( 1.0f, 0.0f, 0.0f)},
		Vertex { glmath::vec3( 0.5f, -0.5f, -0.5f), glmath::vec2(0.0f, 1.0f), glmath::vec3( 1.0f, 0.0f, 0.0f)},
		Vertex { glmath::vec3( 0.5f, -0.5f,  0.5f), glmath::vec2(0.0f, 0.0f), glmath::vec3( 1.0f, 0.0f, 0.0f)},

		Vertex { glmath::vec3(-0.5f, -0.5f, -0.5f), glmath::vec2(0.0f, 1.0f), glmath::vec3( 0.0f, -1.0f, 0.0f)},
		Vertex { glmath::vec3( 0.5f, -0.5f, -0.5f), glmath::vec2(1.0f, 1.0f), glmath::vec3( 0.0f, -1.0f, 0.0f)},
		Vertex { glmath::vec3( 0.5f, -0.5f,  0.5f), glmath::vec2(1.0f, 0.0f), glmath::vec3( 0.0f, -1.0f, 0.0f)},
		Vertex { glmath::vec3(-0.5f, -0.5f,  0.5f), glmath::vec2(0.0f, 0.0f), glmath::vec3( 0.0f, -1.0f, 0.0f)},

		Vertex { glmath::vec3(-0.5f, 0.5f, -0.5f), glmath::vec2(0.0f, 1.0f), glmath::vec3( 0.0f, 1.0f, 0.0f)},
		Vertex { glmath::vec3( 0.5f, 0.5f, -0.5f), glmath::vec2(1.0f, 1.0f), glmath::vec3( 0.0f, 1.0f, 0.0f)},
		Vertex { glmath::vec3( 0.5f, 0.5f,	 0.5f), glmath::vec2(1.0f, 0.0f), glmath::vec3( 0.0f, 1.0f, 0.0f)},
		Vertex { glmath::vec3(-0.5f, 0.5f,	 0.5f), glmath::vec2(0.0f, 0.0f), glmath::vec3( 0.0f, 1.0f, 0.0f)},
	};

	std::vector<uint32_t> indices = {
		 0,	2,	1,	2,	0,	3,
		 4,	5,	6,	6,	7,	4,
		 8,	9, 10, 10, 11,	8,
		12, 14, 13, 14, 12, 15,
		16, 17, 18, 18, 19, 16,
		20, 22, 21, 22, 20, 23,
	};

	std::unique_ptr<Mesh> mesh(new Mesh());
	mesh->init(vertices, indices);
	return mesh;
}

void Mesh::init(std::vector<Vertex>& vertices, std::vector<uint32_t>& indices) {
	GLsizei vertexSize = vertices.size();
	m_elementSize = indices.size();

	m_vertexArray = VertexArray::create();

	m_vertexBuffer = Buffer::create(GL_ARRAY_BUFFER, sizeof(Vertex) * vertexSize,
									vertices.data(), GL_STATIC_DRAW);
	m_vertexArray->setAttribute(0, 3, sizeof(Vertex), offsetof(Vertex, pos));
	m_vertexArray->setAttribute(1, 2, sizeof(Vertex), offsetof(Vertex, texCoord));
	m_vertexArray->setAttribute(2, 3, sizeof(Vertex), offsetof(Vertex, normal));

	m_elementBuffer = Buffer::create(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint32_t) * m_elementSize,
									indices.data(), GL_STATIC_DRAW);
}

void Mesh::draw() {
	m_vertexArray->bind();
	glDrawElements(GL_TRIANGLES, m_elementSize, GL_UNSIGNED_INT, 0);
}
