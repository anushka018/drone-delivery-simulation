/**
 * @file drone_factory.h
 * @author Audrey Kelly
 */
#ifndef DRONE_FACTORY_H
#define DRONE_FACTORY_H

#include <EntityProject/entity_factory.h>
#include "entity_base.h"
#include "json_helper.h"
#include "drone.h"

namespace csci3081 {
/**
 * @brief The Drone Factory class is used to create new drones for the delivery simulation. 
 * 
 */
class DroneFactory : public IEntityFactory {
 public:
    /**
     * @brief Construct a new Drone Factory object
     * 
     */
    DroneFactory();
    /**
     * @brief Create a new Drone from picojson object
     * 
     * @param[in] picsojson object val for drone creation
     * @return IEntity* pointer to new Drone entity
     */
    IEntity* CreateEntity(const picojson::object& val) override;
};

}   // namespace csci3081

#endif  // DRONE_FACTORY_H
