/**
 * @file robot_factory.h
 * @author Audrey Kelly
 */
#ifndef ROBOT_FACTORY_H
#define ROBOT_FACTORY_H

#include <EntityProject/entity_factory.h>
#include "entity_base.h"
#include "json_helper.h"
#include "robot.h"

namespace csci3081 {
/**
 * @brief The Robot Factory class is used to create new robots for the delivery simulation. 
 * 
 */
class RobotFactory : public IEntityFactory {
 public:
    /**
     * @brief Construct a new robot Factory object
     * 
     */
    RobotFactory();
    /**
     * @brief Create a new robot from picojson object
     * 
     * @param[in] picsojson object val for the robot's creation
     * @return IEntity* pointer to new robot entity
     */
    IEntity* CreateEntity(const picojson::object& val) override;
};

}   // namespace csci3081

#endif  // ROBOT_FACTORY_H