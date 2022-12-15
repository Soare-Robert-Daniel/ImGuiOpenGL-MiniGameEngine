//
// Created by Robert on 15.12.2022.
//

#ifndef CGE_SRC_EMPTYCOMPONENT_H_
#define CGE_SRC_EMPTYCOMPONENT_H_

class EmptyComponent : public Component {
 public:
  EmptyComponent() = default;

  void Start(GameObject *object) override {

  }
  void Update(GameObject *object, const SceneResources &resources) override {

  }
  void OnEnable() override {

  }
  void OnDisable() override {

  }
};

#endif //CGE_SRC_EMPTYCOMPONENT_H_
