//
// Created by Robert on 28.11.2022.
//

#ifndef CGE_COMPONENT_H
#define CGE_COMPONENT_H

#include <string>
#include <iostream>
#include "Camera.h"
#include "SceneResources.h"

enum class CType {
  Transform,
  Unknown
};

class GameObject;

class Component {
 public:
  CType ctype{CType::Unknown};
  std::string name;
  bool active{true};
  std::shared_ptr<GameObject> object;

  Component() = default;

  virtual void Start(GameObject *object) = 0;
  virtual void Update(GameObject *object, const SceneResources &resources) = 0;

  virtual void OnEnable() = 0;
  virtual void OnDisable() = 0;

  virtual std::unique_ptr<Component> Clone();

  bool IsActive() const;
  void Activate();
  void Deactivate();

  virtual ~Component();
};

#endif //CGE_COMPONENT_H
