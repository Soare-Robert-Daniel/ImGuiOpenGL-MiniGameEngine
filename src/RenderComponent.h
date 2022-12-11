//
// Created by Robert on 28.11.2022.
//

#ifndef CGE_RENDERCOMPONENT_H
#define CGE_RENDERCOMPONENT_H

#include <map>
#include "Component.h"
#include "Model.h"
#include "Camera.h"
#include "Culling.h"

class RenderComponent : public Component {
 public:

  std::shared_ptr<Model> model;
  std::vector<std::shared_ptr<Texture>> textures;
  std::shared_ptr<Shader> shader;
  std::unique_ptr<CullingBoundingVolume> culling_bounding_volume;

  RenderComponent() = default;

  void Start(GameObject *object) override;

  void Update(GameObject *object, const SceneResources &resources) override;

  void OnEnable() override;

  void OnDisable() override;

  std::unique_ptr<Component> Clone() override;

  ~RenderComponent() override;
};

#endif //CGE_RENDERCOMPONENT_H
