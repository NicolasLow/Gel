#include <Gel.h>
#include "UnlitMaterial.h"

class SandboxApp : public Gel::Application {
public:
	SandboxApp() {

	}
	~SandboxApp() {

	}
	Gel::SceneObject floorObject;
	UnlitMaterial* floorMaterial;
	Gel::SceneObject cubeObject;
	void OnStart() override {
		Gel::EngineHandler::SetWindowTitle("Test Window");
		Gel::RenderSettings::SetClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		Gel::ResourceManager::UnpackResources("Resources/Resources.ger");
		Gel::RenderSettings::SetCullingMode(Gel::CullingMode::CullingMode_Back);
		Gel::RenderSettings::SetDepthTestMode(Gel::DepthTestMode::DepthTest_Enabled);
		Gel::Camera::SetPosition(glm::vec3(4.0f, 3.0f, 15.0f));

		floorMaterial = new UnlitMaterial();
		floorMaterial->texture = Gel::TextureContainer::GetTextureData("Default_Pattern");
		floorMaterial->SetShader(Gel::ShaderContainer::GetShader("Unlit"));

		floorObject = Gel::SceneObject("FloorObject", glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
		floorObject.AddComponent(new Gel::ModelRendererComponent(floorObject.GetTransform()));
		Gel::Model floorModel = Gel::ModelContainer::GetModel("Sample_Floor");
		floorModel.SetMaterial(0, floorMaterial);
		floorObject.GetComponent<Gel::ModelRendererComponent>()->SetModel(floorModel);
		floorObject.AddComponent(new Gel::RigidBodyComponent(floorObject.GetTransform(), Gel::BodyType::Box, 0.0f));
		floorObject.GetComponent<Gel::RigidBodyComponent>()->SetSize(btVector3(10.0f, 1.0f, 10.0f));

		cubeObject = Gel::SceneObject("CubeObject", glm::vec3(0.0f, 10.0f, 0.0f), glm::vec3(28.0f, 0.0f, 28.0f), glm::vec3(1.0f, 1.0f, 1.0f));
		cubeObject.AddComponent(new Gel::ModelRendererComponent(cubeObject.GetTransform()));
		Gel::Model cubeModel = Gel::ModelContainer::GetModel("Sample_Cube");
		cubeModel.SetMaterial(0, floorMaterial);
		cubeObject.GetComponent<Gel::ModelRendererComponent>()->SetModel(cubeModel);
		cubeObject.AddComponent(new Gel::RigidBodyComponent(cubeObject.GetTransform(), Gel::BodyType::Box, 1.0f));
	}
	void OnUpdate() override {
		if (Gel::Input::GetKey(GLFW_KEY_SPACE)) {
			Gel::EngineHandler::TerminateEngine();
		}
		floorObject.Update();
		cubeObject.Update();
	}
	void OnTerminate() override {
		
	}
};

Gel::Application* Gel::CreateApplication() {
	return new SandboxApp();
}