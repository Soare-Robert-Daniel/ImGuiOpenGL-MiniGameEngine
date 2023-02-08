//
// Created by Robert on 15.12.2022.
//

#ifndef CGE_SRC_CONTINUOUSROTATIONCOMPONENT_H_
#define CGE_SRC_CONTINUOUSROTATIONCOMPONENT_H_

#include "Component.h"
#include <iostream>

class ContinuousRotationComponent : public Component {
 public:
  glm::vec3 rotation;

  void Start(GameObject *object) override;
  void Update(GameObject *object, const SceneResources &resources) override;
  void OnEnable() override;
  void OnDisable() override;
};

#endif //CGE_SRC_CONTINUOUSROTATIONCOMPONENT_H_
