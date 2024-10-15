#include "../include/context.h"

void Context::reshape(int width, int height) {
	m_width = width;
	m_height = height;
	glViewport(0, 0, m_width, m_height);
}

std::unique_ptr<Context> Context::create() {
	std::unique_ptr<Context> context(new Context());
	if (!context->init()) return nullptr;
	return context;
}

void Context::mouseButton(int button, int action, double x, double y) {
	if (button == GLFW_MOUSE_BUTTON_RIGHT)
	{
		if (action == GLFW_PRESS)
		{
			m_camera.saveCurrentPos((float)x, (float)y);
			m_cameraControl = true;
		}
		else if (action == GLFW_RELEASE)
			m_cameraControl = false;
	}
}

void Context::mouseMove(double x, double y) {

	if (!m_cameraControl) { return ; }

	glmath::vec2 pos ((float)x, (float)y);
	m_camera.rotate(pos);
}

void Context::processCameraControl(GLFWwindow *window) {

	if (!m_cameraControl) { return ; }

	bool isPressW = glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS;
	bool isPressS = glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS;
	bool isPressD = glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS;
	bool isPressA = glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS;
	bool isPressE = glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS;
	bool isPressQ = glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS;

	m_camera.move(isPressW, isPressS, isPressD, isPressA, isPressE, isPressQ);
}

void Context::processAnimation(GLFWwindow *window) {

	int inputState = 0;

	int arrowNum = 0;
	float yaw = 0.0f;
	if (glfwGetKey(window, GLFW_KEY_UP)) {
		inputState = inputState | eAct::WALK;
		arrowNum++;
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT)) {
		inputState = inputState | eAct::WALK;
		yaw += 90.0f;
		arrowNum++;
	}
	if (glfwGetKey(window, GLFW_KEY_DOWN)) {
		inputState = inputState | eAct::WALK;
		yaw += 180.0f;
		arrowNum++;
	}
	if (glfwGetKey(window, GLFW_KEY_RIGHT)) {
		inputState = inputState | eAct::WALK;
		yaw += 270.0f;
		arrowNum++;
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_ALT)) {
		inputState = inputState | eAct::JUMP;
	}

	if (arrowNum == 0) {
		m_animationManager->changeState(inputState, yaw);
	} else {
		inputState = inputState | eAct::ROTATE;
		m_animationManager->changeState(inputState, yaw / arrowNum);
	}

	std::map<ePart, Transform> transformList = m_animationManager->getTransform();
	m_human->update(transformList);
}

bool Context::init() {

	m_human = Model::createHuman();
	m_ground = Model::createGround();
	m_animationManager = Animation::createAnimationManager();
	m_program = Program::create("./shader/simple.vs", "./shader/simple.fs");

	if (!m_human || !m_program) { return false; }

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_MULTISAMPLE);
	
	return true;
}

void Context::render() {

	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	glmath::mat4 view = m_camera.getViewMatrix();
	glmath::mat4 projection = glmath::perspective(glmath::radians(45.0f), (float)m_width / (float)m_height, 0.01f, 60.0f);
	
	m_program->useProgram();
	Model::s_stack.push(projection * view);
	m_ground->draw(m_program.get());
	m_human->draw(m_program.get());
	Model::s_stack.pop();
}
