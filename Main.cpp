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
// #include "Main.h"

using namespace glm;
using namespace std;

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
	const float cameraSpeed = 0.001f;
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		cameraPos += cameraSpeed * cameraFront;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		cameraPos -= cameraSpeed * cameraFront;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		cameraPos -= normalize(cross(cameraFront, cameraUp)) * cameraSpeed;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		cameraPos += normalize(cross(cameraFront, cameraUp)) * cameraSpeed;
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
		cameraPos += cross(cameraFront, normalize(cross(cameraFront, cameraUp))) * cameraSpeed;
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
		cameraPos -= cross(cameraFront, normalize(cross(cameraFront, cameraUp))) * cameraSpeed;
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
	{
		mat4 rotationMatrix = glm::rotate(mat4(1.0f), 0.001f, vec3(0.0f, 1.0f, 0.0f));
		vec4 rotatedVectorHomogeneous = rotationMatrix * vec4(cameraFront, 1.0f);
		cameraFront = vec3(rotatedVectorHomogeneous);
	}
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
	{
		mat4 rotationMatrix = glm::rotate(mat4(1.0f), 0.001f, vec3(0.0f, -1.0f, 0.0f));
		vec4 rotatedVectorHomogeneous = rotationMatrix * vec4(cameraFront, 1.0f);
		cameraFront = vec3(rotatedVectorHomogeneous);
	}
}

//! note the the drawing method should be GL_TRIANGLE_FAN for this to work
Polygon makeCirclePlate(float r, vec3 c, vec3 center = vec3(0.0f, 0.0f, 0.0f))
{
	vector<vec3> v;

	const int seg = 32;

	//? center
	v.push_back(center);

	//? c-r points
	for (int i = 0; i <= seg; i++)
	{
		float angle = (float)i * (2.0f * pi<float>() / seg);
		float x = cos(angle) * r;
		float y = sin(angle) * r;

		v.push_back(vec3(x, y, center.z));
	}

	return Polygon(v, c);
}

//! note the the drawing method should be GL_TRIANGLE_STRIP for this to work
Polygon make3dPoly(vector<vec3> vertices, vec3 c, float z)
{
	vector<vec3> v;
	
	//? front
	for (vec3 vec : vertices)
	{
		v.push_back(vec);
	}
	v.push_back(vertices.at(0));

	//? back
	for (vec3 vec : vertices)
	{
		v.push_back(vec3(vec.x, vec.y, vec.z + z));
	}
	v.push_back(vec3(vertices.at(0).x, vertices.at(0).y, vertices.at(0).z + z));
	
	//? sides
	int s = vertices.size();
	for (int i = 0; i < s; i++)
	{
		int n = (i + 1) % s;
		v.push_back(vertices.at(i));
		v.push_back(vec3(vertices.at(i).x, vertices.at(i).y, vertices.at(i).z + z));
		v.push_back(vertices.at(n));
		v.push_back(vec3(vertices.at(n).x, vertices.at(n).y, vertices.at(i).z + z));
		v.push_back(vertices.at(i));
	}

	return Polygon(v, c);
}
// Polygon make3dPoly(vector<vec3> vertices, vec3 c, float z) // GL_TRIANGLE_STRIP
// {
// 	vector<vec3> v;
//
// 	int n = vertices.size();
// 	for (vec3 v3 : vertices)
// 	{ // front
// 		v.push_back(v3);
// 	}
// 	v.push_back(vec3(vertices.at(0)));
//
// 	for (vec3 v3 : vertices)
// 	{ // back
// 		v.push_back(vec3(v3.x, v3.y, z));
// 	}
// 	v.push_back(vec3(vertices.at(0).x, vertices.at(0).y, z));
//
// 	// right
// 	v.push_back(vertices.at(0));
// 	v.push_back(vec3(vertices.at(0).x, vertices.at(0).y, z));
// 	v.push_back(vertices.at(3));
// 	v.push_back(vec3(vertices.at(3).x, vertices.at(3).y, z));
// 	v.push_back(vertices.at(0));
//
// 	// left
// 	v.push_back(vertices.at(1));
// 	v.push_back(vec3(vertices.at(1).x, vertices.at(1).y, z));
// 	v.push_back(vertices.at(2));
// 	v.push_back(vec3(vertices.at(2).x, vertices.at(2).y, z));
// 	v.push_back(vertices.at(1));
//
// 	// top
// 	v.push_back(vertices.at(0));
// 	v.push_back(vertices.at(1));
// 	v.push_back(vec3(vertices.at(0).x, vertices.at(0).y, z));
// 	v.push_back(vec3(vertices.at(1).x, vertices.at(1).y, z));
// 	v.push_back(vertices.at(0));
//
// 	// bottom
// 	v.push_back(vertices.at(3));
// 	v.push_back(vertices.at(2));
// 	v.push_back(vec3(vertices.at(3).x, vertices.at(3).y, z));
// 	v.push_back(vec3(vertices.at(2).x, vertices.at(2).y, z));
// 	v.push_back(vertices.at(3));
//
// 	return Polygon(v, c);
// }

