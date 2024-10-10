#include "../include/context.h"

void Context::Reshape(int width, int height) {
	m_width = width;
	m_height = height;
	glViewport(0, 0, m_width, m_height);
}

std::unique_ptr<Context> Context::create() {
	std::unique_ptr<Context> context(new Context());
	if (!context->init()) return nullptr;
	return context;
}

bool Context::init() {

	m_human = Model::createHuman();
	m_program = Program::create("./shader/simple.vs", "./shader/simple.fs");

	if (!m_human || !m_program) { return false; }

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_MULTISAMPLE);
	
	return true;
}

void Context::Render() {

	glClearColor(0.1f, 0.2f, 0.3f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

}
