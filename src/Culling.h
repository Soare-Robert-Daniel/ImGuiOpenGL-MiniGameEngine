//
// Created by Robert on 10.12.2022.
//

#ifndef CGE_SRC_CULLING_H_
#define CGE_SRC_CULLING_H_

#include <memory>
#include "Transform.h"
#include "Camera.h"

// +------ Helping Structure ------+

struct Plan {
  glm::vec3 normal = { 0.f, 1.f, 0.f };
  float distance = 0.0f;

  Plan() = default;

  Plan(const glm::vec3& position, const glm::vec3& norm)
	  : normal(glm::normalize(norm)),
		distance(glm::dot(normal, position))
  {}

  float getSignedDistanceToPlan(const glm::vec3& point) const
  {
	return glm::dot(normal, point) - distance;
  }
};

struct Frustum {
  Plan topFace;
  Plan bottomFace;

  Plan rightFace;
  Plan leftFace;

  Plan farFace;
  Plan nearFace;
};

Frustum createFrustumFromCamera(std::shared_ptr<Camera> camera, float aspect, float fovY, float zNear, float zFar);

struct CullingBoundingVolume {
  virtual bool IsTransformOnFrustum(const Frustum& frustum, const Transform& transform) const = 0;
  virtual bool IsOnOrForwardPlan(const Plan& plan) const = 0;
  virtual void SetPosition(const glm::vec3& pos) = 0;

  bool isOnFrustum(const Frustum& frustum) const
  {
	return (IsOnOrForwardPlan(frustum.leftFace) &&
		IsOnOrForwardPlan(frustum.rightFace) &&
		IsOnOrForwardPlan(frustum.topFace) &&
		IsOnOrForwardPlan(frustum.bottomFace) &&
		IsOnOrForwardPlan(frustum.nearFace) &&
		IsOnOrForwardPlan(frustum.farFace));
  };
};

struct SphereVolume : CullingBoundingVolume {
  glm::vec3 center{ 0.f, 0.f, 0.f };
  float radius{ 0.f };

  SphereVolume(const glm::vec3& inCenter, float inRadius)
	  : CullingBoundingVolume{}, center{ inCenter }, radius{ inRadius }
  {}

  bool IsOnOrForwardPlan(const Plan& plan) const final
  {
	return plan.getSignedDistanceToPlan(center) > -radius;
  }

  // FIX: Rotation
  bool IsTransformOnFrustum(const Frustum& frustum, const Transform& transform) const final
  {
	// Preia dimensiunea obiectului
	const glm::vec3 global_scale = transform.getGlobalScale();

	// Calculeaza centrul modelului
	const glm::vec3 global_center{transform.model_matrix * glm::vec4(center, 1.f) };

	// Gaseste dimensiunea sferei care incadreaza obiectul
	const float maxScale = std::fmax(std::fmax(global_scale.x, global_scale.y), global_scale.z);

	// Creaza sfera
	SphereVolume global_sphere(global_center, radius * (maxScale * 0.5f));

	// Verfica daca sfera se afla in frustum
	return (global_sphere.IsOnOrForwardPlan(frustum.leftFace) &&
		global_sphere.IsOnOrForwardPlan(frustum.rightFace) &&
		global_sphere.IsOnOrForwardPlan(frustum.farFace) &&
		global_sphere.IsOnOrForwardPlan(frustum.nearFace) &&
		global_sphere.IsOnOrForwardPlan(frustum.topFace) &&
		global_sphere.IsOnOrForwardPlan(frustum.bottomFace));
  };

  void SetPosition(const glm::vec3 &pos) override {
	center = pos;
  }
};

bool IsTransformOnFrustumWithSphereVolume(const Frustum& frustum, const Transform& transform);

#endif //CGE_SRC_CULLING_H_