int main()
{
	glfwInit();
	GLFWwindow *window = glfwCreateWindow(width, height, "Hamza Syrage & Nabil Mahmah", NULL, NULL);
	glfwMakeContextCurrent(window);
	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

	glEnable(GL_DEPTH_TEST);

	Shader ourShader("./shaders/vs/L3.vs", "./shaders/fs/L3.fs");

	vector<vec3> body = {};
	body.push_back(vec3(0.5f, 0.5f, 0.0f));
	body.push_back(vec3(-0.5f, 0.5f, 0.0f));
	body.push_back(vec3(-0.5f, -0.5f, 0.0f));
	body.push_back(vec3(0.5f, -0.5f, 0.0f));
	Polygon body3d = make3dPoly(body, vec3(0.8f, 0.0f, 0.0f), -1.0f);

	vector<vec3> headTringle = {};
	headTringle.push_back(vec3(0.501f, 0.501f, 0.0f));
	headTringle.push_back(vec3(0.001f, 0.9f, 0.0f));
	headTringle.push_back(vec3(-0.501f, 0.501f, 0.0f));
	Polygon headTringle3d = make3dPoly(headTringle, vec3(0.0f, 0.8f, 0.0f), -1.0f);

	vector<vec3> stick = {};
	stick.push_back(vec3(0.1f, -0.5f, -0.1f));
	stick.push_back(vec3(-0.1f, -0.5f, -0.1f));
	stick.push_back(vec3(-0.1f, -1.0f, -0.1f));
	stick.push_back(vec3(0.1f, -1.0f, -0.1f));
	Polygon stick3d = make3dPoly(stick, vec3(0.0f, 0.0f, 0.8f), -0.1f);

	vector<vec3> stickThing = {};
	stickThing.push_back(vec3(0.2f, -1.0f, -0.0f));
	stickThing.push_back(vec3(-0.2f, -1.0f, -0.0f));
	stickThing.push_back(vec3(-0.2f, -1.4f, -0.0f));
	stickThing.push_back(vec3(0.2f, -1.4f, -0.0f));
	Polygon stickThing3d = make3dPoly(stickThing, vec3(0.0f, 0.0f, 0.8f), -0.4f);

	Polygon plate = makeCirclePlate(0.4f, vec3(0.8f, 0.8f, 0.8f), vec3(0.0f, 0.0f, 0.01f));

	
	Polygon bolt3d = makeCirclePlate(0.03f, vec3(1.0f, 1.0f, 1.0f), vec3(0.0f, 0.0f, 0.02f));

	vector<vec3> secounds = {};
	secounds.push_back(vec3(0.005f, 0.30f, 0.016f));
	secounds.push_back(vec3(0.0f, 0.34f, 0.016f));
	secounds.push_back(vec3(-0.005f, 0.30f, 0.016f));
	secounds.push_back(vec3(-0.005f, -0.0f, 0.016f));
	secounds.push_back(vec3(0.005f, -0.0f, 0.016f));
	Polygon secounds3d = make3dPoly(secounds, vec3(0.0f, 0.0f, 0.0f), 0.0001f);

	vector<vec3> minutes = {};
	minutes.push_back(vec3(0.01f, 0.20f, 0.014f));
	minutes.push_back(vec3(0.0f, 0.24f, 0.014f));
	minutes.push_back(vec3(-0.01f, 0.20f, 0.014f));
	minutes.push_back(vec3(-0.01f, -0.0f, 0.014f));
	minutes.push_back(vec3(0.01f, -0.0f, 0.014f));
	Polygon minutes3d = make3dPoly(minutes, vec3(0.2f, 0.2f, 0.2f), 0.0001f);

	vector<vec3> hours = {};
	hours.push_back(vec3(0.02f, 0.15f, 0.012f));
	hours.push_back(vec3(0.0f, 0.19f, 0.012f));
	hours.push_back(vec3(-0.02f, 0.15f, 0.012f));
	hours.push_back(vec3(-0.02f, -0.0f, 0.012f));
	hours.push_back(vec3(0.02f, -0.0f, 0.012f));
	Polygon hours3d = make3dPoly(hours, vec3(0.4f, 0.4f, 0.4f), 0.0001f);

	ourShader.use();

	mat4 projection = mat4(1.0f);
	projection = perspective(radians(45.0f), (float)width / (float)height, 0.1f, 100.0f);
	ourShader.setMat4("projection", projection);

	while (!glfwWindowShouldClose(window))
	{
		processInput(window);

		glClearColor(0.12f, 0.24f, 0.24f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		mat4 view = mat4(1.0f);
		view = translate(view, vec3(0.0f, 0.0f, -4.0f));
		view = lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
		ourShader.setMat4("view", view);

		body3d.drawStrip(ourShader);
		 //body3d.drawOutline(ourShader);

		headTringle3d.drawStrip(ourShader);
		 //headTringle3d.drawOutline(ourShader);

		vec3 stickOrigin = vec3(0.0f, -0.5f, -0.1f);

		mat4 stickTransformation = mat4(1.0f);
		stickTransformation = translate(stickTransformation, -stickOrigin);
		//stickTransformation = rotate(stickTransformation, (float)cos(glfwGetTime() * 3.18) * 0.2f, vec3(0.0f, 0.0f, 1.0f));
		stickTransformation = rotate(
			stickTransformation, (float)cos(glfwGetTime() * 6.283f / 2) * 0.35f, vec3(0.0f, 0.0f, 1.0f));

		stickTransformation = translate(stickTransformation, stickOrigin);

		stick3d.transformation(stickTransformation);

		stickThing3d.transformation(stickTransformation);

		stick3d.drawStrip(ourShader);
		 //stick3d.drawOutline(ourShader);

		stickThing3d.drawStrip(ourShader);
		 //stickThing3d.drawOutline(ourShader);

		plate.drawFan(ourShader);
		 //plate.drawOutline(ourShader);

		vec3 centerOrigin = vec3(0.0f, 0.0f, -0.0f);

		mat4 secoundsTransformation = mat4(1.0f);
		secoundsTransformation = translate(secoundsTransformation, -centerOrigin);
		secoundsTransformation = rotate(secoundsTransformation, -radians((float)(int)glfwGetTime())*6, vec3(0.0f, 0.0f, 1.0f));
		secoundsTransformation = translate(secoundsTransformation, centerOrigin);

		secounds3d.transformation(secoundsTransformation);
		secounds3d.drawFan(ourShader);
		 //secounds3d.drawOutline(ourShader);

		mat4 minutesTransformation = mat4(1.0f);
		minutesTransformation = translate(minutesTransformation, -centerOrigin);
		minutesTransformation = rotate(minutesTransformation, -radians((float)(int)glfwGetTime())*6 / 60, vec3(0.0f, 0.0f, 1.0f));
		minutesTransformation = translate(minutesTransformation, centerOrigin);

		minutes3d.transformation(minutesTransformation);
		minutes3d.drawFan(ourShader);
		 //minutes3d.drawOutline(ourShader);

		mat4 hoursTransformation = mat4(1.0f);
		hoursTransformation = translate(hoursTransformation, -centerOrigin);
		hoursTransformation = rotate(hoursTransformation, -radians((float)(int)glfwGetTime())*6 / 60 / 60, vec3(0.0f, 0.0f, 1.0f));
		hoursTransformation = translate(hoursTransformation, centerOrigin);

		hours3d.transformation(hoursTransformation);
		hours3d.drawFan(ourShader);
		 //hours3d.drawOutline(ourShader);

		// bolt3d.drawStrip(ourShader);
		bolt3d.drawFan(ourShader);
		 //bolt3d.drawOutline(ourShader);

		// cout << (float)(int)glfwGetTime() << endl;
		// cout << radians((float)(int)glfwGetTime()) << endl;

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}
