//
// Created by Robert on 28.11.2022.
//

#ifndef CGE_RENDERCOMPONENT_H
#define CGE_RENDERCOMPONENT_H


#include "Component.h"

class RenderComponent : public Component {
public:
    RenderComponent() = default;

    void Start() override;

    void Update() override;

    void OnEnable() override;

    void OnDisable() override;

    std::unique_ptr<Component> Clone() override;

    ~RenderComponent() override;
};


#endif //CGE_RENDERCOMPONENT_H
