#pragma once
#include "Core.h"
#include "RenderSettings.h"
#include "Input.h"
#include <stdio.h>
#include <iostream>
#include <vector>

#include <GL\glew.h>
#include <GLFW\glfw3.h>



namespace Gel {

	class SceneObject;

	static class GEL_API EngineHandler
	{
	public:
		static void InitEngine();
		static void LaunchEngine();
		static void TerminateEngine();
		static void SetWindowTitle(const char title[]);

		static GLFWwindow* window;
		static bool windowIsInFocus;
		static void windowFocusCallback(GLFWwindow* window, int inFocus);
		
		static std::vector<SceneObject*> sceneObjects;
		static std::vector<SceneObject*> instancedSceneObjects;
		static void UpdateSceneObjects();
	private:
	};

}