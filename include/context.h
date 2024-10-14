#ifndef CONTEXT_H
# define CONTEXT_H

# include "humanGL.h"
# include "vertexArray.h"
# include "buffer.h"
# include "program.h"
# include "mesh.h"
# include "model.h"
# include "camera.h"

class Context {
public:
	static std::unique_ptr<Context> create();
	void render();
	void processInput(GLFWwindow *window);
	void reshape(int width, int height);
	void mouseMove(double x, double y);
	void mouseButton(int button, int action, double x, double y);

private:
	Context() {};
	bool init();

	int m_width {WINDOW_WIDTH};
	int m_height {WINDOW_HEIGHT};

	Camera m_camera;
	bool m_cameraControl { false };

	std::unique_ptr<Model> m_human;
	std::unique_ptr<Model> m_ground;
	std::unique_ptr<Program> m_program;
};

#endif