// GLProject.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <learnopengl/shader_m.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include "Polygon.cpp"
#include "Main.h"

using namespace glm;

int width = 800;
int height = 600;

vec3 cameraPos = vec3(0.0f, 0.0f, 4.0f);
vec3 cameraFront = vec3(0.0f, 0.0f, -1.0f);
vec3 cameraUp = vec3(0.0f, 1.0f, 0.0f);

void processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
	{

		 cameraPos = vec3(0.0f, 0.0f, 4.0f);
		cameraFront = vec3(0.0f, 0.0f, -1.0f);
		cameraUp = vec3(0.0f, 1.0f, 0.0f);
	}

	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
    const float cameraSpeed = 0.005f; 
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        cameraPos += cameraSpeed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        cameraPos -= cameraSpeed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        cameraPos -= normalize(cross(cameraFront, cameraUp)) * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        cameraPos += normalize(cross(cameraFront, cameraUp)) * cameraSpeed;
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
		cameraPos += cross(cameraFront,normalize(cross(cameraFront, cameraUp))) * cameraSpeed;
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
		cameraPos -= cross(cameraFront, normalize(cross(cameraFront, cameraUp))) * cameraSpeed;
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
		mat4 rotationMatrix = glm::rotate(mat4(1.0f), 0.001f, vec3(0.0f, 1.0f, 0.0f));
		vec4 rotatedVectorHomogeneous = rotationMatrix * vec4(cameraFront, 1.0f);
		cameraFront = vec3(rotatedVectorHomogeneous);
	}
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
		mat4 rotationMatrix = glm::rotate(mat4(1.0f), 0.001f, vec3(0.0f, -1.0f, 0.0f));
		vec4 rotatedVectorHomogeneous = rotationMatrix * vec4(cameraFront, 1.0f);
		cameraFront = vec3(rotatedVectorHomogeneous);
	}
}



int main()
{
	glfwInit();
	GLFWwindow* window = glfwCreateWindow(width, height, "Lecture 3", NULL, NULL);
	glfwMakeContextCurrent(window);
	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

	glEnable(GL_DEPTH_TEST);

	Shader ourShader("./shaders/vs/L3.vs", "./shaders/fs/L3.fs");

	std::vector<vec3> vertices0 = {};
	vertices0.push_back(vec3(0.01f, -3.0f, 0.0f));
	vertices0.push_back(vec3(-0.01f, -3.0f, 0.0f));
	vertices0.push_back(vec3(-0.01f, 3.0f, 0.0f));
	vertices0.push_back(vec3(0.01f, 3.0f, 0.0f));
	Polygon axis = Polygon(vertices0, vec3(0.0f, 0.0f, 0.0f));

	std::vector<vec3> vertices1 = {};
	vertices1.push_back(vec3(0.5f, 0.5f, 0.0f));
	vertices1.push_back(vec3(-0.5f, 0.5f, 0.0f));
	vertices1.push_back(vec3(-0.5f, -0.5f, 0.0f));
	vertices1.push_back(vec3(0.5f, -0.5f, 0.0f));
	Polygon polygon1 = Polygon(vertices1, vec3(1.0f, 0.0f, 0.0f));

	std::vector<vec3> vertices2 = {};
	vertices2.push_back(vec3(0.03f, 0.0f, 0.0f));
	vertices2.push_back(vec3(0.03f, -0.75f, 0.0f));
	vertices2.push_back(vec3(-0.03f, -0.75f, 0.0f));
	vertices2.push_back(vec3(-0.03f, 0.0f, 0.0f));
	Polygon polygon2 = Polygon(vertices2, vec3(0.0f, 0.0f, 1.0f));

	std::vector<vec3>vertices3 = {};
	vertices3.push_back(vec3(0.1f,-0.8f,0.0f));
	vertices3.push_back(vec3(0.1f, -1.0f, 0.0f));
	vertices3.push_back(vec3(-0.1f, -1.0f, 0.0f));
	vertices3.push_back(vec3(-0.1f, -0.8f, 0.0f));
	Polygon polygon3 = Polygon(vertices3, vec3(0.0f, 1.0f, 0.0f));

	std::vector<vec3>vertices4 = {};
	vertices4.push_back(vec3(0.01f, 0.0f, 0.01f));
	vertices4.push_back(vec3(0.01f, 0.4f, 0.01f));
	vertices4.push_back(vec3(-0.01f, 0.4f, 0.01f));
	vertices4.push_back(vec3(-0.01f, 0.0f, 0.01f));
	Polygon polygon4 = Polygon(vertices4, vec3(1.0f, 1.0f, 0.0f));

	std::vector<vec3>vertices5 = {};
	vertices5.push_back(vec3(0.01f, 0.0f, 0.015f));
	vertices5.push_back(vec3(0.01f, 0.35f, 0.015f));
	vertices5.push_back(vec3(-0.01f, 0.35f, 0.015f));
	vertices5.push_back(vec3(-0.01f, 0.0f, 0.015f));
	Polygon polygon5 = Polygon(vertices5, vec3(1.0f, 0.5f, 0.0f));

	std::vector<vec3>vertices6 = {};
	vertices6.push_back(vec3(0.01f, 0.0f, 0.02f));
	vertices6.push_back(vec3(0.01f, 0.3f, 0.02f));
	vertices6.push_back(vec3(-0.01f, 0.3f, 0.02f));
	vertices6.push_back(vec3(-0.01f, 0.0f, 0.02f));
	Polygon polygon6 = Polygon(vertices6, vec3(0.5f, 1.0f, 0.0f));



	ourShader.use();

	mat4 projection = mat4(1.0f);
	projection = perspective(radians(45.0f), (float)width / (float)height, 0.1f, 100.0f);
	ourShader.setMat4("projection", projection);

	while (!glfwWindowShouldClose(window))
	{
		processInput(window);

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		mat4 view = mat4(1.0f);
		view = translate(view, vec3(0.0f, 0.0f, -4.0f));
		view = lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
		ourShader.setMat4("view", view);

		mat4 transformation = mat4(1.0f);
		transformation = translate(transformation, vec3(-0.5f, -0.5f, 0.0f));
		axis.transformation(transformation);
		axis.draw(ourShader);


		polygon1.draw(ourShader);

		transformation = translate(transformation, vec3(0.5f, 0.0f, 0.0f));
		transformation = rotate(transformation, (float)cos(glfwGetTime()) / 2, vec3(0.0f, 0.0f, 1.0f));
		polygon2.transformation(transformation);
		polygon2.draw(ourShader);

		transformation = mat4(1.0f);
		transformation = translate(transformation, vec3(0.0f, -0.45f, 0.0f));
		transformation = rotate(transformation, (float)cos(glfwGetTime()) / 2, vec3(0.0f, 0.0f, 1.0f));
		polygon3.transformation(transformation);
		polygon3.draw(ourShader);
		transformation = mat4(1.0f);

		transformation = rotate(transformation, (float)glfwGetTime()/25, vec3(0.0f, 0.0f, -1.0f));
		polygon4.transformation(transformation);
		polygon4.draw(ourShader);

		transformation = mat4(1.0f);
		transformation = rotate(transformation, (float)glfwGetTime() / 15, vec3(0.0f, 0.0f, -1.0f));
		polygon5.transformation(transformation);
		polygon5.draw(ourShader);
		transformation = mat4(1.0f);
		transformation = rotate(transformation, (float)glfwGetTime() / 5, vec3(0.0f, 0.0f, -1.0f));
		polygon6.transformation(transformation);
		polygon6.draw(ourShader);
		

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}
