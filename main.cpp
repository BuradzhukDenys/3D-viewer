#include "ViewerWindow.h"
#include "OpenglRenderSystem.h"
#include "GeometryPrimitives.h"

#include <glm/gtc/matrix_transform.hpp>

// Глобальна змінна або змінна для позиції куба
glm::vec3 cubePosition(0.0f, 0.0f, 0.0f);
static bool isPaused = false;

void renderScene(OpenglRenderSystem& rs)
{
	static const auto& data = GeometryPrimitives::createPyramidVertices();
	rs.renderTriangleSoup(data);
}

// Змінюємо координати куба
void moveCube(glm::vec3 offset)
{
	cubePosition += offset;
}

int main()
{
	constexpr int width = 640;
	constexpr int height = 480;

	OpenglRenderSystem rs;
	ViewerWindow window("MeshViewer", width, height);

	// Обробка клавіш
	window.setKeyCallback([&rs](KeyCode key, Action action, Modifier mods)
		{
			// Реагуємо на натискання (Press) або утримання (Repeat)
			if (action == Action::Press || action == Action::Repeat)
			{
				float speed = 0.2f;
				if (key == KeyCode::UP)
					moveCube({ 0, speed, 0 });

				if (key == KeyCode::DOWN)
					moveCube({ 0, -speed, 0 });

				if (key == KeyCode::LEFT)
					moveCube({ -speed, 0, 0 });

				if (key == KeyCode::RIGHT)
					moveCube({ speed, 0, 0 });

				if (key == KeyCode::SPACE)
					isPaused = !isPaused;
			}
		});

	rs.init();

	// Ставимо світло його так, щоб воно світило спереду-зверху-збоку
	rs.setupLight(0, glm::vec3(5.0f, 5.0f, 5.0f), glm::vec3(0.2f), glm::vec3(0.8f), glm::vec3(1.0f));
	rs.turnLight(0, true);

	// Відсуваємо і піднімаємо камеру, щоб бачити 3D перспективу
	glm::vec3 cameraPosition(3.0f, 3.0f, 5.0f);
	glm::vec3 lookAtCenter(0.0f, 0.0f, 0.0f);
	glm::vec3 cameraUpVector(0.0f, 1.0f, 0.0f);

	glm::mat4 viewMatrix = glm::lookAt(cameraPosition, lookAtCenter, cameraUpVector);
	rs.setViewMatrix(viewMatrix);

	glm::mat4 projMatrix = glm::perspective(glm::radians(60.0f), float(width) / float(height), 0.1f, 100.f);
	rs.setProjectionMatrix(projMatrix);

	float angle = 0.0f;
	double lastTime = glfwGetTime();

	while (!glfwWindowShouldClose(window.getGLFWHandle()))
	{
		double currentTime = glfwGetTime();
		float deltaTime = float(currentTime - lastTime);
		lastTime = currentTime;

		rs.setViewport(0, 0, window.getWidth(), window.getHeight());

		// Робимо фон світлішим, щоб краще бачити куб
		rs.clearDisplay(0.7f, 0.7f, 0.7f);

		// Обертання + Переміщення
		if (!isPaused)
			angle += 1.5f * deltaTime; // Швидкість обертання

		glm::mat4 world = glm::mat4(1.0f);
		world = glm::translate(world, cubePosition);       // Спочатку суваємо куди треба
		world = glm::rotate(world, angle, glm::vec3(0, 1, 0)); // Потім крутимо навколо Y

		rs.setWorldMatrix(world);

		renderScene(rs);
		glfwSwapBuffers(window.getGLFWHandle());
		glfwPollEvents();
	}

	return 0;
}