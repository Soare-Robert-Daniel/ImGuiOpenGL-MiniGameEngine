//
// Created by Robert on 01.11.2022.
//

#include "GameObject.h"

void GameObject::Start() {
    for(auto& c : components) {
        if( c != nullptr ) {
            c->Start();
        }
    }

    for(auto& g : children) {
        if( g != nullptr ) {
            g->Start();
        }
    }
}

void GameObject::Update() {
    for(auto& c : components) {
        if( c != nullptr ) {
            c->Update();
        }
    }

    for(auto& g : children) {
        if( g != nullptr ) {
            g->Update();
        }
    }
}

void GameObject::Destroy() {

}

void GameObject::AddComponent(std::shared_ptr<Component> component) {
    components.push_back(std::move(component));
}

void GameObject::AddComponents(std::vector<std::shared_ptr<Component>> otherComponents) {
    std::move(std::begin(otherComponents), std::end(otherComponents), std::back_inserter(components));
}

std::optional<std::shared_ptr<Component>> GameObject::GetComponent(CType componentType) const {

    for(auto& c : components) {
        if( c->ctype == componentType ) {
            return c;
        }
    }
    return std::nullopt;
}

std::vector<std::shared_ptr<Component>> GameObject::GetComponents(CType componentType) const {
    std::vector<std::shared_ptr<Component>> results;

    for(auto& c : components) {
        if( c->ctype == componentType ) {
            results.push_back(c);
        }
    }

    return results;
}

std::optional<std::shared_ptr<Component>> GameObject::GetComponentByName(const std::string& componentName) {
    for(auto& c : components) {
        if(c->name == componentName ) {
            return c;
        }
    }
    return std::nullopt;
}

std::vector<std::shared_ptr<Component>> GameObject::GetComponents() const {
    return components;
}

std::vector<std::shared_ptr<GameObject>> GameObject::GetChildren() const {
    return children;
}

void GameObject::AddChildren(std::shared_ptr<GameObject> obj) {
    children.push_back(std::move(obj));
}

std::optional<std::shared_ptr<GameObject>> GameObject::FindChild(const std::string& objectName) const {

    for(auto& c : children) {
        if(c->name == objectName ) {
            return c;
        }
    }

    return std::nullopt;
}

void GameObject::RemoveDeadPointers() {
    components.erase(
        std::remove_if( components.begin(), components.end(),
        [](auto &c){
                return c == nullptr;
            } ),
        components.end()
    );

    children.erase(
    std::remove_if( children.begin(), children.end(),
        [](auto &c){
            return c == nullptr;
        } ),
    children.end()
    );
}


