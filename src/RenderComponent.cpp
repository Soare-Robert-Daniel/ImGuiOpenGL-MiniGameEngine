//
// Created by Robert on 28.11.2022.
//

#include "RenderComponent.h"
#include "GameObject.h"

void RenderComponent::Start(GameObject *object) {
  culling_bounding_volume = std::make_unique<SphereVolume>(SphereVolume{glm::vec3(0.5), 1.0f});
}

void RenderComponent::Update(GameObject *object, const SceneResources &resources) {
  culling_bounding_volume->SetPosition(object->transform.GetGlobalLocation(object));
  if (!culling_bounding_volume->IsTransformOnFrustum(resources.frustum, object->transform)) {
	return;
  }

  shader->Use();
  int loaded_textures_index = 0;
  for (auto &texture : textures) {
	if (loaded_textures_index >= shader->data.texture_num) {
	  break;
	}

	auto texture_location = "texture" + std::to_string(loaded_textures_index);
	texture->ActivateAndBind(loaded_textures_index);
	shader->SetInt(texture_location, loaded_textures_index);
	loaded_textures_index += 1;
  }

  int loaded_normal_maps = 0;
  for (auto &texture : normalMap) {
	if (loaded_normal_maps >= shader->data.normal_num) {
	  break;
	}

	// std::cout << GL_TEXTURE0<< " " << GL_TEXTURE1 << " " << GL_TEXTURE0 + loaded_normal_maps + loaded_textures_index << std::endl;
	auto texture_location = "normalMap" + std::to_string(loaded_normal_maps);
	texture->ActivateAndBind(loaded_normal_maps + loaded_textures_index);
	shader->SetInt(texture_location, loaded_normal_maps + loaded_textures_index);
	loaded_normal_maps += 1;
  }

  shader->SetMatrix("model", object->transform.GetSceneView());
  shader->SetMatrix("view", resources.camera->GetView());
  shader->SetMatrix("projection", resources.projection);

  shader->SetVector3("lightPos", resources.lighting_data.position);
  shader->SetVector3("lightColor", resources.lighting_data.color);
  shader->SetVector3("viewPos", resources.camera->pos);

  model->RenderMeshes();

  shader->Stop();

  for (auto &texture : textures) {
	texture->Unbind();
  }

  for (auto &texture : normalMap) {
	texture->Unbind();
  }


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
