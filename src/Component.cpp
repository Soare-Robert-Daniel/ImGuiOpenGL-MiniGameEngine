//
// Created by Robert on 28.11.2022.
//

#include "Component.h"

Component::~Component() = default;

bool Component::IsActive() const {
  return active;
}

void Component::Activate() {
  active = true;
  OnEnable();
}

void Component::Deactivate() {
  active = false;
  OnDisable();
}

std::unique_ptr<Component> Component::Clone() {
  return {};
}
