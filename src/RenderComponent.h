//
// Created by Robert on 28.11.2022.
//

#ifndef CGE_RENDERCOMPONENT_H
#define CGE_RENDERCOMPONENT_H

#include <map>
#include "Component.h"
#include "Model.h"

class RenderComponent : public Component {
public:

    std::shared_ptr<Model> model;

    RenderComponent() = default;

    void Start() override;

    void Update() override;

    void OnEnable() override;

    void OnDisable() override;

    std::unique_ptr<Component> Clone() override;

    ~RenderComponent() override;
};


#endif //CGE_RENDERCOMPONENT_H
