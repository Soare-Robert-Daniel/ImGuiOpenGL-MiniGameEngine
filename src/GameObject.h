//
// Created by Robert on 01.11.2022.
//

#ifndef CGE_GAMEOBJECT_H
#define CGE_GAMEOBJECT_H

#include <string>
#include <vector>
#include <optional>
#include <algorithm>
#include <iostream>
#include <iterator>
#include <ranges>
#include <vector>
#include "Component.h"
#include "Transform.h"

class GameObject {

 public:
  unsigned int componentId{0};
  std::string name;
  Transform transform{};
  std::vector<std::shared_ptr<Component>> components{};
  std::vector<std::shared_ptr<GameObject>> children{};
  std::shared_ptr<GameObject> parent;
  bool wasRendered;

  GameObject() = default;

  virtual void Start();
  virtual void Update(const SceneResources &resources);
  virtual void UpdateChildrenModelView();

  // Components
  virtual void AddComponent(std::shared_ptr<Component> component);
  virtual void AddComponents(std::vector<std::shared_ptr<Component>> otherComponents);

  virtual std::vector<std::shared_ptr<Component>> GetComponents() const;
  virtual std::optional<std::shared_ptr<Component>> GetComponentByName(const std::string &componentName);

  virtual std::optional<std::shared_ptr<Component>> GetComponent(CType componentType) const;
  virtual std::vector<std::shared_ptr<Component>> GetComponents(CType componentType) const;

  // Children
  virtual void AddChildren(std::shared_ptr<GameObject> obj);
  virtual std::vector<std::shared_ptr<GameObject>> GetChildren() const;

  virtual std::optional<std::shared_ptr<GameObject>> FindChild(const std::string &objectName) const;

  virtual void Destroy();

  virtual void RemoveDeadPointers();

  virtual int CountRenderedObjects();

};

#endif //CGE_GAMEOBJECT_H
