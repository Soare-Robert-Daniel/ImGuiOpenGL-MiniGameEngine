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

Frustum createFrustumFromCamera(const std::shared_ptr<Camera> camera, float aspect, float fovY, float zNear, float zFar);

struct CullingBoundingVolume {
  virtual bool isTransformOnFrustum(const Frustum& frustum, const Transform& transform) const = 0;
  virtual bool isOnOrForwardPlan(const Plan& plan) const = 0;

  bool isOnFrustum(const Frustum& frustum) const
  {
	return (isOnOrForwardPlan(frustum.leftFace) &&
		isOnOrForwardPlan(frustum.rightFace) &&
		isOnOrForwardPlan(frustum.topFace) &&
		isOnOrForwardPlan(frustum.bottomFace) &&
		isOnOrForwardPlan(frustum.nearFace) &&
		isOnOrForwardPlan(frustum.farFace));
  };
};

struct SphereVolume : CullingBoundingVolume {
  glm::vec3 center{ 0.f, 0.f, 0.f };
  float radius{ 0.f };

  SphereVolume(const glm::vec3& inCenter, float inRadius)
	  : CullingBoundingVolume{}, center{ inCenter }, radius{ inRadius }
  {}

  bool isOnOrForwardPlan(const Plan& plan) const final
  {
	return plan.getSignedDistanceToPlan(center) > -radius;
  }

  // FIX: Rotation
  bool isTransformOnFrustum(const Frustum& frustum, const Transform& transform) const final
  {
	// Preia dimensiunea obiectului
	const glm::vec3 globalScale = transform.getGlobalScale();

	// Calculeaza centrul modelului
	const glm::vec3 globalCenter{ transform.modelMatrix * glm::vec4(center, 1.f) };

	// Gaseste dimensiunea sferei care incadreaza obiectul
	const float maxScale = std::fmax(std::fmax(globalScale.x, globalScale.y), globalScale.z);

	// Creaza sfera
	SphereVolume globalSphere(globalCenter, radius * (maxScale * 0.5f));

	// Verfica daca sfera se afla in frustum
	return (globalSphere.isOnOrForwardPlan(frustum.leftFace) &&
		globalSphere.isOnOrForwardPlan(frustum.rightFace) &&
		globalSphere.isOnOrForwardPlan(frustum.farFace) &&
		globalSphere.isOnOrForwardPlan(frustum.nearFace) &&
		globalSphere.isOnOrForwardPlan(frustum.topFace) &&
		globalSphere.isOnOrForwardPlan(frustum.bottomFace));
  };
};

bool IsTransformOnFrustumWithSphereVolume(const Frustum& frustum, const Transform& transform);

#endif //CGE_SRC_CULLING_H_
