#ifndef CONTEXT_H
# define CONTEXT_H

# include "humanGL.h"
# include "vertexArray.h"
# include "buffer.h"
# include "program.h"
# include "mesh.h"
# include "model.h"

class Context {
public:
	static std::unique_ptr<Context> create();
	void Render();
	void ProcessInput(GLFWwindow *window);
	void Reshape(int width, int height);

private:
	Context() {};
	bool init();

	int m_width {WINDOW_WIDTH};
	int m_height {WINDOW_HEIGHT};

	glmath::vec3 m_cameraPos {0.0f, 0.0f, 5.0f};
	glmath::vec3 m_cameraUp {0.0f, 1.0f, 0.0f};
	glmath::vec3 m_cameraFront {0.0f, 0.0f, -1.0f};

	std::unique_ptr<Model> m_human;
	std::unique_ptr<Program> m_program;
};

#endif