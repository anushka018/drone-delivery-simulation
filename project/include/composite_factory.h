/**
 * @file composite_factory.h
 * @author Audrey Kelly
 */
#ifndef COMPOSITE_FACTORY_H
#define COMPOSITE_FACTORY_H

#include <EntityProject/facade/delivery_system.h>
#include <EntityProject/entity.h>
#include <vector>
#include "drone_factory.h"
#include "customer_factory.h"
#include "package_factory.h"
#include "robot_factory.h"

namespace csci3081 {
/**
 * @brief The Composite Factory class is used to create all types of entities in the simulation.
 * 
 * @details The class contains a list of all types of entity factories and iterates through them 
 * using the CreateEntity() method to generate new entities for the delivery simulation.  
 * 
 */
class CompositeFactory : public IEntityFactory {
 public:
    /**
     * @brief Construct a new Composite Factory
     * 
     */
    CompositeFactory();
    /**
     * @brief Create an entity for the simulation using a picojson object
     * 
     * @param[in] val: picsojson object for entity creation
     * @return IEntity* 
     */
    IEntity* CreateEntity(const picojson::object& val) override;
    /**
     * @brief Add factory to the class's current list of factories
     * 
     * @param[in] factory: an entity factory to add to Composite Factory's list
     */
    void AddFactory(IEntityFactory* factory);
    /**
     * @brief Destroy the Composite Factory
     * 
     */
    ~CompositeFactory();

 private:
    std::vector<IEntityFactory*> factories;
};

}   // namespace csci3081

#endif  // COMPOSITE_FACTORY_H
