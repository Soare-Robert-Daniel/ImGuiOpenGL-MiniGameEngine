//
// Created by Robert on 28.11.2022.
//

#include "RenderComponent.h"
#include "GameObject.h"

void RenderComponent::Start(GameObject *object) {

}

void RenderComponent::Update(GameObject *object, const SceneResources &resources) {
  shader->Use();
  int loadedTexturesIndex = 0;
  for (auto &texture : textures) {
	if (loadedTexturesIndex > shader->data.textureNum) {
	  break;
	}

	auto textureLocation = "texture" + std::to_string(loadedTexturesIndex);
	texture->ActivateAndBind(loadedTexturesIndex);
	shader->SetInt(textureLocation, loadedTexturesIndex);
  }

  shader->SetMatrix("model", object->transform.GetSceneView());
  shader->SetMatrix("view", resources.camera->GetView());
  shader->SetMatrix("projection", resources.projection);

  model->RenderMeshes();
}

void RenderComponent::OnEnable() {

}

void RenderComponent::OnDisable() {

}

std::unique_ptr<Component> RenderComponent::Clone() {
  return Component::Clone();
}

RenderComponent::~RenderComponent() = default;
