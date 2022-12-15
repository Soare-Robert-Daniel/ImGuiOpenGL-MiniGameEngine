//
// Created by Robert on 15.12.2022.
//

#ifndef CGE_SRC_SCENEPARSER_H_
#define CGE_SRC_SCENEPARSER_H_

#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>
#include "SceneResources.h"
#include "GameObject.h"
#include "EmptyComponent.h"
#include "ContinuousRotationComponent.h"
#include "RenderComponent.h"
#include "Global.h"

using json = nlohmann::json;

class SceneParser {

 public:
  static void ParseConfigFile(const std::string &fileName,
							  SceneResources &scene_resources,
							  std::shared_ptr<GameObject> &scene_root) {
	std::ifstream f(fileName);

	json data = json::parse(f);

	if (data.contains("sceneRoot")) {
	  scene_root = ParseGameObject(data.at("sceneRoot"));
	}
  }

  static std::shared_ptr<GameObject> ParseGameObject(const json &raw_game_object) {
	std::shared_ptr<GameObject> obj(new GameObject());

	if (raw_game_object.contains("transform")) {
	  auto t = raw_game_object.at("transform");

	  if (t.contains("position")) {
		obj->transform.position.x = t.at("position").at("x").get<float>();
		obj->transform.position.y = t.at("position").at("y").get<float>();
		obj->transform.position.z = t.at("position").at("z").get<float>();
	  }

	  if (t.contains("rotation")) {
		obj->transform.rotation.x = t.at("rotation").at("x").get<float>();
		obj->transform.rotation.y = t.at("rotation").at("y").get<float>();
		obj->transform.rotation.z = t.at("rotation").at("z").get<float>();
	  }

	  if (t.contains("scale")) {
		obj->transform.scale.x = t.at("scale").at("x").get<float>();
		obj->transform.scale.y = t.at("scale").at("y").get<float>();
		obj->transform.scale.z = t.at("scale").at("z").get<float>();
	  }
	}

	if (raw_game_object.contains("children")) {
	  auto c = raw_game_object.at("children");
	  for (auto &child : c) {
		auto result = ParseGameObject(child);
		result->parent = obj;
		obj->AddChildren(result);
	  }
	}

	if (raw_game_object.contains("components")) {
	  auto c = raw_game_object.at("components");
	  for (auto &child : c) {
		obj->AddComponent(ParseComponent(child));
	  }
	}

	return obj;
  }

  static std::shared_ptr<Component> ParseComponent(json raw_c) {
	std::shared_ptr<EmptyComponent> empty(new EmptyComponent());

	if (!raw_c.contains("type")) {
	  return (std::shared_ptr<Component>)empty;
	}

	auto t = raw_c.at("type").get<std::string>();

	if (t=="rotation") {
	  std::shared_ptr<ContinuousRotationComponent> rot(new ContinuousRotationComponent());

	  if (raw_c.contains("rotation")) {
		rot->rotation.x = raw_c.at("rotation").at("x").get<float>();
		rot->rotation.y = raw_c.at("rotation").at("y").get<float>();
		rot->rotation.z = raw_c.at("rotation").at("z").get<float>();
	  }

	  return (std::shared_ptr<Component>)rot;
	}

	if (t=="render") {
	  std::shared_ptr<RenderComponent> render(new RenderComponent());

	  if (raw_c.contains("modelRef") && Global::HasModel(raw_c.at("modelRef").get<std::string>())) {
		render->model = Global::GetModel(raw_c.at("modelRef").get<std::string>());
	  }

	  if (raw_c.contains("shaderRef") && Global::HasShader(raw_c.at("shaderRef").get<std::string>())) {
		render->shader = Global::GetShader(raw_c.at("shaderRef").get<std::string>());
	  }

	  if (raw_c.contains("texturesRef")) {
		render->textures = {};
		for(auto& texture : raw_c.at("texturesRef")) {
		  auto name = texture.get<std::string>();
		  if( Global::HasTexture(name) ) {
			render->textures.push_back(Global::GetTexture(name));
		  }
		}
	  }

	  return (std::shared_ptr<Component>)render;
	}

	return (std::shared_ptr<Component>)empty;
  }
};

#endif //CGE_SRC_SCENEPARSER_H_
