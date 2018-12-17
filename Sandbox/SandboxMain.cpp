#include <Gel.h>
#include "UnlitMaterial.h"
#include "InvertColorEffect.h"
#include "PixelationEffect.h"

void OnCollisionStay(Gel::RigidBodyComponent* other) {
	std::cout << other->sceneObject->name << std::endl;
}

class SandboxApp : public Gel::Application {
public:
	SandboxApp() {

	}
	~SandboxApp() {

	}

	Gel::SceneObject* floorObject;
	UnlitMaterial* floorMaterial;
	UnlitMaterial* shotgunMaterial;
	Gel::SceneObject* cubeObject;
	Gel::SceneObject* shotgun;
	Gel::SceneObject* cameraObject;

	void OnStart() override {
		Gel::EngineHandler::SetWindowTitle("Test Window");
		Gel::RenderSettings::SetClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		Gel::ResourceManager::UnpackResources("Resources/Resources.ger");
		Gel::RenderSettings::SetCullingMode(Gel::CullingMode::CullingMode_Back);
		Gel::RenderSettings::SetDepthTestMode(Gel::DepthTestMode::DepthTest_Enabled);
		Gel::Input::SetCursorMode(Gel::EngineHandler::window, Gel::CursorMode::CursorMode_Disabled);
		Gel::Camera::SetPosition(glm::vec3(0.0f, 3.0f, 15.0f));
		Gel::RenderSettings::postProcessingStack.AddEffect(new InvertColorEffect());
		Gel::RenderSettings::postProcessingStack.AddEffect(new PixexlationEffect());

		floorMaterial = new UnlitMaterial();
		floorMaterial->texture = Gel::TextureContainer::GetTextureData("Default_Pattern");
		floorMaterial->color = glm::vec3(0.3f, 1.0f, 0.0f);
		floorMaterial->SetShader(Gel::ShaderContainer::GetShader("Unlit"));

		shotgunMaterial = new UnlitMaterial();
		shotgunMaterial->texture = Gel::TextureContainer::GetTextureData("Shotgun");
		shotgunMaterial->color = glm::vec3(1.0f, 1.0f, 1.0f);
		shotgunMaterial->SetShader(Gel::ShaderContainer::GetShader("Unlit"));

		floorObject = new Gel::SceneObject("FloorObject", glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
		floorObject->AddComponent(new Gel::ModelRendererComponent(floorObject->GetTransform()));
		Gel::Model floorModel = Gel::ModelContainer::GetModel("Sample_Floor");
		floorModel.SetMaterial(0, floorMaterial);
		floorObject->GetComponent<Gel::ModelRendererComponent>()->SetModel(floorModel);
		floorObject->AddComponent(new Gel::RigidBodyComponent(floorObject->GetTransform(), Gel::BodyType::Box, 0.0f));
		floorObject->GetComponent<Gel::RigidBodyComponent>()->SetSize(btVector3(8.0f, 0.01f, 8.0f));

		cubeObject = new Gel::SceneObject("CubeObject", glm::vec3(0.0f, 5.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
		cubeObject->AddComponent(new Gel::ModelRendererComponent(cubeObject->GetTransform()));
		Gel::Model cubeModel = Gel::ModelContainer::GetModel("Sample_Cube");
		cubeModel.SetMaterial(0, floorMaterial);
		cubeObject->GetComponent<Gel::ModelRendererComponent>()->SetModel(cubeModel);
		cubeObject->AddComponent(new Gel::RigidBodyComponent(cubeObject->GetTransform(), Gel::BodyType::Box, 1.0f));
		cubeObject->GetComponent<Gel::RigidBodyComponent>()->SetSize(btVector3(2.0f, 2.0f, 2.0f));
		cubeObject->GetComponent<Gel::RigidBodyComponent>()->OnCollisionExitCallback = OnCollisionStay;

		cameraObject = new Gel::SceneObject("Camera", glm::vec3(0.0f, 2.0f, -15.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
		cameraObject->AddComponent(new Gel::CameraComponent(cameraObject->GetTransform()));

		shotgun = new Gel::SceneObject("ShotgunObject", glm::vec3(-0.3f, -0.5f, 1.5f), glm::vec3(0.0f, 180.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
		shotgun->AddComponent(new Gel::ModelRendererComponent(shotgun->GetTransform()));
		Gel::Model shotgunModel = Gel::ModelContainer::GetModel("Shotgun");
		shotgunModel.SetMaterial(0, shotgunMaterial);
		shotgun->GetComponent<Gel::ModelRendererComponent>()->SetModel(shotgunModel);
		shotgun->GetTransform()->parent = cameraObject->GetTransform();
		
	}
	void OnUpdate() override {
		if (Gel::Input::GetKey(GLFW_KEY_W)) {
			cameraObject->GetTransform()->Translate(cameraObject->GetTransform()->forward * Gel::System::GetDeltaTime() * 10.0f);
		}
		if (Gel::Input::GetKey(GLFW_KEY_S)) {
			cameraObject->GetTransform()->Translate(cameraObject->GetTransform()->forward * Gel::System::GetDeltaTime() * -10.0f);
		}
		if (Gel::Input::GetKey(GLFW_KEY_D)) {
			cameraObject->GetTransform()->Translate(cameraObject->GetTransform()->right * Gel::System::GetDeltaTime() * -10.0f);
		}
		if (Gel::Input::GetKey(GLFW_KEY_A)) {
			cameraObject->GetTransform()->Translate(cameraObject->GetTransform()->right * Gel::System::GetDeltaTime() * 10.0f);
		}
		if (Gel::Input::GetMouseButtonDown(0)) {
			Gel::RaycastHitResult hitResult = Gel::PhysicsEngine::RayCast(cameraObject->GetTransform()->position, cameraObject->GetTransform()->forward, 50.0f);
			if (hitResult.hit) {
				hitResult.body->AddForce(cameraObject->GetTransform()->forward * 10.0f + glm::vec3(0.0f, 10.0f, 0.0f), Gel::ForceType::Impulse);
			}
		}
		cameraObject->GetTransform()->Rotate(glm::vec3(0.0f, 1.0f, 0.0f), -Gel::Input::GetMouseOffset(0) * 0.3f * Gel::System::GetDeltaTime());
		glm::vec3 right = cameraObject->GetTransform()->right;
		cameraObject->GetTransform()->Rotate(right, -Gel::Input::GetMouseOffset(1) * 0.3f * Gel::System::GetDeltaTime());
		Gel::PhysicsEngine::CheckForCollision();
	}
	void OnTerminate() override {
		delete floorObject;
		delete floorMaterial;
		delete shotgunMaterial;
		delete cubeObject;
		delete shotgun;
		delete cameraObject;
	}
};

Gel::Application* Gel::CreateApplication() {
	return new SandboxApp();
}