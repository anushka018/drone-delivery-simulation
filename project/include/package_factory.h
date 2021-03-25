/**
 * @file drone_factory.h
 * @author Audrey Kelly
 */
#ifndef PACKAGE_FACTORY_H
#define PACKAGE_FACTORY_H

#include <EntityProject/entity_factory.h>
#include "entity_base.h"
#include "json_helper.h"
#include "package.h"

namespace csci3081 {
/**
 * @brief The Package Factory class is used to create new packages for the delivery simulation. 
 * 
 */
class PackageFactory : public IEntityFactory {
 public:
    /**
     * @brief Construct a new Package Factory object
     * 
     */
    PackageFactory();
    /**
     * @brief Create a new Package Entity from picojson object
     * 
     * @param[in] val: picsojson object for package creation
     * @return IEntity* pointer to new Package entity
     */
    IEntity* CreateEntity(const picojson::object& val) override;
};

}   // namespace csci3081

#endif  // PACKAGE_FACTORY_H