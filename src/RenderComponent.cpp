//
// Created by Robert on 28.11.2022.
//

#include "RenderComponent.h"
#include "GameObject.h"

void RenderComponent::Start(GameObject *object) {
	culling_bounding_volume = std::make_unique<SphereVolume>( SphereVolume{ glm::vec3(0), 0.5f });
}

void RenderComponent::Update(GameObject *object, const SceneResources &resources) {

  if( ! culling_bounding_volume->isTransformOnFrustum(resources.frustum, object->transform) ) {
	return;
  }

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

  shader->SetVector3("lightPos", resources.lighting_data.position);
  shader->SetVector3("lightColor", resources.lighting_data.color);
  shader->SetVector3("viewPos", resources.camera->pos);

  model->RenderMeshes();

  object->wasRendered = true;
}

void RenderComponent::OnEnable() {

}

void RenderComponent::OnDisable() {

}

std::unique_ptr<Component> RenderComponent::Clone() {
  return Component::Clone();
}

RenderComponent::~RenderComponent() = default;
