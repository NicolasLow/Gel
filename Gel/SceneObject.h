#pragma once

#include "Core.h"

#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <stdio.h>
#include <iostream>
#include <vector>
#include <string>
#include <typeinfo>

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>
#include <glm\gtx\rotate_vector.hpp>
#include "Shader.h"
#include "ResourceManager.h"
#include "Camera.h"
#include "System.h"
#include "Material.h"
#include "Transform.h"
#include "Component.h"
#include <functional>

namespace Gel {
	class GEL_API SceneObject {
	public:
		SceneObject() {};
		SceneObject(vector<Model*> models, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale);
		SceneObject(std::string name, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale);
		void Update();
		//Position
		void SetPosition(glm::vec3 position);
		void SetPosition(float x, float y, float z);
		void Translate(glm::vec3 translation);
		void Translate(float x, float y, float z);
		void AddPosition(glm::vec3 offset);
		void AddPosition(float x, float y, float z);

		//Rotation
		void SetRotation(glm::vec3 rotation);
		void SetRotation(float x, float y, float z);
		void Rotate(glm::vec3 axis, float angle);

		//Scale
		void SetScale(glm::vec3 scale);
		void SetScale(float x, float y, float z);
		void Scale(glm::vec3 scale);
		void Scale(float x, float y, float z);

		//Components
		void AddComponent(Component* newComponent);
		template<class ComponentType>
		ComponentType* GetComponent() {
			for each(Component* c in components) {
				ComponentType* tempComp = dynamic_cast<ComponentType*>(c);
				if (tempComp != nullptr) {
					return tempComp;
				}
			}
			std::cout << "The SceneObject \"" << this->name << "\" does not have this Component attached to it!" << std::endl;
			return new ComponentType;
		}
		Transform* GetTransform();

		std::string name;

	private:
		Transform transform;
		vector<Component*> components;
	};
}