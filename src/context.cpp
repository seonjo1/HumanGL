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

	bool pressW = glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS;
	bool pressS = glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS;
	bool pressD = glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS;
	bool pressA = glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS;
	bool pressE = glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS;
	bool pressQ = glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS;

	m_camera.move(pressW, pressS, pressD, pressA, pressE, pressQ);
}

glmath::vec3 Context::setDirection(int& inputState, bool pressUp, bool pressLeft, bool pressDown, bool pressRight) {
	if (!pressUp && !pressLeft && !pressDown && !pressRight) {
		return glmath::vec3(0.0f);
	}

	glmath::vec3 movement(0.0f);

	if (pressUp) {
		movement.z -= 1.0f;
	}
	if (pressDown) {
		movement.z += 1.0f;
	}
	if (pressLeft) {
		movement.x -= 1.0f;
	}
	if (pressRight) {
		movement.x += 1.0f;
	}

	if (glmath::length(movement) < 1.0f) {
		return glmath::vec3(0.0f);
	}
	
	movement = glmath::normalize(movement);

	inputState = inputState | eAct::WALK;
	inputState = inputState | eAct::ROTATE;

	return movement;
}

void Context::processAnimation(GLFWwindow *window) {

	int inputState = 0;

	bool pressUp = glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS;
	bool pressLeft = glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS;
	bool pressDown = glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS;
	bool pressRight = glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS;
	glmath::vec3 dir = setDirection(inputState, pressUp, pressLeft, pressDown, pressRight);


	if (glfwGetKey(window, GLFW_KEY_LEFT_ALT)) {
		inputState = inputState | eAct::JUMP;
	}

	m_animationManager->changeState(inputState, dir);
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
	std::map<ePart, Transform> transformList = m_animationManager->getTransform();

	m_program->useProgram();
	Model::s_stack.push(projection * view);
	m_ground->draw(m_program.get(), transformList);
	m_human->draw(m_program.get(), transformList);
	Model::s_stack.pop();
}
