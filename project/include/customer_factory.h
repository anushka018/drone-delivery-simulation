/**
 * @file customer_factory.h
 * @author Audrey Kelly
 */
#ifndef CUSTOMER_FACTORY_H
#define CUSTOMER_FACTORY_H

#include <EntityProject/entity_factory.h>
#include "entity_base.h"
#include "json_helper.h"
#include "customer.h"

namespace csci3081 {
/**
 * @brief The Customer Factory class is used to create new customers for the delivery simulation. 
 * 
 */
class CustomerFactory : public IEntityFactory {
 public:
    /**
     * @brief Construct a new Customer Factory
     * 
     */
    CustomerFactory();
    /**
     * @brief Create a new Customer Entity from picojson object
     * 
     * @param[in] picsojson object val for customer creation
     * @return IEntity* pointer to new Customer entity
     */
    IEntity* CreateEntity(const picojson::object& val) override;
};

}   // namespace csci3081

#endif  // CUSTOMER_FACTORY_H
