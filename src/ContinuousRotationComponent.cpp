//
// Created by Robert on 15.12.2022.
//

#include "ContinuousRotationComponent.h"
#include "GameObject.h"

void ContinuousRotationComponent::Start(GameObject *object) {

}
void ContinuousRotationComponent::Update(GameObject *object, const SceneResources &resources) {

  object->transform.rotation += resources.deltaTime*5.0f*glm::vec3(
	  glm::radians(rotation.x),
	  glm::radians(rotation.y),
	  glm::radians(rotation.z)
  );
  object->transform.SetRotation(
	  object->transform.rotation + resources.deltaTime*
		  glm::vec3(
			  glm::radians(rotation.x),
			  glm::radians(rotation.y),
			  glm::radians(rotation.z)
		  )
  );
  std::cout << object->transform.rotation.x << std::endl;
}
void ContinuousRotationComponent::OnEnable() {

}
void ContinuousRotationComponent::OnDisable() {

}
