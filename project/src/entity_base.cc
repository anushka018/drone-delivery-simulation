/**
 * @file entity_base.cc
 * @author Audrey Kelly
 */
#include "entity_base.h"

namespace csci3081 {

    int EntityBase::entityCount = 0;

    EntityBase::EntityBase() {};

    EntityBase::EntityBase(const picojson::object& details, std::vector<float> position,
                            std::vector<float> direction, const std::string name,
                                float speed, float radius) {
        details_ = details;                    
        posVector = position;
        dirVector = direction;
        this->position_ = Vector3D(position);
        this->direction_ = Vector3D(direction);

        version = 0;
        ID = ++entityCount;
        name_ = name;
        speed_  = speed;
        radius_ = radius;
        isDynamic = false;
    }

    int EntityBase::GetEntityCount() {
        return entityCount;
    }

    int EntityBase::GetId() const {
        return ID;
    }

    const std::string& EntityBase::GetName() {
        return name_;
    }

    const std::string& EntityBase::GetType() {
        return type_;
    }

    const std::vector<float>& EntityBase::GetPosition() const {
        return posVector;
    }

    void EntityBase::SetPosition(const std::vector<float>& newPosition) {
        position_ = Vector3D(newPosition);
        posVector = newPosition;
    }

    void EntityBase::SetDirection(const std::vector<float>& newDirection) {
        direction_ = Vector3D(newDirection);
        dirVector = newDirection;
    }

    float EntityBase::GetSpeed() {
        return speed_;
    }

    void EntityBase::SetSpeed(float speed) {
        speed_ = speed;
    }

    const std::vector<float>& EntityBase::GetDirection() const {
        return dirVector;
    }

    float EntityBase::GetRadius() const {
        return radius_;
    }

    int EntityBase::GetVersion() const {
        return version;
    }

    const picojson::object& EntityBase::GetDetails() {
        return details_;
    }

    bool EntityBase::IsDynamic() const {
        if (speed_ > 0 && isDynamic) {
            return true;
        }
        return false;
    }
    void EntityBase::Update(float dt) {};
    
}   // namespace csci3081
