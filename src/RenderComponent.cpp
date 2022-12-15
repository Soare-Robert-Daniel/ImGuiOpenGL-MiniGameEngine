//
// Created by Robert on 28.11.2022.
//

#include "RenderComponent.h"
#include "GameObject.h"

void RenderComponent::Start(GameObject *object) {
  culling_bounding_volume = std::make_unique<SphereVolume>(SphereVolume{object->transform.position, 0.5f});
}

void RenderComponent::Update(GameObject *object, const SceneResources &resources) {
  culling_bounding_volume->setPosition(object->transform.position);
  if (!culling_bounding_volume->isTransformOnFrustum(resources.frustum, object->transform)) {
	return;
  }

  shader->Use();
  int loaded_textures_index = 0;
  for (auto &texture : textures) {
	if (loaded_textures_index > shader->data.texture_num) {
	  break;
	}

	auto texture_location = "texture" + std::to_string(loaded_textures_index);
	texture->ActivateAndBind(loaded_textures_index);
	shader->SetInt(texture_location, loaded_textures_index);
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
